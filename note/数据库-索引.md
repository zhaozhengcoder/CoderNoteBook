# MYSQL


## 目录

* [索引](#索引)

* [字段类型](#字段类型)


---

## 索引


### 索引类型
1. UNIQUE唯一索引

    不可以出现相同的值,可以有NULL值

2. INDEX普通索引

    允许出现相同的索引内容

3. PRIMARY KEY主键索引

    不允许出现相同的值,且不能为NULL值,一个表只能有一个primary_key索引

4. fulltext index 全文索引

    上述三种索引都是针对列的值发挥作用,但全文索引,可以针对值中的某个单词,比如一篇文章中的某个词,然而并没有什么卵用,因为只有myisam以及英文支持,并且效率让人不敢恭维,但是可以用coreseek和xunsearch等第三方应用来完成这个需求。


### 创建索引的原则

1. 维度高的列创建索引

    举个反例，给性别创建索引，是不合适的。因为，理想的索引是要有区分度的，但是，性别索引只能区分出一半的数据，剩下的一般还需要顺序查找。

2. 对常用where，order by ，group by 中加入索引

3. 对字符串使用**前缀索引**

4. 不要过多使用索引

    因为加入索引之后，除了有额外的磁盘开销之外，**另外，每一次插入数据都会导致索引被修改。**

### 关于联合索引

联合索引匹配的原则是最左匹配原则。


### 写尽量可以命中索引的sql语句

* 不会命中索引的sql语句
    
    ```
    SELECT `sname` FROM `stu` WHERE `age`+10=30;-- 不会使用索引,因为所有索引列参与了计算

    SELECT `sname` FROM `stu` WHERE LEFT(`date`,4) <1990; -- 不会使用索引,因为使用了函数运算,原理与上面相同

    select * from dept where dname='xxx' or loc='xx' or deptno=45 
    --如果条件中有or,即使其中有条件带索引也不会使用。
    --换言之,就是要求使用的所有字段,都必须建立索引, 我们建议大家尽量避免使用or 关键字
    ```

## 字段类型

* 数值

    int, tinyint, bigint, float, double ...

* 字符串

    varchar,char, ...

    char(20) 和 varchar(20) 的区别 ： 

    CHAR 把这个大小视为值的大小，不长度不足的情况下就用空格补足。而 VARCHAR 类型把它视为最大值并且只使用存储字符串实际需要的长度（增加一个额外字节来存储字符串本身的长度）来存储值。所以短于指示器长度的 VARCHAR 类型不会被空格填补，但长于指示器的值仍然会被截短。

* 时间

    date，time，year ，datetime，timestamp 

* 符合类型

    枚举 enum ，集合 set

mysql如何选择数据类型：**选择合理范围内最小的**   
```
姓名：char(20)
价格：DECIMAL(7, 3)
产品序列号：SMALLINT(5) unsigned
文章内容: TEXT
MD5: CHAR(32)
ip: char(15)
time: int(10)
email char(32)
```