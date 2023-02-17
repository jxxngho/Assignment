#include <bits/stdc++.h>
using namespace std;
long long dp[301][21] = { 0, };
ifstream fin("addingways.inp");
ofstream fout("addingways.out");
void adding() {
	for (int i = 1; i <= 300; i++) {
		dp[i][1] = 1;
	}
	for (int i = 1; i <= 300; i++) {
		dp[i][2] = i / 2;
	}
	for (int i = 1; i <= 20; i++) {
		dp[i][i] = 1;
	}
	for (int i = 2; i <= 300; i++) {
		for (int j = 1; j <=20; j++) {
			if (dp[i][j] != 0) continue;
			else if (j > i) break;
			else if (i >= j) {
				int k = 1;
				long long sum = 0;
				while (k <= j) {
					sum += dp[i - j][k];
					k++;
				}
				sum = sum % 1000000007;
				dp[i][j] = sum;
			}
		}
	}
}
int main() {

	adding();
	while (true) {
		int a, b;
		fin >> a >> b;
		if (a == 0 && b == 0) {
			fin.close();
			fout.close();
			return 0;
		}
		else {
			fout << dp[a][b] << endl;
		}
	}

}