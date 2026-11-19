#include <iostream>

using namespace std;

struct A {
    virtual void f() {cout << "A" << endl;};
};

struct B : virtual A {
    void f() override {cout << "B" << endl;};
};

struct C : virtual A {
    void f() override {cout << "C" << endl;};
};

struct D : B, C {
    void f() override {
        A::f();
        B::f();
        C::f();
        cout << "D" << endl;
    };
};

int main(){
    D d;
    cout << sizeof(d) << endl;
    d.f();
}