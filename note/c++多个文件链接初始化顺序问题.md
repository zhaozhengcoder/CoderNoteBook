# c++ 多个文件链接的时候非static变量初始化顺序问题

这是一个非常需要注意的坑，在多个文件链接的时候，文件a定义了test1对象，文件b定义了test2对象。那么，问题来了，test1对象先初始化，还是test2对象先初始化？

答：其实是不一定的。当然，这个可能没有问题，但是如果test2对象的初始化依赖于test1，或者是test1的对象依赖于test2，那么，问题就来了。举个例子，如果test1的初始化依赖于test2，但是编译器先初始化了test1，test1初始化的时候test2还没有初始化，那么test1的初始化就会失败。

举个例子：
show_code_here -> https://github.com/zhaozhengcoder/CoderNoteBook/tree/master/example_code/mult_file_no_static_obj_init

**这个问题出现在程序执行main函数之前，初始化“全局变量”(数据段的成员)之前，如果在代码里面出现了一个no-static变量的初始化依赖于另外一个，这个的代码估计是要除问题的，需要做检查。**


* 解决的办法

如果在程序中出现全局变量的初始化依赖问题，那么ok，不需要关心这个问题。如果在代码中，写了类似于**一个对象的初始化**依赖于**另外一个全局变量的对象**，那么就需要注意了。

解决的办法：

```
# 原来初始化对象的方法
# TEST test1 

# 修改办的创建对象的方法
TEST1 &get_test1_obj()
{
    static TEST1 test1;
    return test1;
}

# 这样如果需要访问一个对象的话，那么一定要通过访问这个函数
# 那么c++的机制可以保证访问函数的时候，static变量一定会函数被调用的时候初始化
```

show_code_here -> https://github.com/zhaozhengcoder/CoderNoteBook/tree/master/example_code/mult_file_no_static_obj_init/fix_bug_demo