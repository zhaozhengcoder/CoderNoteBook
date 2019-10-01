#include <iostream>
#include "file1.h"
#include "file2.h"

using namespace std;

int main()
{
    cout << "enter main" << endl;
    cout << "test1 : " << get_test1_obj().val1 << " , " << get_test1_obj().val2 << endl;
    cout << "test2 : " << get_test2_obj().val1 << " , " << get_test2_obj().val2 << endl;
    return 0;
}