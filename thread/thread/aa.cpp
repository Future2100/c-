//
//  aa.cpp
//  thread
//
//  Created by future on 16/3/15.
//  Copyright © 2016年 future. All rights reserved.
//

#include <stdio.h>



#include <queue> /* For std::queue and std::deque. */
#include <process.h> /* For ::_beginthreadex. */
#include <windows.h> /* For Windows APIs. */
#include <atomic> /* For std::atomic_size_t. */



// The runnable task interface.
class Runnable {
public:
    virtual void Run() = 0;
    virtual ~Runnable() {}
};

// The executor interface.
class Executor {
public:
    virtual void Execute(Runnable *task) = 0;
};

// Base class for any concrete thread service.
class ThreadService {
protected:
    // Virtual destructor.
    virtual ~ThreadService() {}
    
    // The main logic of the service, which should be overridden in subclasses.
    virtual void Run() = 0;
    
    // Create a windows thread.
    void StartThread() {
        // Close the thread handle to release the resource.
        ::CloseHandle(
                      (::HANDLE)::_beginthreadex(
                                                 NULL, 0u, ThreadInterface, this, 0u, NULL));
    }
    
private:
    // The entry function of the thread.
    static unsigned __stdcall ThreadInterface(void *argv) {
        ThreadService *thread_service = (ThreadService*)argv;
        thread_service->Run();
        delete thread_service;
        return 0;
    }
};

// A thread-safe proxy, which cannot be inherited.
template <typename ProxyType>
class AccessProxy final {
public:
    // Initialize the number of users with 1, set the proxy object.
    inline AccessProxy(ProxyType *proxy_object)
    : user_count_(1u), proxy_object_(proxy_object)
    { ::InitializeCriticalSection(&critical_section_); }
    
    // Add a user.
    inline void AddUser() { ++user_count_; }
    
    // Remove a user.
    inline void RemoveUser() { if (--user_count_ == 0u) delete this; }
    
    // Access to the critical section.
    inline void Access() { ::EnterCriticalSection(&critical_section_); }
    
    // Exit from the critical section.
    inline void Exit() { ::LeaveCriticalSection(&critical_section_); }
    
    // If the proxy object is valid, then access the critical section.
    // Function returns whether accessed successfully.
    bool TryAccess() {
        bool result;
        Access();
        if (proxy_object_ == NULL) {
            result = false;
            Exit();
        } else {
            result = true;
        }
        return result;
    }
    
    // Set the proxy object invalid.
    inline void SetInvalid() {
        proxy_object_ = NULL;
        RemoveUser();
    }
    
    inline ProxyType *get_proxy_object() { return proxy_object_; }
    
private:
    // Release system resources.
    inline ~AccessProxy() {
        ::DeleteCriticalSection(&critical_section_);
    }
    
    // An atomic counter, which indicates the number of users.
    std::atomic_size_t user_count_;
    ProxyType *proxy_object_;
    ::CRITICAL_SECTION critical_section_; // The critical section.
};

// Implementation of a common thread pool,
// inheriting from Executor interface, which cannot be inherited.
class ThreadPoolExecutor : public Executor {
private:
    // Worker thread of the thread pool, cannot be inherited.
    class Worker final : public ThreadService {
    public:
        // Worker threads should be assigned the first task.
        // Within the construction process of a worker thread,
        // the thread pool should promise to be alive.
        Worker(AccessProxy<ThreadPoolExecutor> *proxy,
               ::DWORD keep_alive_time,
               Runnable *task)
        : event_(::CreateEvent(NULL, FALSE, FALSE, NULL)),
        task_(task),
        proxy_(proxy),
        KEEP_ALIVE_TIME(keep_alive_time) {
            StartThread();
        }
        
        // The destruction process of a worker thread involves the destruction of
        // the kernel objects and removal from the proxy.
        ~Worker() {
            ::CloseHandle(event_);
            proxy_->RemoveUser();
        }
        
        // Thread pool assigns a task to a worker thread at dormant state.
        // First assigns the task, then activate the worker. Sequence counts.
        void AssignTask(Runnable *task) {
            task_ = task;
            ::SetEvent(event_);
        }
        
