#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 100, S = 60;
int main() {
	/*
	���⣺��n��������ȡ���ɸ���������������
	���Ի���ԭ���ϵ�һ����С�Ӽ���ʹ����ֵ����ԭ������ͬ
	������Ի��������Ի���̰�� 
	*/
	int n; cin >> n;
	LL a[S+5] = {0};
	for (int i = 1; i <= n; i++) {
		LL u; cin >> u;
		for (int j = S; ~j; j--)
			if (u & 1LL << j)
				if (!a[j]) { a[j] = u; break; }  // ���û�������ǵ�jλ���Ͱ�uѡ���� 
				else u ^= a[j];  // ��u�ĵ�jλ����0 
		// ���Ҫôu������0,����u���Ա����Ի��е�Ԫ����������Ҫôu���������Ի� 
	}
	LL ans = 0;
	for (int i = S; ~i; i--)
		ans = max(ans, ans ^ a[i]);  // �Ӹ�λ��ʼ̰��ѡ 
	cout << ans << endl;
	return 0;
}

