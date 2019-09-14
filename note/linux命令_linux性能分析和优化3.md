## linux性能优化整理一个例子

## 目录
* [内存泄漏](#内存泄漏)

----


## 内存泄漏

### 1. 内存泄漏导致的问题

简单的讲，内存泄漏指的是在堆上面分配的内存没有被free或是delete。
这样导致的问题是，系统的可用内存不断减少，于是导致：
* 系统启用swap的空间，然后导致性能变差
* 系统开始回收cache和buffer的空间，然后导致性能变差

### 2. 如何发现内存泄漏

使用memleak工具和valgrind工具可以分析。

简单的思路，比如说：
1. 发现问题，程序oom （out of memory）。
2. 或者使用free 观察到 可用内存在不停的降低
3. 使用 memleak 定位
    ```
    $ /usr/share/bcc/tools/memleak -p $(pidof app) -a
    Attaching to pid 12512, Ctrl+C to quit.
    [03:00:41] Top 10 stacks with outstanding allocations:
        addr = 7f8f70863220 size = 8192
        addr = 7f8f70861210 size = 8192
        addr = 7f8f7085b1e0 size = 8192
        addr = 7f8f7085f200 size = 8192
        addr = 7f8f7085d1f0 size = 8192
        40960 bytes in 5 allocations from stack
            fibonacci+0x1f [app]
            child+0x4f [app]
            start_thread+0xdb [libpthread-2.27.so] 
    ```