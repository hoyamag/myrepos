
#include<math.h>
#include<limits.h>
#include<iostream>
#include<string>
#include<vector>
#include<stdio.h>
#include<sstream>
#include<list>
#include<queue>
#include<algorithm>
#include<functional>
#include<map>
#include<set>
#include<utility>
#include<initializer_list>
#include<tuple>
#include<regex>
using namespace std;
#define ull unsigned long long
#define ll long long
#define rep(i, n) for(int i=0;i<(int)(n);i++)
#define all(t) t.begin(), t.end()
#define mat(type, row, col, init) vector<vector<type>>(row, vector<type>(col, init));
#include<math.h>
#include<limits.h>
#include<iostream>
#include<string>
#include<vector>
#include<stdio.h>
#include<sstream>
#include<list>
#include<queue>
#include<algorithm>
#include<functional>
#include<map>
#include<set>
#include<utility>
#include<initializer_list>
#include<tuple>
#include<regex>
using namespace std;
#define ull unsigned long long
#define ll long long
#define rep(i, n) for(int i=0;i<(int)(n);i++)
#define all(t) t.begin(), t.end()
#define mat(type, row, col, init) vector<vector<type>>(row, vector<type>(col, init));

int main() {
	// ABC067d
	int n;
	cin >> n;
	vector<list<int>>g(n);
	rep(i, n - 1) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	int nl, nr;// �h�����_�̐�(�_0����Ɠ_n-1����)
	nl = nr = 1;
	vector<bool>splat(n, false);// �F�h��ς݂��ǂ������i�[
	splat[0] = splat[n - 1] = true;

	// �_0�Ɠ_n-1��2�_������݂�BFS��i�߂āA
	// �����̒T�����������Ȃ��Ȃ�����A
	// �h�ꂽ�_�̐��𐔂��ď��s���o�͂���
	queue<int>sl, sr;
	sl.push(0);
	sr.push(n - 1);
	while (!sl.empty() || !sr.empty()) {
		// ����1�񕪂�POP�́A����(pop��)�̓_�����ׂĒT�����邱�ƂƂ͈�v���Ȃ����߁A
		// ���̎����ł�AC���Ȃ��B
		if (!sl.empty()) {
			int l = sl.front();
			sl.pop();
			for (auto v : g[l]) {
				if (splat[v] == false) {
					splat[v] = true;
					sl.push(v);
					nl++;
				}
			}
		}
		if (!sr.empty()) {
			int r = sr.front();
			sr.pop();
			for (auto v : g[r]) {
				if (splat[v] == false) {
					splat[v] = true;
					sr.push(v);
					nr++;
				}
			}
		}
	}
	

	if (nl > nr) cout << "Fennec" << endl;
	else cout << "Snuke" << endl;


	return 0;
}


