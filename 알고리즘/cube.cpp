#include <bits/stdc++.h>
using namespace std;
int cube[201][201][201] = { 0, };
int w, l, h;
ifstream fin("cube.inp");
ofstream fout("cube.out");

int ans(int w, int l, int h) {

	if (cube[w][l][h] != 0) { //있을경우 바로 리턴
		return cube[w][l][h];
	}
	else if ((w == 1 && l == 1 && h == 1) || (w == l && l == h)) { // 111 또는 세 개 다 같은경우
		cube[w][l][h] = 1;
		cube[w][h][l] = 1;
		cube[l][w][h] = 1;
		cube[l][h][w] = 1;
		cube[h][w][l] = 1;
		cube[h][l][w] = 1;
		return 1;
	}
	else if (w == 1) { //w가 1인경우
		cube[w][l][h] = l * h;
		cube[w][h][l] = l * h;
		return l * h;
	}
	else if (l == 1) { // l이 1인경우
		cube[w][l][h] = w * h;
		cube[h][l][w] = w * h;
		return w * h;
	}
	else if (h == 1) { // h가 1인경우
		cube[w][l][h] = w * l;
		cube[l][w][h] = w * l;
		return w * l;
	}
	else {
		int m1 = 10000000;
		int m2 = 10000000;
		int m3 = 10000000;
		for (int i = 1; i <= w / 2; i++) {
			//cube[i-1][j][k] =
			m1 = min(m1, ans(w - i, l, h) + ans(i, l, h));
		}
		for (int i = 1; i <= l / 2; i++) {
			m2 = min(m2, ans(w, l - i, h) + ans(w, i, h));
		}
		for (int i = 1; i <= h / 2; i++) {
			m3 = min(m3, ans(w, l, h - i) + ans(w, l, i));
		}
		int m = min(m1, min(m2, m3));
		cube[w][l][h] = m;
		cube[w][h][l] = m;
		cube[l][w][h] = m;
		cube[l][h][w] = m;
		cube[h][w][l] = m;
		cube[h][l][w] = m;
		return m;
	}
}
		

int main() {

	int cnt;
	fin >> cnt;
	while (cnt--) {
		fin >> w >> l >> h;
		fout << ans(w,l,h)<< endl;
	}

	return 0;
}