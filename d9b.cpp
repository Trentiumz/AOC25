#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>
#include <set>
#include <map>

using namespace std;
#define forR(i, a) for(int i = 0; i < (a); ++i)
#define REP(i, a, b) for(int i = (a); i < (b); ++i)
#define int ll
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
    ll x, y;
};

const int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
ll getMaxPair(vector<coord> &fullCds) {
    set<int> xcds, ycds;
    for(auto [x, y] : fullCds) {
        xcds.insert(x); xcds.insert(x-1); xcds.insert(x+1);
        ycds.insert(y); ycds.insert(y-1); ycds.insert(y+1);
    }
    // xcds.insert(-1); ycds.insert(-1);
    // xcds.insert(999999); ycds.insert(999999);
    vector<int> xc, yc;
    for(int i : xcds) xc.push_back(i);
    for(int i : ycds) yc.push_back(i);

    vector<coord> cds;
    for(auto [x, y] : fullCds) {
        cds.push_back({lower_bound(xc.begin(), xc.end(), x) - xc.begin(),
                        lower_bound(yc.begin(), yc.end(), y) - yc.begin()});
    }

    int c = cds.size();
    // cds = {{x, y}}, where x \in [0, n) and y\in [0, m)
    int n = xc.size(), m = yc.size();
    vector<vector<bool>> border(n, vector<bool>(m));
    forR(i, c) {
        coord cur = cds[i], nex = cds[(i+1)%c];
        if(nex.x == cur.x) {
            REP(cy, min(cur.y, nex.y), max(cur.y, nex.y) + 1) border[cur.x][cy] = true;
        } else if(nex.y == cur.y) {
            REP(cx, min(cur.x, nex.x), max(cur.x, nex.x) + 1) border[cx][cur.y] = true;
        } else {
            throw string("oops something went wrong..");
        }
    }

    forR(cy, m) {
        forR(cx, n) dout << border[cx][cy];
        dout << endl;
    }

    vector<vector<bool>> vis(n, vector<bool>(m, false));
    deque<coord> bfs;
    bfs.push_back({0, 0});
    vis[0][0] = true;
    while(!bfs.empty()) {
        coord las = bfs.front();
        bfs.pop_front();
        for(auto dir : dirs) {
            int nx=las.x+dir[0], ny=las.y+dir[1];
            if(0 <= nx && nx < n && 0 <= ny && ny < m && !border[nx][ny] && !vis[nx][ny]) {
                bfs.push_back({nx, ny});
                vis[nx][ny] = true;
            }
        }
    }

    vector<vector<bool>> good(n, vector<bool>(m));
    forR(cx, n) forR(cy, m) good[cx][cy] = !vis[cx][cy];

    dout << "good:" << endl;
    forR(cy, m) {
        forR(cx, n) dout << good[cx][cy];
        dout << endl;
    }

    vector<vector<int>> psa(n, vector<int>(m, 0));
    forR(cx, n) forR(cy, m){
        psa[cx][cy] = (good[cx][cy] ? 1 : 0) + (cx > 0 ? psa[cx-1][cy] : 0) + (cy > 0 ? psa[cx][cy-1] : 0) - (cx > 0 && cy > 0 ? psa[cx-1][cy-1] : 0);
    }

    ll ret = -1;
    forR(i, c) REP(j, i+1, c) {
        coord a=cds[i], b = cds[j];
        int lx=min(a.x, b.x), hx=max(a.x, b.x);
        int ly=min(a.y, b.y), hy=max(a.y, b.y);
        int numIn = psa[hx][hy] - (lx > 0 ? psa[lx-1][hy] : 0) - (ly > 0 ? psa[hx][ly-1] : 0) + (lx > 0 && ly > 0 ? psa[lx-1][ly-1] : 0);
        assert(numIn <= (hx-lx+1) * (hy-ly+1));
        if(numIn == (hx-lx+1) * (hy-ly+1)) {
            dout << i << ' ' << j << endl;
            ret = max(ret, (abs(fullCds[i].x-fullCds[j].x) + 1) * (abs(fullCds[i].y-fullCds[j].y) + 1));
        }
    }
    return ret;
}
signed main() {
    string line;
    vector<coord> cds;
    while(getline(cin, line)) {
        string p1, p2;
        stringstream lines(line);
        getline(lines, p1, ','); getline(lines, p2, ',');
        cds.push_back({stol(p1), stol(p2)});
    }

    ll bes = getMaxPair(cds);
    cout << bes << endl;
}