#include <bits/stdc++.h>
using namespace std;
int arr[1001] = { 0, };
int dp[1001] = { -99999, };
int dp_2[1001] = { -99999, };
ifstream fin("card.inp");
ofstream fout("card.out");

int ans = -999999;
int card(int num,int check) {
	int c1=ans, c2=ans, c3 = ans;
	int a =num-2;
	int b=num-3;
	int c=num-4;
	
    if (num==2||num==1||num==0) {
		return arr[num];
	}
	
	if (check == 2) {
		if (dp_2[num]) {
			return dp_2[num];
		}
	}
	else {
		if (dp[num]) {
			return dp[num];
		}
	}
	if (check == 2) {
		if (num == 3) {
			c2 = card(b, 3);
		}
		else {
			// 두 칸 두 칸 간 경우
			c2 = card(b, 3);
			c3 = card(c, 4);
		}
	}
	else if (check != 2) {
		if (num ==3) {
			c1 = card(a, 2);
			c2 = card(b, 3);
		}
		else {
			c1 = card(a, 2);
			c2 = card(b, 3);
			c3 = card(c, 4);
		}
	}
	// 제일 큰 값 리턴
	if (check == 2) {
		int max_card = max(c1, max(c2, c3));
		dp_2[num] = max_card + arr[num];
		return dp_2[num];
	}
	else {
		int max_card = max(c1, max(c2, c3));
		dp[num] = max_card + arr[num];
		return dp[num];
	}

}
int main() {
	int cnt;
	fin >> cnt;
	while (cnt--) {
		int tmp;
		fin >> tmp;
		int num;
		for (int i = 0; i < tmp; i++) {
			fin >> num;
			arr[i] = num;
		}
		for (int i = 0; i < 3; i++) {
			dp[i] = arr[i];
			dp_2[i] = arr[i];
		}
		int end=card(tmp-1, 0);
		fout << end << endl;
		memset(arr,0, sizeof(int) * 1001);
		memset(dp, 0, sizeof(int) * 1001);
		memset(dp_2, 0, sizeof(int) * 1001);
	}
	fout.close();
	fin.close();
}