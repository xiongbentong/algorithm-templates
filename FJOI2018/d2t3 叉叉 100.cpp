/*
luoguU19766 day2T3 ���(square) 100pts

���⣺��һ��һȦ'.'һȦ'#'��ͼ�Σ�����һЩ����ַ��������ĵ������λ��
���Ŷ���Ϊ�����پ�����С��������������������ĵ�

�ⷨ��ÿ���㻭��ֿ飬������������������ÿ���ж�ԭ�㡢�ĸ��˵㡢�������Ľ���
�жϷ���Ϊö����Χ8*8�����ж�
ע�⽻�������xx.5����Ҫ������������������Ϊ�����ľ��ǲ��Ϸ��� 
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1050;
const LL INF = 1e16;

struct Line {
    LL b; int bel;  // bΪֱ�߽ؾ࣬belΪֱ�߶�Ӧ�ĵ����� 
    Line(LL _b=0, int _bel=0): b(_b), bel(_bel) {}
    bool operator < (const Line &t) const { return b < t.b; }
} lx[N], ly[N];

struct Point {
    LL x, y;
    Point(LL _x=0, LL _y=0): x(_x), y(_y) {}
} d[N], ans;

int n;
bool sx[N], sy[N];
int xjo[2], yjo[2], txjo[2], tyjo[2];
bool cr[N];

LL Mhd(const Point &a) {
    return abs(a.x) + abs(a.y);
}

Point Min(const Point &a, const Point &b) {
    LL tmp = Mhd(a) - Mhd(b);
    if (tmp != 0) return tmp > 0 ? b : a;
    if (a.x != b.x) return a.x > b.x ? a : b;
    return a.y > b.y ? a : b;
}

namespace C {
    LL a1, a2, b1, b2;
    bool px, py;
    
    bool In(const Point &p) {
        return p.y >= p.x+a1 && p.y <= p.x+a2 && p.y >= -p.x+b1 && p.y <= -p.x+b2;
    }
    
    bool CheckOne(const Point &p) {
        if ((p.x & 1) || (p.y & 1)) return false;  // ���Ϊxx.5�Ͳ��Ϸ� 
        if (!In(p)) return false;  // �ж��Ƿ��ڿ��� 
        return (p.x >> 1 & 1) == px && (p.y >> 1 & 1) == py;  // �Ȼ�ԭ��ԭ���꣬Ȼ���ж���ż�� 
    }
    
    void Check(const Point &p) {
        if (Mhd(p) > Mhd(ans) + 10) return;  // ��֦������Ҫ 
        // ö��8*8���� 
        for (int dx = -4; dx <= 4; dx++)
            for (int dy = -4; dy <= 4; dy++) {
                Point v(p.x+dx, p.y+dy);
                if (CheckOne(v)) ans = Min(ans, v);
            }
    }
}

Point Jd(LL b1, LL b2) {
    return Point(b2-b1>>1, b1+b2>>1);
}

void Calc(LL a1, LL a2, LL b1, LL b2, bool px, bool py) {
    C::a1 = a1; C::a2 = a2; C::b1 = b1; C::b2 = b2; C::px = px; C::py = py;
    // ԭ�㣬�ĸ��˵㣬�����ύ�� 
    C::Check(Point(0, 0)); C::Check(Jd(a1, b1)); C::Check(Jd(a1, b2)); C::Check(Jd(a2, b1)); C::Check(Jd(a2, b2)); 
    C::Check(Point(0, a1)); C::Check(Point(0, a2)); C::Check(Point(0, b1)); C::Check(Point(0, b2));
    C::Check(Point(-a1, 0)); C::Check(Point(-a2, 0)); C::Check(Point(b1, 0)); C::Check(Point(b2, 0)); 
}

void CalcAns(int i, int j) {
    for (int px = 0; px < 2; px++)
        for (int py = 0; py < 2; py++)
            if (!xjo[!px] && !yjo[!py])  // ��������������෴��ż�Եĵ� 
                Calc(lx[i].b, lx[i+1].b, ly[j].b, ly[j+1].b, px, py);
}

void Solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char ch;
        cin >> d[i].x >> d[i].y >> ch;
        sx[i] = sy[i] = ch == '#';
        sx[i] ^= d[i].x & 1; sy[i] ^= d[i].y & 1;
        d[i].x <<= 1; d[i].y <<= 1;  // �������� 
        lx[i] = Line(d[i].y-d[i].x, i);
        ly[i] = Line(d[i].x+d[i].y, i);
    }
    
    sort(lx+1, lx+n+1); sort(ly+1, ly+n+1);
    lx[0] = Line(-INF); lx[n+1] = Line(INF);
    ly[0] = Line(-INF); ly[n+1] = Line(INF);
    // �ӱ߽� 
    
    xjo[0] = xjo[1] = yjo[0] = yjo[1] = 0;
    txjo[0] = txjo[1] = tyjo[0] = tyjo[1] = 0;
    for (int i = 1; i <= n; i++)
        yjo[sy[i]]++;
    tyjo[0] = yjo[0]; tyjo[1] = yjo[1];
    
    memset(cr, 0, sizeof(cr));
    
    ans = Point(-INF, -INF);
    
    for (int i = 0; i <= n; i++) {
        if (i > 0) {
            xjo[0] = txjo[0]; xjo[1] = txjo[1];
            yjo[0] = tyjo[0]; yjo[1] = tyjo[1];
            int tmp = lx[i].bel;
            yjo[sy[tmp]]--; xjo[sx[tmp]]++;
            cr[tmp] = true;
            txjo[0] = xjo[0]; txjo[1] = xjo[1];
            tyjo[0] = yjo[0]; tyjo[1] = yjo[1];
        }
        CalcAns(i, 0);
        for (int j = 1; j <= n; j++) {
            int tmp = ly[j].bel;
            if (cr[tmp]) xjo[sx[tmp]]--, yjo[sy[tmp]]++;
            else yjo[sy[tmp]]--, xjo[sx[tmp]]++;
            CalcAns(i, j);
        }
    }
    if (ans.x > -INF)
        cout << ans.x / 2 << ' ' << ans.y / 2 << endl;
    else cout << "Too damaged" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    for (int cas = 1; cas <= T; cas++) {
        cout << "Case #" << cas << ": ";
        Solve();
    }
    return 0;
}

