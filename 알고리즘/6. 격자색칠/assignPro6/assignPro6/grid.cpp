#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
ifstream fin("grid.inp");
ofstream fout("grid.out");
void one(int N, int M, int mat, vector<int> v) {
	if (mat <= v[0]) {
		fout << "Yes" << endl;
	}
	else {
		fout << "No" << endl;
	}
	return;
}

void two(int N, int M, int mat, vector<int> v) {
	int a = (v[0] / N) * N;
	int b = (v[0] / M) * N;
	if (a == b) {
		if (M > N) {
			b = M;
			a = 0;
		}
		else {
			a = N;
			b = 0;
		}
	}
	if (a > b) {
		int c = v[0] / N;
		mat -= c * N;
		if (mat <= v[1]) {
			fout << "Yes" << endl;
			return;
		}
		else {
			fout << "No" << endl;
			return;
		}
	}
	else {
		int c = v[0] / M;
		mat -= c * M;
		if (mat <= v[1]) {
			fout << "Yes" << endl;
			return;
		}
		else {
			fout << "No" << endl;
			return;
		}
	}

}

void up(int N, int M, int mat, vector<int> v) {
	int a = (v[0] / N) * N;
	int b = (v[0] / M) * N;
	if (a == b) {
		if (M > N) {
			b = M;
			a = 0;
		}
		else {
			a = N;
			b = 0;
		}

	}
	if (b > a) {
		for (int i = 0; i < v.size(); i++) {
			if (i == v.size() - 1) { //마지막 원소
				if (v[i] >= mat) {
					fout << "Yes" << endl;
					return;
				}
				else {
					fout << "No" << endl;
					return;
				}

			}
			else {
				if (v[i] < M * 2) {
					fout << "No" << endl;
					return;
				}
				else {
					int tmp = v[i] / M;
					mat -= M * tmp;
				}
			}
			if (mat <= 0) {
				fout << "Yes" << endl;
				return;
			}
		}
	}
	else {
		for (int i = 0; i < v.size(); i++) {
			if (i == v.size() - 1) { //마지막 원소
				if (v[i] >= mat) {
					fout << "Yes" << endl;
					return;
				}
				else {
					fout << "No" << endl;
					return;
				}

			}
			else {
				if (v[i] < N * 2) {
					fout << "No" << endl;
					return;
				}
				else {
					int tmp = v[i] / N;
					mat -= N * tmp;
				}
			}
		}
	}
}

int main(void) {
	int count;
	fin >> count;
	while (count--) {
		int N; //격자 크기
		int M; //격자 크기
		int K; // 물감
		fin >> N >> M >> K;
		int cnt = (N > M) ? M : N;

		vector <int> v;
		for (int i = 0; i < K; i++) {
			int a;
			fin >> a;
			if (a >= cnt * 2) { //2개 이상 있어야 grid완성
				v.push_back(a);
			}
		}

		int mat = N * M; // 크기
		sort(v.begin(), v.end());

		if (v.size() == 0) {
			fout << "No" << endl;
		}
		if (v.size() == 1) { //쓸수 있는 물감수
			one(N, M, mat, v);
		}
		else if (v.size() == 2) {
			two(N, M, mat, v);
		}
		else {
			up(N, M, mat, v);
		}
	} //while
	fin.close();
	fout.close();
	return 0;
}