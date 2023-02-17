#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void ninespin(char** arr, int n) {  //90�� ȸ��
	char** tmparr = new char* [n];
	for (int i = 0; i < n; i++) {
		tmparr[i] = new char[n];
	} // �ӽù迭

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tmparr[j][n - i - 1] = arr[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = tmparr[i][j];
		}
	}
}
void slide(char** arr, int n) {
	char** tmparr = new char* [n];
	for (int i = 0; i < n; i++) {
		tmparr[i] = new char[n];
	} ///�ӽù迭

	int count = 0;
	for (int i = 0; i <= n - 1; i++) {
		vector <char> c;
		for (int j = n - 1; j >= 0; j--) {
			if (arr[j][i] != '.') {
				c.push_back(arr[j][i]);
			}
		}
		int tm = c.size();
		for (int j = n - 1; j >= 0; j--) {
			if (c.size() > 0) {
				tmparr[j][i] = c[0];
				c.erase(c.begin());
			}
			else {
				tmparr[j][i] = '.';
			}
		}

	}

	//�����ϱ�.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = tmparr[i][j];
		}
	}
}

int main() {
	ifstream fin("spinslide.inp");
	ofstream fout("spinslide.out");
	int testcase; //�׽�Ʈ����
	fin >> testcase;
	int count = 1;
	while (testcase--) {
		int n; // �������� �� ���� ũ��
		fin >> n;
		char** arr = new char* [n];
		for (int i = 0; i < n; i++) {
			arr[i] = new char[n];
		}
		int m; // spinslide ������ Ƚ��
		fin >> m;
		char ch;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				fin >> ch;
				arr[i][j] = ch;
			}
		} //�����̳ʿ� ����.
		while (m--) {
			ninespin(arr, n);
			slide(arr, n);
		}
		fout << "Case #" << count << ":" << endl;
		count++;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				fout << arr[i][j];
			}
			fout << endl;
		}
		fout << endl;
	}
	fin.close();
	fout.close();
}