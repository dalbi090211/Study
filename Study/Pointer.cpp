#include <iostream>
#include <memory>
#include <stdint.h>

using namespace std;

/*
    포인터는 주소를 저장한다.
    저장한 주소는 타입에 따라 이동하고 해석할 바이트를 정한다
    void*는 주소만 저장하고, 이동과 해석은 불가능하다
    type cast를 통해 void*를 원래 객체의 포인터 타입으로 되돌려 해석할 수는 있다
    이때 type cast 중 static_cast는 타입 규칙에 따른 변환
    reinterpret_cast는 해석 방식을 자유롭게 변환한다
    허용되지 않는 변환은 컴파일 오류가 나며, 변환 후 잘못된 포인터 접근은 정의되지 않은 동작이 될 수 있다
*/
void avatar1()
{
    void *AnyPointer; // 주소만 저장가능, 연산과 해석은 불가능
    int data1 = 10;

    // static_cast<T>(데이터) : c++에서 정의한 타입 규칙에 따라서 변환
    // 허용되지 않는 변환은 컴파일 오류. void*를 되돌릴 때는 실제 객체의 타입에 맞춰야 함
    // int -> float은 가능하지만 int* -> float*은 불가능함. 바이트 수는 같지만 둘의 해석 방식이 전혀 다름
    AnyPointer = &data1;
    int *intPointer = static_cast<int *>(AnyPointer);
    cout << "int value : 10, cast value : " << *intPointer << endl;

    // reinterpret_cast<T>(데이터) : 영어 그대로 해석방식을 바꿈
    // static_cast에 비해 자유로운 방식
    // 포인터 타입을 int*에서 float*으로 바꿔도 원래 int 객체가 float 객체로 바뀌는 것은 아님.
    // float은 단정밀도(32비트) 방식을 사용. 1비트 부호 + 8비트 지수 + 23비트 가수 로 구분됨
    // double은 배정밀도(64비트) 방식을 사용. 1비트 부호 + 11비트 지수 + 52비트 가수 로 구분됨
    // int는 1비트 부호 + 31비트가 정수표현에 사용됨
    float *floatPointer = reinterpret_cast<float *>(intPointer);
    cout << "cast address : " << floatPointer << endl;
    // cout << "int value : 10, cast value : " << *floatPointer << endl; // 정의되지 않은 동작: 출력값이나 정상 실행을 보장할 수 없음
}

/*
    vector는 공간을 미리 할당한 후 사용, linked list와 같은 자료구조는 그때그때 생성해서 파편화된 데이터 구조를 가짐
    vector는 할당된 공간보다 큰 공간이 필요하다면 배율만큼 곱하면서 확장과 복사가 필요하다는 단점이 존재
    vector는 인덱스로 조회할 때 빠르고, linked list는 위치를 이미 알고 있을 때 삽입, 삭제가 O(1)임
*/
void avatar2()
{
    // vector 구현
    //  1. 16바이트 만큼의 연결된 공간을 힙에 할당
    //  2. 8바이트(64비트 운영체제)의 포인터가 공간의 첫 주소를 가리킴
    int *intPointer = new int[4];
    int *vectorBegin = intPointer;

    // vector 초기화
    //  원시 포인터는 범위 체크가 없음. i < 5로 바뀐다면 i가 4까지 올라가 데이터가 존재할 수도 있는 공간에 포인터가 접근함
    //  이 오류를 heap buffer overflow라고 함. 컴파일러가 항상 잡아주지는 않으며, 정적 분석이나 AddressSanitizer 같은 실행 시 검사로 찾을 수 있음
    for (int i = 0; i < 4; i++, intPointer++)
    {
        *intPointer = i + 1;
        cout << "value : " << *intPointer << " address : " << intPointer << endl; // address의 주소값이 연결됨을 확인
    }

    // 간단한 linked list용 노드
    class Node
    {
    public:
        Node *last = nullptr;
        Node *next = nullptr;
        int value;
    };

    // linked list 초기화
    Node *temp = new Node();
    Node *LinkedFirstAddress = temp;
    temp->value = 1;
    for (int i = 1; i < 4; i++)
    {
        Node *newLink = new Node();
        newLink->value = i + 1;
        temp->next = newLink;
        newLink->last = temp;
        temp = newLink;
    }

    // 복구
    intPointer -= 4;
    while (temp->last != nullptr)
    {
        temp = temp->last;
    }

    /*      각 자료구조 별 데이터 간 거리 계산   */
    // 값 조회, 주소 조회
    // 초기 주소 저장
    uintptr_t VectorAddress = reinterpret_cast<uintptr_t>(intPointer);
    uintptr_t LinkedAddress = reinterpret_cast<uintptr_t>(temp);

    for (int i = 0; i < 4; i++)
    {
        // 주소값 변환
        uintptr_t TempVectorAddress = reinterpret_cast<uintptr_t>(intPointer);
        uintptr_t TempLinkedAddress = reinterpret_cast<uintptr_t>(temp);

        // 거리 차이 계산
        cout << "Vector Index: " << i << " Distance: " << (TempVectorAddress >= VectorAddress ? TempVectorAddress - VectorAddress : VectorAddress - TempVectorAddress) << endl;
        cout << "Linked Index : " << i << " Distance : " << ((TempLinkedAddress >= LinkedAddress) ? (TempLinkedAddress - LinkedAddress) : (LinkedAddress - TempLinkedAddress)) << endl;

        // 값 1칸 이동
        intPointer++;
        temp = temp->next;
    }

    // 해제
    intPointer = vectorBegin;
    delete[] intPointer;

    temp = LinkedFirstAddress;
    while (temp != nullptr)
    {
        Node *next = temp->next;
        delete temp;
        temp = next;
    }
}

/*
    원시 포인터가 가지는 관리와 책임을 없애고, 잊어버려도 좋도록 만들기 위해 unique_ptr이 c+11에서 등장함
    객체와 자원의 라이프 사이클을 일치시킨다는 RAII 원칙에 적합함.
*/

void avatar3()
{
    int *pastPointer = new int[4];
    bool UnExpectedFire = true;
    unique_ptr<int[]> uniquePtr = make_unique<int[]>(10);

    if (UnExpectedFire) // pastPointer는 그대로 죽어서 메모리 누수가, uniquePtr은 해제하고 죽음
        return;

    delete[] pastPointer;
}

/*
    유니크 포인터의 동작 방식은 단순히 원시 포인터를 가지고 있다가 죽을 때 삭제한다임
    이때 하나의 메모리에 대한 2개 이상의 유니크 포인터가 존재한다면 삭제를 2번 시도하는 이중 해제 문제가 발생함
    따라서 유니크 포인터는 복사 생성자와 복사 대입 연산자가 삭제되어있음
    소유권을 이전하고 싶다면 move 함수를 사용해야 함
*/
void avatar4()
{
    const int arrSize = 10;
    unique_ptr<int[]> firstPtr = make_unique<int[]>(arrSize);
    unique_ptr<int[]> secondPtr;

    // 대입
    for (int i = 0; i < arrSize; i++)
    {
        firstPtr[i] = i + 1;
    }
    secondPtr = move(firstPtr);

    // 출력
    cout << "is Null : " << (firstPtr == nullptr ? "true" : "false") << endl;
    cout << "Value : " << secondPtr[0];
}

int main()
{
    // avatar1();
    // avatar2();
    // avatar3();
    avatar4();
}
