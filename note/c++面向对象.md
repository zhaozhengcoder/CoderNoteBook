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

c++11 引入了final的关键字，在设计一个类的时候，如果不想让这个类被继承，可以在后面加上final的关键字。
```
class TEST final{};
```