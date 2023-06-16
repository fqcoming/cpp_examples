#include <iostream>
using namespace std;

class Test {
public:
    Test(int a = 10) : ma(a) { cout << "Test(int)" << endl; }
    ~Test() { cout << "~Test()" << endl; }
    Test(const Test& t) : ma(t.ma) { cout << "Test(const Test& t)" << endl; }
    Test& operator=(const Test& t) {
        cout << "operator=(const Test& t)" << endl;
        ma = t.ma;
        return *this;
    }
    int getData() const { return ma; }
private:
    int ma;
};


/*
1.函数参数传递过程中，对象优先按引用传递，不要按值传递
2.函数返回使用临时对象，会减少一个拷贝构造和析构；函数返回对象的时候，应该优先返回一个临时对象，而不要返回一个定义过的对象
3.接收返回值是对象的函数调用的时候，优先按初始化的方式接收，不要按赋值的方式接收
*/

#if 0

Test GetObject(Test t) {
    int val = t.getData();
    Test tmp(val);
    return tmp;     
}

#elif 1 

Test GetObject(Test &t) {
    int val = t.getData();
    return Test(val);  // 返回临时对象 这里类似于 Test t = Test(30) 用临时对象拷贝构造一个新对象，编译器会产生一个优化，直接生成对象。
                       // 这里总结：
                       // 初始执行逻辑：Test tmp(val) => Test main_tmp = tmp => t2 = main_tmp;
                       // 原本执行逻辑：Test main_tmp = Test(val) => t2 = main_tmp;
                       // 优化执行逻辑：Test main_tmp(val) => t2 = main_tmp;
}

// g++ -o example03 example03.cpp -fno-elide-constructors
// 返回临时对象和关闭编译器优化情况下，这样会减少临时对象的一次拷贝构造和析构
// 运行结果如下
// Test(int)
// Test(int)

// 少了临时对象在GetObject函数栈上的构造和析构
// Test(int)     // return Test(val) 构造
// operator=(const Test& t)  // 直接将main函数栈上临时对象拷贝赋值给main函数中的t2
// ~Test()       // 临时对象析构

// ~Test()
// ~Test()


#endif


int main() {

    Test t1;   // 
#if 0
    Test t2;   // 
    t2 = GetObject(t1);

// Test(int)
// Test(int)
// Test(int)
// operator=(const Test& t)
// ~Test()
// ~Test()
// ~Test()

#else 
    Test t2 = GetObject(t1);

// Test(int)   t1构造
// Test(int)   t2构造
// ~Test()     t2析构
// ~Test()     t1析构

#endif

    return 0;
}