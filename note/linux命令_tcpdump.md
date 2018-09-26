# tcpdump 命令


* 获取一个到指定端口的数据
    ```
    tcpdump -n -i eth0 port 23
    ```

* 观察重复建立连接的情况
    
    ```
    tcpdump -n -i eth0 port 23
    ```

    如果连接一个不存在的ip的23端口，那么就会出现重复建立连接的情况。每一条输出的间隔分别是1s , 2s , 4s , 8s, 16s 等。

    也就是向一个不存在的ip发送syn，这样对方就不会回复它。这样他就会不停的重发。
    ```
    10:23:23.323597 IP 100.64.150.81.49416 > 192.168.3.87.23: Flags [S], seq 2826371792, win 29200, options [mss 1460,sackOK,TS val 425996656 ecr 0,nop,wscale 7], length 0

    10:23:24.321698 IP 100.64.150.81.49416 > 192.168.3.87.23: Flags [S], seq 2826371792, win 29200, options [mss 1460,sackOK,TS val 425996906 ecr 0,nop,wscale 7], length 0

    10:23:26.325704 IP 100.64.150.81.49416 > 192.168.3.87.23: Flags [S], seq 2826371792, win 29200, options [mss 1460,sackOK,TS val 425997407 ecr 0,nop,wscale 7], length 0

    10:23:30.329689 IP 100.64.150.81.49416 > 192.168.3.87.23: Flags [S], seq 2826371792, win 29200, options [mss 1460,sackOK,TS val 425998408 ecr 0,nop,wscale 7], length 0

    10:23:38.345710 IP 100.64.150.81.49416 > 192.168.3.87.23: Flags [S], seq 2826371792, win 29200, options [mss 1460,sackOK,TS val 426000412 ecr 0,nop,wscale 7], length 0

    10:23:54.361731 IP 100.64.150.81.49416 > 192.168.3.87.23: Flags [S], seq 2826371792, win 29200, options [mss 1460,sackOK,TS val 426004416 ecr 0,nop,wscale 7], length 0
    ```

    ```
    Flags [S] : 表示 SYN 
    seq 2826371792 :  表示发送的序号是 2826371792 
    win 29200      ： 接受窗口是 29200
    length 0       ： tcp消息的长度是0 （因为是连接连接的报文，所以没有长度）

    options  [mss 1460,sackOK,TS val 425997407 ecr 0,nop,wscale 7]
    表示tcp头部的选项字段
    mss 表示 来协商最大报文长度 （max segment size），一般等于 mtu-40
    wscale 表示 窗口扩大的因子
    sackOK 表示选择性ack，如果tcp报文丢失，则tcp模块会重传后面的所有报文。如果带上sack，就只会重传丢失的这个报文。
    TS val 426004416  表示时间戳
    ```

* 观察tcp建立连接的情况

    tcpdump 监听1234 端口

    ```
    sudo tcpdump -n -i lo port 1234
    tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
    listening on lo, link-type EN10MB (Ethernet), capture size 262144 bytes

    10:48:56.195211 IP 127.0.0.1.36702 > 127.0.0.1.1234: Flags [S], seq 909028172, win 43690, options [mss 65495,sackOK,TS val 426379874 ecr 0,nop,wscale 7], length 0

    10:48:56.195230 IP 127.0.0.1.1234 > 127.0.0.1.36702: Flags [S.], seq 2567911667, ack 909028173, win 43690, options [mss 65495,sackOK,TS val 426379874 ecr 426379874,nop,wscale 7], length 0

    10:48:56.195248 IP 127.0.0.1.36702 > 127.0.0.1.1234: Flags [.], ack 1, win 342, options [nop,nop,TS val 426379874 ecr 426379874], length 0

    10:49:09.528631 IP 127.0.0.1.36702 > 127.0.0.1.1234: Flags [F.], seq 1, ack 1, win 342, options [nop,nop,TS val 426383207 ecr 426379874], length 0

    10:49:09.528740 IP 127.0.0.1.1234 > 127.0.0.1.36702: Flags [F.], seq 1, ack 2, win 342, options [nop,nop,TS val 426383207 ecr 426383207], length 0

    10:49:09.528774 IP 127.0.0.1.36702 > 127.0.0.1.1234: Flags [.], ack 2, win 342, options [nop,nop,TS val 426383207 ecr 426383207], length 0
    ```

    nc命令监听1234端口
    ```
    nc -l 1234
    ```

    telnet 建立连接
    ```
    telnet 127.0.0.1 1234
    Trying 127.0.0.1...
    Connected to 127.0.0.1.
    Escape character is '^]'.
    ^]

    telnet> quit
    Connection closed.
    ```


