#include <iostream>

#include <string>
#include <vector>

using namespace std;

vector<vector<int>> graph;

vector<int> solution(vector<string> park, vector<string> routes)
{
    int maxX;
    int maxY = park.size();

    vector<int> answer;
    pair<int, int> pos;

    int x = 0, y = 0;

    for (string st : park)
    {
        x = 0;
        vector<int> arr;
        for (char c : st)
        {
            if (c == 'S')
            {
                pos = {y, x};
                arr.push_back(1);
            }
            if (c == 'O')
                arr.push_back(1);
            if (c == 'X')
                arr.push_back(2);
            x++;
        }
        y++;
        graph.push_back(arr);
        maxX = x;
    }

    for (string st : routes)
    {
        int num = static_cast<int>(st[2]);
        int next;
        pair<int, int> dir;
        switch (st[0])
        {
        case 'N':
            dir = {1, 0};
            break;
        case 'S':
            dir = {-1, 0};
            break;
        case 'W':
            dir = {0, -1};
            break;
        case 'E':
            dir = {0, 1};
            break;
        }

        for (int i = 0; i < num; i++)
        {
            pair<int, int> next = {pos.first + dir.first, pos.second + pos.second};
            if (next.first >= maxY || next.first < 0 || next.second >= maxX || next.second < 0 || graph[next.first][next.second] == 2)
                break;
            else
                pos = next;
        }
    }
    answer.push_back(pos.first);
    answer.push_back(pos.second);
    return answer;
}

int main()
{
    for (int i : solution({"SOO", "OOO", "OOO"}, {"E 2", "S 2", "W 1"}))
    {
        cout << i << " ";
    }
}