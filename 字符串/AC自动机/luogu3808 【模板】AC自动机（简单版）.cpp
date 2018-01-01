#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
const int N = 1e6+50;

struct AC {
	int top, ch[N][26], cnt[N], fail[N];
	
	void Insert(char *s) {  // Trie������ 
		int len = strlen(s), u = 0;
		for (int i = 0; i < len; i++) {
			int t = s[i] - 'a';
			if (!ch[u][t]) ch[u][t] = ++top;
			u = ch[u][t];
		}
		cnt[u]++;
	}
	
	void Build() {  // ��ʼ��failָ�� 
		queue<int> q;
		for (int i = 0; i < 26; i++)
			if (ch[0][i]) q.push(ch[0][i]);  // ��������ĵ㣬failָ�붼ָ��� 
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = 0; i < 26; i++)
				if (ch[u][i]) {
					fail[ch[u][i]] = ch[fail[u]][i];
					q.push(ch[u][i]);
				}
				// ����Ҫ�����ʧ��ߵ��������·��ѹ�������Ʋ��鼯�� 
				else ch[u][i] = ch[fail[u]][i]; 
		}
	}
	
	int Query(char *s) {
		int len = strlen(s), u = 0, ret = 0;
		for (int i = 0; i < len; i++)
			// ��Ϊ�Ѿ�������·��ѹ�������Բ���fail���飬ֱ��ͨ��ch��ת�� 
			for (int t = u = ch[u][s[i]-'a']; t && ~cnt[t]; t = fail[t])
				// ��Ϊ�����ʵ���ģʽ���Ƿ���֣�����ʹ��Ĵ������ظ����ʣ���Ϊ-1 
				ret += cnt[t], cnt[t] = -1;  
		return ret;
	}
} ac;

char r[N];

int main() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%s", r), ac.Insert(r);
	ac.Build();
	scanf("%s", r);
	printf("%d\n", ac.Query(r));
    return 0;
}

