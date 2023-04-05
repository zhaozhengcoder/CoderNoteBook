# C++ 风格的类型转换

## 目录

## static_cast

*   用于类层次结构中基类（父类）和派生类（子类）之间指针或引用的转换。

    进行上行转换（把派生类的指针或引用转换成基类表示）是安全的；
　　

    进行下行转换（把基类指针或引用转换成派生类表示）时，由于没有动态类型检查，所以是不安全的。
　　
* 用于基本数据类型之间的转换，如把int转换成char，把int转换成enum。这种转换的安全性也要开发人员来保证。
　　
* 把空指针转换成目标类型的空指针。
　　
* 把任何类型的表达式转换成void类型。

----

比如：

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


static_cast 相比较于c风格的类型转换，编译器自带了一些语法检查。比如int * 指针 转换为char * 指针，显然是不科学的。编译器会报错。
```
// 这个是我理解不了的地方，在基本指针类型之间的转换 int * 和 char * ，会无法通过编译
int * p_val = &val;
//char * p_c = static_cast<char *>(p_val); 
char * p_c =(char *)p_val;
cout<<*p_c<<endl;
```



同样的问题，不同的自定义结构体指针，也是不允许装换的。编译器会报错。如果真的想要转换的话，可以先转换为void * ，然后再转换为dst *。
    
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

---

## dynamic_cast

static_cast 在下行检查的时候（把基类指针或引用转换成派生类表示）时，由于没有动态类型检查，所以是不安全的。

dynamic_cast是可以在运行的时候，进行动态检查。检查需要运行时信息RTTI，而RTTI存储在虚函数表中。

[C++的对象布局](
https://mp.weixin.qq.com/s?__biz=MzkyODE5NjU2Mw==&mid=2247484758&idx=1&sn=4e614430f666f63ab135c13a716d07c1&source=41#wechat_redirect)

----

## const_cast 
用于常量指针或引用与非常量指针或引用之间的转换，只有const_cast才可以对常量进行操作，一般都是用它来去除常量性，去除常量性是危险操作，还是要谨慎操作。

---

## reinterpret_cast
没啥场景，类似C语言中的强制类型转换，什么都可以转，万不得已不要使用，一般前三种转换方式不能解决问题了使用这种强制类型转换方式。

-----

## 参考

https://mp.weixin.qq.com/s/6YW7VX787X7kZiRBLbVn-Q

https://blog.csdn.net/wangshubo1989/article/details/49105627