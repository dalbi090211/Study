#include <iostream>

#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

unordered_map<long long, long long> has;
unordered_map<long long, long long> has2;

long long getSize(long long num)
{
    return 2 * (num) * (num - 1) / 2;
}

long long solution(vector<int> weights)
{
    long long answer = 0;

    for (long long data : weights)
    {
        has2[data]++;

        for (int i = 2; i <= 4; i++)
        {
            long long result = data * i;
            if (has[result] > 0)
                answer += has[result];
            has[result]++;
        }
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