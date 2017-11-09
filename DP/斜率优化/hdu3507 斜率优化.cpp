#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 500050;
int n, m, s[N], f[N];
int q[N], h, t;

int getx(int j, int k) { return 2 * (s[j] - s[k]); }
int gety(int j, int k) { return f[j] + s[j] * s[j] - (f[k] + s[k] * s[k]); }
int getf(int i, int j) { return f[j] + m + (s[i] - s[j]) * (s[i] - s[j]); }

int main() {
	/*
	���⣺��n�����ֳ����ɶΣ�ÿ�λ���Ϊ������ĺ͵�ƽ���ӳ���m������С����
	f[i]=f[j]+m+(s[i]-s[j])*(s[i]-s[j])
	��k<j����j��k�ţ��� 
	f[i]-2*s[i]*s[j]+s[j]*s[j]-(f[k]-2*s[i]*s[k]+s[k]*s[k])<=0
	�����((f[j]+s[j]*s[j])-(f[k]+s[k]*s[k]))/(2*(s[j]-s[k]))<=s[i]
	��y[i]=f[i]+s[i]*s[i], x[i]=2*s[i]��
	��ԭʽ��Ϊ(y[j]-y[k])/(x[j]-x[k])<=s[i]
	��߿��Կ���б��ʽ����i<j, i,jб��Ϊg[i][j]
	����k<j��g[k][j]<=s[i]����j��k��
	��k<j<i����g[k][j]>g[j][i]����j������
	��Ϊ��g[j][i]<=s����i��j�ţ�j����
	��g[j][i]>s����j��i�ţ���g[k][j]>g[j][i]>s����k��j�ţ�j����
	����ά��һ��б�ʵ�����������͹�ǣ�����Ϊs��ǰ׺�ͣ�����������
	����ÿ�δӶ��׿�ʼ����g<s�Ķ�ɾ����ʣ�µĶ��׾������ž��ߵ�
	Ȼ��Ӷ�β������Ԫ�أ�ά�������� 
	*/
	while (scanf("%d%d", &n, &m) == 2) {
		h = 0; q[t = 0] = 0;
		for (int i = 1, tmp; i <= n; i++) {
			s[i] = s[i-1] + (scanf("%d", &tmp), tmp);
			while (h < t && gety(q[h+1], q[h]) <= s[i] * getx(q[h+1], q[h])) ++h;
			f[i] = getf(i, q[h]);
			while (h < t && gety(q[t], q[t-1]) * getx(i, q[t]) >= gety(i, q[t]) * getx(q[t], q[t-1])) --t;
			q[++t] = i;
		}
		printf("%d\n", f[n]);
	}
	return 0;
}

