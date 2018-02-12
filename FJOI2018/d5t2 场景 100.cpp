/*
luoguU20012 day5T2 ����(game) 100pts

���⣺�����ϴӸ�������k�Σ�ÿ�����߾����ĵ�Ȩ��ÿ����ֻ�ܱ���һ�Σ�������ֵ

�ⷨ��̰�ģ�ÿ���ߵ��ܻ�ü�ֵ����Ҷ�ӣ�Ȼ���Ҷ�ӵ���·���ϵĵ�Ȩ������
���ߵ�Ȩʱ�����������������Ҷ�ӽڵ㶼��Ӱ�죬�������޸�
Ȼ��Ҫ֧���������ֵ�����߶������� 
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, LL> Data;
const int N = 2e5+50;
vector<int> e[N];
int n, m;
LL val[N];
int fa[N], leafCnt, leafL[N], leafR[N], id[N];  // id[i]Ϊ��i��Ҷ����ԭͼ�ı�� 
bool vis[N];
int dfn[N], dfsCnt;

struct Seg {
    struct Node {
        int L, R;
        LL lazy, mxVal;
        int mxPos;
    } tr[N<<2];
    
    int Son(int u, bool lr) {
        return u << 1 | lr;
    }
    
    void Update(int u) {
        int ls = Son(u, 0), rs = Son(u, 1);
        if (tr[ls].mxVal > tr[rs].mxVal) {
            tr[u].mxPos = tr[ls].mxPos;
            tr[u].mxVal = tr[ls].mxVal;
        } else {
            tr[u].mxPos = tr[rs].mxPos;
            tr[u].mxVal = tr[rs].mxVal;
        }
    }
    
    void Build(int u, int L, int R) {
        tr[u].L = L; tr[u].R = R;
        if (L == R) {
            tr[u].mxPos = L;
            return;
        }
        int mid = L + R >> 1;
        Build(Son(u, 0), L, mid);
        Build(Son(u, 1), mid+1, R);
        Update(u);
    }
    
    void PushDown(int u) {
        LL tmp = tr[u].lazy; tr[u].lazy = 0;
        int ls = Son(u, 0), rs = Son(u, 1);
        tr[ls].lazy += tmp; tr[ls].mxVal += tmp;
        tr[rs].lazy += tmp; tr[rs].mxVal += tmp;
    }
    
    void Add(int u, int l, int r, LL val) {
        if (tr[u].L == l && tr[u].R == r) {
            tr[u].mxVal += val;  // ��lazyʱ���ֵҲҪ�� 
            tr[u].lazy += val;
            return;
        }
        PushDown(u);
        int mid = tr[u].L + tr[u].R >> 1;
        if (l <= mid) Add(Son(u, 0), l, min(mid, r), val);
        if (r > mid) Add(Son(u, 1), max(mid+1, l), r, val);
        Update(u);
    }
    
    Data QueryMax() {  // ֻ��Ҫ��ȫ�����ֵ��Ҳ���Ǹ��ڵ�����ֵ 
        return make_pair(tr[1].mxPos, tr[1].mxVal);
    }
} seg;

void Dfs(int s) {  // ֱ��dfs���ݴ�ᱬջ������ջ�����dfs��Ȼ��dfs������ 
    stack<int> st; st.push(s);
    while (!st.empty()) {  // ��dfs�� 
        int u = st.top(); st.pop();
        dfn[++dfsCnt] = u;
        for (int siz = e[u].size(), i = 0; i < siz; i++)
            st.push(e[u][i]);
    }
    for (int i = dfsCnt; i >= 1; i--) {  // dfs������ 
        int u = dfn[i], siz = e[u].size();
        if (!siz) {
            leafL[u] = leafR[u] = ++leafCnt;
            id[leafCnt] = u;
            continue;
        }
        leafL[u] = N; leafR[u] = 0;
        for (int i = 0; i < siz; i++) {
            int v = e[u][i];
            leafL[u] = min(leafL[u], leafL[v]);
            leafR[u] = max(leafR[u], leafR[v]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> val[i];
    for (int u, v, i = 1; i < n; i++) {
        cin >> u >> v;
        e[u].push_back(v);
        fa[v] = u; 
    }
    Dfs(1);
    seg.Build(1, 1, leafCnt);
    for (int i = 1; i <= n; i++)
        seg.Add(1, leafL[i], leafR[i], val[i]);
    LL ans = 0;
    for (; m--; ) {
        Data res = seg.QueryMax();
        ans += res.second;
        for (int u = id[res.first]; u && !vis[u]; u = fa[u]) {
        	// ע��Ĺ��ĵ㲻���ٸĵڶ��� 
			// ���ߵ��Ѿ��߹��ĵ㣬�����ϵĵ�һ�����߹��ˣ�����Ҫ���� 
            vis[u] = true;
            seg.Add(1, leafL[u], leafR[u], -val[u]);
        }
    }
    cout << ans << endl;
    return 0;
}

