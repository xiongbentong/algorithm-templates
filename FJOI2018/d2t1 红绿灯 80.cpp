/*
luoguU19764 day2T1 ���̵�(light) 80pts

���⣺n��·�ڣ��̵�g����r�룬q��ѯ�ʣ�ѯ�ʴ�ʱ��t���������յ�����ʱ�� 

�ⷨ��f[i]��ʾ��i���̵Ƹտ�ʼʱ�ߵ��յ�������ʱ
f[i]������dp�󣺴�i�㿪ʼ�ߣ�ֱ����j���������
f[i]=dis(i,j)+�Ⱥ��ʱ��+f[j]
��ansҲ�����ƣ��ߵ���һ�����i��ans=dis(0,i)+wait+f[i]
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 5e4+50;
int n;
LL g, r, d[N], f[N];

void Init() {
	for (int i = n; i; i--) {
		for (int j = i+1; j <= n+1; j++) {
			f[i] += d[j];
			if (j <= n && f[i] % (g+r) >= g) {
				//�̵�ʱ��Ϊg+r������Ҫ�ȵ�ʱ��Ϊg+r-����ʱ�� 
				f[i] += g+r-f[i]%(g+r) + f[j];
				break;
			}
		}
	}
}

LL Solve(LL st) {
	LL ans = st;
	for (int i = 1; i <= n+1; i++) {
		ans += d[i];
		if (i <= n && ans%(g+r) >= g) {
			// ͬ�� 
			ans += g+r-ans%(g+r) + f[i];
			break;
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> g >> r;
	for (int i = 1; i <= n+1; i++)
		cin >> d[i];
	Init();
	int q; cin >> q;
	for (LL r; q--; ) {
		cin >> r;
		cout << Solve(r) << endl;
	}
    return 0;
}

