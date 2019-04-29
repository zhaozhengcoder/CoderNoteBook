# vscode 插件

使用vscode开发c/c++,推荐的一些插件。

* c/c++

* c++ intellisense 

* Chinese (Simplified) Language Pack

* C/C++ GNU Global 

    **有的时候vscode会出现F12无法跳转的情况**，解决的办法：

    1. 安装 C/C++ GNU Global 

    2. 安装 gtags

        下载 ： http://adoxa.altervista.org/global/  ，下载win32的版本

        然后，解压缩，可以看到里面包含 3 个文件夹。我们需要把三个文件夹统一移动到 VSCode 的安装目录下。

        然后，将 xxx\glo656wb\bin 加入环境变量。

* YouCompleteMe , vscode-youcompleteme

    自动补全代码的插件


* 使用Clang-format格式化代码

    这个首先要手动安装一个llvm的东西，然后配置好环境变量。

    "clang-format.executable": "C:/Program Files/LLVM/bin/clang-format.exe"

    这个需要格式化的时候，点击右键->格式化文件，代码就格式化了。


* vscode 还有一个功能就是把 cmd 窗口 连接到里面，这样就可以不用切换窗口了。

    https://www.canftin.com/2018/VSCode%E5%9C%A8WSL%E4%B8%8B%E7%9A%84c-c-%E7%8E%AF%E5%A2%83%E9%85%8D%E7%BD%AE/

* One Dark Pro 

    我很喜欢的颜色主题

---

* Setting Sync 

    这个插件可以帮助在不同的机器同步vscode的配置

* Project Manager

    用来管理工程，可以方便的实现工程切换。

* Bookmarks

    用来标记代码，可以全局跳转，非常方便。

---

* vscode 隐藏文件/文件夹
    ```
        "files.exclude": 
        {
            "**/.git": true,
            "**/.svn": true,
            "**/*.pyc": true
        }
    ```

* 我的vscode的setting.json的配置 : 
    ```
    {
        "terminal.integrated.shell.windows": "C:\\WINDOWS\\System32\\bash.exe",
        "git.autofetch": true,
        "clang-format.executable": "clang-format",
        "workbench.colorTheme": "One Dark Pro",
        //"editor.formatOnSave": true
        "clang.cxxflags": [
            "-IC:\\Users\\wwwa8\\Documents\\GitHub\\muduo\\build\\release-install\\include"
        ]
    }
    ```

    ```
    {
        "editor.fontSize": 15,
        "extensions.ignoreRecommendations": true,
        "http.proxy": "http://web-proxy.tencent.com:8080",
        "files.encoding": "gb2312",
        "search.location": "panel",
        "php.suggest.basic": false,
        "php.executablePath": "C:\\Program Files\\php\\php.exe",
        "php.validate.executablePath": "C:\\Program Files\\php\\php.exe",
        "php-cs-fixer.executablePath": "C:\\Program Files\\php\\php-cs-fixer.phar",
        "editor.formatOnSave": true,
        
        // tab = 4 空格，以及显示tab 
        "editor.detectIndentation": false,
        "editor.tabSize": 4,
        "editor.renderControlCharacters": true,
        "editor.renderWhitespace": "all",
        "editor.fontFamily": "Consolas, 'Menlo', Menlo",
        "editor.formatOnPaste": false,
        
        // "workbench.activityBar.visible": false,
        "workbench.iconTheme": "material-icon-theme",
        "workbench.colorCustomizations": {},
        "materialTheme.cache.workbench.settings": {
            "themeColours": "Darker",
            "accentPrevious": "Acid Lime"
        },
        "editor.lineHeight": 24,
        "sync.gist": "5de3d3f39269386af3048d7d502add0e",
        "workbench.colorTheme": "Monokai Seti",
    }
    ```


---

* 参考 ： 

    1. https://fallenwood.github.io/2016/05/24/configuring-visual-studio-code/


    2. https://blogs.msdn.microsoft.com/c/2016/04/18/visual-studio-code%E7%9A%84cc%E6%89%A9%E5%B1%95%E5%8A%9F%E8%83%BD/


    3. 30个极大提高开发效率的VSCode插件 ： https://zhuanlan.zhihu.com/p/40417719


    4. 按f12无法跳转的原因 ： https://blog.csdn.net/danxibaoxxx/article/details/81289651 

        不过这样需要 ctrl+shift+c ,然后运行gtags 

    5. https://jasper-1024.github.io/2018/03/24/Vscode%E7%B3%BB%E5%88%97-c%E8%AF%AD%E8%A8%80/
