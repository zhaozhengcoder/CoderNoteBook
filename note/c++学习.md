# C++ 学习

## 目录

* [语法](#语法)
    * [extern](#extern关键字)
    * [初始化列表初始化](#初始化列表初始化)
    * [右值引用 / move / 移动构造函数 / 移动赋值函数](#右值引用)
    * [智能指针](#智能指针)
    * [函数指针](#函数指针)
    * [cpp11的语法糖](#cpp11的语法糖)
    * [cpp11的新特性](#cpp11的新特性)
    * [临时对象](#临时对象)
    * [作用域符号 : :](#作用域符号)
    * [宏，const，inline](#宏)
    * [一个对象的空间布局](#一个对象的空间布局)

---

## 关于C++ 

关于c++ 是一门什么样的语言，分享一篇我觉得写的很好的文章
http://www.cnblogs.com/miloyip/archive/2010/09/17/behind_cplusplus.html


## 语法

在这个地方，我罗列的一些内容是对我而言，比较容易忘记的，或者是掉过一些坑的东西。各个点之间也没有什么逻辑关系。

## 1. 理解extern关键字

思考一个问题，如何在main.cpp文件里面调用 fun.c 文件里面的func 函数？
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
如果对main.o 文件里面的符号表感兴趣，可以用nm命令来查看。

```
// 在很多工程代码里面的写法

#ifdef __cplusplus   //__cplusplus 是一个宏，在不同的c++标准的输出都不同  cout<<__cplusplus<<endl;
extern "C" {
#endif
    
int add(int x, int y);
    
#ifdef __cplusplus
}
#endif
```

当extern 修饰变量的时候，表示此变量在其他的编译单元中定义。

```
// module_a.cpp

extern int val;

int foo(int a)
{
    return val * a;
}
```

## 2. 使用初始化列表初始化

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

## 3. 右值引用

右值引用，是c++里面一个重要的特性。他解决的问题是：**延长临时对象的生命周期，避免对象拷贝的开销**。

从下面几个方面入手：

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

struct A {
    A(){
        cout<<"construct: "<<++g_constructCount<<endl;    
    }
    
    A(const A& a) {
        cout<<"copy construct: "<<++g_copyConstructCount <<endl;
    }

    ~A() {
        cout<<"destruct: "<<++g_destructCount<<endl;
    }
};

A GetA() {
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

class test {
public:
    test() {
        cout<<"construct"<<endl;
    }
    test(const test & t) {
        cout<<"copy construct"<<endl;
    }
    ~test() {
        cout<<"desconstruct"<<endl;
    }
};

test get_test() {  
    return test();
}

int main() {
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
    test && t1 = get_test();    // -std=c++11
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

    ```
    // 补充一个例子 
    vector<string> vi;
    string str1 = "hello world";
    string str2 = "hello cpp";

    vi.push_back(str1);
    cout<<str1<<endl;
    vi.push_back(move(str2));
    cout<<str2<<endl;           //st2的输出是空
    ```

## 4. 移动构造函数 / 移动赋值函数 
```
class Socket
{
    private:
        int _sockfd;
    public:
        explicit Socket(int sockfd);
        ~Socket();

        // 移动构造函数
        Socket(Socket && rhs) :Socket(rhs._sockfd)
        {
            cout << "Socket(Socket && rhs)" << endl;
            rhs._sockfd = -1;
        }

        // 移动赋值函数
        Socket& operator=(Socket&& rhs)
        {
            cout << "Socket& operator=(Socket&& rhs)" << endl;
            swap(rhs);
            return *this;
        }

        void swap(Socket& rhs)
        {
            cout << "void swap(Socket& rhs)" << endl;
            std::swap(_sockfd, rhs._sockfd);
        }
};


Socket::Socket(int sockfd):_sockfd(sockfd)
{
    cout << "Socket::Socket(int sockfd) fd : "<<sockfd<< endl;
}

Socket::~Socket()
{
    cout << "Socket::~Socket()" << endl;
    if (_sockfd > 0)
    {
        //int ret = ::close(_sockfd);
    }
}


int main()
{
    Socket s1(100);
    Socket s2(200);

    s1 = move(s2);
    Socket s4(move(s1));
    // Socket s5 = 100;   // explicit , error
    // Socket s6 = s5;    // no copy constructor , error

    return 0;
}
```

```
# 输出
Socket::Socket(int sockfd) fd : 100         # Socket s1(100); 的输出
Socket::Socket(int sockfd) fd : 200         # Socket s2(200); 的输出
Socket& operator=(Socket&& rhs)             # s1 = move(s2);  的输出
Socket::Socket(int sockfd) fd : 100         # Socket s4(move(s1)); 的输出 ，fd=100 是 Socket(Socket && rhs) :Socket(rhs._sockfd) 由这个产生的
Socket(Socket && rhs)
```

## 5. 完美转发 forward

在函数模板中，完全依照模板的参数的类型（即保持参数的左值、右值特征），将参数传递给函数模板中调用的另外一个函数。

## 6. 智能指针

这个写起来发现似乎比较多，单独开一个文件写吧。

> [c++智能指针](./c++智能指针.md)

## 7. 函数指针

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

c++11使用functional表示函数指针
```
#include <iostream>
#include <functional>
using namespace std;
int func(int)
{
    cout<<"int func(int)"<<endl;
}

int main()
{
    function<int(int)> func_work2 = func;
    func_work2(100);
    return 0;
}
```

c++11里面提供了bind的函数和placeholder的实现方式。

**绑定函数调用的参数的，它解决的需求是我们有时候可能并不一定能够一次性获得调用某个函数的全部参数，通过这个函数，我们可以将部分调用参数提前绑定到函数身上成为一个新的对象，然后在参数齐全后，完成调用。**
```
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <functional>

using namespace std;
using namespace std::placeholders;

int f(int val, int val2, int val3)
{
	cout << "int f(int val, int val2, int val3) : " <<val<<" , "<<val2<<" , "<<val3<< endl;
	return 100;
}

class TEST
{
public:
	void test_func(int val,int val2,int val3)
	{
		cout << "test_func : " << val << " , " << val2 << " , " << val3 << endl;
	}
};

int main()
{
	auto p_f = bind(f, 1, 2, 3);
	p_f();


	auto p_f2 = bind(f, _1, _2, _3);  //using namespace std::placeholders;
	p_f2(1, 2, 3);

	auto p_f3 = bind(f, 100, _1, _2);
	p_f3(10, 20);

	TEST test;
	auto p_f4 = bind(&TEST::test_func,test, _1, _2, _3);
	p_f4(10,20,30);

	return 0;
}

```


https://elloop.github.io/c++/2015-12-15/learning-using-stl-12-std-bind

## 8. cpp11的语法糖

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

* decltype 

    类型推导
    ```
    auto x = 100;
    auto y = 200;

    decltype(x+y) z = 300;   //decltype(x+y) 推到x+y的类型，然后用这个类型定义z
    cout<<z<<endl;
    ```

* lambda
    ```

    ```

## 9. cpp11的其他新特性

* 占位符和bind函数 

    https://blog.csdn.net/zhangxiangDavaid/article/details/43638747
    ```
    #include <iostream>
    #include <functional>
    using namespace std;
    using namespace std::placeholders;
    
    int main()
    {
        auto fun = [](int *array, int n, int num){
            for (int i = 0; i < n; i++)
            {
                if (array[i] > num)
                    cout << array[i] << ends;
            }
            cout << endl;
        };
        int array[] = { 1, 3, 5, 7, 9 };
        //_1，_2 是占位符
        auto fun1 = bind(fun, _1, _2, 5);
        //等价于调用fun(array, sizeof(array) / sizeof(*array), 5);
        fun1(array, sizeof(array) / sizeof(*array));
        
        return 0;
    }
    ```

* stl 增加的新容器

    unorder_map/set

* 增加跨平台的线程库

    c++11 线程库

## 10. 临时对象
c++ 里面的临时对象是不可见的 —— 他们不在堆上面创建，同时也没有名字，这样的对象就是临时对象。

常见的有两种：

1. 函数传递参数的时候，为了可以是函数调用成功，进行隐式类型转换产生的对象。

2. 函数返回对象时进行的隐式类型转换。


* 函数传递参数产生临时对象

第一个例子,看下面的这段代码：
```
void func(const string & str)
{
    cout<<"str"<<endl;
}

int main()
{
    char c_arr[] = "hello world";
    func(c_arr);
    

    return 0;
}
```

为什么c_arr 可以作为参数，去调用func呢？func的形参的类型是const string & , 实参是 char * c_arr 。

这里就会在调用的时候，发生一个类型的转换，产生一个临时的对象。

我猜测一下，编译器处理的过程：
```
// 这个temp应该是函数栈上面的临时对象
string temp = string(c_arr); 
const string & str = temp;
```

但是，如果去掉函数参数里面的const，就会出问题
```
//去掉了const ，编译器报错 
void func(string & str)
{
    cout<<"str"<<endl;
    str[0]='a';
}

int main()
{
    char c_arr[] = "hello world";
    func(c_arr);
    

    return 0;
}
```

为什么呢？

这个原因是，如果不是const，那么在语义上面是可以修改的。**这样就存在一个歧义，就是修改的是临时的对象，但是对原来的c_arr不会有作用的**。那么，编译器自然不会允许这样事情发生。所以，编译器就不会通过编译。

* 函数的返回值产生临时对象
```
A getA()
{
    A * get_a = new A();
    return get_a;
}

int main()
{
    A a = getA();
}

//
这里代码做的
1. 在getA里面 A temp = get_a;     //产生临时对象
2. A a = temp;                    //复制
3. temp.~A();                     //析构临时对象              

// 不过一般gcc/g++ 会把这种情况进行优化，来避免创建临时对象。
// g++ -fno-elide-constructors 好像是这个参数可以关闭
```

## 11. 作用域符 ::

1. global scope (全局作用域符），用法（::name)

2. class scope (类作用域符），用法(class::name)

3. namespace scope (命名空间作用域符），用法(namespace::name)

## 12. 宏

宏，const，inline的区别在《effective c++》里面的第一部分就由提到。
但是，我的学习顺序是 先学习了c++，然后再看了c。我会更习惯于用const，inline，而不是宏。

关于宏函数的例子：
https://github.com/zhaozhengcoder/CoderNoteBook/blob/master/example_code/cpp/macro.cpp


另外一个《effective c++》里面没有讲的区别是，inline是一个请求，对编译器提出优化的请求。但是，编译器不一定会满足它。所以，这里就存在一个负优化的概念。对比说，一个函数无法确定需要不需要inline，那么最好不要自作聪明的加上inline，这样是因为编译器可以对需要被inline的函数自动加上inline，但是如果一个函数本身不需要inline，但是被加上inline，那么编译器很难去判断把inline变成非inline。

优点：

减少函数调用开销

缺点：

增加函数体积，exe太大，占用CPU资源，可导致cache装不下(减小了cache的命中) ，不方便调试。debug模式下编译器一般不内联（也可以手动调整参数）， 每次修改会重新编译头文件增加编译时间 （经过进一步学习后这一条也不准确）注意:inline只是一个请求，编译器有权利拒绝。有7种情况下都可能会拒绝，虚调用，体积过大，有递归，可变数目参数，通过函数指针调用，调用者异常类型不同，declspec宏等（这里描述不严谨，现代编译器会有更多的方式去采用inline去优化，比如虚调用也可能会被内联） 

forceinline字面意思上是强制内联，一般可能只是对代码体积不做限制了，但是对于上面的那些情况仍然不会内联，如果没有内联他会返回一个警告。 构造函数析构函数不建议内联，里面可能会有编译器优化后添加的内容，比如说初始化列表里面的东西。

>作者：Jerish
链接：https://zhuanlan.zhihu.com/p/47869981
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。


## 13. 比较重要的零散的东西

* 拷贝构造函数为什么需要是const

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

## 一个对象的空间布局

    > [c++多态和虚函数](./c++的多态和虚函数.md)
    