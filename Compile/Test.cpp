#include <iostream>

using namespace std;

// a > b 여야 함
long long gcd(long long a, long long b)
{
    long long rest = a % b;
    if (rest > 0)
        return gcd(b, rest);
    else
        return b;
}

long long solution(int w, int h)
{
    long long answer = (long long)w * h; // 오버플로우 발생 가능
    long long white = 0;
    long long period = w > h ? gcd(w, h) : gcd(h, w);

    long long width = w / period;
    long long height = h / period;

    white = width + height - 1;
    answer -= white * period;

    return answer;
}

int main()
{
    cout << solution(4, 3);
}