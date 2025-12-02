#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>

using namespace std;
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
    vector<ll> bads;
    for(int digs = 1, st = 1, ed = 10; digs < 8; ++digs, st *= 10, ed *= 10) {
        for(int times = 2; times * digs < 12; ++times) { // up to 12-digit numbers
            ll mulBy = 1;

            ll addBy = ed;
            for(int exp = 1; exp < times; ++exp, addBy *= ed) {
                mulBy += addBy;
            }

            for(int pt = st; pt < ed; ++pt) {
                bads.push_back((ll) pt * mulBy);
            }
        }
    }
    sort(bads.begin(), bads.end());

    vector<ll> val;
    for(int i = 0; i < bads.size(); ++i) {
        if(i == 0 || bads[i-1] != bads[i]) val.push_back(bads[i]);
    }

    string inp;
    getline(cin, inp);
    stringstream ss(inp);

    string curPart;
    ll totWays = 0;
    while(getline(ss, curPart, ',')) {
        string lef, rig;
        stringstream cp(curPart);
        getline(cp, lef, '-');
        getline(cp, rig, '-');

        stringstream ls(lef), rs(rig);
        ll li, ri;
        ls >> li; rs >> ri;

        // int ways = upper_bound(val.begin(), val.end(), ri) - lower_bound(val.begin(), val.end(), li);
        ll ways = 0;
        auto st = lower_bound(val.begin(), val.end(), li);
        auto ed = upper_bound(val.begin(), val.end(), ri);
        dout << li << ' ' << ri << ": " << endl;
        for(auto i = st; i < ed; ++i) {
            dout << "\t" << *i << endl;
            ways += *i;
        }
        totWays += ways;
    }
    cout << totWays << endl;
}