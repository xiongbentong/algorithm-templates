#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 50000;
bool vis[N+50];
int miu[N+50], sum[N+50];
int prime[N+50], pcnt;

void calcMiu() {  // miu�ǻ��Ժ�������������ɸ
	miu[1] = 1;
	for (int i = 2; i <= N; i++) {
		if (!vis[i]) miu[i] = -1, prime[pcnt++] = i;  // ����miu=-1 
		for (int j = 0; j < pcnt && i * prime[j] <= N; j++) {
			vis[i*prime[j]] = true;
			if (i % prime[j] == 0) break;  // �� p[j]|i���� p[j]*p[j]|i*p[j]��miu[i*p[j]]=0 
			miu[i*prime[j]] = -miu[i];  // ��p[j]��i���ʣ��ɻ��Ժ�����miu[i*p[j]]=miu[i]*miu[p[j]]=-miu[i]
		}
	}
	for (int i = 1; i <= N; i++)
		sum[i] = sum[i-1] + miu[i];  // ǰ׺�� 
}

int calc(int n, int m) {
	if (n > m) swap(n, m);
	int ret = 0;
	for (int l = 1, r; l <= n; l = r + 1) {
		r = min(n / (n/l), m / (m/l));  // ����n/i=n/l��i���Ϊn/(n/l)
		ret += (sum[r] - sum[l-1]) * (n/l) * (m/l);  // ��[l,r]�ڵĦ�miu(i)*f(i) 
	}
	return ret;
}

/*
������������[1,n]��[1,m]�ڸ�ѡһ�������ʵ����Ը���

Ī����˹������
miu[1] = 1
miu[p1*p2*...*pk] = (-1)^k
miu[other] = 0
��Ϊ�ɵ�����������ɵ���miu=-1��˫����miu=1�����������ݳ�ϵ�������ٽ���������йص��ݳ�����

��f(i)Ϊ i|gcd(a,b) �����Ը���
f(i) = (n/i) * (m/i) ������ĳ�����ȡ���� 
�������Ը��� = f(1) - f(2) - f(3) + 0*f(4) - f(5) + f(2*3=6)...
f(i)ǰ��ϵ��Ϊmiu[i] 
ע�⵽ n/i ��ֵ�������ںü�����������ͬ�ģ���֤��ΪO(����n)�� 
���Զ�miu��һ��ǰ׺�ͣ�Ȼ��һ��һ������ʱ�临�Ӷ� O(����n) 
*/
int main() {
	calcMiu();
	int T; scanf("%d", &T);
	for (int xl, xr, yl, yr, g; T--; ) {
		scanf("%d%d%d%d%d", &xl, &xr, &yl, &yr, &g);
		xl = (xl - 1) / g; yl = (yl - 1) / g; xr /= g; yr /= g;
		printf("%d\n", calc(xl, yl) + calc(xr, yr) - calc(xl, yr) - calc(xr, yl));
	}
    return 0;
}

