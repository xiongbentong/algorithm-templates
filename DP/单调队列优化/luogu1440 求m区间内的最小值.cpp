#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <deque>
#include <utility>
using namespace std;
deque< pair<int, int> > q;
int main() {
	/*
	���⣺��ÿ����ǰm������Сֵ
	���������Ż�dp��������O(n)�ڽ�����磺
	"f[x] = max or min{g(k) | b[x] <= k < x} + w[x]
	����b[x]��x����������g[k]��ʾһ����k��f[k]�йصĺ�����w[x]��ʾһ����x�йصĺ���"
	������
	������ά��һ���������̶��½��ĵ������У����Կ��ɴ��ڣ���ÿ���ƶ����ھͰѶ��׹�ʱ��Ԫ���ӵ���
	��β�ӽ���Ԫ��ʱά�������ԣ������ž��ߵ��ڶ��� 
	*/
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1, t; i <= n; i++) {
		// pair��first����ʱ�䣬second����ֵ 
		while (!q.empty() && q.front().first < i - m) q.pop_front();
		if (!q.empty()) printf("%d\n", q.front().second);
		else printf("0\n");
		scanf("%d", &t);
		while (!q.empty() && q.back().second > t) q.pop_back();
		q.push_back(make_pair(i, t));
	} 
    return 0;
}

