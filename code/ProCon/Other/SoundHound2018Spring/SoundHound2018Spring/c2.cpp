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
	// �a�{P199�AP240���Q�l�ɂȂ�炵��
	int r, c;
	vector<list<char>>t;
	rep(i, r*c) {
		t[i].push_back(i + 1);
		t[i].push_back(i - 1);
		t[i].push_back(i + c);
		t[i].push_back(i - c);
	}


	return 0;
}



