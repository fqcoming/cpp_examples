
#include <stdio.h>
#include <string>
#include <iostream>
#include <functional>
using namespace std;


typedef void(*func_t)();


// bind function
// c++ STL bind1st/bind2nd => 返回一个函数对象

void hello1() {
    cout << "hello1" << endl;
}

void hello2(string str) {
    cout << "hello2:" << str << endl;
}


// 什么时候会用到函数指针变量或函数对象
// 在一段程序中，如果某个函数部分功能不确定，功能未实现等情况时
// 程序设计者会将这个设置成一个接口，由使用这段程序的人员设置回调。
// 这种情况可以有多种实现方式：
// 1.多态机制来实现
// 2.模板机制来实现
// 3.回调机制来实现
// ......

class Base {
public:
    virtual void run() {
        cout << "base run" << endl;
    }
};

class Derive : public Base {
public:
    virtual void run() {
        cout << "derive run" << endl;
    }
};


void foo_oo(Base *ptr) {
    ptr->run();
}

template <typename T>
void foo_tem(T func) {
    func();
}

void run() {
    cout << "template run" << endl;
}


class Test {
public:
    // 类成员函数名不代表地址&Test::hello格式取地址
    void hello(string str) {  // 必须依赖一个对象
        cout << str << endl;
    }
    // 类的静态成员函数名可以直接代表函数的地址
    static void hello1(string str) {  
        cout << "test static hello1:" << str << endl;
    }
};

typedef void (Test::*phandler)(string str);

// 用于类静态成员变量类型
typedef void (*pcallback)(string str);

int main() {

    cout << (&Test::hello) << endl;
    cout << (&Test::hello1) << endl;
    cout << (run) << endl;

    printf("%p\n", run);
    printf("%p\n", &run);
    printf("%p\n", &Test::hello);
    // printf("%p\n", Test::hello);   // 语法错误
    printf("%p\n", Test::hello1);
    printf("%p\n", &Test::hello1);

    function<void(Test*, string)> fun5 = &Test::hello;
    function<void(Test*, string)> fun6 = &Test::hello;
    fun6(new Test(), "fff");


    pcallback callback = &Test::hello1;
    Test *tt = new Test();
    // (tt->*(callback))("nihao"); // 这里错误语法格式

    callback("test callback");


    phandler handler = &Test::hello;
    Test *t = new Test();
    (t->*(handler))("fq");


    foo_tem<void()>(run);

    Derive d;
    foo_oo(&d);

    void (*pfunc)() = hello1;
    pfunc();

    func_t func = hello1;  
    func();

    function<void()> func1 = hello1;
    func1();  // func1.operator() => hello1()

    function<void(string)> func2 = hello2;
    func2("fu"); // func2.operator(string str) => hello2(string str)

    function<int(int, int)> func4 = [](int a, int b) ->int { return a + b; };
    cout << func4(1, 2) << endl;

    return 0;
}

























