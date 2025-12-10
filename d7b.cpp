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
const bool DEBUG = true;
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

    vector<ll> preFreq(m);
    forR(c, m) {
        if(lines[0][c] == 'S') preFreq[c] = 1;
        else preFreq[c] = 0;
    }

    for(int i : preFreq) dout << i << ' ';
    dout << endl;
    REP(cr, 1, n) {
        vector<ll> curFreq(m, 0);
        forR(c, m) {
            if(lines[cr][c] == '.') {
                curFreq[c] += preFreq[c];
            } else if(lines[cr][c] == '^') {
                if(c > 0) curFreq[c-1] += preFreq[c];
                if(c+1 < m) curFreq[c+1] += preFreq[c];
            }
        }
        preFreq = std::move(curFreq);

        for(ll i : preFreq) dout << i << ' ';
        dout << endl;
    }

    ll tot = 0;
    for(ll i : preFreq) tot += i;
    cout << tot << endl;
}