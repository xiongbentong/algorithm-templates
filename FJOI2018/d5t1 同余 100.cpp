/*
luoguU20011 day5T1 ͬ��(exclaim) 100pts

���⣺��1<=a<=b<=c<=n��a+b^2ͬ��c^3��(a,b,c)����

�ⷨ����[b^2+1,b^2+b]ÿ����%mod������״���飬ö��c�������ѯ
����ķ������������ѭ���ڣ����ȼ���������ѭ���ڸ�����Ȼ��ͷβ�������޸� 
*/ 
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+50;
int n, mod;

struct Bit {  // �����޸ĵ����ѯ 
    int siz, tr[N];
    void Init(int _siz) { siz = _siz; memset(tr, 0, sizeof(tr)); }
    int Lowbit(int x) { return x & -x; }
    void Add(int pos, int val) {
        for (int i = ++pos; i <= siz; i += Lowbit(i))  // pos�Ǵ�0��ʼ�ģ�Ҫ+1 
            tr[i] += val;
    }
    void Add(int l, int r, int val) {
        Add(l, val); Add(r+1, -val);
    }
    int Query(int pos) {
        int ret = 0;
        for (int i = ++pos; i; i -= Lowbit(i))
            ret += tr[i];
        return ret;
    }
} bit;

void Insert(int l, int r) {
    if (l > r) Insert(0, r), Insert(l, mod-1);  // �߽Ƿ������� 
    else bit.Add(l, r, 1);
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    for (int cas = 1; cas <= T; cas++) {
        cin >> n >> mod;
        bit.Init(mod);
        long long ans = 0, cnt = 0;
        for (int i = 1; i <= n; i++) {
            cnt += i / mod;  // �𰸼�������ѭ���ڸ���i/mod 
            if (i % mod) Insert((1LL*i*i+1) % mod, (1LL*i*i+i) % mod);
            ans += cnt + bit.Query(1LL*i*i%mod*i%mod);
        }
        cout << "Case " << cas << ": " << ans << endl;
    }
    return 0;
}

