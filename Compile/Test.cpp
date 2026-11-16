#include <iostream>

using namespace std;

class Human{
    public :
        virtual void speak(){
            cout << "I am a human" << endl;
        }

};

class Zombie : public Human{
    public :
        void speak() override {
            cout << "grrrrrrrrrr" << endl;
        }
}; 

int main(){
    Zombie z;
    Human* h = &z;  //동적바인딩이 일어나서 사람이 좀비가 됨
    Human h1;

    h1.speak(); //객체의 타입이 Human이므로 Human::speak()가 호출됨
    h->speak(); //virtual 키워드가 붙은 함수는 객체의 가상테이블에 저장된 함수 포인터를 통해 호출됨. 이때 함수는 코드 영역에 생성되고, 함수 포인터는 객체의 구현에 따라 원본을 가리킬 수도, 객체를 가리킬수도 있음. 함수 포인터의 주소는 컴파일러에 의해 자동으로 배정되므로 확인하기 어려움
}