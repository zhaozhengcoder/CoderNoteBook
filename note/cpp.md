# C++ 

## 目录

* [语法](#语法)
* [比较重要的零散的东西](#比较重要的零散的东西)

---
## 语法

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

    int main() 
    {
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

        ```
        {
            // 正常的vector拷贝
            vector<int> vi = {1,2,3,4,5,65,6,0};
            vector<int> vv = vi;
        }
        {
            // 使用move，更加高效的拷贝vector
            // 拷贝完成之后，vi2的元素被移动到vv2里面，然后vi2就是一个空的vector
            vector<int> vi2 = {4,3,54,6,234,234234,234};
            vector<int> vv2 = move(vi2);
            
            cout<<"size : "<<vi2.size()<<"  "<<vv2.size()<<endl;
            vi2.push_back(-1);
            cout<<"size : "<<vi2.size()<<"  "<<vv2.size()<<endl;
        }
        ```

        ```
        # 输出
        size : 0  7
        size : 1  7
        ```

        如果不用 std::move，拷贝的代价很大，性能较低。使用move几乎没有任何代价，只是转换了资源的所有权。他实际上将左值变成右值引用，然后应用移动语义，调用移动构造函数，就避免了拷贝，提高了程序性能。


    * 完美转发 forward

        在函数模板中，完全依照模板的参数的类型（即保持参数的左值、右值特征），将参数传递给函数模板中调用的另外一个函数。

* 智能指针

    * 为什么要使用智能指针？

        c++ 是一个需要手动执行gc的语言，new 和 delete 如果没有成对出现，就会出现内存泄漏的问题。

    * 如果使用？

        * shared_ptr
            ```
            //test 是一个class ，需要include <memory>
            //创建
            shared_ptr<test> p_test(new test());
            
            //调用
            p_test->print_func();

            //查看引用计数
            cout<<p_test.use_count()<<endl;

            //多个指针，指向一个对象
            shared_ptr<test> p_test2;
            p_test2 = p_test;
            cout<<p_test.use_count()<<"  "<<p_test2.use_count()<<endl;
            ```

            shared_ptr 实现的原理是对 对象的引用计数，引用计数就会出现一个问题，就是相互引用的出现。
            ```
            class B;
            class A
            {
            public:
                shared_ptr<B> pb_;
                ~A()
                {
                    cout<<"A delete\n";
                }
            };
            class B
            {
            public:
                shared_ptr<A> pa_;
                ~B()
                {
                    cout<<"B delete\n";
                }
            };
            
            void fun()
            {
                shared_ptr<B> pb(new B());
                shared_ptr<A> pa(new A());
                pb->pa_ = pa;
                pa->pb_ = pb;
                cout<<pb.use_count()<<endl;
                cout<<pa.use_count()<<endl;
            }
            
            int main()
            {
                fun();
                return 0;
            }
            ```

        * weak_ptr

            weak_ptr是用来解决shared_ptr相互引用时的死锁问题,如果说两个shared_ptr相互引用,那么这两个指针的引用计数永远不可能下降为0,资源永远不会释放。它是对对象的一种弱引用，不会增加对象的引用计数，和shared_ptr之间可以相互转化，shared_ptr可以直接赋值给它，它可以通过调用lock函数来获得shared_ptr。

            ```
            class B;
            class A
            {
            public:
                weak_ptr<B> pb_;
                ~A()
                {
                    cout<<"A delete\n";
                }
            };
            class B
            {
            public:
                shared_ptr<A> pa_;
                ~B()
                {
                    cout<<"B delete\n";
                }
            };
            
            void fun()
            {
                shared_ptr<B> pb(new B());
                shared_ptr<A> pa(new A());
                pb->pa_ = pa;
                pa->pb_ = pb;
                cout<<pb.use_count()<<endl;
                cout<<pa.use_count()<<endl;
            }
            
            int main()
            {
                fun();
                return 0;
            }
            ```

        * unique_ptr 

            unique_ptr 是一个独享所有权的智能指针。无法进行复制构造，无法进行复制赋值操作。即无法使两个unique_ptr指向同一个对象。但是可以进行移动构造和移动赋值操作。

* 函数指针

    定义一个函数的指针
    ```
    int func1(int val)
    {
        cout<<val<<endl;
    }
    
    int main()
    {
        //定义一个函数指针
        int (*pfunc)(int) = NULL;
        
        pfunc = func1;
        pfunc(100);
        
        return 0;
    }
    ```

    使用函数指针作为参数
    ```
    int func1(int val)
    {
        cout<<val<<endl;
    }

    int test(int (*pfunc)(int), int val)
    {
        pfunc(val);
    } 
    int main()
    {
        //定义一个函数指针
        int (*pfunc)(int) = NULL;
        pfunc = func1;

        test(pfunc,10);
        
        return 0;
    }
    ```

    typedef 简化函数指针类型
    ```
    float add(float a,float b)
    {
        cout<<a<<"  "<<b<<endl;
        return a+b;
    }

    typedef float(*pfunType)(float, float);

    int main()
    {
        pfunType p = add;
        p(3.33, 2.22);

        return 0;
    }
    ```

* cpp11的语法糖

    * for-each
        ```
        vector<int> vi = {1,2,3,4,5,6,7};

        for(auto val : vi)
        {
            cout<<val<<endl;
        }

        for(auto & val : vi)
        {
            val = val * 2;
            cout<<val<<endl;
        }
        ```

    * auto
        ```
        auto iter = vi.begin()
        ```

    * lambda
        ```

        ```

* 模板与泛型编程

* 异常机制

* 空间分配 

* 多态/虚函数


## 比较重要的零散的东西

* 拷贝构造函数

    下面这段代码有什么问题？
    ```
    class A
    {
        private:
            int m;
        public:
            A() { m=10; }
            A(A other) { m = other.m; }
    };
    ```

    拷贝构造函数无法通过编译。原因是，实参给形参赋值的时候，又存在一个给调用拷贝构造函数的过程。因此必须要改成 const + 引用的形式。
    ```
    A(const A & other) { m = other.m; }
    ```

* 一个对象的空间布局（带有虚函数的）

* STL迭代器失效

    迭代器失效的原理
    ```
    vector<int> vi = {1,2,3};
    iter = vi.begin();
    vi.erase(iter);

    //由于iter已经失效，再使用的时候，迭代器已经失效了，无法使用。
    cout<<*iter<<endl;
    ```

    一般情况下，最容易造成迭代器失效的场景。
    安全的从vector里面删除某些元素。
    ```
    void delete_ele(vector<int> &vi,int delete_ele)
    {
        for (auto iter = vi.begin(); iter != vi.end(); )
        {
            if (*iter != delete_ele)
            {
                iter = vi.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    }

    int main()
    {
        vector<int> vi = { 1,2,3,3,5,3};
        delete_ele(vi, 3);


        return 0;
    }
    ```

    