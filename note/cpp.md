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

    右值引用，是c++11里面一个新特性。他解决的问题是：
    
    * 临时对象非必要的拷贝操作；

    * 模板参数中如何按照实际类型进行转发；

    * A(A&&  a) 的构造函数；

    为什么需要解决第一个问题？
    ```
    #include <iostream>
    using namespace std;

    int g_constructCount=0;
    int g_copyConstructCount=0;
    int g_destructCount=0;
    struct A
    {
        A(){
            cout<<"construct: "<<++g_constructCount<<endl;    
        }
        
        A(const A& a)
        {
            cout<<"copy construct: "<<++g_copyConstructCount <<endl;
        }
        ~A()
        {
            cout<<"destruct: "<<++g_destructCount<<endl;
        }
    };

    A GetA()
    {
        return A();
    }

    int main() {
        A a = GetA();
        return 0;
    }
    ```

    输出

    为了清楚的观察临时值，在编译时设置编译选项-fno-elide-constructors用来关闭返回值优化效果。
    ```
    construct: 1             # 执行 getA() 函数里面的 A()
    copy construct: 1        # 将A()创建的对象复制给函数的临时返回值对象 tmp = A()
    destruct: 1              # 析构 A() 对象
    copy construct: 2        # A a = tmp
    destruct: 2              # 析构tmp
    destruct: 3              # 析构 a
    ```

    上面的例子是一个结构体,换成结构体也是一样的。
    ```
    #include <iostream>
    using namespace std;

    class test
    {
    public:
        test()
        {
            cout<<"construct"<<endl;
        }
        test(const test & t)
        {
            cout<<"copy construct"<<endl;
        }
        ~test()
        {
            cout<<"desconstruct"<<endl;
        }
    };

    test get_test()
    {  
        return test();
    }
    int main()
    {
        test t1 = get_test();
    }
    ```

    **区分左值和右值的一个简单办法是：** 看能不能对表达式取地址，如果能，则为左值，否则为右值。

    getvar函数返回一个临时对象，临时对象完成赋值之后，被析构掉。
    ```
    int i = getvar();
    ```


    下面这一行代码，创建了一个右值引用对象k，这个可以给返回的临时对象“续命” ， 他的生命周期将会通过右值引用得以延续，和变量k的声明周期一样长。
    ```
    int && k = getvar();
    ```
    通过右值引用的声明，右值又“重获新生”，其生命周期与右值引用类型变量的生命周期一样长，只要该变量还活着，该右值临时量将会一直存活下去。

    ```
    #include <iostream>
    using namespace std;

    class test
    {
    public:
        test()
        {
            cout<<"construct"<<endl;
        }
        test(const test & t)
        {
            cout<<"copy construct"<<endl;
        }
        ~test()
        {
            cout<<"desconstruct"<<endl;
        }
    };

    test get_test()
    {  
        return test();
    }
    int main()
    {
        test && t1 = get_test();
    }
    ```

    编译：
    ```
    g++ -fno-elide-constructors -std=c++11 main.cpp
    ```

    输出：
    ```
    construct           # get_test 函数里面 test() 构造
    copy construct      # test tmp = test() 将创建的对象拷贝给临时对象
    desconstruct        # 析构get_test test()对象
    desconstruct        # 程序结束的时候，析构tmp对象
    ```

    移动构造函数
    ```
    #include <iostream>
    using namespace std;

    class test
    {
    public:
        test()
        {
            cout<<"construct"<<endl;
        }
        test(const test & t)
        {
            cout<<"copy construct"<<endl;
        }

        //在这里添加一个移动构造函数
        test(test && t)
        {
            cout<<"move construct"<<endl;
        }
        
        ~test()
        {
            cout<<"desconstruct"<<endl;
        }
    };

    test get_test()
    {  
        return test();
    }
    int main()
    {
        test && t1 = get_test();
    }
    ```

    ```
    $ g++ -fno-elide-constructors -std=c++11 main.cpp
    $ ./a.out
    construct
    move construct
    desconstruct
    desconstruct
    ```

    这里思考一个问题，

    为什么这里会调用移动函数？而不是拷贝构造函数？
    因为，因为这个构造函数只能接受右值参数，**而函数返回值是右值**，所以就会匹配到这个构造函数。

    * std::move

        move的作用就是把左值变成右值，这样就可以调用移动构造函数。就避免了拷贝，提高了程序性能。

    * 完美转发 forward

        在函数模板中，完全依照模板的参数的类型（即保持参数的左值、右值特征），将参数传递给函数模板中调用的另外一个函数。

* 智能指针

* 函数指针

* cpp11的语法糖

* 模板与泛型编程