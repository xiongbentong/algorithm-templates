#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 500050;
const double INF = 0x3f3f3f3f;
int n;
double a[N], f[N], g[N];

void bs(double *f, int ul, int ur, int l, int r) {  // ���֣������f����Ϊul~ur�����ߵ�����Ϊl~r 
	if (ul > ur || l > r) return;
	int mid = (ul + ur) >> 1, pos;
	f[mid] = -INF;
	for (int i = l; i <= r && i <= mid; i++)  // ����ö��f[mid]�ľ��ߵ� 
		if (a[i] + sqrt(mid - i) > f[mid])
			f[mid] = a[i] + sqrt(mid - i), pos = i;
	f[mid] -= a[mid];
	bs(f, ul, mid - 1, l, pos);  // ����ul~mid-1���䣬���ߵ����l~pos֮�� 
	bs(f, mid + 1, ur, pos, r);  // ͬ�� 
}

int main() {
	// ���⣺һ�����ߵ���dp���������治��Ҫ 
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lf", &a[i]);
	bs(f, 1, n, 1, n);
	reverse(a + 1, a + n + 1);
	bs(g, 1, n, 1, n);
	for (int i = 1; i <= n; i++)
		printf("%.0lf\n", ceil(max(f[i], g[n-i+1])));
	return 0;
}

