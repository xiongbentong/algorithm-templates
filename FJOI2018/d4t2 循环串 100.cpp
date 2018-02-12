/*
luoguU19961 day4T2 ѭ����(string) 100pts

���⣺���峤��Ϊn����Сѭ���ڳ���Ϊm���ַ����ļ�ֵΪn^2/m��
����һ��ֻ����abc���ַ��������ַ����������е�����ֵ 

�ⷨ�����ݳ���ԭ��������һ����ĸ���ֳ���n/3��
�������ĸ��������������ֵΪn^2/9����������ֻҪ������<=8��ѭ����
���ѭ�����д�����ĸ����>=3�Σ���ѭ���ڳ��ִ���Ϊk
�ǰ������ĸ����������ֵΪ9k^2����ԭ����ֵ����Ϊ8k^2
��������ֻҪö��ÿ����ĸ����<=2�ε�ѭ���� 
�ý��ۿ����ƹ㣬8�ĳ�m*m-1��2�ĳ�m-1 
*/ 
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+50, M = 4;
long long ans;
int n, m = 3, cnt[M];
char s[N], t[M*M];

void Calc(int top) {
	int k = 0;
	for (int i = 1, j = 1; i <= n; i++)
		if (s[i] == t[j])
			if (j == top) j = 1, k++;
			else j++;
	ans = max(ans, 1LL * k * k * top);
}

void Dfs(int u) {
	for (int i = 0; i < m; i++) {
		if (cnt[i] + 1 >= m) continue;  // cntҪ���ϵ�ǰ��ĸ 
		cnt[i]++;
		t[u] = 'a' + i;
		Calc(u);
		Dfs(u + 1);
		cnt[i]--;
	}
}

int main() {
	ios::sync_with_stdio(false);
	int T; cin >> T;
	while (T--) {
		cin >> n >> (s+1);
		ans = (n-1)/m+1;  // ����ԭ��Ҫ��ȡ�� 
		ans *= ans;
		Dfs(1);
		cout << ans << endl;
	}
    return 0;
}

