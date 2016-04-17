//
//  main.cpp
//  pcap
//
//  Created by future on 16/4/10.
//  Copyright © 2016年 future. All rights reserved.
//



/*
 * sniffex.c
 *
 * Sniffer example of TCP/IP packet capture using libpcap.
 *
 * Version 0.1.1 (2005-07-05)
 * Copyright (c) 2005 The Tcpdump Group
 *
 * This software is intended to be used as a practical example and
 * demonstration of the libpcap library; available at:
 * http://www.tcpdump.org/
 *
 ****************************************************************************
 *
 * ..... 字数太长了，此处版权信息就省了
 *
 ****************************************************************************
 *
 * Example compiler command-line for GCC:
 *   gcc -Wall -o sniffex sniffex.c -lpcap
 *
 ****************************************************************************
 *
 * Code Comments
 *
 * This section contains additional information and explanations regarding
 * comments in the source code. It serves as documentaion and rationale
 * for why the code is written as it is without hindering readability, as it
 * might if it were placed along with the actual code inline. References in
 * the code appear as footnote notation (e.g. [1]).
 *
 * 1. Ethernet headers are always exactly 14 bytes, so we define this
 * explicitly with "#define". Since some compilers might pad structures to a
 * multiple of 4 bytes - some versions of GCC for ARM may do this -
 * "sizeof (struct sniff_ethernet)" isn't used.
 *
 * 2. Check the link-layer type of the device that's being opened to make
 * sure it's Ethernet, since that's all we handle in this example. Other
 * link-layer types may have different length headers (see [1]).
 *
 * 3. This is the filter expression that tells libpcap which packets we're
 * interested in (i.e. which packets to capture). Since this source example
 * focuses on IP and TCP, we use the expression "ip", so we know we'll only
 * encounter IP packets. The capture filter syntax, along with some
 * examples, is documented in the tcpdump man page under "expression."
 * Below are a few simple examples:
 *
 * Expression                        Description
 * ----------                        -----------
 * ip                                        Capture all IP packets.
 * tcp                                        Capture only TCP packets.
 * tcp port 80                        Capture only TCP packets with a port equal to 80.
 * ip host 10.1.2.3                Capture all IP packets to or from host 10.1.2.3.
 *
 ****************************************************************************
 *
 */


#include "sniffer_header.h"



/*
 * app name/banner
 */
int main(int argc, char **argv)
{
    
    const char *dev = NULL;                              /* 捕获设备的名称 | capture device name */
    char errbuf[PCAP_ERRBUF_SIZE];                /* 错误的缓冲区   | error buffer */
    pcap_t *handle;                                                /* 数据包捕获句柄 | packet capture handle */
    
    char filter_exp[] = " ";                        /* 过滤表达示          | filter expression [3] */
    struct bpf_program fp;                                /* 编译过滤表达示 | compiled filter program (expression) */
    bpf_u_int32 mask;                                        /* 子网掩码                  | subnet mask */
    bpf_u_int32 net;                                        /* IP 地址                  | ip */
    
    /* 检查来自命令行参数需要捕获设备的名称
     check for capture device name on command-line */
    if (argc == 2) {
        dev = argv[1];
    }
    else if (argc > 2) {
        fprintf(stderr, "error: unrecognized command-line options\n\n");
        exit(EXIT_FAILURE);
    }
    else {
        /* 如果命令行参数没有指定, 则自动找到一个设备
         find a capture device if not specified on command-line */
        dev = pcap_lookupdev(errbuf);
        if (dev == NULL) {
            fprintf(stderr, "Couldn't find default device: %s\n",
                    errbuf);
            exit(EXIT_FAILURE);
        }
    }
    /* 获得捕获设备的网络号和掩码
     get network number and mask associated with capture device */
    if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
        fprintf(stderr, "Couldn't get netmask for device %s: %s\n",
                dev, errbuf);
        net = 0;
        mask = 0;
    }
    
    /* 显示捕获设备信息
     print capture info */
    printf("Device: %s\n", dev);
    printf("Filter expression: %s\n", filter_exp);
    
    /* 打开捕获设备
     @1        捕获的设备
     @2        每次捕获数据的最大长度
     @3        1 启用混杂模式
     @4        捕获时间, 单位ms
     @5        错误缓冲区
     open capture device */
    handle = pcap_open_live(dev, SNAP_LEN, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
        exit(EXIT_FAILURE);
    }
    
    /*        pcap_datalink();
     返回数据链路层类型，例如DLT_EN10MB;
     
     确保我们对以太网设备捕获
     make sure we're capturing on an Ethernet device [2] */
    if (pcap_datalink(handle) != DLT_EN10MB) {
        fprintf(stderr, "%s is not an Ethernet\n", dev);
        exit(EXIT_FAILURE);
    }
    
    /* 编译过滤表达式
     compile the filter expression */
    if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
        fprintf(stderr, "Couldn't parse filter %s: %s\n",
                filter_exp, pcap_geterr(handle));
        exit(EXIT_FAILURE);
    }
    
    /* 应用过滤规则
     apply the compiled filter */
    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Couldn't install filter %s: %s\n",
                filter_exp, pcap_geterr(handle));
        exit(EXIT_FAILURE);
    }
    
    /* 设置回高函数并开始捕获包
     now we can set our callback function */
    pcap_loop(handle, 0, got_packet, NULL);
    
    /* cleanup */
    pcap_freecode(&fp);
    pcap_close(handle);
    
    printf("\nCapture complete.\n");
    
    return 0;
}