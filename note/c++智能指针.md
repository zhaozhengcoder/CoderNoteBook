# C++ 智能指针

## 目录

* [智能指针的基本概念](#智能指针的基本概念)

* [智能指针的基本用法](#智能指针的基本用法)

* [其他](#其他)

---

## 智能指针的基本概念

1. 为什么要使用智能机制？

* 解决new之后，需要手动delete

* 异常安全
    ```
    void process()
    {
        Widget* w = new Widget();
        w->do_something(); // 可能会发生异常
        delete w;
    }
    ```

    在正常流程下，我们会在函数末尾 delete 创建的对象 w，正常调用析构函数，释放内存。

    但是如果 w->do_something() 发生了异常，那么 delete w 将不会被执行。此时就会发生 内存泄漏。
    我们当然可以使用 try…catch 捕捉异常，在 catch 里面执行 delete，但是这样代码上并不美观，也容易漏写。

    如果我们用 std::unique_ptr，那么这个问题就迎刃而解了。无论代码怎么抛异常，在 unique_ptr 离开函数作用域的时候，内存就将会自动释放。

2. 什么场景下，应该什么什么样的指针？ shared_ptr, weak_ptr, unique_ptr 

    这三种语义是不一样的，要看new出来的内存的管理权。unqiue ptr表示的是唯一的管理权，shared ptr表示是共享的管理权。

    所以，unique ptr 没有提供拷贝的接口，只有移动的接口。 

    有的时候写代码的时候，可能会无脑使用shared ptr。如果这个内存资源没有共享的需求，那最好使用unique ptr。并且，unique ptr 的性能会高。（因为移动的语义比拷贝的语义更好）

    **使用场景**：

    * shared_ptr 通常使用在共享权不明的场景。有可能多个对象同时管理同一个内存时。

    * 对象的延迟销毁。陈硕在《Linux 多线程服务器端编程》中提到，当一个对象的析构非常耗时，甚至影响到了关键线程的速度。可以使用 BlockingQueue<std::shared_ptr<void>> 将对象转移到另外一个线程中释放，从而解放关键线程。

3. 为什么要使用weak ptr ？ 

    weak ptr 是 shared ptr的助手，解决的是 shared ptr 循环引用的问题。（weak ptr 也智能是 shared ptr的助手，不能用来做其他的）

    ** 智能指针如何解决循环引用问题**

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

4. 为什么要使用 enable_shared_from_this？ 

    当类A被share_ptr管理，且在类A的成员函数里需要把当前类对象作为参数传给其他函数时，就需要传递一个指向自身的share_ptr。这个时候用enable_shared_from_this 比较好。

    https://blog.csdn.net/caoshangpa/article/details/79392878

    正确的例子：
    ```
    #include <memory>
    #include <iostream>

    struct Good : std::enable_shared_from_this<Good> // 注意：继承
    {
    public:
        std::shared_ptr<Good> getptr() {
            return shared_from_this();
        }
        ~Good() { std::cout << "Good::~Good() called" << std::endl; }
    };

    int main()
    {
        // 大括号用于限制作用域，这样智能指针就能在system("pause")之前析构
        {
            std::shared_ptr<Good> gp1(new Good());
            std::shared_ptr<Good> gp2 = gp1->getptr();
            // 打印gp1和gp2的引用计数
            std::cout << "gp1.use_count() = " << gp1.use_count() << std::endl;
            std::cout << "gp2.use_count() = " << gp2.use_count() << std::endl;
        }
        system("pause");
    }
    ```

    错误的例子：
    ```
    #include <memory>
    #include <iostream>

    class Bad
    {
    public:
        std::shared_ptr<Bad> getptr() {
            return std::shared_ptr<Bad>(this);
        }
        ~Bad() { std::cout << "Bad::~Bad() called" << std::endl; }
    };

    int main()
    {
        // 错误的示例，每个shared_ptr都认为自己是对象仅有的所有者 
        // 造成2个非共享的share_ptr指向同一个对象，未增加引用计数导对象被析构两次。
        std::shared_ptr<Bad> bp1(new Bad());
        std::shared_ptr<Bad> bp2 = bp1->getptr();
        // 打印bp1和bp2的引用计数
        std::cout << "bp1.use_count() = " << bp1.use_count() << std::endl;
        std::cout << "bp2.use_count() = " << bp2.use_count() << std::endl;
    }  // Bad 对象将会被删除两次
    ```

    * enable_shared_from_this 实现的原理是什么？

        // todo , 基于weak_ptr

        // https://www.cnblogs.com/yang-wen/p/8573269.html

## 智能指针的基本用法

* shared_ptr
    接受指针作为参数的智能指针的构造函数是explicit类型，意味着只能以初始化的方式定义。
    ```
    shared_ptr<int> p1;
    //被初始化成为一个空指针

    shared_ptr<int> p2 (new int(4));
    //指向一个值是4的int类型数据

    shared_ptr<int> p3 = new int(4);
    //错误，必须直接初始化
    ```

    shared_ptr的一些操作
    ```
    shared_ptr<T> p;
    //空智能指针，可指向类型是T的对象

    if(p)
    //如果p指向一个对象,则是true

    (*p)
    //解引用获取指针所指向的对象

    p -> number == (*p).number;

    p.get();
    //返回p中保存的指针

    swap(p,q);
    //交换p q指针

    p.swap(q);
    //交换p,q指针

    make_shared<T>(args) 
    //返回一个shared_ptr的对象，指向一个动态类型分配为T的对象，用args初始化这个T对象
    shared_ptr<string> p1 = make_shared<string>(10, '9');  
    shared_ptr<string> p2 = make_shared<string>("hello");  
    shared_ptr<string> p3 = make_shared<string>(); 

    shared_ptr<T> p(q)
    //p 是q的拷贝，q的计数器++，这个的使用前提是q的类型能够转化成是T*

    p = q;
    //p的引用计数-1，q的+1,p为零释放所管理的内存

    p.unique();
    //判断引用计数是否是1，是，返回true

    p.use_count();
    //返回和p共享对象的智能指针数量
    ```

* weak_ptr
```
```

* unique_ptr
    ```
    unique_ptr<string> p(new string("China"));
    //没问题

    unique_ptr<string> p (q);
    //错误，不支持拷贝

    unique_ptr<string> q;

    q = p;
    //错误,不支持赋值
    ```

    unique_ptr的一些操作:
    ```
    unique_ptr<T> p;
    //空智能指针，可指向类型是T的对象

    if(p) 
    //如果p指向一个对象,则是true

    (*p)
    //解引用获取指针所指向的对象

    p -> number == (*p).number;

    p.get();
    //返回p中保存的指针

    swap(p,q);
    //交换p q指针

    p.swap(q);
    //交换p,q指针

    unique_ptr<T,D>p;
    //p使用D类型的可调用对象释放它的指针

    p = nullptr;
    //释放对象，将p置空

    p.release();
    //p放弃对指针的控制，返回指针，p置数空

    p.reset();
    //释放p指向的对象

    p.reset(q);
    //让u指向内置指针q
    ```

* weak ptr 
    weak ptr 并不执行raw Pointer，而是指向shared ptr。
    ```
    weak_ptr<T> w(sp);
    //定义一个和shared_ptr sp指向相同对象的weak_ptr w,T必须能转化成sp指向的类型

    w = p;
    //p是shared_ptr或者weak_ptr，w和p共享对象

    w.reset();
    //w置为空

    w.use_count();
    //计算与w共享对象的shared_ptr个数

    w.expired();
    //w.use_count()为0，返回true

    w.lock();
    //w.expired()为true，返回空shared_ptr,否则返回w指向对象的shared_ptr
    ```

## 其他 

* shared ptr的错误用法

    写一个错误的shared_ptr的使用例子：
    ```
    #include <iostream>
    #include <memory>
    using namespace std;

    struct Task
    {
        int mId;
        int *p;
        Task(int id) : mId(id)
        {
            p = new int[10];
            std::cout << "Task::Constructor" << std::endl;
        }
        ~Task()
        {
            std::cout << "p[1] : " << p[1] << std::endl;
            delete[] p;
            std::cout << "Task::Destructor" << std::endl;
        }
    };

    int main()
    {
        // 使用shared ptr 的问题
        {
            Task *task3 = new Task(333);
            shared_ptr<Task> p1(task3);
            shared_ptr<Task> p2(task3);   // core  

            // 原因p1 和 p2 都认为自己的引用计数是1，于是当自己声明周期结束的时候，去释放ptr。于是导致core

            // 这应该是c++智能智能被诟病的一个原因
        }

        // 改为unique ptr 就没有问题
        {
            Task *task2 = new Task(222);
            std::unique_ptr<Task> testPtr2(task2);
            std::cout << testPtr2->mId << std::endl;

            std::unique_ptr<Task> testPtr3(task2);
            std::cout << testPtr3->mId << std::endl;
        }
    }
    ```

* enable_shared_from_this 的实现 

    一个对象返回this指针，其实是无法确认这个对象是否是被智能指针管理的。这样就带来一个问题，如果没有办法确认，那么如果这个this对象被另外一个shared ptr管理。那么就会出现一个多个shared ptr 管理一个对象。 并且，每个shared ptr的use count 都是 = 1；

    那么，释放的时候，这个对象就会被释放多次。两个shared ptr各自释放一次。 

    ```
    #include <memory>
    #include <iostream>

    class Bad
    {
    public:
        std::shared_ptr<Bad> getptr() {
            return std::shared_ptr<Bad>(this);
        }
        ~Bad() { std::cout << "Bad::~Bad() called" << std::endl; }
    };

    int main()
    {
        // 错误的示例，每个shared_ptr都认为自己是对象仅有的所有者 
        // 造成2个非共享的share_ptr指向同一个对象，未增加引用计数导对象被析构两次。
        std::shared_ptr<Bad> bp1(new Bad());
        std::shared_ptr<Bad> bp2 = bp1->getptr();
        // 打印bp1和bp2的引用计数
        std::cout << "bp1.use_count() = " << bp1.use_count() << std::endl;
        std::cout << "bp2.use_count() = " << bp2.use_count() << std::endl;
    }  // Bad 对象将会被删除两次
    ```


---

附上一个《c++ 标准库》的例子 
```
作者：明月照我心
链接：https://zhuanlan.zhihu.com/p/72354412
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

 1 #include <iostream>
 2 #include <string>
 3 #include <vector>
 4 #include <memory>
 5 using namespace std;
 6 
 7 int main(void)
 8 {
 9     // two shared pointers representing two persons by their name
10     shared_ptr<string> pNico(new string("nico"));
11     shared_ptr<string> pJutta(new string("jutta"),
12             // deleter (a lambda function) 
13             [](string *p)
14             { 
15                 cout << "delete " << *p << endl;
16                 delete p;
17             }
18         );
19 
20     // capitalize person names
21     (*pNico)[0] = 'N';
22     pJutta->replace(0, 1, "J");
23 
24     // put them multiple times in a container
25     vector<shared_ptr<string>> whoMadeCoffee;
26     whoMadeCoffee.push_back(pJutta);
27     whoMadeCoffee.push_back(pJutta);
28     whoMadeCoffee.push_back(pNico);
29     whoMadeCoffee.push_back(pJutta);
30     whoMadeCoffee.push_back(pNico);
31 
32     // print all elements
33     for (auto ptr : whoMadeCoffee)
34         cout << *ptr << " ";
35     cout << endl;
36 
37     // overwrite a name again
38     *pNico = "Nicolai";
39 
40     // print all elements
41     for (auto ptr : whoMadeCoffee)
42         cout << *ptr << " ";
43     cout << endl;
44 
45     // print some internal data
46     cout << "use_count: " << whoMadeCoffee[0].use_count() << endl;
47 
48     return 0;
49 }

// 

1）对智能指针pNico的拷贝是浅拷贝，所以当我们改变对象“Nico”的值为“Nicolai”时，指向它的指针都会指向新值。　　

2）指向对象“Jutta”的有四个指针：pJutta和pJutta的三份被安插到容器内的拷贝，所以上述程序输出的use_count为4。
```

