# C/C++ 

## IO标准库

* 缓冲
    
    标准io库提供缓冲的目的是为了尽可能的减少调用read 和 write 的次数。于是，标准io库提供了缓冲的机制。标准io库的缓冲机制分为三种：

    * 全缓冲

        全缓冲表示直到写满缓冲区的时候，才进行实际的io操作。

    * 行缓冲

        行缓冲表示遇到/n就进行fflush的操作，或者是达到了行缓冲的大小，就执行fflush（好像默认是1024）。这个是stdin 和 stdout的默认操作行缓冲。

    * 不带缓冲

        不缓冲就是不缓冲。stderr就是不缓冲。
    
    （这个说的stdin，stdout 是行缓冲 指的是他们默认连接至终端）

* 关于 stdin , stdout , stderr

    stdin，stdout，stderr默认是连接至终端，也就是从终端获取输入和输出。但是也可以通过重定向修改默认的路径。

    ```
    ./a.out < /etc/passwd  > std.out 2>std.err

    # 这个表示 
    # stdin 是从 /etc/passwd 获得输入
    # stdout 输出道std.out 文件里面
    # stderr 输出道std.err 文件里面
    ```

    如果stdin，stdout被重定向到文件，那么它们就变成全缓冲了。

    

