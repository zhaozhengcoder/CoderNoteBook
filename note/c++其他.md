# c++ 一些乱七八糟的东西整理


* 看到一个来自知乎的问题，https://zhuanlan.zhihu.com/p/82895086

```
// Version 1, by-value copy name to the function.
void addName(std::string name) {
    names_.push_back(std::move(name));
}
 
// Version 2, provide two overloads, one with const reference, another with rvalue reference.
void addName(const std::string& name) {
    names_.push_back(name);
}
void addName(std::string&& name) {
    names_.push_back(std::move(name));
}
 
// Version 3, use universal reference to integrate lvalue reference and rvalue reference.
template<typename T>
void addName(T&& name) {
    names_.push_back(std::forward<T>(name));
}

作者：王金戈
链接：https://zhuanlan.zhihu.com/p/82895086
来源：知乎
著作权归作者所有，转载请联系作者获得授权。
```

这里没有最优解，版本2和版本3最节约性能，但可能会导致源码或二进制码体积较大，版本1最简洁，但会多出一个移动构造。取舍的关键在于具体的应用场景，假如对象的移动构造非常廉价，完全不耗费性能，那就选择版本1，否则就选择版本2或3。

说到这里，便又涉及到另一个问题，你是否清楚对象拷贝构造和移动构造的代价？对于自定义类，如果没有手动声明这些构造函数和赋值运算符，编译器会为我们自动生成。但编译器自动生成的这些函数长什么样？如果我们需要自定义这些函数，应该遵循什么规则？答案很繁琐，但我们必须逐一理清。