* 正常tcp的过程

    nc 监听1234端口
    ```
    nc -l 1234
    hello world   #收到hello world
    yes           #发送yes
    ```

    ```
    nc 127.0.0.1 1234
    hello world   #主动发送hello world
    yes           #收到yes
    ```

    ```
    # 建立连接
    11:11:47.081879 IP 127.0.0.1.36746 > 127.0.0.1.1234: Flags [S], seq 22427316, win 43690, options [mss 65495,sackOK,TS val 426722596 ecr 0,nop,wscale 7], length 0

    11:11:47.081902 IP 127.0.0.1.1234 > 127.0.0.1.36746: Flags [S.], seq 1998354527, ack 22427317, win 43690, options [mss 65495,sackOK,TS val 426722596 ecr 426722596,nop,wscale 7], length 0

    11:11:47.081924 IP 127.0.0.1.36746 > 127.0.0.1.1234: Flags [.], ack 1, win 342, options [nop,nop,TS val 426722596 ecr 426722596], length 0

    # 发送消息
    11:11:55.248233 IP 127.0.0.1.36746 > 127.0.0.1.1234: Flags [P.], seq 1:13, ack 1, win 342, options [nop,nop,TS val 426724637 ecr 426722596], length 12

    11:11:55.248252 IP 127.0.0.1.1234 > 127.0.0.1.36746: Flags [.], ack 13, win 342, options [nop,nop,TS val 426724637 ecr 426724637], length 0

    11:12:03.575472 IP 127.0.0.1.1234 > 127.0.0.1.36746: Flags [P.], seq 1:5, ack 13, win 342, options [nop,nop,TS val 426726719 ecr 426724637], length 4

    11:12:03.575490 IP 127.0.0.1.36746 > 127.0.0.1.1234: Flags [.], ack 5, win 342, options [nop,nop,TS val 426726719 ecr 426726719], length 0
    
    # 断开
    11:23:54.735945 IP 127.0.0.1.36746 > 127.0.0.1.1234: Flags [F.], seq 13, ack 5, win 342, options [nop,nop,TS val 426904509 ecr 426726719], length 0

    11:23:54.736041 IP 127.0.0.1.1234 > 127.0.0.1.36746: Flags [F.], seq 5, ack 14, win 342, options [nop,nop,TS val 426904509 ecr 426904509], length 0

    11:23:54.736087 IP 127.0.0.1.36746 > 127.0.0.1.1234: Flags [.], ack 6, win 342, options [nop,nop,TS val 426904509 ecr 426904509], length 0
    ```


* 观察发送rst包

    如果向一个没有监听的端口，建立tcp连接
    ```
    nc 127.0.0.1 54321
    ```
    
    ```
    sudo tcpdump -n -i lo port 54321

    19:18:01.063037 IP 127.0.0.1.43590 > 127.0.0.1.54321: Flags [S], seq 1145802608, win 43690, options [mss 65495,sackOK,TS val 434016091 ecr 0,nop,wscale 7], length 0
    
    19:18:01.063060 IP 127.0.0.1.54321 > 127.0.0.1.43590: Flags [R.], seq 0, ack 1145802609, win 0, length 0
    ```

    查看输出的结果，客户端发送了一个syn的请求，但是对方回复了一个rst。


    另外，一个收到rst的情况是：

    如果tcp连接处于一个半连接的状态，这个时候，如果其中的一方 向里面写的时候，就会收到一个rst的包。


* 观察建立连接之后，超时重传的情况

    使用iperf 命令
    在一台机器A上面使用iperf监听5001端口，在另外一个机器B上面，使用telnet建立连接。
    然后，在机器B上面发送消息之后，然后断开网络（断开网线）。
    这样机器A的ack机器B就会收不到，这样机器B就会不停的重发。


    这个重传的时间分别是 ： 
    
    0.2s 

    0.4s
    
    0.8s
    
    1.6s
    
    3.2s
