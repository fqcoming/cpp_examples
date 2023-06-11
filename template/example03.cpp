
/*模板的完全特例化和部分特例化03*/

#include <iostream>
#include <typeinfo>
using namespace std;


template <typename T>
void func(T a) {
    cout << typeid(T).name() << endl;
}

template <typename T>
void func(T* a) {
    cout << typeid(T).name() << endl;
}


int sum(int a, int b) { return a + b; }


int main() {

    func(10);
    cout << typeid(int).name() << endl;

    func("aaa");
    cout << typeid(const char*).name() << endl;

    func(sum);
    cout << typeid(sum).name() << endl;

    func(&sum);
    cout << typeid(&sum).name() << endl;

    return 0;
}







