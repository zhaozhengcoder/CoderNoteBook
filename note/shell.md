## shell脚本

## 目录
* [启动行参数解析](#启动行参数解析)
* [参数调用](#参数调用)
* [执行shell命令](#执行shell命令)
* [文本比较](#文本比较)
* [获得脚本的路径和脚本名称](#获得脚本的路径和脚本名称)
* [从代码仓库里面拉取代码](#从代码仓库里面拉取代码)
* [读取配置ini文件](#读取配置ini文件)
* [打印时间](#打印时间)
* [输出重定向](#输出重定向)
* [脚本debug](#脚本debug)

---

## 启动行参数解析
使用getopts进行参数解析
* 如果一个字母后面有一个":"，表示该命令行选项后面要跟一个参数。
* 如optsting写成"b:o:h"，表示支持-b、-o、-h选项识别，-b和-o选项后面需要跟一个参数
* 输出-b 但是又没有指定参数，就走到这里 :)
```
while getopts "b:o:h" opt_name
do
    case $opt_name in
        b) echo "-b Option is recognized, argument=$OPTARG"
            build
           ;;
        o) echo "-o Option is recognized, argument=$OPTARG"
            update $OPTARG
           ;;
        h) echo "-h Option is recognized"
            package
           ;;
        :) echo "$OPTARG Option need a argument"   # 比如输出-b 但是又没有指定参数，就走到这里
            print_help
           ;;
    esac
done
```
---

## 参数调用

* 普通的函数调用
```
function build()
{
    echo "building ..."
}

build 
```

* 函数带参数
```
function update()
{
    update_mode=$1
    # “STRING” 的长度为零则为真
    if [ -z "${update_mode}" ]
    then
        echo ">> ERROR: build mode required."
        return 1
    fi

    if [[ ${update_mode} != "release" ]] && [[ ${update_mode} != "debug" ]]
    then
        echo ">> ERROR: invalid build mode: ${update_mode}"
        return 1
    fi

    if [ ${update_mode} == "release" ]
    then
        echo ">>>> relese update mode ..."
    fi

    if [ ${update_mode} == "debug" ]
    then
        echo ">>>> debug update mode ..."
    fi
    return 0
}

update debug
```

----

## 执行shell命令

```
function build_svr()
{
    core=`grep -c ^processor /proc/cpuinfo`
    echo ${core}

    res=`make svr`
    if [ $? != 0 ] 
    then 
        echo "build svr fail"
    fi
    echo "build svr successfully"
    echo ${res}
}
```

----

## 文本比较
``` shell
function update()
{
    update_mode=$1
    # # “STRING” 的长度为零则为真
    if [ -z "${update_mode}" ]
    then
        echo ">> ERROR: build mode required."
        return 1
    fi

    if [[ ${update_mode} != "release" ]] && [[ ${update_mode} != "debug" ]]
    then
        echo ">> ERROR: invalid build mode: ${update_mode}"
        return 1
    fi

    if [ ${update_mode} == "release" ]
    then
        echo ">>>> relese update mode ..."
    fi

    if [ ${update_mode} == "debug" ]
    then
        echo ">>>> debug update mode ..."
    fi
    return 0
}
```
---- 

## 获得脚本的路径和脚本名称
```
SCRIPT_DIR="$(cd `dirname $0`; pwd)"
SCRIPT_NAME=`basename $0`
OUTPUT_PATH=${SCRIPT_DIR}/data

function show_path()
{
    echo ${SCRIPT_DIR}
    echo ${SCRIPT_NAME}

    cd ${OUTPUT_PATH}
    echo "hello" > 1.log
    
    cd ${SCRIPT_DIR}
}

show_path
```

---------------

## 从代码仓库里面拉取代码
```
function svn_checkout() 
{
    if [ ! -d ${OUTPUT_PATH} ]
    then
        mkdir ${OUTPUT_PATH}
        echo "create dir"
    fi
    echo "dir created"

    rm -rf ${OUTPUT_PATH}
    cd ${OUTPUT_PATH}
    svn checkout ${SVN_URL} . --username ${USERNAME} --password ${PASSWORD}
    cd ${SCRIPT_DIR}
}
```


----------------

## 读取配置ini文件
```
SCRIPT_DIR="$(cd `dirname $0`; pwd)"
SCRIPT_NAME=`basename $0`
OUTPUT_PATH=${SCRIPT_DIR}/data
SHELL_CFG=${SCRIPT_DIR}/cfg.ini

function load_cfg()
{
    if [ -f "${SHELL_CFG}" ]
    then
        source ${SHELL_CFG}
    fi

    echo ${OUTPUT_CFG_PATH}
}

load_cfg

echo ${OUTPUT_CFG_PATH}
```

对应的ini文件（cfg.ini）
```
OUTPUT_CFG_PATH=./data
```

----
## 打印时间

```
print_date()
{
    echo "========date========" 
    date 
}
```

----
## 输出重定向

```
LOG_FILE="build.log"
ERR_FILE="build.err"
TEE="/usr/bin/tee"

set_env()
{
    if [ ${SILENT} == 'true' ] 
    then
        exec 1>${LOG_FILE}
        exec 2>${ERR_FILE}
    else
        NPIPE=/tmp/$$.tmp
        trap "rm -f ${NPIPE}" EXIT
        mknod $NPIPE p
        ${TEE} <$NPIPE ${LOG_FILE} &
        exec 1>&-         # &- 关闭标准输出  # n&- 表示将 n 号输出关闭
        exec 1>$NPIPE

        exec 2>${ERR_FILE}
    fi
}
```

----

## 脚本debug
脚本debug神器，把每一行的脚本执行了什么都打印出来
```
#!/bin/sh -x
```