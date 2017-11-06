#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 150;

struct Seg {
	int sgn;
	double l, r, h;
	Seg() {}
	Seg(double _l, double _r, double _h, int _sgn): l(_l), r(_r), h(_h), sgn(_sgn) {}
	bool operator<(const Seg &t) const { return h < t.h; }  // ��y�������򣬴�������ɨ 
}seg[N<<1];
double all[N<<1];
int add[N<<3];
double sum[N<<3];

void pushup(int u, int ul, int ur) {
	/*
	������߶�������ѧ������Ҫ�´���ǣ���������add��sum����
	add�����ʾ�������䱻���˼��Σ�sum���鱣�渲���������
	���add��Ϊ0������������϶����������ˣ�sum=len
	���addΪ0�����ö��ӵĴ�������sum 
	���������ܻ����һ�����⣬���Ƕ�������(l,r)���޸�û��Ӱ�쵽(l,r)������
	����ʵ���������㲢��������⣬��Ϊ���(l,r)��add��Ϊ��0����(l,r)ȫ�������ˣ�������sum�Դ���Ӱ�� 
	���(l,r)��add��Ϊ0����(l,r)������һȦ�ֻص���ʼ״̬����Щ��(l,r)���޸���Ȼ��������Ӱ�� 
	*/ 
	if (add[u]) sum[u] = all[ur+1] - all[ul];
	else if (ul == ur) sum[u] = 0;
	else sum[u] = sum[u<<1] + sum[u<<1|1];
}

void update(int u, int ul, int ur, int l, int r, int sgn) {
	if (ul == l && ur == r) {
		add[u] += sgn;
		pushup(u, ul, ur);
		return;
	}
	int mid = (ul + ur) >> 1;
	if (l <= mid) update(u<<1, ul, mid, l, min(r, mid), sgn);
	if (r > mid) update(u<<1|1, mid+1, ur, max(l, mid+1), r, sgn);
	pushup(u, ul, ur);
}

int main() {
	// ��������Ϊ�����ɾ������������������ɢ��+ɨ����+�߶��� 
	for (int n, cas = 1; scanf("%d", &n) == 1 && n; cas++) {
		for (int i = 0; i < n; i++) {
			double r1, r2, r3, r4;
			scanf("%lf%lf%lf%lf", &r1, &r2, &r3, &r4);
			seg[i<<1] = Seg(r1, r3, r2, 1);  // ���εױ� 
			seg[i<<1|1] = Seg(r1, r3, r4, -1);  // ���ζ��� 
			all[i<<1] = r1; all[i<<1|1] = r3;  // ��ɢ��x���� 
		}
		n <<= 1;
		sort(seg, seg + n);
		sort(all, all + n);
		int m = unique(all, all + n) - all;  // �õ���ɢ�������ĸ��� 
		memset(add, 0, sizeof(add));
		memset(sum, 0, sizeof(sum));
		double ans = 0;
		for (int i = 0; i < n - 1; i++) {
			int l = lower_bound(all, all + m, seg[i].l) - all;  // ������������ɢ�����ֵ 
			int r = lower_bound(all, all + m, seg[i].r) - all;
			/*
			�������ͨ�߶�����һ�����𣬸��µ���l~r-1������l~r
			��Ϊ�߶����������[1,2],[2,3]����2�����ᱻ�����Σ���(1,2)(2,3)�������߶��ǲ��ص���
			���������߶������ܱ�ʾһ���㣬��Ӧ�ñ�ʾһ�����䣬�Ų�������й����˵���߶��������ص� 
			�����������ҿ����䣬�߶����ϵ�i��ʾ����[i, i+1)������ʱ����l~r-1��ʾ[l, r)�����߶� 
			*/ 
			if (l < r) update(1, 0, m - 1, l, r-1, seg[i].sgn);
			ans += sum[1] * (seg[i+1].h - seg[i].h);  // ʡȥѯ�ʲ�����ֱ����sum[1]��ʾ�ܸ��������� 
		}
		printf("Test case #%d\nTotal explored area: %.2f\n\n", cas, ans);  
	}
    return 0;
}

