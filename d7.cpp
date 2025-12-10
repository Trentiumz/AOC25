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
    string line;
    while(getline(cin, line)) {
        lines.push_back(line);
    }

    int n = lines.size(), m = lines[0].size();

    set<int> pre;
    forR(c, m) if(lines[0][c] == 'S') pre.insert(c);

    int tot = 0;
    REP(cr, 1, n) {
        set<int> cur;
        forR(c, m) {
            if(lines[cr][c] == '.') {
                if(pre.count(c)) cur.insert(c);
            } else if(lines[cr][c] == '^') {
                if(pre.count(c)) {
                    cur.insert(c-1);
                    cur.insert(c+1);
                    ++tot;
                }
            }
        }
        pre = std::move(cur);
    }

    cout << tot << endl;
}