## linux 配置

## 目录


## linux产生core文件

1. 修改corefile文件的大小
    ```
    vi /etc/profile
    然后再文件里面添加一句
    ulimit -c unlimited

    source /etc/profile  #使配置生效
    ```

    ```
    ulimit -c unlimited
    # 查看
    # 这个时候，已经会产生core文件了
    ```

2. 修改配置
    ```
    sudo su root
    sudo /sbin/sysctl -w kernel.core_pattern=core-%e-%p-%t
    ```

    ```
    # 查看
    cat /proc/sys/kernel/core_pattern
    core-%e-%p-%t
    ```

## linux更换源
```
```

