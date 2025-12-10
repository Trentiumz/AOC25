#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <cassert>

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
typedef vector<int> vi;
typedef vector<vi> vvi;

const int MAXBITS = 30;
int bts(int n) {
    int tot = 0;
    forR(i, MAXBITS) if(n & (1 << i)) ++tot;
    return tot;
}

struct machine {
    int n;
    int m;
    string ind;
    vvi bts;
    vvi jr;
};

signed main() {
    string line;
    vector<machine> mcs;
    while(getline(cin, line)) {
        mcs.push_back({});
        auto &i = mcs.back();
        stringstream lines(line);
        string tkn;
        while(getline(lines, tkn, ' ')) {
            if(tkn[0] == '[') {
                i.ind = tkn.substr(1, (int) tkn.size() - 2);
            }
            if(tkn[0] == '(') {
                i.bts.push_back({});
                auto &j = i.bts.back();
                stringstream part(tkn.substr(1, (int) tkn.size() - 2));
                string cur;
                while(getline(part, cur, ',')) {
                    j.push_back(stoi(cur));
                }
            }
            if(tkn[0] == '{') {
                i.jr.push_back({});
                auto &j = i.jr.back();
                stringstream part(tkn.substr(1, (int) tkn.size() - 2));
                string cur;
                while(getline(part, cur, ',')) {
                    j.push_back(stoi(cur));
                }
            }
        }

        i.n = i.ind.size();
        i.m = i.bts.size();
    }

    for(auto &i : mcs) {
        dout << i.n << endl;
        dout << "\t" << i.ind << endl;
        dout << '\t';
        for(auto &j : i.bts) {
            dout << "(";
            for(auto z : j) dout << z << ' ';
            dout << ")";
        }
        dout << endl;
        dout << '\t';
        for(auto &j : i.jr) {
            dout << "{";
            for(auto z : j) dout << z << ' ';
            dout << "}";
        }
        dout << endl;
    }

    int tot = 0;
    for(auto &mc : mcs) {
        int goal = 0;
        forR(i, mc.n) if(mc.ind[i] == '#') goal ^= (1 << i);
        int bes = -1;
        forR(msk, 1 << mc.m) {
            int res = 0;
            forR(i, mc.m) if(msk & (1 << i)) {
                for(int j : mc.bts[i]) res ^= (1 << j);
            }
            if(res == goal) {
                int amt = bts(msk);
                if(bes == -1) bes = amt;
                else bes = min(bes, amt);
            }
        }
        assert(bes != -1);
        tot += bes;
        dout << bes << endl;
    }

    cout << tot << endl;
}