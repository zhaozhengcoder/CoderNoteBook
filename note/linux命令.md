# Linux 命令

## 目录

* [Linux 基础](#Linux基础)

* [Linux 工具命令](#Linux工具命令)

    * [GDB 命令]

    * [MAKE 命令]

    * [GCC/G++ 命令]

    * [vim]

* [Linux 进阶](#linux进阶)

* [参考资料](#参考资料)

---

## Linux 基础

* which 命令

* tcpdump 命令

* ps命令

    * ps查看线程
    
        ps -T -p pid

## Linux 工具命令

* GDB 命令

    * GDB 调试
        ```
        run + 参数  #开始
        break       #断点

        next      #下一行
        step      #单步进入
        continue  #跳到下一个断点
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

* GCC/G++

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

* MAKE 命令

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

## Linux 进阶

* netstat

* iostat

* ifstat

* vmstat

* mpstat

* strace

    跟踪系统运行的过程中，执行的系统调用和收到的信号。

* nc

    ```
    nc -l 12345   #监听12345端口
    ```

    ```
    nc 127.0.0.1 12345   #向12345端口建立连接
    ```

* ulimit 命令


## 参考资料

>[GDB 教程](https://wizardforcel.gitbooks.io/100-gdb-tips/set-follow-fork-mode-child.html)


>[linux tool quick tutorial](https://linuxtools-rst.readthedocs.io/zh_CN/latest/base/index.html)

>[make教程](http://www.ruanyifeng.com/blog/2015/02/make.html)
