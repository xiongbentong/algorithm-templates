#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <utility>
#include <stack>
using namespace std;
const int N = 1050;
vector<int> e[N];
int dfscnt, dfn[N], low[N], bcnt, kcnt, belong[N];
stack<int> st;
pair<int, int> bridge[N];

void tarjan(int u, int fa) {  // Tarjan���� 
	low[u] = dfn[u] = ++dfscnt;
	st.push(u);  // ��˫��ͨ����û���ظ��㣬����ջ���㣬��˫��ͨ�ʹ�� 
	for (int siz = e[u].size(), i = 0; i < siz; i++) {
		int v = e[u][i];
		if (!dfn[v]) {
			tarjan(v, u);
			low[u] = min(low[u], low[v]);  // �ǵø���low[u] 
			if (low[v] > dfn[u]) {  // ��v�޷�ͨ����(u,v)����ı߷���u��u�����ȣ���(u,v)���� 
				bridge[++bcnt] = make_pair(u, v);
				++kcnt;
				while (!st.empty()) {  // ��v������ʣ�µĵ㶼��ջ������µı�˫��ͨ���� 
					int tmp = st.top(); st.pop();
					belong[tmp] = kcnt;
					if (tmp == v) break;
				}
			}
		}
		else if (v != fa) low[u] = min(low[u], dfn[v]);
	}
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int u, v; m--; e[u].push_back(v), e[v].push_back(u))
		scanf("%d%d", &u, &v);
	tarjan(1, 0);
	if (!st.empty()) {
		++kcnt;
		while (!st.empty()) {
			belong[st.top()] = kcnt;
			st.pop();
		}
	}
	int d[N] = {0};
	for (int i = 1; i <= bcnt; i++) {
		int u = bridge[i].first, v = bridge[i].second;
		++d[belong[u]]; ++d[belong[v]];  // ����ÿ����˫��ͨ��������һ������ĵĶ� 
	}
	int leaf = 0;
	for (int i = 1; i <= kcnt; i++)
		leaf += d[i] == 1;  // leaf��Ҷ�ӽ���� 
	printf("%d\n", (leaf + 1) >> 1);  // һ�����ۣ�����Ҫ��(leaf+1)/2���߲���ʹͼû���ţ�ÿ����������Ҷ�ӣ� 
    return 0;
}

