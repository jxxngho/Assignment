#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main(void) {

	ifstream fin("batch.inp");
	ofstream fout("batch.out");

	string number;
	getline(fin, number);
	int pronum = stoi(number);

	int idlecount = 0;
	int cpucount = 0;
	int i = 0;
	for (i = 0; i < pronum; i++) {
		getline(fin, number);
		stringstream orgnum(number);

		int j = 0, k = 1;
		while (orgnum >> j) {
			if (j == -1) break;
			if (k % 2 == 1) cpucount += j;
			else idlecount += j;
			k++;
		}

	}
	fout << idlecount << " " << cpucount + idlecount << endl;

	return 0;
}