/*模板的完全特例化和部分特例化01*/

#include <iostream>
#include <string.h>
using namespace std;


template <typename T>
bool compare(T a, T b) {
    cout << "template compare" << endl;
    return a > b;
}

// 模板完全特例化
template <>
bool compare<const char*>(const char *a, const char *b) {
    cout << "compare<const char*>" << endl;
    return strcmp(a, b) > 0;
}


int main() {

    compare(10, 20);         // 模板实参推演：int => T
    compare("aaa", "bbb");   // 模板实参推演：const char* => T
                             // 由于字符串比较时，传入的是指针，导致compare函数里面是指针比较，没有字符串比较
                             // 因此需要模板特例化

    return 0;
}














