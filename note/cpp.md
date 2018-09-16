# C++ 

## 目录


---

* extern 关键字

    思考一个问题，如果在main.cpp文件里面调用 fun.c 文件里面的func 函数？
    换一句话，就是如果在c++的代码里面调用c的代码。
    
    **main.cpp 文件**
    ```
    // main.cpp
    #include <iostream>
    using namespace std;

    extern "C" int func();

    int main()
    {
        func();

        return 0;
    }
    ```

    **func.c 文件**
    ```
    // func.c
    #include <stdio.h>

    int func()
    {
        printf("hello \n");
        return 0;
    }
    ```

    **编译**
    ```
    # 编译
    gcc func.c -c
    g++ main.cpp func.o
    ```

    extern 表示这个声明的这个函数是以c的编写的。这个是一个链接指示，表示这个链接这个函数的时候，按照c语言的符号表去查找。


* 构造函数 初始化列表初始化

    为什么要使用初始化列表初始化？
    
    答：**避免二次初始化**
    
    可以思考一个问题，如果这个test类里面有一个vector，如果把它初始化为10个-1 ? 

    这个基本上，必须使用初始化列表来完成。
    ```
    class TEST
    {
    public:
        vector<int> vi;
        TEST():vi(10,-1) {}
    };
    ```

* 右值引用

* move 移动拷贝


* 智能指针

* 函数指针

* cpp11的语法糖

* 模板与泛型编程