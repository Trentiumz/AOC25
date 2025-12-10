#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <map>

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
struct coord{
    ll x, y;
};

signed main() {
    string line;
    vector<coord> cds;
    while(getline(cin, line)) {
        string p1, p2;
        stringstream lines(line);
        getline(lines, p1, ','); getline(lines, p2, ',');
        cds.push_back({stol(p1), stol(p2)});
    }

    ll mx = -1;
    forR(i, cds.size()) REP(j, i+1, cds.size()) {
        mx = max(mx, abs(cds[i].x - cds[j].x + 1) * abs(cds[i].y - cds[j].y + 1));
    }
    cout << mx << endl;
}