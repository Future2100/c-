//
//  main.cpp
//  58
//
//  Created by future on 16/3/2.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>



typedef union{
    int i;
    unsigned char ch[2];
}   Student;


int main(int argc,char *argv[]){
    Student student;
    student.i=0x1420;
    printf("%d %d",student.ch[0],student.ch[1]);
    return 0;
}
