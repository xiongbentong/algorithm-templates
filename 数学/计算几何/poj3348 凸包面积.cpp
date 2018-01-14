#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 10050;
const double EPS = 1e-6;
struct Point {
	double x, y;
	Point(double _x=0, double _y=0): x(_x), y(_y) {}
	Point operator-(const Point &t) const { return Point(x - t.x, y - t.y); }
	double operator^(const Point &t) const { return x * t.y - y * t.x; }
	double operator*(const Point &t) const { return x * t.x + y * t.y; }
	bool operator<(const Point &t) const { return x < t.x || x == t.x && y < t.y; }
	void input() { cin >> x >> y; }
	void print() { cout << x << ' ' << y << endl; }
}point[N];

int sgn(double t) { return t > EPS ? 1 : t < -EPS ? -1 : 0; }
double xc(const Point &a, const Point &b, const Point &c) { return (b - a) ^ (c - a); }
double dis(const Point &a, const Point &b) { return sqrt((a-b)*(a-b)); }
bool cmp(Point t1, Point t2) {
	int t = sgn(xc(point[0], t1, t2));
	return t > 0 || t == 0 && dis(point[0], t1) < dis(point[0], t2);
} 

int main() {  // ��͹����� 
	int n; cin >> n;
	if (n < 3) { cout << 0 << endl; return 0; }  // ����3���㲻�ܹ���͹�� 
	for (int i = 0; i < n; i++) {
		point[i].input();
		if (point[i] < point[0])  // ��x������С�ĵ�Ϊԭ������������ 
			swap(point[i], point[0]); 
	}
	sort(point + 1, point + n, cmp);
	int st[N], top = 1;
	st[0] = 0; st[1] = 1;
	for (int i = 2; i < n; i++) {  // ͹�� 
		while (top > 0 && xc(point[st[top-1]], point[st[top]], point[i]) <= 0) --top;
		st[++top] = i;
	}
	int ans = 0;
	for (int i = 1; i < top; i++)
		ans += xc(point[st[0]], point[st[i]], point[st[i+1]]);  // ��˼������ 
	cout << ans / 2 / 50 << endl;  // ���Ҫ/2����ĿҪ��/50 
	return 0;
}

