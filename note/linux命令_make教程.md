# Make 构建工具

## 基本规则

* make的规则是
    ```
    <target> : <prerequisites> 
    [tab]  <commands>

    # target 表示目标
    # prerequisites 表示前置条件
    ```
* 变量
    * 定义变量
        ```
        cc = g++
        output:p1.txt p2.txt
            $(cc) -o ouput test_cast.cpp
        ```
    * 调用shell的变量
        调用shell变量，需要加上两个$$
        ```
        test:
            echo $$HOME
        ```

* 自动变量
    * $@  

        $@ 指代**当前目标**，就是Make命令当前构建的那个目标。
        ```
        a.txt:
            touch $@
        
        # 约等于 
        a.txt:
            touch a.txt
        ```

    * $< 指代**第一个前置条件**。比如，规则为 t: p1 p2，那么$< 就指代p1。

        ```
        a.txt:p1.txt p2.txt
            touch $<
        ```

    * $^ 指代**所有前置条件**
        ```
        比如，规则为 t: p1 p2，那么 $^ 就指代 p1 p2 。
        ```

* 函数

    * wildcard 函数
        ```
        srcfiles := $(wildcard src/*.txt)
        ```

        一个目录下面所有的.c 文件
        ```
        src = $(wildcard *.c ./sub/*.c)
        ```

## 简单的例子

来自于muduo的make文件
```
# 举一个例子
MUDUO_DIRECTORY ?= $(HOME)/code_test/muduo/build/release-install
#MUDUO_DIRECTORY ?= $(HOME)/build/install
MUDUO_INCLUDE = $(MUDUO_DIRECTORY)/include
MUDUO_LIBRARY = $(MUDUO_DIRECTORY)/lib
SRC = ./

CXXFLAGS = -g -O0 -Wall -Wextra -Werror \
	   -Wconversion -Wno-unused-parameter \
	   -Wold-style-cast -Woverloaded-virtual \
	   -Wpointer-arith -Wshadow -Wwrite-strings \
	   -march=native -rdynamic \
	   -I$(MUDUO_INCLUDE)

LDFLAGS = -L$(MUDUO_LIBRARY)  -lmuduo_net  -lmuduo_base -lpthread -lrt

# lmuduo_inspect 
all: hub sub pub
clean:
	rm -f hub core

hub: $(SRC)/hub.cc codec.cc
	g++ $(CXXFLAGS) -o $@ $^  $(LDFLAGS)

sub: $(SRC)/sub.cc codec.cc pubsub.cc
	g++ $(CXXFLAGS) -o $@ $^  $(LDFLAGS)

pub: $(SRC)/pub.cc codec.cc pubsub.cc
	g++ $(CXXFLAGS) -o $@ $^  $(LDFLAGS)

.PHONY: all clean
```

* 其他
    >[makefile自动推导](https://www.jianshu.com/p/27070bbcba4d)

    