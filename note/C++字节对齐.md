# c++ 字节对齐

## 目录
* [为什么需要字节对齐](#为什么需要字节对齐)
* [字节对齐的原理](#字节对齐的原理)

---

## 为什么需要字节对齐

在cpu访问内存的时候，访问内存的最小单位不是字节，而是字长（4个字节，8个字节，或其他）。如果没有字节对齐的机制，可能访问一个int（4字节的）在某些情况需要cpu访问两次内存，而且需要多余的cpu指令剔除掉不需要的数据。

而在网络的传输中，就一般不需要字节对齐。因为，在网络中需要尽可能的降低数据传输的流量。字节对齐的机制，会加入多余的填充字节，导致网络流量变大。

## 字节对齐的原理

对齐系数，gcc的默认对对齐系数是4，#pragma pack(4)。

假设 对齐系数 = N, 结构体中最长数据类型 = m；

对齐单位 n = min{N,m} 

字节对齐的规则：
1. 成员对齐值：
    
    首个成员的偏置地址(offset) = 0。

    假定该成员的类型占字节数 j，那么本成员的偏移地址(offset)：min{n, j}的整数倍。

2. 整体对齐值：

    结构体的总大小为 有效对齐值n 的整数倍。如果不是的话，需要进行填充字节。

## 验证一下

我的机器默认是pack(8), 我先改成pack(4)
```
#pragma pack(4)
#include <iostream>

struct TEST
{
    int val1;
    double val2;
    char c;
};

int main()
{
    TEST test;
    memset(&test, 0, sizeof(test));
    
    test.val1 = 1;
    test.val2 = 2;
    test.c = 'a';

    std::cout << sizeof(test) << std::endl;     // 输出 16 
    return 0;
}
```

如果改成pack(1)，就是13。

使用gdb看一下具体的内存分布：
```
(gdb) p/x test
$3 = {val1 = 0x1, val2 = 0x2, c = 0x61}

(gdb) x/16xb &test
0x7ffffffee270:	0x01	0x00	0x00	0x00	0x02	0x00	0x00	0x00
0x7ffffffee278:	0x00	0x00	0x00	0x00	0x61	0x00	0x00	0x00
                                                        ^               ^ 
                                                        | <--padding--> |

```


关于gdb的几个命令：
```
# 打印变量
gdb  
p/x 以16进制打印结构体
```


examine查看内存，缩写是x
命令的格式是：
```
x/<n/f/u> <addr>
* n表示要打印的多少个单位的内存，默认是1，单位由u定义
* f表示打印的格式，格式有：
    o，octal，八进制；
    x，hex，十六进制；
    d，decimal，十进制；
    u，unsigned decimal，无符号十进制；
    t，binary，二进制；
    f，float；
    a，address；
    i，instruction，指令；
    c，char，字符；
    s，string，字符串
* u定义单位，b表示1字节，h表示2字节，w表示4字节，g表示8字节

示例：
x/16xb 指针    // 打印后面16的字节的数据
```

