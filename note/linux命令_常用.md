# Linux 命令

## 目录

* [alias](#alias)


## alias

设置alias

```
alias 别名='原命令 -选项/参数'

比如：
alias ll='ls -l --color=auto'
```

查看已经设置的别名列表
```
alias -p 
```

删除别名
```
unalias 别名
```

设置别名每次登入可用
在 ~/.bashrc 文件中 添加
```
source ~/.bashrc
```