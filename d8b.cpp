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
    ll x, y, z;
};
coord operator-(coord a, coord b) {
    return {a.x-b.x, a.y-b.y, a.z-b.z};
}
ll norm(coord a) {
    return a.x * a.x + a.y * a.y + a.z * a.z;
}
ll sqrDist(coord a, coord b) {
    return norm(a-b);
}
struct edge {
    int a, b;
};

signed main() {
    vector<coord> cds;
    string line;
    while(cin >> line) {
        stringstream ls(line);
        string sx, sy, sz;
        getline(ls, sx, ',');
        getline(ls, sy, ',');
        getline(ls, sz, ',');

        int cx=stoi(sx), cy=stoi(sy), cz=stoi(sz);

        cds.push_back({cx, cy, cz});
    }

    vector<pair<int, int>> byDis;
    int n = cds.size();
    forR(i, n) REP(j, i+1, n) {
        byDis.push_back({i, j});
    }
    sort(byDis.begin(), byDis.end(), [&](pair<int, int> a, pair<int, int> b) {
        return sqrDist(cds[a.first], cds[a.second]) < sqrDist(cds[b.first], cds[b.second]);
    });

    cout << byDis.size() << ' ' << n << endl;

    vector<int> par(n), siz(n, 1);
    forR(i, n) par[i] = i;
    auto rt = [&](int cur, auto rt) -> int {
        return par[cur] == cur ? par[cur] : rt(par[cur], rt);
    };
    auto comb = [&](int a, int b) {
        a = rt(a, rt), b=rt(b, rt);
        dout << "res: " << a << ' ' << b << endl;
        if(a != b) {
            if(siz[a] < siz[b]) swap(a, b);
            par[b] = a;
            siz[a] += siz[b];
            siz[b] = 0;
            return a;
        }
        return a;
    };

    int firs=-1, sec=-1;
    for(auto [a, b] : byDis) if(firs == -1 && sec == -1) {
        dout << "conn: " << a << ' ' << b << endl;
        int chk = comb(a, b);
        if(siz[chk] == n) {
            firs = a, sec = b;
        }
        dout << "pars and sizes" << endl;
        for(int i : par) dout << i << ' ';
        dout << endl;
        forR(i, n) dout << rt(i, rt) << ' ';
        dout << endl;
        for(int i : siz) dout << i << ' ';
        dout << endl;
    }


    dout << cds[firs].x << ' ' << cds[sec].x << endl;
    ll prod = cds[firs].x * cds[sec].x;

    cout << prod << endl;
}