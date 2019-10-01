#include "file1.h"
#include "file2.h"
#include <iostream>
using namespace std;

TEST1::TEST1()
{
    val1 = test2.val1 * test2.val2; // 构造test1初始化依赖于test2对象
    cout << "init test1" << endl;
}

TEST1 test1;