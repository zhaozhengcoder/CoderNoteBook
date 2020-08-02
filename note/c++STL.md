# STL

## 目录

* [迭代器失效](#迭代器失效)
* [emplace_back](#emplace_back)



---

## 迭代器失效

* erase 失效的例子

* 在遍历的时候，添加/删除元素

    
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


### map访问一个不存在key的元素会怎么样？

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

        STUDENT(const STUDENT & student)
        {
            cout << "copy" << endl;
            this->student_id = student.student_id;
            this->class_id = student.class_id;
        }

        STUDENT& operator=(const STUDENT & student)
        {
            cout << "operator=" << endl;
            this->student_id = student.student_id;
            this->class_id = student.class_id;
            return *this;
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

    // 1. 这里会先创建会在map里面调用默认的无参数的构造函数 创建对象
    // 2. STUDENT(100,200) 创建一个临时的对象
    // 3. 然后调用赋值构造函数，拷贝到map里面的对象中
    // student_map[100] = STUDENT(100,200);
    
    // 1. 这里也是先创建一个对象
    // 2. 然后调用拷贝构造函数创建pair
    // 3. 再调用一次拷贝构造函数给map里面的对象进行构造
    // student_map.insert(std::make_pair<int, STUDENT>(200, STUDENT(200,201)));

    return 0;
}
```

输出：
```
$ ./a.out
init defualt
-123
```


### emplace_back 

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

### swap 

一个vector中有size和capacity两个概念，当向一个vector里面push元素的时候，size和capacity都增长。然后，当删除元素的时候，size会减小，但是capacity不会。如果希望capacity也可以减小的话，往往会利用swap的机制。

```
vector<int>(vi).swap(vi);

等价于
vector<int> tmp = vi;
vi.swap(tmp); 
```