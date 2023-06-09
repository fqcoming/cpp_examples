
#include <iostream>
using namespace std;

// C++11函数对象的升级版 => lambda表达式
// 函数对象的缺点：
// 使用泛型算法参数传递，比较性质/自定义操作，优先级队列
// 当在优先级队列比较时，函数对象只使用这一次，没有必要定义一个函数类型出来
// [捕获外部变量](形参变量)->返回值{操作代码}；


template <typename T = void>
class TestLambda01 {
public:
    void operator()() const {
        cout << "hello world" << endl;
    }
};





int main() {

    TestLambda01<> f1;
    f1();

    auto f2 = []()->void{ cout << "hello lambda" << endl;};
    f2();

    return 0;
}










