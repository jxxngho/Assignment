#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream fin("stairs.inp");
	ofstream fout("stairs.out");
	int count;
	fin >> count;

	while (count--) {
		int ans = 0; //����
		int m; //  �ǹ��� ����
		int f; //  ��� ��� �ִ� ��
		int n; //  ���� �����°�
		fin >> m >> f >> n;
		int stair = m - 1;
		ans = n / stair + 1;
		if (n % stair == 0) {
			ans -= 1;
		}
		fout << ans << endl;

	}
	fin.close();
	fout.close();
	return 0;
}