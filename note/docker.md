# docker 入门

## 目录

---
## docker简介

### docker简介和优点

### docker的几个概念

* 镜像（image）

* 容器（container）

    镜像（Image）和容器（Container）的关系，**就像是面向对象程序设计中的 类 和 实例 一样，镜像是静态的定义，容器是镜像运行时的实体。**容器可以被创建、启动、停止、删除、暂停等。


    前面讲过镜像使用的是分层存储，容器也是如此。**每一个容器运行时，是以镜像为基础层，在其上创建一个当前容器的存储层，我们可以称这个为容器运行时读写而准备的存储层为容器存储层。**

* 仓库（repository）

---

## 基本使用

### 1. 获取镜像

Docker Hub 上有大量的高质量的镜像可以用，这里我们就说一下怎么获取这些镜像。

从 Docker 镜像仓库获取镜像的命令是 docker pull。其命令格式为：
```
docker pull [选项] [Docker Registry 地址[:端口号]/]仓库名[:标签]
```

具体的选项可以通过 docker pull --help 命令看到，这里我们说一下镜像名称的格式。

* Docker 镜像仓库地址：地址的格式一般是 <域名/IP>[:端口号]。默认地址是 Docker Hub。
* 仓库名：如之前所说，这里的仓库名是两段式名称，即 <用户名>/<软件名>。对于 Docker Hub，如果不给出用户名，则默认为 library，也就是官方镜像。

---

### 2. 运行

* 查看
```
docker image ls

docker ps

docker ps -a

docker stats
```

* pull
```
docker pull ubuntu:16.04
```

* run 
```
docker run -it --rm ubuntu:16.04 bash

-it：这是两个参数，一个是 -i：交互式操作，一个是 -t 终端。
我们这里打算进入 bash 执行一些命令并查看返回结果，因此我们需要交互式终端。

--rm：这个参数是说容器退出后随之将其删除。
默认情况下，为了排障需求，退出的容器并不会立即删除，除非手动 docker rm。
我们这里只是随便执行个命令，看看结果，不需要排障和保留结果，因此使用 --rm 可以避免浪费空间。

ubuntu:16.04：这是指用 ubuntu:16.04 镜像为基础来启动容器。

bash：放在镜像名后的是命令，这里我们希望有个交互式 Shell，因此用的是 bash
```

* 启动/重新启动某一个容器
```
docker stop/restart [name]
```

* 例子

安装和运行nginx
```
C:\Users\wwwa8>docker image ls
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
bitnami/php-fpm     latest              959ab149486d        4 hours ago         244MB
nginx               latest              568c4670fa80        3 days ago          109MB
ubuntu              16.04               a51debf7e1eb        11 days ago         116MB


# 运行
docker run -d --name=my_nginx -p 8888:80 nginx

# 查看
docker ps
CONTAINER ID        IMAGE               COMMAND                  CREATED             STATUS              PORTS                  NAMES
13380cc93176        nginx               "nginx -g 'daemon of…"   2 minutes ago       Up 2 minutes        0.0.0.0:8888->80/tcp   my_nginx
dd5b26affce3        nginx               "bash"                   26 minutes ago      Up 26 minutes       80/tcp                 vibrant_clarke

# 可以从本地的浏览器的8888端口看一下nginx的服务


# 进入nginx内部
docker exec -it my_nginx bash
```





## 参考

- [docker 入门到实践](https://yeasy.gitbooks.io/docker_practice/image/pull.html)

- [使用Docker快速搭建Nginx+PHP-FPM环境](https://www.jianshu.com/p/3384e342502b)
