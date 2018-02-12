/*
luoguU19867 day3T1 ��ƽ�潻(convex) 100pts

���⣺��͹����������ȡһ���㣬����������(p[0],p[1])���ɵ����������������С�ĸ���

�ⷨ���������n-1������ʽ��ת��Ϊ��ƽ�棬�ټ���ԭ��͹����εķ�Χ����
������İ�ƽ�潻�����������ı�����Ϊ�� 
*/ 
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+50;

struct Point {
	double x, y;
	Point(double _x=0, double _y=0): x(_x), y(_y) {}
	Point operator + (const Point &t) const { return Point(x + t.x, y + t.y); }
	Point operator - (const Point &t) const { return Point(x - t.x, y - t.y); }
	Point operator * (double k) const { return Point(x * k, y * k); }
	double operator * (const Point &t) const { return x * t.y - y * t.x; }
	friend ostream& operator << (ostream &out, const Point &t) {
		return out << '(' << t.x << ',' << t.y << ')';
	}
} poi[N];

struct Line {
	Point p, v;  // ֱ���õ�p������v����ʾ 
	double ang;
	Line() {}
	Line(const Point &a, const Point &b): p(a), v(b-a) {}
	bool operator < (const Line &t) const { return ang < t.ang; }
	Point operator * (const Line &t) const {
		/*
			��ֱ��(p,u)��(q,v)�Ľ���
			�轻��Ϊp+ku����(p+ku-q)*v=0
			��k=(q-p)*v/(u*v)
		*/
		double k = (t.p - p) * t.v / (v * t.v);
		return p + v * k;
	}
	friend ostream& operator << (ostream &out, const Line &t) {
		return out << '[' << t.p << ';' << t.v << ']';
	}
} line[N*2];

bool Side(Point a, Line l) {
	return (l.p - a) * l.v > 0;
}

Line New(int i, int j) {
	Line ret;
	double a = (poi[i].y - poi[j].y) - (poi[0].y - poi[1].y);
	double b = (poi[j].x - poi[i].x) - (poi[1].x - poi[0].x);
	double c = poi[i] * poi[j] - poi[0] * poi[1];
	// abc�����Ϲ�Ƽ��� 
	if (b) ret.p = Point(0, -c / b);
	else ret.p = Point(-c / a, 0);
	// �����ѡ��������x�ύ�㻹����y�ύ�� 
	ret.v = Point(b, -a);
	// ax+by+c=0��б��Ϊ-a/b������������(b,-a)����(-b,a)������ֵ������һ�¼��� 
	// ��֮Ҫ��֤�����������ax+by+c>=0 
	return ret;
}

Line deq[N*2];
int l, r;

double Hpl(int n) {
	for (int i = 1; i <= n; i++)
		line[i].ang = atan2(line[i].v.y, line[i].v.x);
	sort(line + 1, line + n + 1);
	l = 1; r = 0;
	for (int i = 1; i <= n; i++) {
		while (l < r && !Side(deq[r-1] * deq[r], line[i])) r--;
		while (l < r && !Side(deq[l] * deq[l+1], line[i])) l++;
		deq[++r] = line[i];
	}
	while (l < r && !Side(deq[r-1] * deq[r], deq[l])) r--;
	// ÿ��ֱ�����ʱ�Ѿ���֤���׽��������������������ﲻ�õ����� 
	deq[l-1] = deq[r]; deq[r+1] = deq[l];
	double area = 0;
	for (int i = l; i <= r; i++)
		area += (deq[i-1] * deq[i]) * (deq[i] * deq[i+1]);
	return area / 2;
}

int main() {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lf%lf", &poi[i].x, &poi[i].y);
	int ltop = 0;
	for (int i = 0; i < n; i++) {
		line[++ltop] = Line(poi[i], poi[(i+1)%n]);
		if (i) line[++ltop] = New(i, (i+1)%n);
	}
	double area = 0;
	for (int i = 0; i < n; i++)
		area += poi[i] * poi[(i+1)%n];
	area = area / 2;
	printf("%.4lf\n", Hpl(ltop) / area);
    return 0;
}

