#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 100050, INF = 0x3f3f3f3f;
int ma[N], a[N], f[N];

int main() {
	/*
	���⣺������1~n�����У�������������У����Բ�������
	�ⷨ��
	3 2 1 4 5
	1 2 3 4 5
	�� 3 2 1 4 5 ���� 1 2 3 4 5 (3->1, 2->2, 1->3...)
	����ӳ���ϵ���ڶ������б�Ϊ 3 2 1 4 5 
	��ԭ���еĹ��������ж�Ӧ�ڶ������е�����������
	����������������� nlogn ģ�� 
	*/ 
	int n; cin >> n;
	for (int i = 0, r; i < n; ma[r] = i++)
		cin >> r;
	for (int i = 0; i < n; i++)
		cin >> a[i], a[i] = ma[a[i]];
	/*
	f[i]��ʾa[0~i]�������������
	����a[i]ʱ�����ö����ҳ���һ��>=a[i]��f[j]��Ȼ����0~j-1������������к����a[i]���� f[j]=a[i] 
	��Ϊ��ǰ�����ţ�����Ӳ��� 
	����Ϊ���һ����ֵ��f��λ�� 
	*/ 
	memset(f, 0x3f, sizeof(f));
	for (int i = 0; i < n; i++)
		*lower_bound(f, f + n, a[i]) = a[i];
	cout << lower_bound(f, f + n, INF) - f << endl;
	return 0;
}

