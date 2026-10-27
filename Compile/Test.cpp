#include <iostream>

using namespace std;

class Calc
{
public:
    static void SwapNum(int &num1, int &num2)
    {
        int temp = num1;
        num1 = num2;
        num2 = temp;
    }
};

class TestClass
{
public:
    TestClass()
    {
        num1 = 5;
        num2 = 10;
    }

    void printCurState(void (*executeFunc)(int &, int &))
    {
        cout << "last : " << num1;
        executeFunc(num1, num2);
        cout << " current : " << num1 << endl;
    }

private:
    int num1, num2;
};

TestClass testClass = TestClass();

// 함수 포인터
void avatar1()
{
    testClass.printCurState(Calc::SwapNum);
}

// 람다식 활용
void avatar2()
{
    auto func = [](int &num1, int &num2)
    {
        int temp = num1;
        num1 = num2;
        num2 = temp;
    };
    testClass.printCurState(func);
}

int main()
{
    avatar1();
    avatar2();
}
