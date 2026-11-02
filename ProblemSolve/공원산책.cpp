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

    // // debug
    // cout << "max y : " << maxY << " max x : " << maxX << endl;

    for (string st : routes)
    {
        bool yesTrigger = true;
        int num = st[2] - '0';
        pair<int, int> dir;

        // // debug
        // cout << "num : " << num << endl;

        switch (st[0])
        {
        case 'N':
            dir = {-1, 0};
            break;
        case 'S':
            dir = {1, 0};
            break;
        case 'W':
            dir = {0, -1};
            break;
        case 'E':
            dir = {0, 1};
            break;
        }

        pair<int, int> next = {pos.first, pos.second};

        for (int i = 0; i < num; i++)
        {
            next = {next.first + dir.first, next.second + dir.second};

            if (next.first >= maxY || next.first < 0 || next.second >= maxX || next.second < 0 || graph[next.first][next.second] == 2)
            {
                yesTrigger = false;
                break;
            }
        }

        if (yesTrigger)
            pos = next;
    }

    answer.push_back(pos.first);
    answer.push_back(pos.second);
    return answer;
}

int main()
{
    for (int i : solution({"OSO", "OOO", "OXO", "OOO"}, {"E 2", "S 3", "W 1"}))
    {
        cout << i << " ";
    }
}