#include <bits/stdc++.h>
using namespace std;
int file[10001][10001] = { 0, };
ifstream fin("replacement_input.txt");
ofstream fout("replacement_output.txt");

int selection(int cnt,vector<int>&v,vector<int>&freeze) {
	sort(v.begin(), v.end());
	int i = 0, j = 0;
	file[i][j++] = v[0];
	v.erase(v.begin()); //제일 작은거 삭제.
	while (true) {
		int tmp;
		fin >> tmp;
		cnt--;
		if (file[i][j - 1] > tmp) { //freeze되는 경우
			freeze.push_back(tmp); //freeze 벡터에 넣음.
			if (freeze.size() == 5 || v.size() == 0) {
				for (int i = 0; i < 5; i++) {
					v.push_back(freeze[i]);
				}
				freeze.clear();
				i++;
				j = 0;
			}
			sort(v.begin(), v.end());
			file[i][j++] = v[0];
			v.erase(v.begin());
		}
		else { //freeze 되지 않은 경우 바로 파일에 넣음.
			v.push_back(tmp);
			sort(v.begin(), v.end());
			file[i][j++] = v[0];
			v.erase(v.begin());

		}
		if (cnt == 0) { //마지막까지 다 읽을경우
			while (v.size()!=0) { //freeze되지 않는 값들은 파일에 저장
				file[i][j++] = v[0];
				v.erase(v.begin());
			}
			i++;
			j = 0;
			sort(freeze.begin(), freeze.end());
			while (freeze.size()) { //freeze값들은 새로운 파일에 저장
				file[i][j++] = freeze[0];
				freeze.erase(freeze.begin());
			}
			return i+1; //i가 0부터 시작이니 +1해서 return
		}
	}
} //selection함수

void print(int num) {
	fout << num << endl;
	for (int i =0;i<num; i++) {
		for (int j = 0;; j++) {
			if (file[i][j] != 0) {
				fout << file[i][j] << " ";
			}
			else {
				break;
			}
		}
		fout << endl;
	}
} //print함수

int main() {
	int test;
	fin >> test; //test 개수
	while (test--) {
		vector<int>v(5, 0);
		vector <int> freeze;
		int cnt;
		fin >> cnt;
		int arr[5] = { 0, }; //초기 5개 넣음.
		for (int i = 0; i < 5; i++) {
			int tmp;
			fin >> tmp;
			v[i] = tmp;
		}
		int num= selection(cnt - 5,v,freeze);
		print(num);
		memset(file, 0, sizeof(int) * 10001 * 10001);
	}
	fin.close();
	fout.close();
	return 0; 
 } //main함수