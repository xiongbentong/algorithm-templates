#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int N = 51, L = 55;

struct LinearBasis{
	LL bin[L+5], b[L+5];
	
	LinearBasis() {
		memset(b, 0, sizeof(b));
		bin[0] = 1;
		for (int i = 1; i <= L; i++)
			bin[i] = bin[i-1] << 1;
	}
	
	bool Insert(LL x) {
		for (int i = L; i >= 0 && x; i--)
			if (x & bin[i]) {
				if (!b[i]) { b[i] = x; return true; }  // ���û�������ǵ�iλ���Ͱ�xѡ���� 
				else x ^= b[i];  // ��x�ĵ�iλ����0 
			}
		// ���Ҫôx������0����x���Ա����Ի��е�Ԫ����������Ҫôx���������Ի� 
		return false;
	}
	
	LL QueryMax(LL x=0) {  // ��x������Ի��е�Ԫ���ܵõ������ֵ 
		for (int i = L; i >= 0; i--)
			x = max(x, x ^ b[i]);  // �Ӹ�λ��ʼ̰��ѡ
		return x;
	}
};

/*
���⣺��n��������ȡ���ɸ���������������
���Ի���ԭ���ϵ�һ����С�Ӽ���ʹ����ֵ����ԭ������ͬ
������Ի��������Ի���̰�� 
*/
int main() {
	int n; cin >> n;
	LinearBasis lb;
	for (int i = 1; i <= n; i++) {
		LL r; cin >> r;
		lb.Insert(r);
	}
	cout << lb.QueryMax() << endl;
	return 0;
}

