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
    vector<string> grid;
    string line;
    while(getline(cin, line)) {
        grid.push_back(line);
    }
    int n = grid.size(), m = grid[0].size();

    auto isBlank = [&](int col) {
        forR(i, n) if(grid[i][col] != ' ') return false;
        return true;
    };

    ll tot = 0;
    int curInd = 0;
    while(curInd < m) {
        while(curInd < m && isBlank(curInd)) ++curInd;
        if(curInd >= m) continue;
        int nexInd = curInd + 1;
        while(nexInd < m && !isBlank(nexInd)) ++nexInd;
        dout << curInd << ' ' << nexInd << endl;

        // [curInd, nexInd)
        vector<ll> nums;
        char op = ' ';
        REP(ci, curInd, nexInd) {
            ll curNum = -1;
            forR(ri, n - 1) if(grid[ri][ci] != ' ') {
                if(curNum == -1) curNum = grid[ri][ci] - '0';
                else curNum = curNum * 10 + (grid[ri][ci] - '0');
            }
            nums.push_back(curNum);

            if(grid[n-1][ci] != ' ') op = grid[n-1][ci];
        }

        dout << '\t';
        for(ll num : nums) dout << num << ' ';
        dout << endl;

        if(op == '*') {
            ll val = 1;
            for(ll num : nums) val = val * num;
            tot += val;
        } else if(op == '+') {
            ll val = 0;
            for(ll num : nums) val = val + num;
            tot += val;
        }

        curInd = nexInd;
    }

    cout << tot << endl;
}