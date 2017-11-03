#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int N = 3000050;
LL n, p, inv[N];
/*
�� a = p % i = p - p / i * i ͬ�� p / i * i 
����ͬ�� a * i
inv(i) ͬ�� -p / i * inv(p % i) 
-p/i�Ǹ������Ӹ�p
���Եõ���Ԫ����ʽ inv[i] = (p - p / i) * inv[p % i] % p 
*/
int main() {
	cin >> n >> p;
	inv[1] = 1; puts("1");
	for (int i = 2; i <= n; i++) {
		inv[i] = (p - p/i) * inv[p%i] % p;
		printf("%lld\n", inv[i]);
	}
	return 0;
}

