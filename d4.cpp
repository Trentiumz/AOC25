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

signed main() {
    vector<string> lines;
    string cur;
    while(getline(cin, cur)) {
        lines.push_back(cur);
    }

    int n = lines.size(), m = lines[0].size();
    int numRolls = 0;
    forR(i, n) forR(j, m) if(lines[i][j] == '@') {
        int tot = 0;
        for(int cr = max(0, i-1); cr <= min(n-1, i +1); ++cr) {
            for(int cc = max(0, j-1); cc <= min(m-1, j+1); ++cc) {
                if(cr != i || cc != j) {
                    if(lines[cr][cc] == '@') ++tot;
                }
            }
        }
        // cout << i << ' ' << j << ' ' << tot << endl;
        if(tot < 4) ++numRolls;
    }
    cout << numRolls << endl;
}