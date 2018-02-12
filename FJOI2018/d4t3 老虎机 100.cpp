/*
luoguU19964 day4T3 �ϻ���(slot) 100pts

���⣺n���ϻ���������Li����ÿ��������ɫ
��������Ҫ�ö��ٸ�Ӳ�Ҳ����õ�������ɫ��ͬ����

�ⷨ������������������ͬһ�������������������Ϊ
min{��ɫ���ظ��Ļ�������ɫ��+1}
�������������������Բ�ͬ�������Ϳ�����ȥ����
��f(i,j)��ʾ����i�ϵ�j�����������������ó�������С����
��ô����һ���ᰴf�ݼ���˳������
��ÿ�������ϵ�f����������ans=min{j+f(i,j)} 
f(i,j)����ͨ������ȡ��ÿ����ɫ����������Сֵ�ʹ�Сֵ�õ� 
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+50, INF = 0x3f3f3f3f;
int min1[N], min2[N], siz[N], f[N];
vector<int> a[N];
int main() {
	ios::sync_with_stdio(false);
	int T; cin >> T;
	while (T--) {
		int ans = INF;
		memset(min1, 0x3f, sizeof(min1));
		memset(min2, 0x3f, sizeof(min2));
		int n; cin >> n;
		for (int i = 1; i <= n; i++) {
			a[i].clear();
			cin >> siz[i];
			for (int j = 0, r; j < siz[i]; j++)
				cin >> r, a[i].push_back(r);
			sort(a[i].begin(), a[i].end());
			int k = unique(a[i].begin(), a[i].end()) - a[i].begin();
			if (k < siz[i]) {  // �������������ͬһ������ 
				ans = min(ans, k + 1);
				siz[i] = k;
			}
			for (int j = 0; j < siz[i]; j++) {
				// ������ɫ������Сֵ�ʹ�Сֵ 
				if (siz[i] < min1[a[i][j]])
					min2[a[i][j]] = min1[a[i][j]], min1[a[i][j]] = siz[i];
				else min2[a[i][j]] = min(min2[a[i][j]], siz[i]);
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < siz[i]; j++) {
				if (siz[i] == min1[a[i][j]])
					f[j] = min2[a[i][j]];
				else f[j] = min1[a[i][j]];
			}
			// ���f������ 
			sort(f, f + siz[i], greater<int>());
			for (int j = 0; j < siz[i]; j++)
				ans = min(ans, j+1+f[j]);  // ��Ϊ�±��0��ʼ��Ҫ�ǵ�+1 
		}
		cout << ans << endl;
	}
    return 0;
}

