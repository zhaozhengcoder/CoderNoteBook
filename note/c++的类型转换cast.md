# C++ 风格的类型转换

## 目录

* static_cast

    ```
    // 在int和char 类型之间的转换
    int val = 80;
    char c = static_cast<char> (val);
    cout<<c<<endl;

    int * p_val = &val;
    //char * p_c = static_cast<char *>(p_val);   //为什么会报错？
    char * p_c =(char *)p_val;
    cout<<*p_c<<endl;
    ```


* dynamic_cast