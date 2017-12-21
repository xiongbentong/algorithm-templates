#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int L = 7;
int f[L+5][L+5];  // f[i][j]��ʾ��iλ�����λΪj���������������ĸ��� 

void init() {
    f[0][0] = 1;
    for (int i = 1; i <= L; i++)
        for (int j = 0; j <= 9; j++)
            for (int k = 0; k <= 9; k++)
                if (j != 4 && !(j == 6 && k == 2))
                    f[i][j] += f[i-1][k];
}

int dp(int n) {  // ��С��n�ĺϷ����ĸ�����ע������û��ȡ�� 
    int len, num[L+5] = {0}, ans = 0;
    for (len = 0; n; n /= 10)
        num[++len] = n % 10;
    for (int i = len; i >= 1; i--) {
        for (int j = 0; j < num[i]; j++)
            if (!(num[i+1] == 6 && j == 2))  // ���ﲻ�÷�4����Ϊf[i][4]=0����f[i][2]��һ��Ϊ0
                ans += f[i][j];
        if (num[i] == 4 || num[i+1] == 6 && num[i] == 2) break;  // ���ö�ٵ�1234xx����12362xx���� 
    }
    return ans;
}

int main() {
	// ���⣺��[l,r]������û��4��62�����ĸ��� 
	// ��λdp 
	init();
	for (int l, r; cin >> l >> r && l + r; )
		cout << dp(r + 1) - dp(l) << endl;
	return 0;
}

