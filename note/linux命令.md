# Linux 命令

## 目录

* [Linux 基础](#Linux基础)

* [Linux 工具命令](#Linux工具命令)

    * [GDB](#GDB)

    * [MAKE](#MAKE)

    * [CMAKE](#CMAKE)

    * [GCC/G++](#GCC/G++)

    * [vim](#vim)

* [Linux 进阶](#linux进阶)

    * [strace](#strace)

* [Linux 性能优化](#linux性能优化)


* [参考资料](#参考资料)

---

## Linux基础

### which 命令


### tcpdump 命令

[tcpdump命令](https://github.com/zhaozhengcoder/CoderNoteBook/blob/master/note/linux%E5%91%BD%E4%BB%A4_tcpdump.md)

### ps命令

* 我常用的
    ```
    ps -aux
    ```

* ps查看线程
    ```
    ps -T -p pid
    ```
## Linux工具命令

### GDB

* GDB 调试
    ```
    run + 参数  #开始
    break      #断点

    next      #下一行
    step      #单步进入
    continue  #跳到下一个断点

    bt        #查看函数栈
    ```
* attach
    ```
    gdb attach 进程号
    ```

* 处理corefile
    ```
    gdb a.out core.xxxx
    ```

* 调试多进程

    方式1：
    ```
    gdb attach 进程号
    ```

    方式2：使用follow-fork-mode
    ```
    (gdb) set follow-fork-mode child   # 表示调试子进程
    (gdb) set follow-fork-mode parent  # 表示调试子进程
    ```

* 调试多线程
    
    ```
    info threads              # 查看线程信息
    set scheduler-locking on  # 锁定线程
    thread 2                  # 选择要调试的线程
    ```

* 推荐一个教程

    https://wizardforcel.gitbooks.io/100-gdb-tips/content/ 

### GCC/G++

常用的参数
```
-c          # 生成 .o 目标文件 ， 不进行连接操作
-s          # 生成汇编代码               gcc -S test.i -o test.s
-E          # 预处理                    gcc -E test.c -o test.i
-Wall       # 显示警告信息
-Werror     # error的时候，停止编译
-lpthread


-I          # 指定头文件搜索的目录
            gcc –c –I /usr/dev/mysql/include test.c –o test.o

-L          #-L -l  指定了链接静态库或者是动态库的路径
-l          
            gcc –L /usr/dev/mysql/lib –lmysqlclient test.o –o test
```

```
静态库链接时搜索路径顺序：

1. ld会去找GCC命令中的参数-L
2. 再找gcc的环境变量LIBRARY_PATH
3. 再找内定目录 /lib /usr/lib /usr/local/lib 这是当初compile gcc时写在程序内的

动态链接时、执行时搜索路径顺序:

1. 编译目标代码时指定的动态库搜索路径
2. 环境变量LD_LIBRARY_PATH指定的动态库搜索路径
3. 配置文件/etc/ld.so.conf中指定的动态库搜索路径
4. 默认的动态库搜索路径/lib
5. 默认的动态库搜索路径/usr/lib

有关环境变量：
LIBRARY_PATH环境变量：指定程序静态链接库文件搜索路径
LD_LIBRARY_PATH环境变量：指定程序动态链接库文件搜索路径
```

segment fault的时候设置产生core文件
```
ulimit -a    #查看core 是否可以产生

core file size          (blocks, -c) 0
data seg size           (kbytes, -d) unlimited
scheduling priority             (-e) 0
file size               (blocks, -f) unlimited
pending signals                 (-i) 7823
max locked memory       (kbytes, -l) 64
max memory size         (kbytes, -m) unlimited
open files                      (-n) 1024
pipe size            (512 bytes, -p) 8
POSIX message queues     (bytes, -q) 819200
real-time priority              (-r) 0
stack size              (kbytes, -s) 8192
cpu time               (seconds, -t) unlimited
max user processes              (-u) 7823
virtual memory          (kbytes, -v) unlimited
file locks                      (-x) unlimited

```

上面可以看出core file的大小是 0 
```
ulimit -c 1024        # 修改成1024，这样就可以产生core file了
```

### MAKE 

* make的规则是
    ```
    <target> : <prerequisites> 
    [tab]  <commands>

    # target 表示目标
    # prerequisites 表示前置条件
    ```
* 变量
    * 定义变量
        ```
        cc = g++
        output:p1.txt p2.txt
            $(cc) -o ouput test_cast.cpp
        ```
    * 调用shell的变量
        调用shell变量，需要加上两个$$
        ```
        test:
            echo $$HOME
        ```

* 自动变量
    * $@  

        $@ 指代**当前目标**，就是Make命令当前构建的那个目标。
        ```
        a.txt:
            touch $@
        
        # 约等于 
        a.txt:
            touch a.txt
        ```

    * $< 指代**第一个前置条件**。比如，规则为 t: p1 p2，那么$< 就指代p1。

        ```
        a.txt:p1.txt p2.txt
            touch $<
        ```

    * $^ 指代**所有前置条件**
        ```
        比如，规则为 t: p1 p2，那么 $^ 就指代 p1 p2 。
        ```

* 函数

    * wildcard 函数
        ```
        srcfiles := $(wildcard src/*.txt)
        ```

        一个目录下面所有的.c 文件
        ```
        src = $(wildcard *.c ./sub/*.c)
        ```

```
# 举一个例子
MUDUO_DIRECTORY ?= $(HOME)/code_test/muduo/build/release-install
#MUDUO_DIRECTORY ?= $(HOME)/build/install
MUDUO_INCLUDE = $(MUDUO_DIRECTORY)/include
MUDUO_LIBRARY = $(MUDUO_DIRECTORY)/lib
SRC = ./

CXXFLAGS = -g -O0 -Wall -Wextra -Werror \
	   -Wconversion -Wno-unused-parameter \
	   -Wold-style-cast -Woverloaded-virtual \
	   -Wpointer-arith -Wshadow -Wwrite-strings \
	   -march=native -rdynamic \
	   -I$(MUDUO_INCLUDE)

LDFLAGS = -L$(MUDUO_LIBRARY)  -lmuduo_net  -lmuduo_base -lpthread -lrt

# lmuduo_inspect 
all: hub sub pub
clean:
	rm -f hub core

hub: $(SRC)/hub.cc codec.cc
	g++ $(CXXFLAGS) -o $@ $^  $(LDFLAGS)

sub: $(SRC)/sub.cc codec.cc pubsub.cc
	g++ $(CXXFLAGS) -o $@ $^  $(LDFLAGS)

pub: $(SRC)/pub.cc codec.cc pubsub.cc
	g++ $(CXXFLAGS) -o $@ $^  $(LDFLAGS)

.PHONY: all clean
```

## Linux 进阶

### htop/top命令

top的一部分输出是：
```
    PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND
1 root      20   0    8304    132    104 S   0.0  0.0   0:00.06 init
3 root      20   0    8304     92     56 S   0.0  0.0   0:00.00 init
```

VIRT 的定义是：占用的虚拟内存的大小（占用的物理内存+swap空间）

RES 表示的是：占用的物理内存

SHR 表示的是：占用的是共享内存

### netstat

### iostat

### ifstat

### vmstat

### mpstat

### strace

跟踪系统运行的过程中，执行的系统调用和信号。这个简直就是debug的神器呀。

比如说，写了一个tcp的程序，然后程序运行之后阻塞在一个地方，可以用这个命令来查看。

```
strace ./a.out -l 5003
```

```
strace ./netcat -l 5003
execve("./netcat", ["./netcat", "-l", "5003"], [/* 17 vars */]) = 0
brk(NULL)                               = 0x97a000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)

...

futex(0x7f9adebcf1ac, FUTEX_WAKE_PRIVATE, 2147483647) = 0
futex(0x7f9adebcf1b8, FUTEX_WAKE_PRIVATE, 2147483647) = 0
socket(PF_INET, SOCK_STREAM|SOCK_CLOEXEC, IPPROTO_TCP) = 3
setsockopt(3, SOL_SOCKET, SO_REUSEADDR, [1], 4) = 0
bind(3, {sa_family=AF_INET, sin_port=htons(5003), sin_addr=inet_addr("0.0.0.0")}, 16) = 0
listen(3, 128)                          = 0
accept(3,
```

说明程序阻塞在了accept上面。当然，这个用gdb也可以实现。


### nc

    ```
    nc -l 12345   #监听12345端口
    ```

    ```
    nc 127.0.0.1 12345   #向12345端口建立连接
    ```

### ulimit 命令

---

## linux性能优化

看了很多文章，很多大牛都提到要关注自己程序的性能问题。比如说，除了你的程序可以work之外，除此之外，还需要考虑你的程序的cpu占用率，
内存占用率，io占用率等。这些都是我之前不太care的事情，我现在才开始考虑这个问题。我试着写一些我的理解和总结。

1. 如何发现问题？

    * htop命令可以查看出**瞬时**的资源占用率（cpu，内存等）。如果说，每个进程的cpu的占用率达到了100%，这样是有问题的。说明程序写的非常糟糕。

    * uptime命令可以查看出**平均负载**。

        平均负载的概念非常重要，我简单的理解一下。
        
        平均负载 = 活跃进程/ cpu的核心数 ， 活跃进程 = runing的进程 + d状态的进程（不可中断的进程）

        ```
        uptime
        22:03:55 up 12 min,  0 users,  load average: 0.52, 0.58, 0.59
        ```

        如果系统的平均负载不正常，比如大于1的时候，那可能需要思考一下，是不是出问题了。

    * linux的一个压力测试的工具

        stress命令

---
## 参考资料

>[GDB 教程](https://wizardforcel.gitbooks.io/100-gdb-tips/set-follow-fork-mode-child.html)


>[linux tool quick tutorial](https://linuxtools-rst.readthedocs.io/zh_CN/latest/base/index.html)

>[make教程](http://www.ruanyifeng.com/blog/2015/02/make.html)
