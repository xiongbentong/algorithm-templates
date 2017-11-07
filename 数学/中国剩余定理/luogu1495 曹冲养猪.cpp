#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long LL;
const int N = 15;

void exgcd(LL a, LL b, LL &x, LL &y) {
	b ? (exgcd(b, a%b, y, x), y -= a/b*x) : (x = 1, y = 0);
}

LL inv(LL a, LL b) {  // ��a����b�ĳ˷���Ԫ 
	LL x, y;
	exgcd(a, b, x, y);
	return (x % b + b) % b;
}

int main() {
	/*
	���⣺���������� x �� r[i] (mod m[i])������С�������� 
	�й�ʣ�ඨ��ģ��
	�ⷨ��
	�� msum Ϊ����m�ĳ˻���M[i] = msum / m[i] 
	�� a[i] �� 1 mod m[i]���� ai �� 0 mod m[����]
	�� a[i] * r[i] �����ģmsum��Ϊx
	����ֻ��Ҫ�� a[i]���� ai �� 0 mod m[����] ��a[i]��M[i]�ı��� 
	�� a[i] = k * M[i]���� k * M[i] �� 1 mod m[i]
	����k��M[i]����m[i]�ĳ˷���Ԫ����exgcd���k�����M[i]��Ϊa[i]
	*/
	int n;
	LL m[N], r[N], msum = 1;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> m[i] >> r[i];
		msum *= m[i];
	}
	LL ans = 0;
	for (int i = 1; i <= n; i++)
		ans = (ans + inv(msum / m[i], m[i]) * msum / m[i] * r[i]) % msum;  // inv(M[i]) * M[i] * r[i]
	cout << (ans % msum + msum) % msum << endl;   // ��С�������� 
    return 0;
}

