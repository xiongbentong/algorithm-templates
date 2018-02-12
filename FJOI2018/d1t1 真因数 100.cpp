/*
luoguU19723 day1T1 ������(factor) 100pts

���⣺��[l,r]֮��ÿ������������С�������ĺ�, l,r<=1e9

�ⷨ��
��f[i][j]��ʾ[2,i]�ڵ���ɸ��ǰj��������ʣ�µ����ĺ�
��j������ɸ����������pri[j]*x
���pri[j]^2>i��ɸ�����κ�����f[i][j]=f[i][j-1]
����2<=x<=i/pri[j]����x����ǰj-1������
��ôx��f[i/pri[j]][j-1]�У��Ҳ�Ϊǰj-1������ 
f[i][j]=f[i][j-1]-pri[i]*(f[i/pri[j]][j-1]-sum[j-1])
sum[j-1]Ϊǰj-1������֮�� 
����𰸺�pri[j]��Ϊminp�Դ𰸵Ĺ���Ϊ(f[i][j-1]-f[i][j])/pri[j]
���ڿռ䣬n/i��ȡ��ֻ��2*sqrt(n)��ȡֵ
��ô����ʵֵ�������±����໥ӳ�伴�� 
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int M = 1e5;
const int PoolSize = 1e7;

LL n, m;
LL pool[PoolSize];
LL *f[M*2+50], *it;
int siz[M*2+50];
int pri[M+50]; int pTop;
bool vis[M+50];
LL pSum[M+50];

void Sieve() {
    for (LL i = 2; i <= M; i++) {
        if (!vis[i]) {
            pri[++pTop] = i;
            pSum[pTop] = pSum[pTop-1] + i;
        }
        for (int j = 1; j <= pTop && 1LL*i*pri[j] <= M; j++) {
            vis[i*pri[j]] = true;
            if (i % pri[j] == 0) break;
        }
    }
}

LL GetF(LL i, int j) {
    LL pos = i <= m ? i : m*2+1-n/i;  // ��������������� 
    return f[pos][min(j, siz[pos])];
}

LL Solve(LL lim) {
    if (!lim) return 0;
    m = sqrt(n = lim); it = pool;
    for (LL pos = 1; pos <= m * 2; pos++) {
        LL i = pos <= m ? pos : n/(m*2+1-pos);
        // iΪ��ʵֵ��posΪ�±꣬��ʵֵ1~m��Ӧ�±�1~m����ʵֵm~nÿһ�ζ�Ӧ�±�m+1~2m 
        f[pos] = it; siz[pos] = 0;
        f[pos][0] = 1LL*i*(i+1)/2-1;
        for (int j = 1; 1LL*pri[j]*pri[j] <= i; j++, siz[pos]++)
            f[pos][j] = f[pos][j-1] - 1LL * pri[j] * (GetF(i/pri[j], j-1) - pSum[j-1]);
        it += siz[pos] + 1;
    }
    LL ret = 0;
    for (LL i = 0; i < siz[m*2]; i++)
        ret += (f[m*2][i] - f[m*2][i+1]) / pri[i+1];
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    Sieve();
    LL l, r; cin >> l >> r;
    cout << Solve(r) - Solve(l - 1) << endl;
    return 0;
}

