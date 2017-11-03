#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
/*
exgcd(a, b)��ax+by=gcd(a, b)��һ���ؽ�
ԭ��
�ݹ����� b*x' + (a%b)*y' = g ��һ���ؽ� 
��Ϊa%b = a - a/b*b
����ԭʽ�ȼ��� b*x' + (a-a/b*b)*y' = g 
b*x' + a*y' - a/b*b*y' = g
a*y' + b*(x'-a/b*y') = g
����x = y', y = x'-a/b*y' 
�߽磺��b=0ʱ��ax+0y=a����x = 1, y = 0 
*/
void exgcd(LL a, LL b, LL &x, LL &y, LL &g) {
	b ? (exgcd(b, a%b, y, x, g), y -= a / b * x) : (x = 1, y = 0, g = a);
}

/*
tyfc(a, b, c)��ax+by=c����С�������� 
������exgcd(a, b)��ax+by=g���ؽ�
Ȼ�������ͬʱ����c/g����
a(x*c/g) + b(y*c/g) = c
����g����c����������c/g��Ϊ�������޽⣩ 
���԰�֮ǰ��x����c/g�������ؽ�
ͨ��Ϊx + t * (b/g)
��Ϊax+by=c��ͨ��Ϊx + t * b
��ax+by=c����ͬ��g�� a/g*x +  b/g*y = c/g
��ʱa��b���ʣ�ͨ��Ϊx + t * (b/g) 
*/
LL tyfc(LL a, LL b, LL c) {  // ͬ�෽�̣�ʵ�ڲ���ȡ���ˣ� 
	LL x, y, g;
	exgcd(a, b, x, y, g);
	if (c % g) return -1;
	int t = b / g;
	return (x * c/g % t + t) % t;
}

int main() {
	LL x, y, m, n, L;
	cin >> x >> y >> m >> n >> L;
	if (m < n) swap(m, n), swap(x, y);
	int ans = tyfc(m - n, L, y - x);
	if (~ans) cout << ans << endl;
	else puts("Impossible");
	return 0;
}

