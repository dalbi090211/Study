#include <iostream>

using namespace std;

struct A {
    void f() {cout << "A" << endl;};
};

struct B : virtual A {
    // void f() override {cout << "B" << endl;};
};

struct C : virtual A {
    // void f() override {cout << "C" << endl;};
};

struct D : B, C {

};

int main(){
    D d;
    d.f();


}