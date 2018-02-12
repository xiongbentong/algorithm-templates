/*
luoguU19958 day4T1 ����(frog) 100pts

���⣺k��ʯͷ�ų�һ�ţ�mֻ���ܴ�1����n��ÿ��ʯͷ����ǡ�ñ���һ��
ÿ����iֻ�������ľ������d����Ҫ֧��һ��c[i]�ķ��á���С���ܷ���

�ⷨ�����ȴ��������ж���ֻ���ܿ�����ѵ����Ϊp
��p>0�����ŷ�������ѵİ�ʯͷ�������ˣ�ʣ��m-pֱֻ�Ӵ�1����n
��p=0�����ŷ�����c[i]��С�����ܰ�1~nȫ��һ�飬ʣ��ֱ�Ӵ�1����n
��p������̰�ģ�ÿֻ�����������������ұߵĵ� 
����أ�����ÿ��i�����dis(i,j)<=d������j����ô������j+1����ͨ��[i+1,j]��j-i��ʯͷ
���Ƕ�ÿ��i��min(j-i)��Ϊp��������i����jҲ���������Ӷ�O(n) 
*/ 
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+50;
int cost[N], pos[N];
int main() {
	ios::sync_with_stdio(false);
	int T; cin >> T;
	for (int n, m, k, d; T--; ) {
		cin >> n >> m >> k >> d;
		for (int i = 1; i <= m; i++)
			cin >> cost[i];
		for (int i = 1; i <= k; i++)
			cin >> pos[i];
		sort(cost + 1, cost + m + 1);
		sort(pos + 1, pos + k + 1); 
		pos[0] = 1; pos[k+1] = n;
		int far = 0;
		for (int i = 0; i <= k; i++)
			if (pos[i+1] - pos[i] > d) far++;
		long long ans = 0;
		if (far) {  // û������ѵ�������� 
			ans = 1LL * far * cost[1];  // ������С������ȫ��һ�� 
			for (int i = 2; i <= m; i++)
				ans += cost[i];  // �����1�ɵ�n 
		} else {
			int free = m;
			for (int l = 0, r = 0; l <= k; l++) {
				while (r <= k && pos[r+1] - pos[l] <= d) r++;
				if (r == k + 1) break;
				free = min(free, r - l);  // p=min{r-l} 
			}
			for (int i = 1; i <= m - free; i++)
				ans += cost[i];  // ʣ��m-pֻ���ܴ�1�ɵ�n 
		}
		cout << ans << endl;
	}
    return 0;
}

