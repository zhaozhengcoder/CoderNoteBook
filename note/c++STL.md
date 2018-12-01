# STL

## 目录

* [迭代器失效](#迭代器失效)



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
                iter = vi.erase(iter);
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