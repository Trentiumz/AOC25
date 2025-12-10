#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>

using namespace std;
typedef long long ll;
#define forR(i, a) for(int i = 0; i < (a); ++i)
#define REP(i, a, b) for(int i = (a); i < (b); ++i)
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

const int DIGS = 12;
ll po10[DIGS + 1];

signed main() {
    po10[0] = 1;
    REP(i, 1, DIGS+1) po10[i] = po10[i-1] * 10;
    string lin;
    ll tot = 0;
    while(getline(cin, lin)) {
        ll lgPast[DIGS];
        forR(j, DIGS) lgPast[j] = -1;
        for(int i = (int) lin.size() - 1; i >= 0; --i) if('1' <= lin[i] && lin[i] <= '9') {
            ll cVal = (ll) lin[i] - '0';
            for(int j = DIGS - 1; j >= 0; --j) {
                if(j == 0) lgPast[j] = max(lgPast[j], cVal);
                else {
                    if(lgPast[j-1] != -1) lgPast[j] = max(lgPast[j], lgPast[j-1] + cVal * po10[j]);
                }
            }
        }
        tot += lgPast[DIGS-1];
    }
    cout << tot << endl;
}