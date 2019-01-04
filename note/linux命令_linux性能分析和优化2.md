# linux性能优化

## 目录
* [linux的内存管理](#linux的内存管理)
* [内存里面的buffer和cache的区别](#内存里面的buffer和cache的区别)
----

## linux的内存管理
```
free -h
              total        used        free      shared  buff/cache   available
Mem:           3.7G        317M        2.6G        546M        755M        2.6G
Swap:          3.8G        108K        3.8G
```

```
# 当使用dd命令读文件的时候，可以使用free查看到内存改变
dd if=/dev/sda1 of=/dev/null bs=1MB count=2000
```

## 内存里面的buffer和cache的区别
```
vmstat
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 1  0    108 114356 508860 2899972    0    0     0     1    2    1  0  0 100  0  0

# 单位是kb
# bi ，bo 表示的是从块设备的读取和写入的速度（单位块/s）
```


vmstat命令的输出里面memroy里面又两个选项，一个是buff，一个是cache。它们两个的区别是什么？

1. buff指的是内核缓冲区用到的内存/proc/meminfo里面的buffers值

2. cache是内核页缓存和slab用到的内存，对应的是/proc/meminfo中的cached的值与sreclaimable之和

    （使用man proc可以查看）

buff和cache的指的是（这是man proc里面的说明）：

* buffer 对应的是读写磁盘的缓存

* cache 对应的是读写文件的缓存


测试案例1（写文件）：
```
# 再测试之前 必须要清理各种缓存
echo 3 > /proc/sys/vm/drop_caches  

dd if=/dev/urandom of=/tmp/file bs=1MB count=500
# 从设备里面读500mb的数据 写到到/tmp/file里面（相当于写文件）
```

```
# 使用vmstat观察
# 发现cache升高，buffer保持不变
vmstat 1 30
```

结论：

通过dd读磁盘，**发现cache升高**，然后buff不变。


测试案例2（写磁盘）：
```
# 再测试之前 必须要清理各种缓存
echo 3 > /proc/sys/vm/drop_caches  

# 向磁盘写入500MB数据
dd if=/dev/urandom of=/dev/sdb1 bs=1MB count=500

# 观察结果
vmstat 1 30
# 发现cache，buffer都升高，但是buffer升高的更快
```

结论：

**通过dd写磁盘，buffer升高，但是cache也会升高。cache升高的原因是因为cache不仅会缓存读磁盘的数据，也会缓存写磁盘的数据。**


测试案例3（读文件）：
```
echo 3 > /proc/sys/vm/drop_caches  

# 读文件
dd if=/tmp/file of=/dev/null bs=1MB count=500

# vmstat 观察
# 发现cache明显的升高
```


测试案例4（读磁盘）
```
echo 3 > /proc/sys/vm/drop_caches  

# 读文件
dd if=/dev/sda1 of=/dev/null bs=1MB count=500

# vmstat 观察
# 发现buffer明显的升高
```


关于读写文件和磁盘的区别：

**读写文件的时候，会经过文件系统。由文件系统负责与磁盘交互。而读写磁盘或者分区的时候，会跳过文件系统，也就是所谓的“裸io”。这两种读写方式的区别的本质也是buff和cache的区别。**


```
ls -l /dev/sda1
brw-rw---- 1 root disk 8, 1 12月 10 14:16 /dev/sda1

# 第一列是b
```

```
ls -l ~
drwxrwxr-x  3 ling ling  4096 3月   9  2018 projects
drwxrwxrwx  9 ling ling  4096 12月 19 21:53 src

# 第一列是d
```

以上讨论的缓存lib c库函数的函数没有任何关系，就是在linux api的这一层。
这一部分是由操作系统管理的，应用程序没有办法控制这些缓存的内容和生命周期。
所以，在应用程序的开发中，一般要设计专门的缓存组件，来提升性能。


### 关于缓存

cachestat 和 cachetop  是查看整个系统缓存的和单个进程读写命中缓存的情况。

```
# 安装cachestat 和 cachetop 

$ history 
184  sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 4052245BD4284CDD
185  echo "deb https://repo.iovisor.org/apt/xenial xenial main" | sudo tee /etc/apt/sources.list.d/iovisor.list
186  sudo apt-get update
187  sudo apt-get install -y bcc-tools libbcc-examples linux-headers-$(uname -r)
188  export PATH=$PATH:/usr/share/bcc/tools/
```

```
cachestat 1 3
Counting cache functions... Output every 1 seconds.
    HITS   MISSES  DIRTIES    RATIO   BUFFERS_MB   CACHE_MB
    1355        0        0   100.0%           26       1126
    1354        0        0   100.0%           26       1126
    1355        0        0   100.0%           26       1126
    1340        0        0   100.0%           26       1126

```


```
cachetop

16:32:31 Buffers MB: 29 / Cached MB: 1127 / Sort: HITS / Order: ascending
PID      UID      CMD              HITS     MISSES   DIRTIES  READ_HIT%  WRITE_HIT%
   21439 root     python                  1        0        0     100.0%       0.0%
     180 root     jbd2/sda5-8             3        3        1      33.3%      33.3%
```