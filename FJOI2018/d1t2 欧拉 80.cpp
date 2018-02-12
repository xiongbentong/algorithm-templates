/*
luoguU19863 day1T2 ŷ��(phi) 80pts

���⣺�������У�֧�ֵ����޸ģ���ѯ����͵�ŷ����������ѯ�������ŷ������
n<=5e4, a<=4e4

�ⷨ��
�����޸ģ�ֱ�Ӹ� 
���ڼӷ������������ᱬint��ֱ������״����ӣ�Ȼ��ֽ�������ֱ����ŷ������
���ڳ˷���ÿ��O(n)ɨһ�飬���Ҷ�ÿ�����ֽ���������ͳ�Ƴ��˻���ÿ���������Ĵ������������ŷ������ 
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 5e4+50, A = 4e4, MOD = 1e9+7;

int pri[A+50], ptop;
int minp[A+50];

namespace Sieve {
    bool vis[A+50];
    
    void Sieve() {
        for (int i = 2; i <= A; i++) {
            if (!vis[i]) pri[ptop++] = minp[i] = i;
            for (int j = 0, t; j < ptop && (t=i*pri[j]) <= A; j++) {
                vis[t] = true;
                minp[t] = pri[j];  // minpΪ��С������ 
                if (i % pri[j] == 0) break;
            }
        }
    }
}

struct Bit {
    int n, a[N];
    
    void Init(int _n) { n = _n; }
    int Lowbit(int x) { return x & -x; }
    
    void Add(int pos, int val) {
        for (int i = pos; i <= n; i += Lowbit(i))
            a[i] += val;
    }
    
    int Query(int pos) {
        int ret = 0;
        for (int i = pos; i; i -= Lowbit(i))
            ret += a[i];
        return ret;
    }
    
    int Query(int l, int r) {
        return Query(r) - Query(l-1);
    }
} bit;

int GetPhi(int x) {
    int ret = x;  // ��ֵΪn 
    for (int i = 0; i < ptop && pri[i]*pri[i] <= x; i++)
        if (x % pri[i] == 0) {
            ret -= ret / pri[i];  // ret*=(1-1/pri[i])��ע�����ÿ��������ֻ�ܳ�һ�� 
            while (x % pri[i] == 0)
                x /= pri[i];
        }
    if (x > 1) ret -= ret / x;  // �п�����һ�����ڸ��ŵ������� 
    return ret;
}

int inv[A];

int qPow(int x, int k) {
    int ret = 1, tmp = x;
    for (; k; k >>= 1, tmp = 1LL * tmp * tmp % MOD)
        if (k & 1) ret = 1LL * ret * tmp % MOD;
    return ret;
}

int Inv(int x) {
    if (!inv[x]) inv[x] = qPow(x, MOD - 2);
    return inv[x];
}

int vis[A];

void Calc(int x, int tim, int &ans) {
    while (x > 1) {
        int p = minp[x];  // ��ΪҪ�ֽ�����Ƚ�С��������Ԥ�������С�������ֽ� 
        if (vis[p] < tim) {
            vis[p] = tim;  // ��֤ÿ��������ֻ��һ�� 
            ans = (ans + MOD - 1LL * ans * Inv(p) % MOD) % MOD;
        }
        while (x % p == 0) x /= p;
    }
}

int main() {
    Sieve::Sieve();
    int n, m, a[N]; scanf("%d%d", &n, &m);
    bit.Init(n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        bit.Add(i, a[i]);
    }
    for (int opt, r1, r2, i = 1; i <= m; i++) {
        scanf("%d%d%d", &opt, &r1, &r2);
        if (opt == 0) bit.Add(r1, r2 - a[r1]), a[r1] = r2;
        if (opt == 1) printf("%d\n", GetPhi(bit.Query(r1, r2)));
        if (opt == 2) {
            int ans = 1;
            for (int j = r1; j <= r2; j++) {
                ans = 1LL * ans * a[j] % MOD;  // ansҪ���ϳ˻����ٳ���ÿ����������(1-1/p) 
                Calc(a[j], i, ans);
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}

