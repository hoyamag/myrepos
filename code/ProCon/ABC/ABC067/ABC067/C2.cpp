//#include<math.h>
//#include<limits.h>
//#include<iostream>
//#include<string>
//#include<vector>
//#include<stdio.h>
//#include<sstream>
//#include<list>
//#include<queue>
//#include <algorithm>
//#include<initializer_list>
//using namespace std;
//#define ul unsigned long long
//#define lol long long
//#define rup(i, a, b) for(int (i) = (a); (i) < (b); (i)++)
//#define rdn(i, a, b) for(int (i) = (a); (i) > (b); (i)--)
//
//vector<lol> a;
//
////lol bin(lol begin, lol end) {
////	// a[begin]����a[floor(end/2)]�̑��a��a[floor(end/2)]����a[end]�܂ł̑��a�̍���Ԃ��B
////	// a[begin]����a[end]��2���������Ƃ��A
////	//	���ꂼ��̑��a���ŏ��ƂȂ�Y����
////	//	���ꂼ��̑��a
////	//	��Ԃ��B
////}
////lol bin2(lol begin, lol ned){
//////a�̓Y����begin��end��^����ƁAbegin~floor(end/2)�̑��a��floor(end / 2 + 1)~end�̑��a���r���āA
//////begin����̂ق����傫�����begin���Afloor(end / 2 + 1)����̕����傫�����floor(end / 2 + 1)��Ԃ�
////}
////lol binSearch(lol begin, lol end, leftSum, rightSum) {
////	//a�̓Y����begin��end��^����ƁAa��2���������Ƃ����ꂼ��̑��a���ł��������Ȃ�悤�ȓY������Ԃ��B
////	lol leftSum = sum(begin, floor(end / 2));
////	lol rightSum = sum(floor(end / 2), end);
////	if (leftSum > rightSum) {
////		binSearch(begin, floor(end / 2));
////	}
////	else {
////		binSearch(floor(end / 2), end);
////	}
////}
////lol bin(lol separate, lol x, lol y) {
////	//vector a��2���������Ƃ��A���ꂼ��̑��a���ł��߂��Ȃ�悤�ȓY������Ԃ��B
////	// �ċN�֐��Bseparate�ɂ͂͂���floor((a.size())/2)��n���Bx��y��a��separate�ŕ������Ƃ��́A���ꂼ��̕����a
////	if (x > y) {
////		lol s = floor(separate / 2);
////	}
////
////}
//lol sum(lol begin, lol end) {
//	lol sum = 0;
//	for (lol i = begin; i < end; i++) {
//		sum += a[i];
//	}
//	return sum;
//}
//
//int main() {
//	int n;
//	cin >> n;
//	a = vector<lol>(n, 0);
//	rup(i, 0, n) cin >> a[i];
//	lol s = lol(ceil(n / 2));
//	lol x = sum(0, s);
//	lol y = sum(s, n);
//	lol eva = abs(x-y);
//	if (n != 2) {
//		while (1) {
//
//			lol nx = x;
//			lol ny = y;
//			lol ns = s;
//			if (x > y) {
//				nx -= a[ns - 1];
//				ny += a[ns - 1];
//				ns--;
//			}
//			else {
//				nx += a[ns];
//				ny -= a[ns];
//				ns++;
//			}
//			lol newEva = abs(nx - ny);
//			if (newEva < eva) {
//				x = nx;
//				y = ny;
//				s = ns;
//				eva = newEva;
//			}
//			else {
//				break;
//			}
//		}
//	}
//	cout << eva;
//	return 0;
//}
//
//
//
