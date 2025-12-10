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

const int CONN = 1000;
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

    vector<vector<int>> adj(n);
    dout << "edges:" << endl;
    forR(i, CONN) {
        auto [a, b] = byDis[i];
        adj[a].push_back(b);
        adj[b].push_back(a);
        dout << '\t' << a << ' ' << b << endl;
    }

    vector<bool> vis(n, false);
    vector<int> grp(n, -1);
    forR(st, n) if(!vis[st]) {
        deque<int> bfs = {st};
        grp[st] = st; vis[st] = true;
        while(!bfs.empty()) {
            int cur = bfs.front();
            bfs.pop_front();
            for(int nex : adj[cur]) {
                if(!vis[nex]) {
                    vis[nex] = true;
                    grp[nex] = st;
                    bfs.push_back(nex);
                }
            }
        }
    }

    for(int i : grp) dout << i << ' ';
    dout << endl;

    map<int, int> sizes;
    for(int i : grp) ++sizes[i];

    vector<int> sizList;
    for(auto [st, siz] : sizes) {
        sizList.push_back(siz);
    }
    sort(sizList.begin(), sizList.end(), [](int a, int b){ return a > b;});

    ll prod = (ll) sizList.at(0) * sizList.at(1) * sizList.at(2);

    cout << prod << endl;
}