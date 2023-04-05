# CMAKE 教程

* 一个最简单的例子

    目录结构
    ```
    .
    ├── CMakeLists.txt
    └── main.cc

    0 directories, 2 files
    ```

    main.cc
    ```
    #include <stdio.h>

    int main (int argc, char *argv[])
    {
        printf("ok \n");
        return 0;
    }
    ```

    CMakeLists.txt
    ```
    PROJECT(main)          # 名称是 PROJECT ,参数是 main ,该命令表示项目的名称是 main
    CMAKE_MINIMUM_REQUIRED(VERSION 2.6)  # 第二行的命令限定了 CMake 的版本
    AUX_SOURCE_DIRECTORY(. DIR_SRCS)     # AUX_SOURCE_DIRECTORY 将当前目录中的源文件名称赋值给变量 DIR_SRCS
    ADD_EXECUTABLE(main ${DIR_SRCS})     # 源文件需要编译 成一个名称为 main 的可执行文件
    ```

    ```
    cmake .      # 注意 这里有一个点 . , 这个指明了CMakeLists.txt 文件的路径
    make         # make
    ```

* Step 2 处理多源文件目录的方法

    ```
    .
    ├── CMakeLists.txt
    ├── main.cc
    └── src
        ├── CMakeLists.txt
        ├── test1.cc
        └── test1.h

    1 directory, 5 files
    ```

    main.cc 文件
    ```
    #include <stdio.h>
    #include "./src/test1.h"

    int main (int argc, char *argv[])
    {
        int val = test();
        printf("ok , val [%d] \n",val);
        return 0;
    }
    ```

    test1.cc
    ```
    int test()
    {
        return 1;
    }
    ```

    test1.h
    ```
    int test();
    ```

    CMakeLists.txt
    ```
    PROJECT(main)
    CMAKE_MINIMUM_REQUIRED(VERSION 2.6) 
    ADD_SUBDIRECTORY( src )
    AUX_SOURCE_DIRECTORY(. DIR_SRCS)
    ADD_EXECUTABLE(main ${DIR_SRCS})
    TARGET_LINK_LIBRARIES(main Test)
    ```

    src/CMakeLists.txt
    ```
    AUX_SOURCE_DIRECTORY(. DIR_TEST1_SRCS)
    ADD_LIBRARY (Test ${DIR_TEST1_SRCS})
    ```


    ```
    # 执行
    cmake .   #在执行 cmake 的过程中,首先解析目录 step2 中的 CMakeLists.txt ,当程序执行命令 ADD_SUBDIRECTORY( src ) 时进入目录 src 对其中的 CMakeLists.txt 进行解析。
    make
    ```

* 参考

    翻译自 https://cmake.org/cmake-tutorial/ 

    https://www.ibm.com/developerworks/cn/linux/l-cn-cmake/index.html
