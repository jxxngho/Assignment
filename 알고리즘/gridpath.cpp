#include <bits/stdc++.h>
#include <utility>
using namespace std;
int DP[201][201] = { 0 };
int grid[201][201] = {0};
vector<pair<int,int>> pa;
int main() {

    ifstream fin("gridpath.inp");
    ofstream fout("gridpath.out");
    int n, m;
    fin >> n >> m; // n가로 m세로
    int tmp; //
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fin >> tmp;
            grid[i][j] = tmp;
        }
    }
    //1행 채워주기.
    DP[0][0] = grid[0][0];
    for (int i = 1; i < m; i++) {
        if (grid[0][i] == -1) {
            DP[0][i] = -1;
            while (i != m-1) {
                i++;
                DP[0][i] = -1;
            }
            break;
        }
        else {
            DP[0][i] = grid[0][i] + DP[0][i-1];
        }
    } //1열 채워주기.
    for (int i = 1; i < n; i++) {
        if (grid[i][0] == -1) {
            DP[i][0] = -1;
            while (i != n-1) {
                i++;
                DP[i][0] = -1;
            }
            break;
        }
        else {
            DP[i][0] = grid[i][0] + DP[i-1][0];
        }
    } // 1열 채워주기.

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (grid[i][j] == -1) {
                DP[i][j] = -1;
            }
            //else if
            else if (DP[i - 1][j] == -1 && DP[i][j - 1] == -1) {
                    DP[i][j] = -1;
            }
            else if (DP[i - 1][j] == -1) {
                DP[i][j] = DP[i][j - 1]+ grid[i][j];
            }
            else if (DP[i][j - 1] == -1) {
                DP[i][j] = DP[i - 1][j]+grid[i][j];
            }
            else
                DP[i][j] = min(DP[i - 1][j], DP[i][j - 1]) + grid[i][j];
        }
    }

    int cnt = n - 1 + m - 1;
    int cnt2 = cnt;
    n = n - 1;
    m = m - 1; // 배열 0이 존재하기때문
    int n2 = n;
    int m2 = m;;
    pa.push_back(pair<int, int>(n, m));
    int ans2 = grid[n][m];
    int ans = DP[n][m];

    while (cnt--) {
        if (n == 0) { //n이 0일때 왼쪽으로만 이동
            pa.push_back(pair<int, int>(n, m - 1));
           // cout << n << " " << m - 1<<endl;
            ans2 += grid[n][m - 1];
            m--;
        }
        else if (m == 0) {  //m이 0일때 위쪽으로만 이동
            pa.push_back(pair<int, int>(n-1, m));
            ans2 += grid[n-1][m];
           // cout << n-1<< " " << m << endl;
            n--;
        }
        else if (DP[n - 1][m] == -1) { //위쪽이 -1이면 왼쪽으로만 이동
          //  cout << n << " " << m-1 << endl;
            pa.push_back( pair<int, int>(n, m - 1));
            ans2 += grid[n][m - 1];
            m--;
        }
        else if (DP[n][m-1] == -1) { // 왼쪽이 -1이면 위쪽으로만 이동
           // cout << n-1 << " " << m << endl;
            pa.push_back(pair<int, int>(n-1, m));
            ans2 += grid[n-1][m];
            n--;
        }
        else if (DP[n - 1][m] == DP[n][m - 1]) { //크기비교
   
            if (DP[n - 1][m - 1] != -1) { //대각선이 -1이 아니면
                pa.push_back(pair<int, int>(n-1,m));
              //  cout << n - 1 << " " << m << endl;
                ans2 += grid[n-1][m];
                n--;
                pa.push_back(pair<int, int>(n, m-1));
             //   cout << n << " " << m-1 << endl;
                ans2 += grid[n][m - 1];
                m--;
                cnt--;
            }
            else {
                pa.push_back(pair<int, int>(n-1, m));
              //  cout << n-1  << " " << m << endl;
                ans2 += grid[n-1][m];
                n--;
            }
        }
        else if (DP[n - 1][m] >DP[n][m - 1]) { //크기비교
          //  cout << n-1 << " " << m  << endl;
            pa.push_back(pair<int, int>(n, m-1));
            ans2 += grid[n][m - 1];
            m--;
        }
        else {
          //  cout << n-1 << " " << m  << endl;
            pa.push_back(pair<int, int>(n-1, m));
            ans2 += grid[n-1][m];
            n--;
        }
    }//m_loop
    if (ans2 != ans) {
        fout << "No path.";
    }
    else {
        fout << ans << endl; //정답 최소경로
        for (int i = pa.size() - 1; i >= 0; i--) {
            fout << "(" << pa[i].first << " " << pa[i].second << ")" << endl;
        }
    }
    return 0;
}
