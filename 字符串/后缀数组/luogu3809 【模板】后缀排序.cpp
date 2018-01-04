#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 2e6+50;
char s[N];
int n, t[N], rk[N], tmp[N], sa[N], height[N];

void GetSA() {  // ��sa,rk,height���� 

    int m = 'z' + 5;  // m��Ͱ�ŵ��Ͻ磬�ɱ� 
    
    // ��Ͱ�ţ��൱�ڰ��ַ���ɢ��һ�� 
    for (int i = 1; i <= n; i++) t[rk[i] = s[i]]++;
    for (int i = 1; i <= m; i++) t[i] += t[i-1];
    for (int i = n; i >= 1; i--) sa[t[rk[i]]--] = i;  // ����ѭ������֤�����ȶ� 
    
    for (int k = 1; ; k <<= 1) {  // k��ʾ��ǰҪ����Ĵ�����/2 
        int cnt = 0;
        
        // y�д洢�������Ԫ��ĵ�һ�ؼ��ֵ�λ�� 
        // ��k����û�еڶ��ؼ��֣����ȼ���ߣ��ȷŽ��� 
        for (int i = n - k + 1; i <= n; i++) tmp[++cnt] = i;  
        
        // �еڶ��ؼ��ֵĶ�Ԫ�飬���ڶ��ؼ��ִ�С����Ž�������֤˫�ؼ������� 
        for (int i = 1; i <= n; i++) if (sa[i] > k) tmp[++cnt] = sa[i] - k;
        
        // �Ե�һ�ؼ��ֽ���Ͱ����rk�б��������һ������Ľ���� 
        memset(t, 0, sizeof(int) * (m + 5));
        for (int i = 1; i <= n; i++) t[rk[tmp[i]]]++;
        for (int i = 1; i <= m; i++) t[i] += t[i-1];
        for (int i = n; i >= 1; i--) sa[t[rk[tmp[i]]]--] = tmp[i];
        
        // ���ϴ���������ʱ����tmp���tmp������û��ϵ�����������������rk 
        // ���swapֻ�ǽ���ָ�룬��ʡ�ռ���ʡʱ�� 
        swap(rk, tmp); rk[sa[1]] = cnt = 1;
        for (int i = 2; i <= n; i++)
            // �������ͬ������ͬ 
            rk[sa[i]] = tmp[sa[i]] == tmp[sa[i-1]] && tmp[sa[i]+k] == tmp[sa[i-1]+k] ? cnt : ++cnt;
        
        // ����Ͱ���Ͻ磨����ͬ��Ԫ�ظ����������Ͻ�Ϊn���Ѿ��ź���û��Ҫ������ 
        if ((m = cnt) >= n) break;
    }
    
    // height[i]>=height[i��ǰһ��]-1�������������O(n)���� 
    for (int i = 1, k = 0, j; i <= n; height[rk[i++]] = k)
        for (k = k ? k - 1 : k, j = sa[rk[i]-1]; rk[i] != 1 && s[i+k] == s[j+k]; k++);
}

/*
���⣺���ַ��������зǿպ�׺���ֵ����С��������Ȼ��˳�������׺�ĵ�һ���ַ���ԭ���е�λ��
������sa���飩 
*/
int main() { 
    scanf("%s", s + 1); n = strlen(s + 1);
    GetSA();
    for (int i = 1; i <= n; i++)
        printf("%d ", sa[i]);
    putchar('\n');
    return 0;
}


