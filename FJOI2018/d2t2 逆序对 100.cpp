/*
luoguU19765 day2T2 �����(perm) 100pts

���⣺������������Ϊ��ɢ������ͬ������
��P1,P2����[1,n]�����У�F(P1,P2)Ϊ����P1[l,r]��P2[l,r]���ƣ�
��P1[l,r]�������������m��(l,r)��Ŀ
��P1,P2ȡ��[1,n]���������е�F(P1,P2)֮��

�ⷨ��
��g(i,j)Ϊ����Ϊi�����У��������ĿΪj�ķ�����
��g(i,j)=g(i-1,j-k)��0<=k<=i-1����ʾ�������������Ϊk 
f(i,j)Ϊ����Ϊi�����У��������Ŀ������j�ķ�����
��f(i,j)Ϊg(i,j)��ǰ׺��
����������
���ȿ���[l,r]����
[l,r]�����������е�λ����(n-len+1)��
ÿ���������ļ���������������ΪC(n,len)��������ΪC(n,len)^2 
���伸�����Ĵ�С��ϵ��f(len,m)��
�ٿ���ʣ�����䣬����������ÿ��������������ȡ��������Ϊ((n-len)!)^2
ans(len)=(n-len+1)*f(len,m)*(C(n,len)*(n-len)!)^2
   =(n-len+1)*f(len,m)*(n!/len!)^2
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 500, MOD = 1e9+7;

int f[N+50][N*N/2+50], fac[N+50], inv[N+50];

int qPow(int a, int k) {
	int ret = 1, tmp = a;
	for (; k; k >>= 1, tmp = 1LL * tmp * tmp % MOD)
		if (k & 1) ret = 1LL * ret * tmp % MOD;
	return ret;
}

void Pret() {
	f[1][0] = f[1][1] = 1;
	for (int i = 2; i <= N; i++) {
		int k = i*(i-1)/2;  // ��������� 
		for (int j = 0; j <= k; j++) {
			f[i][j] = f[i-1][j];
			if (j - i >= 0) f[i][j] = (f[i][j] - f[i-1][j-i] + MOD) % MOD;
			// g[i][j]=f[i-1][(j-i+1)~j]����f[i][j]=f[i-1][j]-f[i-1][j-i] 
			if (j > 0) f[i][j] = (f[i][j] + f[i][j-1]) % MOD;  // ��Ϊ��ǰ׺�ͣ�������һ��f 
		}
		int k1 = (i+1)*i/2;
		for (int j = k + 1; j <= k1; j++)
			f[i][j] = f[i][j-1];
		// ��Ϊf[i+1][j]���õ�f[i][j]�����Ե�i���jҪ����i+1��ķ�Χ 
	}
	fac[0] = fac[1] = inv[0] = inv[1] = 1;
	for (int i = 2; i <= N; i++) {
		fac[i] = 1LL * fac[i-1] * i % MOD;
		inv[i] = qPow(fac[i], MOD - 2);
	}
}

int main() {
	ios::sync_with_stdio(false);
	Pret();
	int T; cin >> T;
	for (int n, m; T--; ) {
		cin >> n >> m;
		int ans = 0;
		for (int len = 1; len <= n; len++) {  // ö�����䳤��len 
			int k = min(m, len*(len-1)/2);  // m���ֻҪ����������� 
			int tmp = 1LL * fac[n] * inv[len] % MOD;
			ans = (ans + 1LL * (n-len+1) * f[len][k] % MOD * tmp % MOD * tmp % MOD) % MOD;
			// �����湫ʽ���ǵ�ȡģ 
		}
		cout << ans << endl;
	}
    return 0;
}

