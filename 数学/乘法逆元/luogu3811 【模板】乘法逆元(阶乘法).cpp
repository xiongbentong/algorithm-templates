#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int N = 3000050;
LL n, p, f[N], ans[N];

LL fastPow(LL a, LL k) {
	LL ret;
	for (ret = 1; k; k >>= 1, a = a * a % p)
		if (k & 1) ret = ret * a % p;
	return ret;
}
/*
�� ny(x) ��ʾx�ĳ˷���Ԫ 
�� f[i] = i! % p, g[i] = ny(i!) % p
���԰� g[i] ���� 1/(i!) 
�� g[i] = g[i+1] * (i+1)
���� ny(i) = f[i-1] * g[i]
*/
int main() {
	scanf("%lld%lld", &n, &p);
	f[0] = 1;
	for (int i = 1; i <= n; i++)
		f[i] = f[i-1] * i % p; 
	// ����С������p��������gcd(a,p)=1����a^(p-1)ͬ��1(mod p)��a^(p-2)����a�ĳ˷���Ԫ 
	LL g = fastPow(f[n], p-2);
	ans[n] = g * f[n-1] % p;
	for (int i = n-1; i; i--) {
		g = g * (i + 1) % p;
		ans[i] = g * f[i-1] % p;
	}
	for (int i = 1; i <= n; i++)
		printf("%lld\n", ans[i]);
	return 0;
}

