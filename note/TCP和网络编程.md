# TCP/IP 和 网络编程

## 目录

* [tcp/ip原理](#tcp/ip原理)

    * tcp的状态转移图

    * tcp在建立连接和断开连接的示意图

    * time_wait

    * 带外数据

    * tcp 接收和发送的内核的缓冲区

    * rst包什么时候发送

* [基本的api使用](#基本的api使用)

    * listen 函数

    * close 和 shutdown 的区别

    * sockaddr 和 sockaddr_in 的区别

* [网络编程模型](#网络编程模型)

    * 同步io 和 异步 io

    * reactor 和 proactor 的区别

* [I/O复用](#I/O复用)

* [惊群问题](#惊群问题)

* [TCP内核缓冲区大小](#TCP内核缓冲区大小)

---

## tcp/ip原理

* rst 包

    使用tcpdump去抓一个telnet向一个没有监听的端口建立tcp连接。
    ```
    zz@ubuntu:~$ telnet 127.0.0.1 9999
    Trying 127.0.0.1...
    telnet: Unable to connect to remote host: Connection refused
    ```
    用tcpdump抓包分析。可以发现，首先telnet向9999的端口发送了一个 FLAG 是[S]的 syn的包。然后，对方回应了一个FLAG 是[R]的rest的包。
    ```
    zz@ubuntu:~$ sudo tcpdump -nt -i lo port 9999
    tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
    listening on lo, link-type EN10MB (Ethernet), capture size 262144 bytes
    
    IP 127.0.0.1.51254 > 127.0.0.1.9999: Flags [S], seq 1916550518, win 43690, options [mss 65495,sackOK,TS val 586810 ecr 0,nop,wscale 7], length 0
    IP 127.0.0.1.9999 > 127.0.0.1.51254: Flags [R.], seq 0, ack 1916550519, win 0, length 0
    ```

## 基本的api使用

* listen 

    listen 函数的第二个参数是等待队列的长度 ， （这个后面在写）

* close 和 shutdown 的区别

    http://senlinzhan.github.io/2016/09/15/%E5%AE%89%E5%85%A8%E5%85%B3%E9%97%ADTCP%E8%BF%9E%E6%8E%A5/


* sockaddr 和 sockaddr_in 的区别

    ```
    include <netinet/in.h>  
  
    struct sockaddr 
    {  
        unsigned short    sa_family;        // 2 bytes address family, AF_xxx  
        char              sa_data[14];      // 14 bytes of protocol address  
    };  
    
    // IPv4 AF_INET sockets:  
    struct sockaddr_in 
    {  
        short            sin_family;       // 2 bytes e.g. AF_INET, AF_INET6  
        unsigned short   sin_port;         // 2 bytes e.g. htons(3490)  
        struct in_addr   sin_addr;         // 4 bytes see struct in_addr, below  
        char             sin_zero[8];      // 8 bytes zero this if you want to  
    };  
    ```

    这两个结构体一样大，都是16个字节，而且都有family属性，不同的是：
    
    sockaddr用其余14个字节来表示sa_data，而sockaddr_in把14个字节拆分成sin_port, sin_addr和sin_zero分别表示端口、ip地址。sin_zero用来填充字节使sockaddr_in和sockaddr保持一样大小。


    用法 : 
    ```
    int sockfd;  
    struct sockaddr_in servaddr; 
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);  
    
    /* 填充struct sockaddr_in */  
    bzero(&servaddr, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(SERV_PORT);  
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);  
    
    /* 强制转换成struct sockaddr */  
    connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));  
    ```

## 网络编程模型


## I/O复用

select，poll，epoll 虽然可以同时监听多个文件描述符，但是它本身是阻塞的。（因为如果没有fd就绪，那么程序会一直卡在epoll的这个地方）并且，如果多个文件描述符同时就绪，如果不采取额外的措施，那么程序就会顺序依次处理其中的每一个文件符。如果要实现并发，就要使用多进程或多线程的方式去处理。

* select / poll / epoll 的原理和区别

* select / poll / epoll 的api

* epoll的et 和 lt模式的区别

    举一个例子，如果client发送了10个字节的消息，epoll第一次读取了8个字节，那么下一次epoll_wait的时候，会再一次读到这个fd吗？

    如果是et模式，这个fd还是可读的；如果是lt，这个fd就是不可读的了。


## 惊群问题

* 什么是惊群问题

    这个时候有多个进程同时在listen一个端口，当这个事件发生时，这些进程被同时唤醒，就是“惊群”。但最终只可能有一个进程/线程对该事件进行处理，其他进程/线程会在失败后重新休眠，这种性能浪费就是惊群。

* 举个例子 

    prefork 出4个子进程，在监听同一个端口，然后如果有一个事件到来，那么就会产生一个惊群的想象。4个进程都被唤醒，但是只有一个会accept成功。

    ```
    #include <stdio.h>
    #include <unistd.h>
    #include <sys/types.h>  
    #include <sys/socket.h>  
    #include <netinet/in.h>  
    #include <arpa/inet.h>  
    #include <assert.h>  
    #include <sys/wait.h>
    #include <string.h>
    #include <errno.h>

    #define IP   "127.0.0.1"
    #define PORT  8888
    #define WORKER 4

    int worker(int listenfd, int i)
    {
        while (1) {
            printf("I am worker %d, begin to accept connection.\n", i);
            struct sockaddr_in client_addr;  
            socklen_t client_addrlen = sizeof( client_addr );  
            int connfd = accept( listenfd, ( struct sockaddr* )&client_addr, &client_addrlen );  
            if (connfd != -1) {
                printf("worker %d accept a connection success.\t", i);
                printf("ip :%s\t",inet_ntoa(client_addr.sin_addr));
                printf("port: %d \n",client_addr.sin_port);
            } else {
                printf("worker %d accept a connection failed,error:%s", i, strerror(errno));
    　　　　　　　　 close(connfd);
            }
        }
        return 0;
    }

    int main()
    {
        int i = 0;
        struct sockaddr_in address;  
        bzero(&address, sizeof(address));  
        address.sin_family = AF_INET;  
        inet_pton( AF_INET, IP, &address.sin_addr);  
        address.sin_port = htons(PORT);  
        int listenfd = socket(PF_INET, SOCK_STREAM, 0);  
        assert(listenfd >= 0);  

        int ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));  
        assert(ret != -1);  

        ret = listen(listenfd, 5);  
        assert(ret != -1);  

        for (i = 0; i < WORKER; i++) {
            printf("Create worker %d\n", i+1);
            pid_t pid = fork();
            /*child  process */
            if (pid == 0) {
                worker(listenfd, i);
            }

            if (pid < 0) {
                printf("fork error");
            }
        }

        /*wait child process*/
        int status;
        wait(&status);
        return 0;
    }
    ```

    ```
    nc 127.0.0.1 8888
    ```

    按照“惊群"现象，期望结果应该是4个子进程都会accpet到请求，其中只有一个成功，另外三个失败的情况。而实际的结果显示，父进程开始创建4个子进程，每个子进程开始等待accept连接。当telnet连接来的时候，只有worker2 子进程accpet到请求，而其他的三个进程并没有接收到请求。

    这是什么原因呢？难道惊群现象是假的吗？于是赶紧google查一下，惊群到底是怎么出现的。

    其实在Linux2.6版本以后，内核内核已经解决了accept()函数的“惊群”问题，大概的处理方式就是，当内核接收到一个客户连接后，只会唤醒等待队列上的第一个进程或线程。所以，如果服务器采用accept阻塞调用方式，在最新的Linux系统上，已经没有“惊群”的问题了。

    但是，对于实际工程中常见的服务器程序，大都使用select、poll或epoll机制，此时，服务器不是阻塞在accept，而是阻塞在select、poll或epoll_wait，这种情况下的“惊群”仍然需要考虑。接下来以epoll为例分析：

    使用epoll非阻塞实现代码如下所示：


    ```
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <sys/epoll.h>
    #include <netdb.h>
    #include <string.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <sys/wait.h>
    #include <unistd.h>

    #define IP   "127.0.0.1"
    #define PORT  8888
    #define PROCESS_NUM 4
    #define MAXEVENTS 64

    static int create_and_bind ()
    {
        int fd = socket(PF_INET, SOCK_STREAM, 0);
        struct sockaddr_in serveraddr;
        serveraddr.sin_family = AF_INET;
        inet_pton( AF_INET, IP, &serveraddr.sin_addr);  
        serveraddr.sin_port = htons(PORT);
        bind(fd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
        return fd;
    }

    static int make_socket_non_blocking (int sfd)
    {
        int flags, s;
        flags = fcntl (sfd, F_GETFL, 0);
        if (flags == -1) {
            perror ("fcntl");
            return -1;
        }
        flags |= O_NONBLOCK;
        s = fcntl (sfd, F_SETFL, flags);
        if (s == -1) {
            perror ("fcntl");
            return -1;
        }
        return 0;
    }

    void worker(int sfd, int efd, struct epoll_event *events, int k) {
        /* The event loop */
        while (1) {
            int n, i;
            n = epoll_wait(efd, events, MAXEVENTS, -1);
            printf("worker  %d return from epoll_wait!\n", k);
            for (i = 0; i < n; i++) {
                if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events &EPOLLIN))) {
                    /* An error has occured on this fd, or the socket is not ready for reading (why were we notified then?) */
                    fprintf (stderr, "epoll error\n");
                    close (events[i].data.fd);
                    continue;
                } else if (sfd == events[i].data.fd) {
                    /* We have a notification on the listening socket, which means one or more incoming connections. */
                    struct sockaddr in_addr;
                    socklen_t in_len;
                    int infd;
                    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
                    in_len = sizeof in_addr;
                    infd = accept(sfd, &in_addr, &in_len);
                    if (infd == -1) {
                        printf("worker %d accept failed!\n", k);
                        break;
                    }
                    printf("worker %d accept successed!\n", k);
                    /* Make the incoming socket non-blocking and add it to the list of fds to monitor. */
                    close(infd); 
                }
            }
        }
    }

    int main (int argc, char *argv[])
    {
        int sfd, s;
        int efd;
        struct epoll_event event;
        struct epoll_event *events;
        sfd = create_and_bind();
        if (sfd == -1) {
            abort ();
        }
        s = make_socket_non_blocking (sfd);
        if (s == -1) {
            abort ();
        }
        s = listen(sfd, SOMAXCONN);
        if (s == -1) {
            perror ("listen");
            abort ();
        }
        efd = epoll_create(MAXEVENTS);
        if (efd == -1) {
            perror("epoll_create");
            abort();
        }
        event.data.fd = sfd;
        event.events = EPOLLIN;
        s = epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &event);
        if (s == -1) {
            perror("epoll_ctl");
            abort();
        }

        /* Buffer where events are returned */
        events = calloc(MAXEVENTS, sizeof event);
        int k;
        for(k = 0; k < PROCESS_NUM; k++) {
            printf("Create worker %d\n", k+1);
            int pid = fork();
            if(pid == 0) {
                worker(sfd, efd, events, k);
            }
        }
        int status;
        wait(&status);
        free (events);
        close (sfd);
        return EXIT_SUCCESS;
    }
    ```

    使用nc测试一下，依然不会出现惊群的问题。从结果看出，与上面是一样的，只有一个进程接收到连接，其他三个没有收到，说明没有发生惊群现象。这又是为什么呢？

    在早期的Linux版本中，内核对于阻塞在epoll_wait的进程，也是采用全部唤醒的机制，所以存在和accept相似的“惊群”问题。新版本的的解决方案也是只会唤醒等待队列上的第一个进程或线程，所以，新版本Linux 部分的解决了epoll的“惊群”问题。所谓部分的解决，意思就是：对于部分特殊场景，使用epoll机制，已经不存在“惊群”的问题了，但是对于大多数场景，epoll机制仍然存在“惊群”。


    epoll存在惊群的场景如下：在worker保持工作的状态下，都会被唤醒，例如在epoll_wait后调用sleep一次。改写woker函数如下：

    ```
    void worker(int sfd, int efd, struct epoll_event *events, int k) {
    /* The event loop */
    while (1) {
        int n, i;
        n = epoll_wait(efd, events, MAXEVENTS, -1);
        /*keep running*/
        sleep(2);
        printf("worker  %d return from epoll_wait!\n", k); 
        for (i = 0; i < n; i++) {
            if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events &EPOLLIN))) {
                /* An error has occured on this fd, or the socket is not ready for reading (why were we notified then?) */
                fprintf (stderr, "epoll error\n");
                close (events[i].data.fd);
                continue;
            } else if (sfd == events[i].data.fd) {
                /* We have a notification on the listening socket, which means one or more incoming connections. */
                struct sockaddr in_addr;
                socklen_t in_len;
                int infd;
                char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
                in_len = sizeof in_addr;
                infd = accept(sfd, &in_addr, &in_len);
                if (infd == -1) {
                    printf("worker %d accept failed,error:%s\n", k, strerror(errno));
                    break;
                }   
                printf("worker %d accept successed!\n", k); 
                /* Make the incoming socket non-blocking and add it to the list of fds to monitor. */
                close(infd); 
            }   
        }   
        }   
    }
    ```


## TCP内核缓冲区大小

```
$ sysctl -A | grep tcp.*mem

sysctl: permission denied on key 'fs.protected_hardlinks'
sysctl: permission denied on key 'fs.protected_symlinks'
sysctl: permission denied on key 'kernel.cad_pid'
sysctl: permission denied on key 'kernel.unprivileged_userns_apparmor_policy'
sysctl: permission denied on key 'kernel.usermodehelper.bset'
sysctl: permission denied on key 'kernel.usermodehelper.inheritable'
sysctl: permission denied on key 'net.ipv4.tcp_fastopen_key'
sysctl: permission denied on key 'net.ipv6.conf.all.stable_secret'
net.ipv4.tcp_mem = 187974       250633  375948
net.ipv4.tcp_rmem = 4096        87380   6291456
net.ipv4.tcp_wmem = 4096        16384   4194304
```

这里的tcp输入和输出缓冲区的大小都是2MB。如果发送的数据将tcp的发送缓冲区写满了，**程序就阻塞在这里了**。这个一定要注意，很多情况的阻塞都是这样发生的。


使用netstat的命令，可以查看缓冲区里面数据的大小。这个recv-q 和 send-q 就是缓冲区的大小。
```
Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name
tcp        0      0 127.0.0.1:27017         0.0.0.0:*               LISTEN      -
tcp        0      0 127.0.0.1:3306          0.0.0.0:*               LISTEN      -
```