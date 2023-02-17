#include <bits/stdc++.h>
using namespace std;
int dp[1001][1001] = { 0, };
int sum[1001] = { 0, };
void card(int sum[],int t) {
	int cnt = t % 2;
	if (cnt==1) { //홀수 개수가 들어올 경우
		for (int i = 1; i <= t; i++) {
			dp[i][i] = sum[i];
		}
	}
	for (int i = 1; i <= t; i++) {
		int k = 1;
		for (int j = i+1; j <= t; j++) {
			//if (i == j) continue; // 같은경우 패스
			//else
			if (cnt % 2 == 0) {
				dp[k][j] = max(dp[k][j - 1] + sum[j], dp[k + 1][j] + sum[k]);
				k++;
			}
			else {
				dp[k][j] = min(dp[k][j - 1], dp[k+1][j]);
				k++;
			}
		}
		cnt++;
	}
}

int main() {
	ifstream fin("card.inp");
	ofstream fout("card.out");
	int n;
	fin >> n;
	while(n--){
		int  t; fin >> t;
		for (int i = 1; i <= t; i++) {
			int tmp;
			fin >> tmp;
			sum[i] = tmp;
		}
		card(sum, t);
		fout << dp[1][t] << endl;
		memset(dp, 0, sizeof(dp));
		memset(sum, 0, sizeof(sum));
	}
	return 0;
}