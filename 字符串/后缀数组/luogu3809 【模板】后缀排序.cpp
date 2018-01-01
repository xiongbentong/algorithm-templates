#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 2e6+50;
char s[N];
int n, t[N], x[N], y[N], sa[N], rk[N], height[N];

void GetSA() {  // ��sa,rk,height���� 

	int m = 'z' + 5;  // m��Ͱ�ŵ��Ͻ磬�ɱ� 
	
	// ��Ͱ�ţ��൱�ڰ��ַ���ɢ��һ�� 
	for (int i = 1; i <= n; i++) t[x[i] = s[i]]++;
	for (int i = 1; i <= m; i++) t[i] += t[i-1];
	for (int i = n; i >= 1; i--) sa[t[x[i]]--] = i;  // ����ѭ������֤�����ȶ� 
	
	for (int k = 1; ; k <<= 1) {  // k��ʾ��ǰҪ����Ĵ�����/2 
		int cnt = 0;
		
		// y�д洢�������Ԫ��ĵ�һ�ؼ��ֵ�λ�� 
		// ��k����û�еڶ��ؼ��֣����ȼ���ߣ��ȷŽ��� 
		for (int i = n - k + 1; i <= n; i++) y[++cnt] = i;  
		
		// �еڶ��ؼ��ֵĶ�Ԫ�飬���ڶ��ؼ��ִ�С����Ž�������֤˫�ؼ������� 
		for (int i = 1; i <= n; i++) if (sa[i] > k) y[++cnt] = sa[i] - k;
		
		// �Ե�һ�ؼ��ֽ���Ͱ����x�б��������һ������Ľ���� 
		memset(t, 0, sizeof(int) * (m + 5));
		for (int i = 1; i <= n; i++) t[x[y[i]]]++;
		for (int i = 1; i <= m; i++) t[i] += t[i-1];
		for (int i = n; i >= 1; i--) sa[t[x[y[i]]]--] = y[i];
		
		// ���ϴ���������ʱ����y���y������û��ϵ�����������������x 
		// ���swapֻ�ǽ���ָ�룬��ʡ�ռ���ʡʱ�� 
		swap(x, y); x[sa[1]] = cnt = 1;
		for (int i = 2; i <= n; i++)
			// �������ͬ������ͬ 
			x[sa[i]] = y[sa[i]] == y[sa[i-1]] && y[sa[i]+k] == y[sa[i-1]+k] ? cnt : ++cnt;
		
		// ����Ͱ���Ͻ磨����ͬ��Ԫ�ظ����������Ͻ�Ϊn���Ѿ��ź���û��Ҫ������ 
		if ((m = cnt) >= n) break;
	}
	
	// ˳����һ��rk��height����Ȼ����û�õ��� 
	for (int i = 1; i <= n; i++) rk[sa[i]] = i;
	
	// height[i]>=height[i��ǰһ��]-1�������������O(n)���� 
	for (int i = 1, k = 0, j; i <= n; height[rk[i++]] = k)
		for (k = k ? k - 1 : k, j = sa[rk[i]-1]; s[i+k] == s[j+k]; k++);
}

/*
���⣺���ַ��������зǿպ�׺���ֵ����С��������Ȼ��˳�������׺�ĵ�һ���ַ���ԭ���е�λ��
������sa���飩 
*/
int main() { 
	scanf("%s", s + 1); n = strlen(s + 1);
	GetSA();
	for (int i = 1; i <= n; i++)
		printf("%d ", sa[i]);
	putchar('\n');
    return 0;
}

