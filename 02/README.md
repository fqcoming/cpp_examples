
### 01 对象使用过程中背后调用了哪些方法？(example01.cpp)

EXAMPLE01 运行结果如下

> Test(int)
> Test(const Test& t)
> Test(const Test& t)
> Test(int)
> -------------
> operator=(const Test& t)
> Test(int)
> operator=(const Test& t)
> ~Test()
> Test(int)
> operator=(const Test& t)
> ~Test()
> Test(int)
> operator=(const Test& t)
> ~Test()
> -------------
> Test(int)
> -------------
> ~Test()
> ~Test()
> ~Test()
> ~Test()
> ~Test()


EXAMPLE02 运行结果如下

Test(int, int)
Test(int, int)
Test(int, int)
Test(const Test& t)
Test(int, int)
Test(int, int)
operator=(const Test& t)
~Test()
Test(int, int)
operator=(const Test& t)
~Test()
Test(int, int)
operator=(const Test& t)
~Test()
Test(int, int)
Test(int, int)
Test(int, int)
Test(int, int)
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()
~Test()























