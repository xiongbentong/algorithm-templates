#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 500, P = 1000007;
int c[N+5][N+5];

void init() {  // �������� 
	for (int i = 0; i <= N; i++) {
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; j++)
			c[i][j] = (c[i-1][j-1] + c[i-1][j]) % P;
	}
}

int main() {
	/*
	���⣺��n*m�ĸ������k���㣬���������ұ�Ե�϶������е㣬�󷽰���
	�ⷨ���ݳ�ԭ���ܷ����� - ��һ��û�� + ������û�� - ������û�� + ���ı�û�� 
	*/
	init();
	int T; cin >> T;
	for (int cas = 1, n, m, k; cas <= T; cas++) {
		cin >> n >> m >> k;
		int ans = 0;
		for (int i = 0; i < 16; i++) {
			int x = n, y = m, one = 0;
			if (i & 1) --x, ++one;
			if (i & 2) --x, ++one;
			if (i & 4) --y, ++one;
			if (i & 8) --y, ++one;
			if (one & 1) ans = (ans + P - c[x*y][k]) % P;  // �ø�������ż���ж��Ǽӻ��Ǽ� 
			else ans = (ans + c[x*y][k]) % P;
		}
		printf("Case %d: %d\n", cas, ans);
	}
    return 0;
}

