#include <iostream>

#include <queue>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

unordered_map<int, int> has;
priority_queue<int> pq;

int solution(int k, vector<int> tangerine)
{
    int answer = 0;

    for (int i = 0; i < tangerine.size(); i++)
    {
        has[tangerine[i]] += 1;
    }

    for (auto [key, value] : has)
    {
        pq.push(value);
    }

    int count = k;
    int trial = 0;
    while (count > 0)
    {
        int temp = pq.top();
        pq.pop();
        count -= temp;
        trial++;
    }

    answer = trial;
    return answer;
}

int main()
{
    cout << solution(6, {1, 3, 2, 5, 4, 5, 2, 3}) << endl;
}