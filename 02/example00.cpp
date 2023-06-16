#include <vector>
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



int main() {

    vector<Test> vec(3);
    vector<Test> vec1(3);

    vec1 = vec;
    

    return 0;
}











