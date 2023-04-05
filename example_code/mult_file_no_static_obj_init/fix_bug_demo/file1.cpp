#include "file1.h"
#include "file2.h"
#include <iostream>
using namespace std;

TEST1::TEST1()
{
    val1 = get_test2_obj().val1 * get_test2_obj().val2;
    cout << "init test1" << endl;
}

TEST1 &get_test1_obj()
{
    static TEST1 test1;
    return test1;
}