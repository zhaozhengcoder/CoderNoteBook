## Address Sanitizer 

## 目录

* [简介](#简介)
* [hello-world实例](#hello-world实例)

---

## 简介

asan是一个Google提供的一个内存检测的工具。

https://github.com/google/sanitizers/wiki/AddressSanitizer

* asan原理

    shadow-memory （影子内存）

---
## hello-world实例

* 测试使用asan定位一个服务器内存泄露的例子
    ```
    #include <stdlib.h>
    #include <stdio.h>
    char leaktest() {
        char * x = (char *)malloc(10 * sizeof(char));
        x[20] = 'b';
        return x[5];
    }

    int main()
    {
        printf("==== main ==== \n");
        
        // 伪造内存越界写入和泄漏
        leaktest();
        // 假设这是一个服务器程序，不停的运行中
        while(1) {}    
        
        printf("==== end ===== \n");
        return 0;
    }

    // g++ -fsanitize=address -fsanitize-recover=address -g test.c -o test
    // export ASAN_OPTIONS=halt_on_error=0:log_path=/home/zhaozheng/log/asan.log
    ```

* 输出日志：

    ```
    cat asan.log.358177 
    =================================================================
    ==358177==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x602000000024 at pc 0x0000004011e8 bp 0x7fffffffe1e0 sp 0x7fffffffe1d0
    WRITE of size 1 at 0x602000000024 thread T0
        #0 0x4011e7 in leaktest() /home/zhaozheng/workspace/asan/test.c:5
        #1 0x401244 in main /home/zhaozheng/workspace/asan/test.c:13
        #2 0x7ffff63376a2 in __libc_start_main (/lib64/libc.so.6+0x236a2)
        #3 0x4010dd in _start (/home/zhaozheng/workspace/asan/test2+0x4010dd)

    0x602000000024 is located 10 bytes to the right of 10-byte region [0x602000000010,0x60200000001a)
    allocated by thread T0 here:
        #0 0x7ffff70f4c58 in __interceptor_malloc (/lib64/libasan.so.5+0xefc58)
        #1 0x4011a8 in leaktest() /home/zhaozheng/workspace/asan/test.c:4
        #2 0x401244 in main /home/zhaozheng/workspace/asan/test.c:13
        #3 0x7ffff63376a2 in __libc_start_main (/lib64/libc.so.6+0x236a2)

    SUMMARY: AddressSanitizer: heap-buffer-overflow /home/zhaozheng/workspace/asan/test.c:5 in leaktest()
    Shadow bytes around the buggy address:
    0x0c047fff7fb0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    0x0c047fff7fc0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    0x0c047fff7fd0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    0x0c047fff7fe0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    0x0c047fff7ff0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    =>0x0c047fff8000: fa fa 00 02[fa]fa fa fa fa fa fa fa fa fa fa fa
    0x0c047fff8010: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
    0x0c047fff8020: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
    0x0c047fff8030: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
    0x0c047fff8040: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
    0x0c047fff8050: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
    Shadow byte legend (one shadow byte represents 8 application bytes):
    Addressable:           00
    Partially addressable: 01 02 03 04 05 06 07 
    Heap left redzone:       fa
    Freed heap region:       fd
    Stack left redzone:      f1
    Stack mid redzone:       f2
    Stack right redzone:     f3
    Stack after return:      f5
    Stack use after scope:   f8
    Global redzone:          f9
    Global init order:       f6
    Poisoned by user:        f7
    Container overflow:      fc
    Array cookie:            ac
    Intra object redzone:    bb
    ASan internal:           fe
    Left alloca redzone:     ca
    Right alloca redzone:    cb
    ```

* asan的编译选项

1. 内存越界时程序直接abort，而是继续执行。（对于服务器程序很关键）
    
    `-fsanitize-recover=address`

2. 通过ASAN_OPTIONS变量设置recover模式

    `ASAN_OPTIONS=halt_on_error=0`
    `#强烈建议你不要这么做，因为recover出来是什么结果是无法预测的`

3. 通过非标准的C++修饰__attribute__((no_sanitize_address)) 指定某些具体函数屏蔽内存检查功能

    也可以通过-fsanitize-blacklist=your_ignore_list.txt 或者 ASAN_OPTIONS=suppressions=your_ignore_list.txt 指定屏蔽列表。

    具体请参考：

    https://github.com/google/sanitizers/wiki/AddressSanitizer#turning-off-instrumentation

4. asan的日志输出到指定的地方
    
    `export ASAN_OPTIONS=log_path=`

5. 内存泄露检测跑得更快 

    `-fsanitize=address替换成-fsanitize=leak`

    https://github.com/google/sanitizers/wiki/AddressSanitizerLeakSanitizer
