# bash&shell 编程

## 目录
* [hello_world](#hello_world) 
* [定义变量](#定义变量)
* [字符串运算](#字符串运算)
* [获得输入](#获得输入)

---

## hello_world

一个简单的demo，输出一个hello world。
```
#!/bin/bash
echo "hello world"
```

## 定义变量

注意 ： var=hello world **等号两边不能有空格**
```
var=hello world #等号两边不能有空格
echo $var
echo ${var}     #两种打印变量的方式

echo "this is : $var"   # 感觉都想php了
```

## 字符串运算
注意 ： [ $a1 = $b1 ] **等号两边必须有空格**
```
a1="123"
b1="dsafdakjkl"

#判断等于
if [ $a1 = $b1 ]
then
   echo "eq"
else
   echo "not eq"
fi

# 判断不等于
if [ $a1 != $b1 ]
then
   echo "not eq"
fi
```

## 数学运算

```
num1=100
num2=200

if [ $num1 == $num2 ]
then
   echo "$num1 等于 $num2"
else
   echo "$num1 不等于 $num2"
fi

if [ $num1 != $num2 ]
then
   echo "$num1 等于 $num2"
fi

# 大于小于
if [ $num1 -lt $num2 ]   # -gt 大于 ； -eq等于  -ne 不等于；
then
   echo "$num1 小于 $num2"
fi

# 与 和 或运算

num3=300
num4=400

if [[ $num3 -lt $num4 && $num1 -lt $num2 ]]
then 
   echo "yes"
fi
```

## 条件和分支

if-else
```
if condition
then
    command1 
    command2
    ...
    commandN
else
    command
fi
```

if else-if else
```
if condition1
then
    command1
elif condition2 
then 
    command2
else
    commandN
fi
```


## 获得输入
```
echo "1 : $1"
echo "2 : $2"
echo "3 : $3"
```

```
./bash_test.sh 100 200 300
```


### 写个小demo
```
#!/bin/bash

flag1="make"
flag2="clean"
flag3="run"

if [ $flag1 = $1 ]
then 
   echo "flag1 = $1"
   g++ main.cc
elif [ $flag2 = $1 ]
then
   rm a.out
else
   ./a.out
fi
```

```
./bash_test.sh make   #编译
./bash_test.sh run    #运行
```




## 参考

http://www.runoob.com/linux/linux-shell.html

《linux shell脚本攻略》