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


// 函数参数传递:
// 对于类类型，函数调用，实参 => 形参，是初始化而不是赋值
// 不能返回局部的或者临时对象的指针或引用
Test GetObject(Test t) {
    int val = t.getData();
    Test tmp(val);
    return tmp;     
}

// 函数返回类对象时，由于类对象在函数GetObject的栈上
// t2 = GetObject(t1) 不能直接将tmp对象赋值给t2，因为tmp是属于函数GetObject的局部对象
// 函数返回类对象的具体步骤:
//      <1> 为了将tmp返回值带出来，需要在main函数栈上构造一个临时对象，这里调用 Test(const Test& t)
//      <2> 然后函数GetObject里面tmp对象调用析构函数 ~Test()
//      <3> 接着将main函数栈上拷贝的tmp的临时对象拷贝赋值给t2，这里调用 operator=(const Test& t)
//      <4> 最后临时对象调用 ~Test() 析构对象


int main() {

    Test t1;   // 
    Test t2;   // 
    t2 = GetObject(t1);

    return 0;
}

// 老师课堂运行结果
/*
    Test(int)                  // t1构造
    Test(int)                  // t2构造

    Test(const Test& t)        // 函数参数传递
    Test(int)                  // tmp 构造

    // t2 = GetObject(t1) 语句背后执行的步骤
    Test(const Test& t)        // <1> 为了将tmp返回值带出来，需要在main函数栈上构造一个临时对象，这里调用 Test(const Test& t)
    ~Test()                    // GetObject函数内 tmp 析构 <2> 然后函数GetObject里面tmp对象调用析构函数 ~Test()
    ~Test()                    // GetObject函数内 t 析构
    operator=(const Test& t)   // <3> 接着将main函数栈上拷贝的tmp的临时对象拷贝赋值给t2，这里调用 operator=(const Test& t)
    ~Test()                    // <4> 最后临时对象调用 ~Test() 析构对象


    ~Test()                    // main函数内t2析构
    ~Test()                    // main函数内t1析构
*/

// 自己运行结果
// g++ -o example02 example02.cpp
/*
    Test(int)                  // t1构造
    Test(int)                  // t2构造
    Test(const Test& t)        // 函数参数传递
    Test(int)                  // tmp 构造
    operator=(const Test& t)   // 直接GetObject函数内tmp拷贝赋值给了main函数的t2对象
    ~Test()                    // GetObject函数内 tmp 析构
    ~Test()                    // GetObject函数内 t 析构
    ~Test()                    // main函数内t2析构
    ~Test()                    // main函数内t1析构
*/

// 老师课堂运行结果与自己运行结果不一致，可能是
// C++中的函数在返回一个类对象时，理论上我们会认为通过复制构造函数复制一个临时对象，然后在赋值给外部变量。
// 实际上编译器做了优化，省去了中间的临时对象环节。和返回值优化相关有两种机制：RVO (Return Value Optimization)、NRVO (Name RVO).



// g++ -o example02 example02.cpp -fno-elide-constructors  // 通过参数-fno-elide-constructors关闭g++的编译优化
// 如下结果就创建了临时对象，多了临时对象的拷贝构造和析构
// Test(int)
// Test(int)
// Test(const Test& t)
// Test(int)
// Test(const Test& t)
// ~Test()
// operator=(const Test& t)
// ~Test()
// ~Test()
// ~Test()
// ~Test()


