#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <cassert>
#include <cmath>
#include <numeric>

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
typedef vector<int> vi;
typedef vector<vi> vvi;
ostream &operator<<(ostream &cur, vi row) {
    cur << '[';
    for(auto i : row) cur << i << ' ';
    cur << ']';
    return cur;
}

ostream &operator<<(ostream &cur, vvi mat) {
    for(auto &i : mat) cur << i << endl;
    return cur;
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

vi mul(const vi &cur, int by) {
    vi ret(cur.size());
    forR(i, cur.size()) ret[i] = cur[i] * by;
    return ret;
}

vi sub(const vi &a, const vi &b) {
    assert(a.size() == b.size());
    vi ret(a.size());
    forR(i, a.size()) ret[i] = a[i] - b[i];
    return ret;
}

vi subRow(const vi &cur, const vi &from, int c) {
    if(from[c] == 0) return from;
    else {
        int gc = gcd(cur[c], from[c]);
        int to = cur[c] * from[c] / gc;

        vi ret = sub(mul(from, to / from[c]), mul(cur, to / cur[c]));
        return ret;
    }
}

void normRow(vi &cur, int makePos) {
    if(cur[makePos] < 0) mul(cur, -1);
}

// RREF A
tuple<vvi, vi, vi> rref(vvi A) {
    int n = A.size(), m = A[0].size();

    int tr = 0;
    vi pivots;
    vi free;
    forR(c, m) {
        int fr = tr;
        while(fr < n && A[fr][c] == 0) ++fr;
        if(fr < n) {
            A[tr].swap(A[fr]);
            pivots.push_back(c);

            normRow(A[tr], c);
            REP(r, tr + 1, n) if(A[r][c] != 0) {
                normRow(A[r], c);

                A[r] = subRow(A[tr], A[r], c);
            }
            ++tr;
        } else {
            free.push_back(c);
        }
    }

    for(int j = tr - 1; j >= 0; --j) {
        int c = pivots[j];
        forR(r, j) {
            A[r] = subRow(A[j], A[r], c);
        }
    }

    forR(r, pivots.size()) {
        int gc = A[r][pivots[r]];
        forR(c, m) gc = gcd(gc, A[r][c]);
        forR(c, m) A[r][c] /= gc;
        if(A[r][pivots[r]] < 0) A[r] = mul(A[r], -1);
    }

    return {A, pivots, free};
}

// solve Ax = b
int calc(vvi A, vi b) {
    vvi B = A;
    forR(i, b.size()) B.at(i).push_back(b[i]);
    // dout << B << endl;

    auto [R, pvt, fre] = rref(B);
    fre.pop_back(); // last column is the row loll
    // dout << R << endl;
    REP(r, pvt.size(), R.size()) forR(c, R[r].size()) assert(R[r][c] == 0);

    int k = fre.size();
    int n = R.size(), m = R[0].size();

    dout << R << endl;
    if(k == 0) {
        int tot = 0;
        forR(r, pvt.size()) {
            assert(R[r][m-1] >= 0 && R[r][m-1] % R[r][pvt[r]] == 0);
            tot += R[r][m-1] / R[r][pvt[r]];
        }
        return tot;
    }

    dout << "testing... " << k << endl;
    int MIN=0, MAX=200;
    vi trivLo(k, MIN), trivHi(k, MAX);
    forR(r, pvt.size()) {
        bool allPos = true;
        for(int c : fre) {
            allPos = allPos && R[r][c] >= 0;
        }

        if(allPos) {
            int ed = R[r][m-1];
            forR(ci, k) {
                int c = fre[ci];
                if(R[r][c] > 0) {
                    // ed - R[r][c] * k >= 0 -> k <= ed / R[r][c]
                    trivHi[ci] = min(trivHi[ci], ed / R[r][c] + 3);
                }
            }
        }
    }
    vi tst(k);
    forR(ci, k) tst[ci] = trivLo[ci];
    int bes = -1;

    while(tst[0] < trivHi[0]) {
        bool pos = true;

        vector<int> vals(m-1);
        forR(i, k) vals[fre[i]] = tst[i];
        for(int r = 0; r < pvt.size() && pos; ++r) {
            int cur = R[r][m-1];
            for(int c : fre) cur -= R[r][c] * vals[c];
            if(cur % R[r][pvt[r]] != 0 || cur < 0) {
                pos = false;
            } else {
                vals[pvt[r]] = cur / R[r][pvt[r]];
            }
        }

        if(pos){ 
            int amt = 0;
            for(int i : vals) amt += i;
            if(bes == -1) bes = amt;
            else bes = min(bes, amt);
        }

        ++tst[k-1];
        for(int j = k-1; j > 0; --j) if(tst[j] >= trivHi[j]) {
            tst[j] = trivLo[j];
            ++tst[j-1];
        }
    }

    assert(bes != -1);
    return bes;
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
        vvi A(mc.n, vi(mc.m));
        vi b = mc.jr;
        forR(c, mc.m) {
            for(int k : mc.bts[c]) A[k][c] = 1;
        }

        int bes = calc(A, b);
        tot += bes;
    }

    cout << tot << endl;
}