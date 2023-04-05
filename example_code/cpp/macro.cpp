#include <iostream>
#include <memory.h>
#include <memory>
#include <stdlib.h>
using namespace std;

#define mymax(a,b) (a>b?a:b) 
#define MALLOC(n, type) \
	((type *) malloc((n)* sizeof(type)))

#define myswap(a,b) \
	int tmp = 10;\
	a = a + b;\
	b = a - b;\
	a = a - b;\
	a = tmp;

#define macro_test(a)\
	cout<<a<<endl;\
	cout<<a<<endl;

void func_test(int aa)
{
	cout<<aa<<endl;
}

// 宏的缺点
// 宏的本质的替换，但是这样在很多场景下会出现问题
void macro_and_func_diff()
{
	cout<<" -- macro_and_func_diff --"<<endl;
	int a = 100;
	macro_test(a++);			//a的值取决于宏里面a被使用的次数
	macro_test(a++);
	cout<<"a : "<<a<<endl;

	int aa = 100;
	func_test(aa++);
	func_test(aa++);
	cout<<"aa : "<<aa<<endl;
	cout<<" -- macro_and_func_diff --"<<endl;
}

int main()
{
	int a = 100;
	int b = 200;
	cout<<mymax(a,b)<<endl;

	// 试着用宏写几个函数
	// 函数1
	int * ptr;
	ptr = MALLOC(5,int);

	// 函数2
	myswap(a,b);
	cout<<"a "<<a<<" b"<<b<<endl;
	
	// 宏的问题
	macro_and_func_diff();
	return 0;
}
