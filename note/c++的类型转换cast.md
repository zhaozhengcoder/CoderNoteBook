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

    ```

    **这个是我理解不了的地方 :**
    ```
    // 这个是我理解不了的地方，在基本指针类型之间的转换 int * 和 char * ，会无法通过编译
    int * p_val = &val;
    //char * p_c = static_cast<char *>(p_val);   //为什么会报错？
    char * p_c =(char *)p_val;
    cout<<*p_c<<endl;
    ```

    同样的问题：
    
    ```
    struct sockaddr
    {
        unsigned short    sa_family;        // 2 bytes address family, AF_xxx  
        char              sa_data[14];      // 14 bytes of protocol address  
    };

    // IPv4 AF_INET sockets:  
    struct sockaddr_in
    {
        short            sin_family;       // 2 bytes e.g. AF_INET, AF_INET6  
        unsigned short   sin_port;         // 2 bytes e.g. htons(3490)  
        //struct in_addr   sin_addr;         // 4 bytes see struct in_addr, below  
        int				sin_addr;
        char             sin_zero[8];      // 8 bytes zero this if you want to  
    };

    int main()
    {

        sockaddr_in addr;
        
        //不报错
        //void * pp = (void *)(&addr);   // 不报错
        void * pp = static_cast<void *>(&addr);
        sockaddr * p = static_cast<struct sockaddr *>(pp);
    
    
        //报错
        //同样的原因，我也不知道为什么
        sockaddr * p = static_cast<sockaddr *>(&addr); 
    }
    ```

    c语言的写法，进行类型转换，但是上面用static_cast 进行类型转换，就有问题 : 
    ```
    int sockfd;  
    struct sockaddr_in servaddr; 
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);  
    
    /* 填充struct sockaddr_in */  
    bzero(&servaddr, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(SERV_PORT);  
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);  
    
    /* 强制转换成struct sockaddr */  
    connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));  
    ```


* dynamic_cast