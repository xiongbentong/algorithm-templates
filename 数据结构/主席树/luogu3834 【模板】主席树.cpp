#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 200050, INF = 1e9;

struct Node {
    int ls, rs, sum;
    Node(): ls(0), rs(0), sum(0) {}
}tr[N*40];  // nlogL
int top = 1, root[N];

void insert(int &cur, int pre, int val, int L, int R) {  // &cur������ĸ��ڵ�Ķ��� 
    (tr[cur = top++] = tr[pre]).sum++;  // insert���ʵ��Ľ��һ����Ҫ�¿� 
    if (L == R) return;
    int mid = (L + R) >> 1;
    // �ı�Ҫ�ľ͸��ıߣ���һ����ԭ���� 
    if (val <= mid) insert(tr[cur].ls, tr[pre].ls, val, L, mid);
    else insert(tr[cur].rs, tr[pre].rs, val, mid + 1, R);
}

int kth(int lu, int ru, int L, int R, int k) {  // ��׼Ȩֵ�߶�����k�󣬲���sumҪ��r��l-1��� 
    if (L == R) return L;
    int lCnt = tr[tr[ru].ls].sum - tr[tr[lu].ls].sum, mid = (L + R) >> 1;
    if (k <= lCnt) return kth(tr[lu].ls, tr[ru].ls, L, mid, k);
    return kth(tr[lu].rs, tr[ru].rs, mid + 1, R, k - lCnt);
}

/*
��Ŀ���⣺��̬�����k��
������
Ҫ��������k�����⣬ֻҪ���������l~r��Ȩֵ�߶�����Ȼ���������ж��ֲ��Ҽ���
��ת��һ�£�ֻҪ�õ�1~l-1��1~r�������߶�����Ȼ����ǰ׺�͵ķ������ܵõ�l~r���� 
��ϯ����ȫ���ɳ־û��߶�����������ͬʱ����1~1,1~2,...,1~n��n�������Ȩֵ�߶���
��Ϊ��i�����ȵ�i-1����ֻ�������һ���������i�����󲿷ֽ�����ֱ���õ�i-1�õ�
ʱ��O(nlogL)����������ͨ�߶�����ͬ�����ռ�O(nlogL)����̬���㣬ÿ����һ����ռ���log�ģ� 
����L�����ַ�Χ������������ɢ�� 
*/
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int t, i = 1; i <= n; i++) {
        scanf("%d", &t);
        insert(root[i], root[i-1], t, -INF, INF);
    }
    for (int l, r, k; m--; ) {
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", kth(root[l-1], root[r], -INF, INF, k));
    }
    return 0;
}

