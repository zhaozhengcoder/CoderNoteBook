## 对于iowait升高的分析

1. 什么是iowait？

    iowait表示的是：CPU空闲、但是**并且有仍未完成的I/O请求。**

    %iowait 表示在一个采样周期内有百分之几的时间属于以下情况：CPU空闲、并且有仍未完成的I/O请求。

    iowait是一个比较抽象的指标，%iowait 所含的信息量非常少的原因。它是一个非常模糊的指标，如果看到 %iowait 升高，还需检查I/O量有没有明显增加。

2. 如何发现iowait升高？

    app.c 文件是一个让iowait升高的例子。可以跑一下，观察一下。

    观察iowait升高
    ```                                                         
    $ top
    top - 20:47:16 up 2 days,  8:54,  3 users,  load average: 0.99, 0.66, 15.58
    Tasks: 176 total,   1 running, 171 sleeping,   2 stopped,   2 zombie
    %Cpu(s):  0.1 us,  0.3 sy,  0.0 ni, 41.5 id, 58.2 wa,  0.0 hi,  0.0 si,  0.0 st

    # 最上面的这一行表示的时，如果有100s的cpu的时间的话，
    # 0.1s用于us，即执行用户态的代码
    # 0.3s用于sys，即执行内核态的代码
    # 41.5s用于id，即执行idle
    # 58.2s用于执行io空闲，但是有未完成的io请求。
    ```

    iowait可会让cpu负载升高
    ```
    uptime 
    ```

    为什么会让cpu负载升高？

    因为cpu平均负载 = 活跃进程/ cpu的核心数 ， 活跃进程 = runing的进程 + D 状态的进程（不可中断的进程）。

    而在这个app.c的例子里面，进程的状态时D。

3. 如果出现了iowait升高的例子，如何观察和定位问题的根源？

    iostat 升高，是一个很模糊的概念。首先，需要分析一下io的情况。

    iostat 命令，dstat命令 都可以观察io。

    iostat命令
    ```
    Device:            tps    kB_read/s    kB_wrtn/s    kB_read    kB_wrtn
    loop0             0.00         0.00         0.00          8          0
    sda               2.34       552.67       277.98  114015848   57346540
    ```

    dstat命令
    ```
    dstat
    ----total-cpu-usage---- -dsk/total- -net/total- ---paging-- ---system--
    usr sys idl wai hiq siq| read  writ| recv  send|  in   out | int   csw 
      0   1  98   1   0   0| 769k  277k|   0     0 |  11k   24k|  64   218 
      0   1  75  25   0   0| 121M    0 | 182B  830B|   0     0 | 177   104 
      0   0  75  24   0   0| 120M    0 | 492B 6518B|   0     0 | 185   114 
      0   0  75  24   0   0| 119M    0 |  64B  350B|   0     0 | 182   129 
      0   0  75  25   0   0| 122M    0 | 246B  414B|   0     0 | 160    72 
      0   0  75  24   0   0| 116M  104k| 428B 6204B|   0     0 | 205   123
    ```

    pidstat
    ```
    pidstat -d  1 10
    # -d 表示 关注磁盘
    # 1 10 表示 ，1秒采样1次，连续输出10次
    ```

    ```
    pidstat -d -p pid 1 10
    ```

    perf命令
    ```
    perf record -a -g sleep 20
    ```

    ```
    perf report
    ```

## 出现大量僵尸进程的分析

1. 发现僵尸进程

    ```
    top 

    Tasks: 285 total,   1 running, 173 sleeping,  67 stopped,  44 zombie

    # 这是top命令的一行输出，其中zombie的进程数量时 44个
    ```

2. 定位问题

    ```
    ps -aux | grep Z 
    # 找到一个僵尸进程的pid

    # 然后通过 pstree 找到这个进程的父进程
    pstree -aps 2415
    systemd,1 splash
    └─sshd,923 -D
        └─sshd,1131   
            └─sshd,1198    
                └─bash,1199
                    └─sudo,2364 su root
                        └─su,2365 root
                            └─bash,2366
                                └─app,2413
                                    └─(app,2415)
    ```

## 参考 

https://github.com/feiskyer/linux-perf-examples/tree/master/high-iowait-process

http://linuxperf.com/?p=33