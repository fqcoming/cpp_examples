
/* 01 对象使用过程中背后调用了哪些方法？*/



#include <iostream>
using namespace std;

#define EXAMPLE01       0
#define EXAMPLE02       1



#if EXAMPLE02


class Test {
public:
    Test(int a = 5, int b = 5) : ma(a), mb(b) { cout << "Test(int, int)" << endl; }
    ~Test() { cout << "~Test()" << endl; }
    Test(const Test& t) : ma(t.ma), mb(t.mb) { cout << "Test(const Test& t)" << endl; }
    Test& operator=(const Test& t) {
        cout << "operator=(const Test& t)" << endl;
        ma = t.ma;
        mb = t.mb;
        return *this;
    }
private:
    int ma;
    int mb;
};

Test t1(10, 10);                    // 1.Test(int, int)

int main() {

    Test t2(20, 20);                // 3.Test(int, int)
    Test t3 = t2;                   // 4.Test(const Test& t)

    static Test t4 = Test(30, 30);  // 静态局部变量是内存提前分配好，但是是第一次运行时才开始初始化的
                                    // 5.Test(int, int)

    t2 = Test(40, 40);              // 6.Test(int, int) && operator=(const Test& t) && ~Test()

    t2 = (Test)(50, 50);            // 7.Test(int, int) && operator=(const Test& t) && ~Test()
                                    // (Test)(50, 50) => (Test)50 => Test(50)
    
    t2 = 60;                        // 8.Test(int, int) && operator=(const Test& t) && ~Test()
                                    // 60 => Test(60)

    Test *p1 = new Test(70, 70);    // 9.Test(int, int)
    Test *p2 = new Test[2];         // 10.Test(int, int) * 2

    // Test *p3 = &Test(80, 80);    // 编译错误
    const Test &p4 = Test(90, 90);  // 11.Test(int, int)  引用临时对象相当于给临时对象起了名字，临时对象就能活下来知道出作用域

    delete p1;                      // 12.~Test()
    delete [] p2;                   // 13.~Test() * 2

    return 0;
}

Test t5(100, 100);                   // 2.Test(int, int)



#elif EXAMPLE01


class Test {
public:
    Test(int a = 10) : ma(a) {
        cout << "Test(int)" << endl;
    }
    ~Test() {
        cout << "~Test()" << endl;
    }
    Test(const Test& t) : ma(t.ma) {
        cout << "Test(const Test& t)" << endl;
    }
    Test& operator=(const Test& t) {
        cout << "operator=(const Test& t)" << endl;
        ma = t.ma;
        return *this;
    }

private:
    int ma;
};



int main() {

    Test t1;             // Test(int)
    Test t2(t1);         // Test(const Test& t)
    Test t3 = t1;        // 等价于 Test t3(t1) => 则只调用一次 Test(const Test& t)

    Test t4 = Test(20);  // Test(20) 显示生成临时对象，生存周期为所在语句。
                         // C++编译器对于对象构造的优化: 用临时对象生成新对象的时候，临时对象就不产生了，直接构造新对象即可。
                         // 等价于 Test t4(20) => 则只调用一次 Test(int) 

    cout << "-------------" << endl;

    t4 = t2;          // operator=(const Test& t)

    // 下面两个语句显示生成临时对象
    t4 = Test(30);    // 产生临时对象，然后使用临时对象给 t4 拷贝赋值，然后语句结束析构临时对象
                      // Test(int) && operator=(const Test& t) && ~Test()

    t4 = (Test)30;    // 把整数30强转成Test类型
                      // 编译器首先看类Test有没有带整型类型参数的构造函数，
                      // 如果有则编译器隐式生成临时对象然后赋值给t4，最后语句结束析构临时对象。否则编译错误
    
    // 下面一个语句隐式生成临时对象
    t4 = 30;          // 对象赋值过程等价于 t4 = (Test)30
    // t4 = "abc";    // 编译器报错

    cout << "-------------" << endl;

    // Test *p = &Test(40);   // p指向的是一个已经析构的临时对象，编译错误
    const Test &ref = Test(50);  // 常引用临时对象编译通过，调用 Test(int)，这里临时对象并不会析构，而是出作用域才会析构

    cout << "-------------" << endl;
    return 0;
}


#endif












