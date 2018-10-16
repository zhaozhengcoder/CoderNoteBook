# C++ 面向对象

## 目录

* [如何设计一个不可拷贝的类](#如何设计一个不可拷贝的类)

* [如何设计一个不可继承的类](#如何设计一个不可继承的类)


---

## 如何设计一个不可拷贝的类
```
class nocopy
{
public:
    nocopy(nocopy & rhs) = delete;
    void operator=(const noncopyable& rhs) = delete;
};
// =delete 是c++11 的新特性，表示 https://www.ibm.com/developerworks/cn/aix/library/1212_lufang_c11new/index.html

class TEST: public nocopy
{
    // ...
};

```

设计一个nocopy的类，在这里类里面，禁用拷贝和赋值的构造函数。对于不可拷贝的类，直接继承这个类就好。 （muduo的代码里面是这样设计的）


## 如何设计一个不可继承的类 

* plan 1

    c++11 里面提供了final的关键字，加上这个一个类就可以被继承了。
    ```
    class A final
    {
    public:
        A()
        {
            cout << "a()" << endl;
        }
    };

    class test :public A    // 报错 A  无法继承
    {
    public:
        test()
        {
            cout << "test()" << endl;
        }
    };
    ```

* plan 2

    如果不可以用final，那我第一个反应就是，单例模式的设计思想，将构造函数设计成一个私有函数。这个派生类就无法继承积累的构造函数，也就无法继承这个类了。

    ```
    class A
    {
    public:
            static A * Construct(int  n)
            {
                    A *pa = new A;
                    pa->num = n;
                    cout << "num  is:" << pa->num << endl;
                    return pa;
            }
            static void Destruct(A * pIntance)
            {
                    delete  pIntance;
                    pIntance = NULL;
            }

    private:
            A() {}
            ~A() {}

    public:
            int num;
    };

    class B : public A
    {
    public:
            B()
            {
                    cout << "B()" << endl;
            }
    };
    ```
    
    编译的错误提示：(这样继承的行为就会报错)
    ```
    g++ test_class.cc
    test_class.cc: In constructor ‘B::B()’:
    test_class.cc:23:2: error: ‘A::A()’ is private
    A() {}
    ^
    test_class.cc:34:2: error: within this context
    {
    ^
    test_class.cc:24:2: error: ‘A::~A()’ is private
    ~A() {}
    ^
    test_class.cc:34:2: error: within this context
    {
    ^
    ```

    但是，这样的方式有一个缺点，就是改变创建基类对象的行为。比如，
    ```
    A a;   #报错
    ```

    只能通过这种方式来创建，（也就是分配再堆上面）
    ```
    A * p = A::Construct(10);
    ```

* plan 3 

    使用友元类实现，设计一个基类base，把需要设计的无法继承的类FinalClass，声明成为它的友元类。

    ```
    class Base
    {
    private:
        Base() {}
        ~Base() {}
        friend class FinalClass;
    };


    // 这个finial class 是无法继承的
    class FinalClass : virtual public Base
    {
    };

    // FinalClass 是Base的友元，因此FinalClass可以访问Base中设置为private的构造函数和析构函数，因此FinalClass可以被构造
    // 如果有某个类X尝试去继承FinalClass，那么X在构造的时候必须要构造Base，并且由于是FinalClass是虚拟继承自Base，
    // X不能通过FinalClass的构造函数来构造Base，它必须直接构造Base，但是由于Base的构造函数是private的，所以X不能被构造


    int main()
    {
        
        FinalClass  *p = new FinalClass;  //堆上对象 ， ok
        FinalClass  fs;                   //栈上对象 ， ok
    
        return 0;
    }
    ```

    如果有一个类，要继承finalclass的话，就会报错。
    ```
    class test :public FinalClass
    {
    public:
        test()
        {
            cout << "test()" << endl;
        }
    };
    ```
