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

struct Network {  // dinic�㷨ģ�� 
	Graph G;
	int s, t;
	int dis[N];
	
	bool bfs() {  // bfs�ֲ� 
		memset(dis, 0, sizeof(dis)); dis[s] = 1;
		queue<int> q; q.push(s);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = G.head[u]; ~i; i = G.e[i].nxt) {
				int v = G.e[i].to;
				if (G.e[i].f && !dis[v]) {
					dis[v] = dis[u] + 1;
					q.push(v);
				}
			}
		}
		return dis[t];  // ��dis[t]==0���޷��������㣬����false 
	}
	
	int dfs(int u, int curFlow) {  // curFlowΪ��ǰ�������������� 
		if (u == t) return curFlow;
		if (dis[u] >= dis[t]) return 0;  // �߹�ͷ���˵� 
		for (int i = G.head[u]; ~i; i = G.e[i].nxt) {
			int v = G.e[i].to, flow;
			// �����߲�����Ϊ0����v��u����һ�㣬���ܼ������� 
			if (G.e[i].f && dis[v] == dis[u] + 1 && (flow = dfs(v, min(curFlow, G.e[i].f)))) {
				G.e[i].f -= flow;
				G.e[i^1].f += flow;
				return flow;
			}
		}
		return 0;  // �޷����㷵��0 
	}
	
	int dinic(int _s, int _t) {
		s = _s; t = _t;
		int maxFlow = 0, flow;
		while (bfs())  // ÿ�ζ�Ҫ���·ֲ� 
			while (flow = dfs(s, INF))
				maxFlow += flow;
		return maxFlow;
	}
} net;

int main() {
	ios::sync_with_stdio(false);
	int n, m, s, t; cin >> n >> m >> s >> t;
	for (int u, v, w; m--; net.G.add(u, v, w))
		cin >> u >> v >> w;
	cout << net.dinic(s, t) << endl;
	return 0;
}

