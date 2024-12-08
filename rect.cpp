#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN = 1e5 + 10;
const int MAXY = 1e6 + 10;
struct Point {
    int x;
    int y;
    bool friend operator < (Point a, Point b) {
        return a.x < b.x;
    }
};
struct Side {
    int x;
    int y1;
    int y2;
    int type;
    int ind;
    bool friend operator < (Side a, Side b) {
        return a.x < b.x;
    }
};
Point points[MAXN];
vector <Side> sides;
int tree[4 * MAXY];
int ans[MAXN];
void update(int node, int l, int r, int qind) {
    if (l == r) {
        tree[node]++;
        return;
    }

    int mid = (l+r) / 2;
    if (qind <= mid) update(node*2, l, mid, qind);
    else update(node*2 + 1, mid+1, r, qind);

    tree[node] = tree[node*2] + tree[node*2 + 1];
}
int query(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return tree[node];
    int mid = (l+r) / 2;

    return query(node*2, l, mid, ql, qr) + query(node*2 + 1, mid+1, r, ql, qr);
}
int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    int x1, y1, x2, y2;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        Side cur = {x1 - 1, y1, y2, 0, i};
        sides.push_back(cur);
        cur.type = 1;
        cur.x = x2;
        sides.push_back(cur);
    }
    sort(points, points + n);
    sort(sides.begin(), sides.end());

    int curp = 0;
    for (int i = 0; i < sides.size(); i++) {
        while (curp < n && points[curp].x <= sides[i].x) {
            update(1, 0, MAXY - 10, points[curp].y);
            curp++;
        }
        int res = query(1, 0, MAXY - 10, sides[i].y1, sides[i].y2);
        if (sides[i].type == 0) ans[sides[i].ind] -= res;
        else ans[sides[i].ind] += res;
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
