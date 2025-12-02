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
        int iVal = stoi(i.substr(1));
        if(i[0] == 'L') {
            int rnp = curPos - iVal;
            if(rnp <= 0) times += ((-curPos + 100) % 100 + iVal) / 100;
            cout << curPos << ' ' << rnp << ' ' << times << endl;
            newPos = (rnp % 100 + 100) % 100;
        }
        if(i[0] == 'R') {
            int rnp = curPos + iVal;
            times += rnp / 100;
            cout << curPos << ' ' << rnp << ' ' << times << endl;
            newPos = (rnp % 100 + 100) % 100;
        }
        curPos = newPos;
    }

    cout << times << endl;
}