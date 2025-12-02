#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

signed main() {
    vector<string> lines;
    string curLine;
    while(cin >> curLine) {
        lines.push_back(curLine);
    }

    int curPos = 50;
    int times = 0;
    for(auto &i : lines) {
        if(i.empty()) continue;
        int newPos = curPos;
        if(i[0] == 'L') newPos = ((newPos - stoi(i.substr(1))) % 100 - 100) % 100;
        if(i[0] == 'R') newPos = ((newPos + stoi(i.substr(1))) % 100 + 100) % 100;
        if(newPos == 0) ++times;
        curPos = newPos;
    }

    cout << times << endl;
}