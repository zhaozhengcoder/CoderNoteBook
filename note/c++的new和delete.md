# c++ 的new和delete


* 使用placement new 在栈上面构建对象

    ```
    class TEST
    {
    private:
        int val;
    public:
        TEST(int value)
        {
            this->val = value;
        }
        void print()
        {
            cout<<this->val<<endl;
        }
    };

    int main()
    {
        //TEST test[10];   //报错，因为没有默认无参数的的构造参数
        
        
        //使用placement new 
        int val = 998;
        
        // 分配空间
        void * raw_memory = operator new(sizeof(TEST) * 10);
        // 强转指针类型
        TEST * test = static_cast<TEST *>(raw_memory);
        // placement new
        for(int i=0;i<10;i++)
        {
        new(test+i) TEST(val);
        }

        // visit
        for(int i=0;i<10;i++)
        {
            (test+i)->print();
        }

        return 0;
    }
    ```

    * 知识点

        1. 使用operator new 分配一块空间 （约等于malloc）
            ```
            void * raw_memory = operator new(size);
            ```

        2. 使用placement new 完成调用构造函数

            ```
            new (raw_memory) Test();
            ```
