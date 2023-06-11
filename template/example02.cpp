/*模板的完全特例化和部分特例化02*/

#include <iostream>
#include <string.h>
using namespace std;



template <typename T>
class Vector {
public:
    Vector() {
        cout << "call Vector template init" << endl;
    }
};

// 对char*类型提供的完全特例化版本
template <>
class Vector<char*> {
public:
    Vector() {
        cout << "call Vector<char*> init" << endl;
    }
};

// 针对指针类型提供的部分特例化版本
template <typename Ty>
class Vector<Ty*> {
public:
    Vector() {
        cout << "call Vector<Ty*> init" << endl;
    }
};


template <typename R, typename A1, typename A2>
class Vector<R(*)(A1, A2)> {
public:
    Vector() {
        cout << "call Vector<R(*)(A1, A2)> init" << endl;
    }    
};


int sumTwo(int a, int b) {
    return a + b;
}




int main() {

    Vector<int> vec1;    // 从原模板实例化
    Vector<char*> vec2;  // 匹配完全特例化
    Vector<int*> vec3;   // 匹配部分特例化

    Vector<int(*)(int, int)> vec4;  // 函数指针类型
    Vector<int(int, int)> vec5;     // 函数类型


    typedef int (func_t)(int, int);  // func_t 是一个函数类型
    // func_t f1 = sumTwo;  // 编译错误
    func_t *f1 = sumTwo;  // sumTwo是一个函数指针
    f1(3, 4);


    // typedef int (*func_t)(int, int);  // func_t 是一个函数指针类型
    // func_t f1 = sumTwo;
    // f1(3, 4);


    const std::type_info& typeI = typeid(sumTwo);
    const std::type_info& typeD = typeid(func_t);  // sumTwo和int (func_t)(int, int)类型相同, 但却func_t f1 = sumTwo编译错误

    // 比较类型
    if (typeI == typeD) {
        std::cout << "i and d have the same type." << std::endl;
    } else {
        std::cout << "i and d have different types." << std::endl;
    }

    // 获取类型名称
    std::cout << "Type of i: " << typeI.name() << std::endl;
    std::cout << "Type of d: " << typeD.name() << std::endl;


    return 0;
}



















