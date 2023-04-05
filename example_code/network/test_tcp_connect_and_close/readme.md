# 使用tcpdump 观察tcp连接建立和关闭的过程

## 问题

1. tcp如何建立连接?
2. 服务器端调用close的时候，会发生什么？
3. 服务器端close之后，服务器再次尝试发送数据会发生什么？
4. 服务器端close之后，服务器再试尝试接受数据会发生什么？
5. 服务器端close之后，client向fd发送数据，会发生什么？
6. 服务器端close之后，client向fd接受数据，会发生什么？
7. sigpipe信号什么时候产生？默认的处理是什么样子的？

---

测试的文件是：

server.cc

client.cc

tcpdump观察9999端口
```
sudo tcpdump -n -i lo port 9999
```

* 问题1 ： tcp如何建立连接?

    可以明显的看出，是三次握手。
    ```
    sudo tcpdump -n -i lo port 9999

    18:45:44.988935 IP 127.0.0.1.54927 > 127.0.0.1.9999: Flags [S], seq 2973985528, win 43690, options [mss 65495,sackOK,TS val 6113144 ecr 0,nop,wscale 7], length 0

    18:45:44.988951 IP 127.0.0.1.9999 > 127.0.0.1.54927: Flags [S.], seq 2517756569, ack 2973985529, win 43690, options [mss 65495,sackOK,TS val 6113144 ecr 6113144,nop,wscale 7], length 0

    18:45:44.988967 IP 127.0.0.1.54927 > 127.0.0.1.9999: Flags [.], ack 1, win 342, options [nop,nop,TS val 6113144 ecr 6113144], length 0
    ```

* 问题2：服务器端调用close的时候，会发生什么？

    当服务器调用close 的使用，tcpdump抓到的包。
    ```
    18:47:17.427152 IP 127.0.0.1.9999 > 127.0.0.1.54927: Flags [F.], seq 15, ack 15, win 342, options [nop,nop,TS val 6136253 ecr 6132295], length 0

    18:47:17.464231 IP 127.0.0.1.54927 > 127.0.0.1.9999: Flags [.], ack 16, win 342, options [nop,nop,TS val 6136263 ecr 6136253], length 0
    ```
    可以看出，服务器向client发送了一个fin，client回复了一个ack。

    **但是，这个close只是表面上看上去很想四次挥手的前两次，但是，其实不是这样的。服务器这一头已经关闭了自己的读和写。**这也就是close和shutdown的区别。接下来，无论client发过来什么，服务器都不会回复了，只会回复rst。（因为，向一个关闭的端口发送数据，对方就会回复rst）



* 问题3：服务器端close之后，服务器再次尝试发送数据会发生什么？

    send 函数，返回-1。 此时tcpdump没有任何输出。

* 问题4：服务器端close之后，服务器再次尝试接收数据会发生什么？

    recv 函数，返回-1。此时tcpdump没有任何输出。(recv函数返回0，表示对方关闭，返回-1，表示出错。)

* 问题5： 服务器端close之后，client向fd发送数据，会发生什么？


    ```
    19:05:02.818185 IP 127.0.0.1.47003 > 127.0.0.1.9999: Flags [P.], seq 15:29, ack 16, win 342, options [nop,nop,TS val 6402601 ecr 6400955], length 14
    
    19:05:02.818206 IP 127.0.0.1.9999 > 127.0.0.1.47003: Flags [R], seq 1956113576, win 0, length 0
    ```
    
    可以看出，client向服务器发送了数据，但是服务器的读和写都关闭了，于是，服务器回复rst报文。


* 问题6： 服务器端close之后，client向fd接收数据，会发生什么？

    recv 函数，返回0。此时tcpdump没有任何输出。(recv函数返回0，表示对方关闭，返回-1，表示出错。)

* 问题7：sigpipe信号什么时候产生？默认的处理是什么样子的？

    如果服务器close之后，client向fd写入两次数据之后，（调用两次send）会触发sigpipe。默认的sigpipe是退出程序。