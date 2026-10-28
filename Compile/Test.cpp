#include <iostream>
#include <thread>
#include <semaphore>

using namespace std;

int counter = 0;

counting_semaphore<3> sem(3); // c++20 부터 지원

auto work = [](int trial)
{
    auto start = chrono::steady_clock::now();

    sem.acquire();
    for (int i = 0; i < 100; i++)
    {
        counter++;
    }
    sem.release();

    auto end = chrono::steady_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << trial << " trial : " << duration.count() << endl;
};

int main()
{
    thread t1(work, 1);
    thread t2(work, 2);
    thread t3(work, 3);
    thread t4(work, 4);
    thread t5(work, 5);
    thread t6(work, 6);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
}