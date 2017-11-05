#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 40050;
int main() {
	/*
	ŷ��������ʽ����(i)=n(1-1/p1)(1-1/p2)...(1-1/pm) ��pΪn����������
	֤����
	��p������ʱ����(p^k) = p^k - p^(k-1) = p^k(1-1/p)
	��Ϊֻ�в���p�ı���������p^k���ʣ��ܹ���p^k���� ��p�ı�����p^(k-1)��
	���й�ʣ�ඨ�������ᣩ�ã�ŷ�������ǻ��Ժ���
	���Ԧ�(n)=p1^k1*p2^k2*...*pm^km*(1-1/p1)(1-1/p2)...(1-1/pm)=n(1-1/p1)(1-1/p2)...(1-1/pm)
	�����������ɸ����ɸ�������� 
	*/
	int n, a[N] = {0}, ans = 0;
	cin >> n;
	if (!--n) { cout << 0 << endl; return 0; }
	ans = a[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!a[i]) {  // i������ 
			a[i] = i;
			for (int j = i; j <= n; j += i) {
				if (!a[j]) a[j] = j;
				a[j] = a[j] * (i - 1) / i;
			}
		}
		ans += a[i];
	}
	cout << ans * 2 + 1 << endl;
    return 0;
}

