# Linux 命令

## 目录

* [Linux 基础](#Linux基础)

* [Linux 工具命令](#Linux工具命令)

    * [GDB 命令]

    * [MAKE 命令]

* [Linux 进阶](#linux进阶)

* [参考资料](#参考资料)

---

## Linux 基础

* which 命令

* tcpdump 命令

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


## Linux 进阶

* netstat

* iostat

* ifstat

* vmstat

* mpstat

* strace

    跟踪系统运行的过程中，执行的系统调用和收到的信号。

* nc

* ulimit 命令


## 参考资料

>[GDB 教程](https://wizardforcel.gitbooks.io/100-gdb-tips/set-follow-fork-mode-child.html)


>[linux tool quick tutorial](https://linuxtools-rst.readthedocs.io/zh_CN/latest/base/index.html)
