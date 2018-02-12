/*
luoguU19868 day3T2 ����ͼ(match) 100pts

���⣺����һ������ͼ��������[����һ��ƥ�串��S�����е�]��[��Ȩ�Ͳ�����t]���Ӽ�S���� 

�ⷨ��������һ��hall����
hall����������X���������Ӽ�W����|W|=k����������W��ͨ��Y��������>=k������ڸ���X��ƥ��
һ�����ۣ���������ߵ�һ���Ӽ�X���ұߵ�һ���Ӽ�Y���ֱ�����hall���������ǵĲ���������
֤���������Ѹ���X��ƥ��ת�ɴ����ҵ�����ͼ����֮��Ȼ���ͻ��γ����ɸ�����·��
ÿ������·��������ѡ�ߣ����������⣨��֤·�����һ����һ������ѡ�����ĵ��У� 
���Ӽ�DP��һ�������Ƿ�����hall�����Ҷ���һ�飬Ȼ������кϷ�״̬����Ȩ����
�������ָ��ɨһ�¼��� 
*/ 
#include <bits/stdc++.h>
using namespace std;
const int N = 22, S = (1 << N) + 50;
int n, m, mx, val[N];
bool e[N][N];
int bits[S], w[S], c[S];
bool hall[S];
int a[S], atop, b[S], btop;

int Lb(int x) { return x & -x; }

void Work(int *q, int &top) {
	for (int i = 0; i < n; i++) {
		w[1<<i] = val[i];  // w[i]Ϊi״̬�ĵ�Ȩ�� 
		c[1<<i] = 0;  // c[i]Ϊi״̬��������� 
		for (int j = 0; j < m; j++)
			if (e[i][j]) c[1<<i] |= 1<<j;
	}
	hall[0] = true; q[top=1] = 0;
	for (int s = 1; s < 1 << n; s++) {
		w[s] = w[Lb(s)] + w[s^Lb(s)];
		c[s] = c[Lb(s)] | c[s^Lb(s)];
		hall[s] = bits[s] <= bits[c[s]];  // hall[i]Ϊi״̬�Ƿ�����hall���� 
		for (int i = 0; i < n && hall[s]; i++)
			if (s & 1<<i) hall[s] &= hall[s ^ 1<<i];  // ת�ƶ��ӵ�ǰ״̬ȥ��һ��1ת�� 
		if (hall[s]) q[++top] = w[s];
	}
	sort(q+1, q+top+1);
}

int main() {
	scanf("%d%d", &n, &m);
	char r[N];
	for (int i = 0; i < n; i++) {
		scanf("%s", r);
		for (int j = 0; j < m; j++)
			e[i][j] = r[j] - '0';
	}
	mx = max(n, m);
	for (int i = 1; i <= 1 << mx; i++)
		bits[i] = bits[i>>1] + (i & 1);  // bits[i]Ϊi״̬1�ĸ��� 
	for (int i = 0; i < n; i++)
		scanf("%d", &val[i]);
	Work(a, atop);  // ��һ��X�� 
	for (int i = 0; i < m; i++)
		scanf("%d", &val[i]);
	swap(n, m);  // n,m���� 
	for (int i = 0; i < mx; i++)
		for (int j = 0; j < i; j++)
			swap(e[i][j], e[j][i]);  // �ѱ߷��� 
	Work(b, btop);  // ����һ��Y�� 
	int tar; scanf("%d", &tar);
	long long ans = 0;
	for (int i = 1, j = btop+1; i <= atop && j >= 1; i++) {
		// ����ָ�������a[i]+b[j]>=t����Сb[j]����Ϊj�ǵ��������� 
		while (j > 1 && a[i] + b[j-1] >= tar) j--;
		ans += btop-j+1;
	}
	cout << ans << endl;
    return 0;
}

