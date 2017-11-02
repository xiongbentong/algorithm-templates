#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 300, S = 10;
int n, b, m, mx[N][N][S], mi[N][N][S];
/*
���������Ǹ���������n,m,b��һ��n*m�ľ��������ɴ�ѯ�ʣ�ѯ��ĳ��b*b���������������Сֵ֮��
mx[i][j][k]��ʾ��(i,j)Ϊ���Ͻǣ��߳�Ϊ2^k���������е����ֵ
״̬ת�ƾͰ���������ηֳ��ĸ��߳�Ϊ2^(k-1)��С��������ȡmax
ѯ��Ҳ�ǰ�ѯ�ʵ������ηֳ��ĸ��߳�Ϊ2^t�������Σ����ܻ��ص���
Ԥ����O(n^2logn)��ѯ��O(1)���ռ�O(n^2logn) 
��������θĳɾ��Σ�����Ҫ����ά�����ʾ����������ꡢ���Ϳ�
Ԥ����O(n^2log2n)��ѯ��O(1)���ռ�O(n^2log2n) 
����ռ俪���£����Զ�ÿ�н���һ��һάRMQ��ѯ��ʱO(n)ö����ȡ���ֵ
����Ԥ����O(n^2logn)��ѯ��O(n)���ռ�O(n^2logn)������Ҳû����٣� 
*/ 
int main() {
	scanf("%d%d%d", &n, &b, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			scanf("%d", &mx[i][j][0]);
			mi[i][j][0] = mx[i][j][0];
		}
	for (int k = 1; k <= log(b) / log(2); k++)
		for (int i = 1, len = 1 << (k - 1); i <= n - (1 << k) + 1; i++)
			for (int j = 1; j <= n - (1 << k) + 1; j++) {
				mx[i][j][k] = max(mx[i][j][k-1], max(mx[i+len][j][k-1], max(mx[i][j+len][k-1], mx[i+len][j+len][k-1])));
				mi[i][j][k] = min(mi[i][j][k-1], min(mi[i+len][j][k-1], min(mi[i][j+len][k-1], mi[i+len][j+len][k-1])));
			}
	for (int t = log(b) / log(2), py = b - (1 << t), x, y; m--; ) {
		scanf("%d%d", &x, &y);
		int maxx = max(mx[x][y][t], max(mx[x+py][y][t], max(mx[x][y+py][t], mx[x+py][y+py][t])));
		int minn = min(mi[x][y][t], min(mi[x+py][y][t], min(mi[x][y+py][t], mi[x+py][y+py][t])));
		printf("%d\n", maxx - minn);
	}
	return 0;
}
