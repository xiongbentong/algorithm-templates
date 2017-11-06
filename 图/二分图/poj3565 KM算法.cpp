#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 105, D = 100000, INF = 0x3f3f3f3f;
int n, pre[N];
double a[N][N], dx[N], dy[N], slack[N];
bool px[N], py[N];

bool dfs(int u) {
	px[u] = true;
	for (int v = 1; v <= n; v++)
		if (!py[v]) {
			double t = dx[u] + dy[v] - a[u][v];
			if (!t) {  // v �������ͼ�� 
				py[v] = true;
				if (!pre[v] || dfs(pre[v])) {  // �������㷨 
					pre[v] = u;
					return true;
				}
			}
			else slack[v] = min(slack[v], t);  // v in T'������� slack[v] 
		}
	return false;
}

void km() {
	/*
	km�㷨�������ͼ���Ȩƥ�䣬����Ȩ����������ƥ��
	�㷨��ÿ���㹹����һ�����ж���dx��dy�����ұ�֤ dx[u] + dy[v] >= w(u,v)  
	���������ͼΪ���е������ dx[u] + dy[v] = w(u,v) �����б�
	��֤�����ͼ������ƥ��Ϊ���Ȩƥ�䣬��Ҫ��취������ж���ʹ�����ͼ��������ƥ��
	��dfs���ĵ㼯Ϊ S �� T ��ûdfs����Ϊ S' �� T'
	�� S -> T' �ޱߣ� S' -> T ��ƥ���
	��ʱ����Ҫ�ı� S �Ķ��꣬ʹ S -> T' ���±߽���
	������ dx[S] -= a, dy[T] += a (a = min(dx[u] + dy[v] - w(u, v)), u in S, v in T')
	�� a �����ֵС�����±߽��룬�����ֵ���򶥱겻�Ϸ�
	ÿ���� v in T' �� min(dx[u] + dy[v] - w(u, v), u in S) ����slack������ά�� 
	���Ӷ� O(n3) 
	*/
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			dx[i] = max(dx[i], a[i][j]);  // ��㹹��һ����ʼ���ж��꣬dx[u]=max(w(u, v)), dy[u]=0 
	for (int i = 1; i <= n; i++) {  // ÿ������һ������· 
		for (int j = 1; j <= n; j++)
			slack[j] = INF;
		while (true) {
			memset(px, 0, sizeof(px));
			memset(py, 0, sizeof(py));
			if (dfs(i)) break;  // �ҵ�����·���˳� 
			double t = INF;
			for (int j = 1; j <= n; j++)
				if (!py[j]) t = min(t, slack[j]);  // �� T' ����һ����С��slackֵ������ 
			for (int j = 1; j <= n; j++) {
				if (px[j]) dx[j] -= t;
				if (py[j]) dy[j] += t;
				else slack[j] -= t;  // S ��ÿ����Ķ��궼 +t ���� T' �е� slack ��ӦҪ�� t 
			}
		}
	}
}

int main() {
	int x[N<<1], y[N<<1];
	cin >> n;
	for (int i = 1; i <= 2 * n; i++)
		cin >> x[i] >> y[i];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			int xx = x[i] - x[j+n], yy = y[i] - y[j+n];
			a[i][j] = D - sqrt(xx * xx + yy * yy);
		}
	km();
	int ans[N];
	for (int i = 1; i <= n; i++)
		ans[pre[i]] = i;
	for (int i = 1; i <= n; i++)
		cout << ans[i] << endl;
	return 0;
}

