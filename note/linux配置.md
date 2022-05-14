## linux 配置

## 目录
* [linux产生core文件](#linux产生core文件)
* [zsh](#zsh)

---

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

## zsh
```
# 1. 安装zsh
yum -y install zsh

# 切换sh
chsh -s /bin/zsh

# 安装oh-my-zsh
sh -c "$(curl -fsSL https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"

# 安装zsh插件
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting

git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions

# 在vim ~/.zshrc添加插件
plugins=(
        git
        zsh-autosuggestions
        zsh-syntax-highlighting
)

# 
source ~/.zshrc 
```

