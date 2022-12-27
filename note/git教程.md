# Git 

## Git VS SVN

1. Git 属于分布式版本控制系统，而 SVN 属于集中式。


2. 集中式版本控制只有中心服务器拥有一份代码，而分布式版本控制每个人的电脑上就有一份完整的代码。

3. 集中式版本控制有安全性问题，当中心服务器挂了所有人都没办法工作了。

4. 集中式版本控制需要连网才能工作，如果网速过慢，那么提交一个文件的会慢的无法让人忍受。而分布式版本控制不需要连网就能工作。

5. 分布式版本控制新建分支、合并分支操作速度非常快，而集中式版本控制新建一个分支相当于复制一份完整代码。

6. 中心服务器用来交换每个用户的修改，没有中心服务器也能工作，但是中心服务器能够 24 小时保持开机状态，这样就能更方便的交换修改。**Github 就是一个中心服务器。**

---

## Git

Git 里面又三个概念：分别是工作区，暂存区，和版本库。

1. 工作区：就是你在电脑里能看到的目录。

2. 暂存区：英文叫stage, 或index。一般存放在 ".git目录下" 下的index文件（.git/index）中，所以我们把暂存区有时也叫作索引（index）。

3. 版本库：工作区有一个隐藏目录.git，这个不算工作区，而是Git的版本库。


下面这个图展示了工作区、版本库中的暂存区和版本库之间的关系：
![tu](../pic/git_6.JPG)

---

提交的流程是比较简答的，整理一下**回滚的流程**。

搞明白要回滚的内容处于哪个状态。

1. 修改后 未git add

    * git checkout -- file         // 回滚单个文件

    * git checkout .               // 回滚全部

2. 修改后 git add，未commit

    * git reset HEAD file          

        // 回滚单个文件
        
        // 这里的回滚流 指的是从版本库用head版本去覆盖stage区

        // 对于这个文件的内容，它是没有变化的，只是文件的状态改变了（相当于去掉 git add状态）
        
        // 如果想回滚文件的内容，那么再次使用git checkout -- file

    * git reset HEAD . 

        // 回滚全部

        // 这里的回滚流 指的是从版本库用head版本去覆盖stage区

3. 修改后 git add，commit

    * reset 回滚：

        git reset commit-id --hard

        git reflog 

        // 查看回滚commit-id

    * revert 回滚：

        // 回滚会变成一次提交

        git reset commit-id 

---------

## 查看
```
git status
git status -s
git log
git log --stat
git reflog
```


## 分支管理

查看分支：
```
git branch
  dev
* master
```

创建分支：
```
git branch dev
```

切换分支：
```
git checkout dev
```

创建并且切换分支：
```
git checkout -b dev
```

合并分支：

```
# 如果要在master分支合并dev分支，那么在切换到master的分支之后，就可以合并dev分支
git merge dev
```

删除分支：
```
git branch -d (branchname)
```

## git diff

用git diff来找你当前工作目录和上次提交与本地索引间的差异。
```
git diff
```

## .gitignore

首先，在你的工作区新建一个名称为.gitignore的文件。
**然后，把要忽略的文件名填进去，Git就会自动忽略这些文件。**

不需要从头写.gitignore文件，GitHub已经为我们准备了各种配置文件，只需要组合一下就可以使用了。
所有配置文件可以直接在线浏览：https://github.com/github/gitignore

比如说，不想把a.out文件加入git,那么在.gitignore的文件里面的内容是：
```
*.o
*.out
```

## git的工具
```
# 很漂亮的图形的显示项目的历史
* sourcetree
```

## 参考

- [廖雪峰教程](https://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000)

- [cyc_git教程](https://github.com/CyC2018/CS-Notes/blob/master/docs/notes/Git.md)

- [runoob教程](http://www.runoob.com/git/git-workspace-index-repo.html)

- [具体的每一个git命令的使用](https://www.yiibai.com/git/git_diff.html)

  https://gist.github.com/285571052/72fe4e85290d170b9de4634b6ad8c082

  https://git-scm.com/book/zh/v2

- [关于远程仓库](https://www.jianshu.com/p/9685a56bdf7a)

更新一部分：

![tu](../pic/git_4.png)


![tu](../pic/git_5.png)


### 分支管理

merge表示的合并某一个分支到当前分支，**但是如果有冲突的话，需要收到解决冲突。**

|命令|内容|
|:---:|:---:|
|git merge dev  | #在当前分支和并dev分支|
|git checkout -b [branch-name]| 创建分支并且切换到这个分支|
|git branch -d [branch-name]|删除分支|



### reset命令

reset 一般指的是将版本库的内容撤回到暂存区。
但是，也可以加上--hard 之后，将版本库的内容直接撤回到workspace里面。


![tu](../pic/git_6.JPG)

| 命令 |  内容  |
|:---:|:---:|
|git reset -- test.txt    | 使用当前版本仓库里面的内容覆盖暂存区，用来覆盖最git add的内容| 
|git reset —hard [commit]	| 暂存区、工作区的内容都会被修改到与提交点完全一致的状态 |
|git reset --hard HEAD	|让工作区回到上次提交时的状态|
|git reset —soft [commit]|	只改变提交点，暂存区和工作目录的内容都不改变|


## checkout


## diff 

| 命令 |  内容  |
|:---:|:---:|
|git diff | 显示暂存区和工作区的差异|
|git diff [file-name]|显示某一个文件，暂存区和工作区的差异|
|git diff HEAD|显示工作区与当前分支最新commit之间的差异|


## fetch 