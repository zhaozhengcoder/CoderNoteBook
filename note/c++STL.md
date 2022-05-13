# STL

## 目录

* [迭代器失效](#迭代器失效)
* [map访问不存在的元素会怎么样](#map访问一个不存在key的元素会怎么样？)
* [emplace_back](#emplace_back)
* [使用swap缩容](#swap)
* [stl sort的坑](#sort)

---

**基本的STL的使用方法就不在这里赘述了，这里会整理一下stl使用的一些常见的坑。**

### 1. 迭代器失效

迭代器在添加，删除元素之后都有可能失效。在添加，删除之后，要确保自己的迭代器是没有失效的。

* erase 失效的例子 ：在遍历的时候，添加/删除元素

    迭代器失效的原理:因为对应的元素存放的内存的地址发生了改变，导致迭代器失效。

    举个例子，比如push_back多次之后，vector会被迁移。这样原来的地址发生了改变。导致迭代器失效。


    再一个例子：
    ```
    // 删除一个元素 导致失效
    vector<int> vi = {1,2,3};
    iter = vi.begin();
    vi.erase(iter);

    //由于iter已经失效，再使用的时候，迭代器已经失效了，无法使用。
    cout<<*iter<<endl;
    ```

    一般情况下，最容易造成迭代器失效的场景。
    安全的从vector里面删除某些元素。
    ```
    void delete_ele(vector<int> &vi,int delete_ele)
    {
        for (auto iter = vi.begin(); iter != vi.end(); )
        {
            if (*iter != delete_ele)
            {
                iter = vi.erase(iter);   // 删除元素之后，iter指向被删除的元素的下一个了，不需要再iter++了
            }
            else
            {
                iter++;
            }
        }
    }

    int main()
    {
        vector<int> vi = { 1,2,3,3,5,3};
        delete_ele(vi, 3);
        return 0;
    }
    ```

---

### 2. map访问一个不存在key的元素会怎么样？

这个如果不知道这个规则的话，可能会掉坑。**如果map里面不存在这个key的话，访问的时候，会创建一个默认的value对象，然后把这个默认的对象返回。** 所以, 判断一个map里面是否包含某个元素，最好用如这样的逻辑进行判断 map.find() == map.end() 

```
class STUDENT
{
    private:
        int student_id;
        int class_id;
    public:
        STUDENT ()
        {
            cout << "init defualt" << endl;
            this->student_id = -123;
            this->class_id = -345;
        }

        STUDENT(int student_id, int class_id)
        {
            cout << "init" << endl;
            this->student_id = student_id;
            this->class_id = class_id;
        }

        int print_student_id()
        {
            return this->student_id;
        }
};

int main()
{
    map<int, STUDENT> student_map;
    cout << student_map[100].print_student_id() << endl;
    return 0;
}
```

输出：
```
$ ./a.out
init defualt
-123
```


----

### 3. emplace_back 

emplace_back和push_back的区别，为什么要使用emplace_back？

emplace_back的优点是避免了一次对象的拷贝构造。explace可以直接在vector的空间上面进行初始化对象。

```
int main()
{
    vector<STUDENT> student_vec;
    cout<<"emplace back" << endl;
    student_vec.emplace_back(200,201);

    cout << "push back" << endl;
    student_vec.push_back(STUDENT(100,101));

    // xxx
}
```

输出：
```
$ ./a.out
emplace back
init
push back
init
copy
copy
```

---
### 4. swap 

一个vector中有size和capacity两个概念，当向一个vector里面push元素的时候，size和capacity都增长。然后，当删除元素的时候，size会减小，但是capacity不会。如果希望capacity也可以减小的话，往往会利用swap的机制。

```
vector<int>(vi).swap(vi);

等价于
vector<int> tmp = vi;
vi.swap(tmp); 
```

### 5. std::sort 的坑

stl中sort函数有个bug或者是个坑（或者是个feature），就是sort的时候，如果重载了cmp函数，需要cmp函数需要满足**严格弱序**。

### 5. 其他

C++后端开发的踩坑整理
https://www.jianshu.com/p/b67222570785