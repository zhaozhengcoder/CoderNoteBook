# 前置声明

举个例子

```
void func(DATA data,ADDRESS address)
{
    cout<<"func"<<endl;
}

int main()
{
    return 0;
}
```


```
# 只编译不链接
g++ -c test.cc -std=c++11

test.cc:6:11: error: variable or field ‘func’ declared void
void func(DATA data,ADDRESS address)
          ^
test.cc:6:11: error: ‘DATA’ was not declared in this scope
test.cc:6:21: error: ‘ADDRESS’ was not declared in this scope
void func(DATA data,ADDRESS address)
                    ^
```

错误的原因是，不知道DATA 和 ADDRESS 的实现。所以，并不知道 DATA 和 ADDRESS 的大小。


但是，如果改成指针或引用，加上DATA 和 ADDRESS的前置声明，就可以了。

```
#include <iostream>
#include <memory>
#include <string>
using namespace std;

// 前置声明
class DATA;
class ADDRESS;

// 改成指针或引用
void func(DATA * data,ADDRESS * address)
{
    cout<<"func"<<endl;
}

int main()
{

    return 0;
}
```


```
# 只编译不链接
g++ -c test.cc -std=c++11
```

* 分析

    因为，对于编译器来说，如果不是一个指针的话
        
    ```
    DATA data;
    ```
    那么，编译器并不知道DATA的大小，没有办法给他分配空间。但是，如果改成指针，

    ```
    DATA * p_data;
    ```

    这样，对于编译器来说，它并不需要知道DATA的大小，只需要知道这是一个指针，给它分配4个字节就好。


* 补充

    《effective c++》 里面也提到了这一点，通过使用指针 和 引用方式，来将文件之间的编译的依赖关系降到最低。