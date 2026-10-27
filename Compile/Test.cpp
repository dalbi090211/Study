#include <iostream>

#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

unordered_map<long long, int> has;
unordered_map<int, int> has2;

int getSize(int num)
{
    return 3 * (num) * (num + 1) / 2;
}

long long solution(vector<int> weights)
{
    long long answer = 0;

    for (int data : weights)
    {
        for (int i = 1; i <= 4; i++)
        {
            long long result = (long long)(data * i);
            if (has[result] > 0)
                answer += has[result];
            has[result]++;
        }
    }

    for (int data : weights)
    {
        has2[data]++;
    }

    for (auto [key, value] : has2)
    {
        answer -= getSize(value);
    }

    return answer;
}

int main()
{
    cout << solution({100, 180, 360, 100, 270}) << endl;
}