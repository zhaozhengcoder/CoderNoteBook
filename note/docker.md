# docker 入门

## 目录


## docker的优点&安装

## 基本使用

* 查看
```
docker image ls

docker ps

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

1. https://yeasy.gitbooks.io/docker_practice/image/pull.html

2. https://www.jianshu.com/p/3384e342502b

3. https://www.yuque.com/grasilife/docker
