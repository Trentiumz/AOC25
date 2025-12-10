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
    vi jr;
};

int minRounds(vi &goal, vvi &options, int ci, vi &cVec) {
    vi &cur = options.at(ci);
    if(ci == (int) options.size() - 1) {
        int cnt = goal[cur[0]] - cVec[cur[0]];
        for(int i : cur) cVec[i] += cnt;

        bool works = true;
        for(int i = 0; i < goal.size() && works; ++i) {
            works = goal[i] == cVec[i];
        }

        for(int i : cur) cVec[i] -= cnt;
    }
    
}
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
                stringstream part(tkn.substr(1, (int) tkn.size() - 2));
                string cur;
                while(getline(part, cur, ',')) {
                    i.jr.push_back(stoi(cur));
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
        dout << "{";
        for(auto &j : i.jr) {
            dout << j << ' ';
        }
        dout << "}";
        dout << endl;
    }

    int tot = 0;
    for(auto &mc : mcs) {
        set<vi> pos;
        vi st;
        forR(i, mc.n) st.push_back(0);
        pos.insert(st);

        int rounds = 0;
        while(!pos.count(mc.jr)) {
            assert(!pos.empty());
            set<vi> nex;
            for(auto &i : pos) {
                for(auto &j : mc.bts) {
                    vi nv = i;
                    for(auto z : j) ++nv.at(z);

                    bool isGood = true;
                    forR(j, mc.n) if(nv[j] > mc.jr[j]) isGood = false;
                    if(isGood) {
                        nex.insert(nv);
                    }
                }
            }

            pos = std::move(nex);
            ++rounds;
        }

        dout << rounds << endl;
        tot += rounds;
    }

    cout << tot << endl;
}