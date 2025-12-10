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
    vector<vector<string>> parts;
    string line;
    while(getline(cin, line)) {
        string token;
        stringstream liness(line);
        int cInd = 0;
        while(liness >> token) {
            while(parts.size() <= cInd) parts.emplace_back();
            parts[cInd].push_back(token);
            ++cInd;
        }
    }

    ll tot = 0;
    forR(ind, (int) parts.size()) {
        vector<string> &part = parts[ind];
        int siz = part.size();
        if(part[siz-1] == "*") {
            ll val = 1;
            forR(ti, siz - 1) val = val * stol(part[ti]);
            tot += val;
        } else if(part[siz-1] == "+") {
            ll val = 0;
            forR(ti, siz - 1) val = val + stol(part[ti]);
            tot += val;
        }
    }
    cout << tot << endl;
}