# C++ 风格的类型转换

## 目录

* static_cast

    ```
    // 在基本数据类型之间转换
    // 在int和char 类型之间的转换
    int val = 80;
    char c = static_cast<char> (val);
    cout<<c<<endl;

    // 在float 和int 之间转换 
    int p = static_cast<int>(3.14);

    // void * 转换为 int *
    void * raw_memory = operator new (sizeof(int));
    int * p_int = static_cast<int *>(raw_memory);

    // int * 转换为 void *
    void * void_p = static_cast<int *>(&val);


    // 这个是我理解不了的地方，在基本指针类型之间的转换 int * 和 char * ，会无法通过编译
    int * p_val = &val;
    //char * p_c = static_cast<char *>(p_val);   //为什么会报错？
    char * p_c =(char *)p_val;
    cout<<*p_c<<endl;
    ```


* dynamic_cast