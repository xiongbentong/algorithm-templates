/*
luoguU19869 day3T3 ������(interval) 100pts

���⣺������������Ϊ�����������õ�����һ����������
ÿ��ѯ�ʸ�������[x,y]�������[x,y]����С��������[l,r]

�ⷨ�����Ӷ���ѧ�ķֿ�
��չ����Ϊ��ѯ[l,r]��ֵ��[mi,mx]���ٲ�ѯ[mi,mx]��λ�ü�ֵ[newl,newr]��ͨ��Ԥ����RMQ��ɣ� 
�ϲ�����Ϊ��l��r�ֱ�ȡmin��max
��Ԥ�����ÿ����֮��Ĵ�
��������ȷ����˵Ŀ�l��Ȼ����������Ⱥϲ�����չ
��ѯʱ����[l,r]����������Ĵ�[tl,tr]����[l,r]����[tl,tr]��Ϊ���մ�
�Ϸ��ԣ�[tl,tr]����[l,r]��Ϊ��������
�����ԣ�[tl,tr]�Ǳ�[l,r]С��һ����������Ž⣬[l,r]�����Žⲻ���ܱ������
���[tl,tr]������[l,r]�����������������кϲ�����չ������[l,r]���ظ����ϲ���
ѯ�ʵĸ��ӶȲ���֤����˵��n*sqrt(n)�������ܵĺܿ� 
*/ 
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+50, LOGN = 22, B = 350;

struct Range {
	int l, r;
	Range(int _l=N-1, int _r=0): l(_l), r(_r) {}  // ��ֵ[N,0]������ϲ�ʱȡmin��max 
	Range operator + (const Range &t) const { return Range(min(l, t.l), max(r, t.r)); }  // �ϲ� 
	Range operator += (const Range &t) { return *this = *this + t; }
	bool operator == (const Range &t) const { return l == t.l && r == t.r; }
	bool operator != (const Range &t) const { return !(*this == t); }
};

int bin[LOGN], lo[N];
int n, siz, m, num[N], bl[N];
Range body[B], ans[B][B];
int lb[N], rb[N];

struct Rmq {
	int a[N];
	Range f[N][LOGN];
	
	void Init() {
		for (int i = 1; i <= n; i++)
			f[i][0] = Range(a[i], a[i]);
		for (int j = 1; bin[j] <= n; j++)
			for (int i = 1; i <= n-bin[j-1]+1; i++)
				f[i][j] = f[i][j-1] + f[i+bin[j-1]][j-1];
				// �ϲ����䣬�൱��ͬʱ����min��max 
	}
	
	Range Query(Range q) {
		int k = lo[q.r-q.l+1];
		return f[q.l][k] + f[q.r-bin[k]+1][k];
	}
} q1, q2;  // q1��ѯλ�������ֵ��q2��ѯֵ�����λ���� 

Range Extend(const Range &x) {  // ��չ 
	return q2.Query(q1.Query(x));
}

int main() {
	ios::sync_with_stdio(false);
	bin[0] = 1; for (int i = 1; i < LOGN; i++) bin[i] = bin[i-1] << 1;
	lo[0] = -1; for (int i = 1; i < N; i++) lo[i] = lo[i>>1] + 1;
	cin >> n; siz = sqrt(n);
	for (int i = 1; i <= n; i++) {
		cin >> num[i];
		q1.a[i] = num[i];
		q2.a[num[i]] = i;
	}
	q1.Init(); q2.Init();
	for (int i = 1; i <= n; i++)
		bl[i] = (i-1)/siz+1;
	m = bl[n];
	for (int i = 1; i <= m; i++)
		body[i] = Range((i-1)*siz+1, min(i*siz, n));
	for (int l = 1; l <= m; l++) {
		Range x = body[l], y;
		while ((y = Extend(x)) != x) x = y; 
		ans[l][l] = x;
		for (int r = l+1; r <= m; r++) {
			y = x + body[r];  // �ϲ��¿� 
			while (y != x) x = y, y = Extend(x);  // ��������չ 
			ans[l][r] = x;  // �õ��µĴ� 
		}
	}
	for (int i = 1; i <= n; i++) {
		lb[i] = bl[i]; if (i != body[bl[i]].l) lb[i]++;
		rb[i] = bl[i]; if (i != body[bl[i]].r) rb[i]--;
		// ����[l,r]�����������������˵���Ҷ˵� 
	}
	int m; cin >> m;
	for (int l, r; m--; ) {
		cin >> l >> r;
		Range x(l, r), y;
		while (true) {
			y = ans[lb[x.l]][rb[x.r]];
			if (y.l <= x.l && x.r <= y.r) {
				// ��[tl,tr]����[l,r]�����Ϊ[tl,tr] 
				x = y;
				break;
			}
			x += y;
			if ((y = Extend(x)) == x) break;
			x = y;
			// �ϲ�����չ��������� 
		}
		printf("%d %d\n", x.l, x.r);
	}
    return 0;
}

