#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>

using namespace std;
#define forR(i, a) for(int i = 0; i < (a); ++i)
#define REP(i, a, b) for(int i = (a); i < (b); ++i)
typedef long long ll;
const bool DEBUG = false;
ll po(ll b, ll e) {
    if(e == 0) return 1;
    else {
        ll h = po(b, e/2);
        return e % 2 == 0 ? h * h : h * h * b;
    }
}
struct debOut {
    template<typename T> debOut &operator<<(T &&i) {
        if(DEBUG) {
            cout << std::forward<T>(i);
        }
        return *this;
    }
    // Handle std::endl and other ostream manipulators
    debOut &operator<<(std::ostream& (*manip)(std::ostream&)) {
        if (DEBUG) {
            std::cout << manip;
        }
        return *this;
    }
} dout;
vector<string> lines;
int n, m;

bool chk(int i, int j) {
    if(lines[i][j] == '@') {
        int tot = 0;
        for(int cr = max(0, i-1); cr <= min(n-1, i +1); ++cr) {
            for(int cc = max(0, j-1); cc <= min(m-1, j+1); ++cc) {
                if(cr != i || cc != j) {
                    if(lines[cr][cc] == '@') ++tot;
                }
            }
        }
        return tot < 4;
    }
    return false;
}
struct coord {
    int r, c;
};

signed main() {
    string cur;
    while(getline(cin, cur)) {
        lines.push_back(cur);
    }

    n = lines.size(), m = lines[0].size();
    int numRolls = 0;
    deque<coord> bfs;
    forR(i, n) forR(j, m) if(chk(i, j)) {
        lines[i][j] = 'x';
        bfs.push_back({i, j});
        ++numRolls;
    }
    while(!bfs.empty()) {
        auto [i, j] = bfs.front();
        bfs.pop_front();
        for(int cr = max(0, i-1); cr <= min(n-1, i +1); ++cr) {
            for(int cc = max(0, j-1); cc <= min(m-1, j+1); ++cc) {
                if(cr != i || cc != j) {
                    if(chk(cr, cc)) {
                        lines[cr][cc] = 'x';
                        bfs.push_back({cr, cc});
                        ++numRolls;
                    }
                }
            }
        }
    }
    cout << numRolls << endl;
}