#include <bits/stdc++.h>
using namespace std;
int coin[101][101][101];

void coin_set() {
	coin[0][0][0] = 1;
	coin[0][0][1] = -1;
	coin[0][1][0] = -1;
	coin[1][0][0] = -1;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				if (i == j && j == k) {
					if (i == 1 || j == 1 || k == 1) {  /// 111 경우
						coin[i][j][k] = -1;
					}
					else { //222 333
						coin[i][j][k] = 1;
					}
				}
				else if (i!=0 && j!=0 && k!=0 && i != j && j != k && k != i) { //123 case 6개
					coin[i][j][k] = -1;
				}
				else if ((i == 0 && j == 3 && k == 3) || (i == 3 && j == 0 && k == 3) || (i == 3 && j == 3 && k == 0)) { // 3 3 0
					coin[i][j][k] = -1;
				}
				else if ((i == 0 && j == 2 && k == 2) || (i == 2 && j == 0 && k == 2) || (i == 2 && j == 2 && k == 0)) { // 2 2 0
					coin[i][j][k] = -1;
				}				
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				if (coin[i][j][k] == 0) coin[i][j][k] = 1;
			}
		}
	}

}
void coin_dp() {
	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 101; j++) {
			for (int k = 0; k < 101; k++) {
				if (coin[i][j][k] != 0) {
					// 숫자있는거 패스
				}
				else {
					int i2 = i % 4;
					int j2 = j % 4;
					int k2 = k % 4;
					coin[i][j][k] = coin[i2][j2][k2];
				}
			}
		}
	}
}

	
int main() {
	coin_set(); //0~3 까지
	coin_dp();
	ifstream fin("coin.inp");
	ofstream fout("coin.out");
	int cnt;
	fin >> cnt;
	while (cnt--) {
	int a, b, c;
		fin >> a >> b >> c;	
		fout << "(" << a << " " << b << " " << c << ") : " <<coin[a][b][c]<< '\n';
	}
	return 0;
}