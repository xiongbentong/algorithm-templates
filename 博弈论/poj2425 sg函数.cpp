#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int N = 1050;
vector<int> e[N];
int sg[N];

int SG(int u) {
	/*
	sg[u]>0��u�Ǳ�ʤ�㣬sg[u]=0���Ǳذܵ�
	sg[u]=mex(sg[v])��v��u�ĺ��״̬��mex����С�Ĳ��ڼ����е��� 
	���ڲ���ɵĶ�������ܵ�ʤ��������������sg��������Ϊ0��ذܣ������ʤ
	��Ϊ�� sg[u] = k���� sg[u] ��һ�����Ե��� 0 ~ k-1 ��ÿһ��sgֵ�����ߵ�sgֵΪ0���Ǳذܵ�
	�����ķ��������ͬ�ģ�����ʤ���ж�Ҳ����ķ������ͬ������Ϊ0��ذ�
	����ķ���ģ���n��ʯ�ӣ�ÿ�ο��Դ�����һ��ȡ����������ȡ���ʤ�� 
	Ψһ�Ĳ�ͬ�����sg������һ�����Ա�࣬��ֻ�бذܵ�һ���Ż����࣬����ʤ��һ��ֻҪ�ٱ�����ͺ��� 
	*/
	if (~sg[u]) return sg[u];
	bool vis[N] = {0};
	for (int siz = e[u].size(), i = 0; i < siz; i++)
		vis[SG(e[u][i])] = true;  // �������״̬ 
	for (sg[u] = 0; vis[sg[u]]; sg[u]++);  // �ں��״̬����mex 
	return sg[u];
}

int main() {
	for (int n; scanf("%d", &n) == 1; ) {
		memset(sg, -1, sizeof(sg));
		for (int i = 0; i < n; i++)
			e[i].clear();
		for (int u = 0, siz; u < n; u++) {
			scanf("%d", &siz);
			if (!siz) sg[u] = 0;
			for (int v; siz--; e[u].push_back(v))
				scanf("%d", &v);
		}
		for (int m; scanf("%d", &m) == 1 && m; ) {
			int s = 0;
			for (int u; m--; s ^= SG(u))  // s�������� 
				scanf("%d", &u);
			printf(s ? "WIN\n" : "LOSE\n");
		}
	}
	return 0;
}

