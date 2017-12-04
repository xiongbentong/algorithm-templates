#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N = 10050, M = 100050, INF = 0x3f3f3f3f;

struct Graph {
	struct Edge {
		int to, f, nxt;
		Edge(int _to=0, int _f=0, int _nxt=0): to(_to), f(_f), nxt(_nxt) {}
	} e[M<<1];
	int head[N], ecnt;
	
	Graph() { memset(head, -1, sizeof(head)); }
	void add1(int u, int v, int f) { e[ecnt] = Edge(v, f, head[u]); head[u] = ecnt++; }
	void add(int u, int v, int f) { add1(u, v, f); add1(v, u, 0); }
};

struct Network {  // sap�㷨ģ�� 
	Graph G;
	int s, t;
	int h[N], gap[N], cur[N];  // gap��϶�Ż���cur��ǰ���Ż� 
	bool stop;
	
	bool bfs() {  // ����bfsԤ����߶� 
		memset(h, -1, sizeof(h)); gap[h[t]=0]++;
		queue<int> q; q.push(t);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = G.head[u]; ~i; i = G.e[i].nxt) {
				int v = G.e[i].to;
				if (h[v] == -1) {
					gap[h[v] = h[u] + 1]++;
					q.push(v);
				}
			}
		}
		return ~h[s];
	}
	
	int dfs(int u, int surplus) {  // surplusΪ��ǰ���ӯ�� 
		if (u == t) return surplus;
		int flow = 0;  // �ɹ����������� 
		for (int i = cur[u]; ~i; i = G.e[i].nxt) {
			int v = G.e[i].to;
			if (G.e[i].f && h[u] == h[v] + 1) {  // �߶Ȳ�1ʱ������ 
				int curFlow = dfs(v, min(surplus - flow, G.e[i].f));
				G.e[i].f -= curFlow;
				G.e[i^1].f += curFlow;
				flow += curFlow;
				if (flow == surplus) {
					cur[u] = i;  // ���µ�ǰ�� 
					return flow;
				}
			}
		}
		if (!--gap[h[u]]) stop = true;  // �жϲ����˳� 
		gap[++h[u]]++;
		cur[u] = G.head[u];  // �ر��֮��ǰ��Ҫ���� 
		return flow;
	}
	
	int sap(int _s, int _t) {
		s = _s; t = _t;
		memcpy(cur, G.head, sizeof(cur));
		if (!bfs()) return 0;  // Դ�㲻��ͨ���˳� 
		int maxFlow = 0;
		while (!stop) maxFlow += dfs(s, INF);
		return maxFlow;
	}
} net;

int main() {
	ios::sync_with_stdio(false);
	int n, m, s, t; cin >> n >> m >> s >> t;
	for (int u, v, w; m--; net.G.add(u, v, w))
		cin >> u >> v >> w;
	cout << net.sap(s, t) << endl;
	return 0;
}

