/*
luoguU19736 day1T3 ��ʽ(expr) 80pts

���⣺����ʽ������1��n������ÿ���������һ�Σ�����������

�ⷨ��
�Ȱѱ��ʽչ�������ÿһ�����ϵ������i����ϵ��Ϊa[i]
��f[i][j]��ʾ1~i��ȡj���ĳ˻�֮�� 
f[i][j]=f[i-1][j]��i��ѡ��+i*f[i-1][j-1]��iѡ������01������࣬��һά���Բ�Ҫ
�ܺͳ��Է������������� 
sigma a[j]*f[n][j]/C(n,j) ��Ϊ�� 
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4+50;

struct Mint {
    static const int MOD = 1e9+7;
    int x;
    
    Mint(int _x=0): x((_x % MOD + MOD) % MOD) {}
    friend Mint operator + (const Mint &a, const Mint &b) { return (a.x + b.x) % MOD; }
    Mint operator += (const Mint &b) { return *this = *this + b; }
    Mint operator - () const { return MOD - x; }
    friend Mint operator - (const Mint &a, const Mint &b) { return a + -b; }
    Mint operator -= (const Mint &b) { return *this = *this - b; }
    friend Mint operator * (const Mint &a, const Mint &b) { return 1LL * a.x * b.x % MOD; }
    Mint operator *= (const Mint &b) { return *this = *this * b; }
    Mint operator ^ (int k) const {
        Mint ret = 1;
        for (Mint tmp = *this; k; k >>= 1, tmp *= tmp)
            if (k & 1) ret *= tmp;
        return ret;
    }
    Mint operator ^= (int k) { return *this = *this ^ k; }
    Mint operator ~ () const { return *this ^ MOD-2; }
    friend Mint operator / (const Mint &a, const Mint &b) { return a * ~b; }
    Mint operator /= (const Mint &b) { return *this = *this / b; }
    friend istream& operator>>(istream &in, Mint &a) { return in >> a.x; }
    friend ostream& operator<<(ostream &out, const Mint &a) { return out << a.x; }
};

struct Item {
    int mx; Mint *a;
    Item(int _mx=0): mx(_mx) {
        a = new Mint[mx+1];
        memset(a, 0, sizeof(Mint)*(mx+1));
        // ��̬���ռ䣬�ǵ��ó�ֵΪ0 
    }
};

Item Opt(Item a, char opt, Item b) {  // ���ض���ʽa,b��opt����Ľ�� 
    Item ret(opt == '*' ? a.mx + b.mx : max(a.mx, b.mx));
    if (opt == '*') {
        for (int i = 0; i <= a.mx; i++)
            for (int j = 0; j <= b.mx; j++)
                ret.a[i+j] += a.a[i] * b.a[j];
    } else {
        for (int i = 0; i <= ret.mx; i++) {
            if (i <= a.mx) ret.a[i] = a.a[i];
            if (i <= b.mx) {
                if (opt == '+') ret.a[i] += b.a[i];
                if (opt == '-') ret.a[i] -= b.a[i];
            }
        }
    }
    return ret;
}

Item Calc(char*&);

Item Num(char* &s) {  // ȡ�����ʽs�еĵ�һ�����֣�����һ���������򷵻������ڵļ����� 
    Item t;
    if (*s == '_') t = Item(1), t.a[1] = 1;
    else t = Calc(++s);
    s++; return t;  // s++������'_'��')'������ 
}

Item Mul(char* &s) {  // �ѱ��ʽs��������һ�γ˷������� 
    Item t = Num(s);
    while (*s == '*') t = Opt(t, '*', Num(++s));
    return t;
}

Item Calc(char* &s) {  // ������ʽs��ֵ���������������˳� 
    Item t = Mul(s);
    for (char ch; (ch=*s) == '+' || ch == '-'; )
        t = Opt(t, ch, Mul(++s));
    return t;
}

char s[N];
int n;
Mint f[N];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> s;
    char *p = s;
    Item t = Calc(p);
    f[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = i; j >= 1; j--)
            f[j] += f[j-1] * i;  // ���� 
    Mint c = 1, ans = 0;
    for (int i = 1; i <= t.mx; i++) {
        c = c * (n-i+1) / i;  // ������ĵ����� 
        ans += t.a[i] * f[i] / c;
    }
    cout << ans << endl;
    return 0;
}

