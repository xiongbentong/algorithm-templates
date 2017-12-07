#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
const int N = 4000050;
const double pi = acos(-1.0);

struct Complex {  // ���� 
    double r, i;  // rΪʵ����iΪ�鲿i��ϵ�� 
    Complex(double _r=0, double _i=0): r(_r), i(_i) {}
    Complex operator+(const Complex &b) const { return Complex(r + b.r, i + b.i); }
    Complex operator-(const Complex &b) const { return Complex(r - b.r, i - b.i); }
	// �˷���ʵ�����ƣ�����ע��i^2=-1
    Complex operator*(const Complex &b) const { return Complex(r*b.r - i*b.i, r*b.i + b.r*i); } 
    Complex operator*=(const Complex &b) { return *this = *this * b; }
    // ����ֻ�õ���������ʵ����ֱ�ӳ��ͺ� 
    Complex operator/(double b) const { return Complex(r / b, i / b); }
    Complex operator/=(double b) { return *this = *this / b; }
} a[N], b[N];

int n, R[N], c[N];

void FFT(Complex *f, int sgn) {  // FFT�ǵݹ�ʵ�֣�sgn=1��DFT�任��-1����DFT�任 
    for (int i = 0; i < n; i++)
        if (i < R[i]) swap(f[i], f[R[i]]);  // �����任 
    for (int i = 1; i < n; i <<= 1) {  // ��ǰ���䳤��Ϊ2*i 
    	// ��λ��wn=e^(2*pi/n*i)����ŷ����ʽ�� 
    	// ŷ����ʽ��e^(x*i) = cos(x) + sin(x) * i
    	// ������DFT��wn=wn^(-1)
        Complex wn(cos(pi / i), sgn * sin(pi / i));
        for (int j = 0; j < n; j += i << 1) {  // jΪ��ǰ������ʼλ�� 
            Complex w(1, 0);
            for (int k = 0; k < i; k++, w *= wn) {  // ����ǰ����ĵ�k���͵�k+i��ϵ��
            	// �Ѷ���ʽA�ֳ�����ϵ����ɵ�n/2�ζ���ʽA[0]��ż��A[1]
				// A(x) = A[0](x^2) + x*A[1](x^2)
				// ����w�����ʣ�w^(i+n/2) = -w^i
				// ��A(x+n/2) = A[0](x^2) - x*A[1](x^2)
                Complex x = f[j + k], y = w * f[j + k + i];
                f[j + k] = x + y; f[j + k + i] = x - y;
            }
        }
    }
    if (sgn == -1) for (int i = 0; i < n; i++) f[i] /= n;  // ��DFT�������n
	// ��DFT֤��Ҫ�õ����󣬼��·����� 
}

/*
FFT�㷨��⣺http://www.gatevin.moe/acm/fft%E7%AE%97%E6%B3%95%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0/
��Ŀ���⣺������������ʽ�������ʽ�ĳ˻������ϵ����n<=1e6
������
FFT�����ٸ���Ҷ�任������O(nlogn)ʱ���ڽ������ʽ�˷�����
FFT�㷨���������ø�����һЩ���ʺͷ��ε�˼�룬��O(nlogn)�ڽ��DFT����DFT����
������ʽϵ����ʾ���͵�ֵ��ʾ�����໥ת����
����ֵ��ʾ�������O(n)���㷨��������O(nlogn)ת�ɵ�ֵ��ʾ����O(n)��ˣ���O(nlogn)ת�������ܸ��Ӷ���O(nlogn) 
*/
int main() {
	int la, lb; scanf("%d%d", &la, &lb);
    for (int i = 0; i <= la; i++) scanf("%lf", &a[i].r);
    for (int i = 0; i <= lb; i++) scanf("%lf", &b[i].r);
    int m = la + lb, len;
    // FFT����2^n�ζ���ʽ�ȽϷ��㣬���԰�n�ʵ����� 
    for (n = 1, len = 0; n <= m; n <<= 1, ++len);
	// Ԥ��������任��R[i]��ʾ�ݹ鵽��ײ���iλ��ԭ���ĵ�R[i]λ��R[i]=(i����lenλ�����������ҵߵ�)
    for (int i = 1; i < n; i++) R[i] = R[i >> 1] >> 1 | (i & 1) << len - 1;
    FFT(a, 1); FFT(b, 1);  // ��a��b��DFT�任����ϵ����ʾ��תΪ��ֵ��ʾ�� 
    for (int i = 0; i < n; i++) a[i] *= b[i];  // ��ֵ��ˣ�O(n) 
    FFT(a, -1);  // ��ab�˻�����DFT�任���ѵ�ֵ��ʾ��ת��ϵ����ʾ�� 
    for (int i = 0; i <= m; i++) c[i] = int(a[i].r + 0.5);  // ������������������� 
    for (int i = 0; i <= m; i++) printf("%d ", c[i]);
    putchar('\n');
    return 0;
}