    private:
        bool Process() {
            // After executing the task, try to apply a new task from the thread pool.
            // This can reduce the overhead of switching contexts,
            // when tasks are more than workers.
            for (;;) {
                task_->Run();
                delete task_;
                // Try to access to the proxy.
                // If the proxy is invalid, the worker should exit.
                if (!(proxy_->TryAccess())) return false;
                task_ = proxy_->get_proxy_object()->TryFetchTask(this);
                proxy_->Exit();
                if (task_ == NULL) return true;
            }
        }
        
        bool Await() {
            // Wait for the signal for at most KEEP_ALIVE_TIME units.
            while (::WaitForSingleObject(event_, KEEP_ALIVE_TIME) != 0) {
                // Try to access to the proxy.
                // If the proxy is invalid, the worker should exit.
                if (!(proxy_->TryAccess())) return false;
                // After accessing to the proxy, check the "event_" signal again
                // to prevent the following circumstances:
                //
                // Providing the task is assigned after the first time waiting
                // for the task timeout and before the deregistration form thread pool,
                // the task will be leaked and never be done.
                if (::WaitForSingleObject(event_, 0u) != 0) {
                    // The operation may not kill the worker itself.
                    proxy_->get_proxy_object()->TryKillOneWorker();
                    proxy_->Exit();
                } else {
                    proxy_->Exit();
                    break;
                }
            }
            return task_ != NULL;
        }
        
        // Operation logic of working thread.
        void Run() override {
            for (;;) {
                if (!Process()) break;
                if (!Await()) break;
            }
        }
        
        const ::HANDLE event_; // A windows HANDLE, indicates a system event.
        Runnable *task_; // The task to be done.
        AccessProxy<ThreadPoolExecutor> * const proxy_; // The thread pool proxy.
        const ::DWORD KEEP_ALIVE_TIME; // Wait timeout.
    };
    
public:
    // Create a thread pool with necessary parameters.
    ThreadPoolExecutor(std::size_t core_pool_size, // Core thread pool size.
                       std::size_t maximum_pool_size, // Maximum thread pool size.
                       ::DWORD keep_alive_time) // Keep alive time.
    : CORE_POOL_SIZE(core_pool_size),
    MAXIMUM_POOL_SIZE(maximum_pool_size),
    KEEP_ALIVE_TIME(keep_alive_time),
    worker_count_(0u),
    proxy_(new AccessProxy<ThreadPoolExecutor>(this)) {}
    
    // The destruction of the thread pool. First kill all waiting threads,
    // and then set proxy invalid.
    ~ThreadPoolExecutor() {
        proxy_->Access();
        while (!free_workers_.empty()) {
            free_workers_.back()->AssignTask(NULL);
            free_workers_.pop_back();
        }
        proxy_->SetInvalid();
        proxy_->Exit();
        proxy_->RemoveUser();
    }
    
    // Try to kill a worker thread if there are more than CORE_POOL_SIZE workers.
    void TryKillOneWorker() {
        proxy_->Access();
        if (CORE_POOL_SIZE < worker_count_) {
            free_workers_.back()->AssignTask(NULL);
            free_workers_.pop_back();
            --worker_count_;
        }
        proxy_->Exit();
    }
    
    // The user submit tasks with this interface,
    // If there are available threads, reuse one,
    // or create a new thread otherwise.
    void Execute(Runnable *task) override {
        proxy_->Access();
        if (free_workers_.empty()) {
            if (worker_count_ <= MAXIMUM_POOL_SIZE) {
                ++worker_count_;
                proxy_->AddUser();
                new Worker(proxy_, KEEP_ALIVE_TIME, task);
            } else {
                tasks_.push(task);
            }
        } else {
            free_workers_.front()->AssignTask(task);
            free_workers_.pop_front();
        }
        proxy_->Exit();
    }
    
    // Worker threads try to apply for tasks via this interface.
    // This operation is NOT thread-safe.
    // Worker threads should access to the proxy before performing the operation.
    Runnable* TryFetchTask(Worker *fetcher) {
        if (tasks_.empty()) {
            free_workers_.push_front(fetcher);
            return NULL;
        }
        Runnable *result = tasks_.front();
        tasks_.pop();
        return result;
    }
    
private:
    const std::size_t CORE_POOL_SIZE;
    const std::size_t MAXIMUM_POOL_SIZE;
    const ::DWORD KEEP_ALIVE_TIME;
    std::size_t worker_count_; // Count for workers.
    
    AccessProxy<ThreadPoolExecutor> * const proxy_;
    std::deque<Worker*> free_workers_; // Container for worker threads.
    std::queue<Runnable*> tasks_; // Container for tasks.
};
