#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 120;
int a[N+5], b[N+5];
 
int main() {  // ĸ����
	/*
	���⣺������n�ķ�����
	����ĸ������x�Ĵ�����ʾѡ�������ܺͣ���i��(1 + x^i + x^2i + ...)����ʾ����ѡ��ѡһ�Σ�ѡ���Σ� 
	����n�ķ�����Ϊ1~n��ĸ������˺�x^n��ϵ�� 
	*/ 
	for (int i = 0; i <= N; i++)
		 a[i] = 1;
	for (int i = 2; i <= N; i++) {  // ����(1 + x^i + x^2i + ...) 
		memset(b, 0, sizeof(b));
		for (int j = 0; j <= N; j++)
			for (int k = 0; j + k <= N; k += i)  // ö�ٷż���i�����ܺͲ��ܴ���N 
				b[j+k] += a[j];  // a����ÿһ����b�����k������� 
		memcpy(a, b, sizeof(b));
	}
	for (int n; cin >> n; )
		cout << a[n] << endl;
	return 0;
}

