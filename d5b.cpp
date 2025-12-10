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
struct range {
    ll lo, hi;
};


signed main() {
    string line;
    map<ll, int> diff;
    while(getline(cin, line)) {
        if(line == "") break;
        stringstream cl(line);
        string lef, rig;
        getline(cl, lef, '-'); getline(cl, rig);

        ll st = stol(lef), ed=stol(rig);
        ++diff[st];
        --diff[ed+1];
    }
    ll tot = 0;
    ll lInd=-1, lVal=0;
    for(auto [ind, cdf] : diff) {
        if(lVal > 0) {
            tot += ind - lInd;
        }
        lVal += cdf;
        lInd = ind;
    }
    cout << tot << endl;
}