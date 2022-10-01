#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
	//ifstream fin("C:\\Users\\admin\\Desktop\\sampleData3 (1)\\2.inp");
	ifstream fin("fcfs.inp");
	ofstream fout("fcfs.out");

	string number; // n���� ���α׷�
	getline(fin, number);
	int pronum = stoi(number);
	//cout << pronum << endl; ���α׷� ���� üũ
	vector <vector<int>> arr(pronum, vector<int>(100, -1)); // 2�����迭�� ������
	//vector<int> vrr(pronum); //���۽ð� üũ�ϴ� ����
	vector<int> turnaround(pronum); //����ð� üũ�ϴ� ����
	vector <int> iotime(pronum, 0);  // ����½ð�üũ.
	//vector <int> cputime; //cpu�ð� üũ
	vector <int> tmp; //�����ϱ�.
	queue <int> pq;
	vector <int> final;

	// 2�����迭�� ����
	for (int i = 0; i < pronum; i++) {
		int count = 0;
		for (int j = 0;; j++) {
			fin >> arr[i][j];
			count++;
			if (arr[i][j] == -1) {
				final.push_back(count);
				break;
			}
		}
	}

	int count = 0; // ¦��������ŭ ���� �ݺ�Ƚ�� ����.
	for (int i = 0; i < pronum; i++) {
		for (int j = 1;; j += 2) {
			if (arr[i][j] == -1) break;
			count++;
		}
	} //�ݺ�Ƚ�� ����.

	int current = 0; //����ð�
	int cputime = 0;
	int i = 0;
	int temp = 0;
	int idletime = 0;

	for (int i = 0; i < pronum; i++) {
		if (current == arr[i][0]) {
			pq.push(i);
			arr[i][0] = -1;
		}
	}
	while (pq.size() <= 0) {
		current++;
		idletime++;
		for (int i = 0; i < pronum; i++) {
			if (current == arr[i][0]) {
				pq.push(i);
				arr[i][0] = -1;
			}
		}

	}

	while (true) {
		if (count == 0) break; //Ż������ 
		while (true) {

			if (!pq.empty()) {
				temp = pq.front();
				pq.pop();
				break;

			}
			else if (pq.empty()) {
				current++;
				idletime++;
				for (int i = 0; i < pronum; i++) {
					iotime[i]--;
					//cout << "iotime[i] : " << iotime[i] << endl;
					if (iotime[i] == 0) {
						for (int j = 0; j < 100; j++) {
							if (arr[i][j] != -1) {
								tmp.push_back(i);
								break;
							}
						}
					}
					if (current == arr[i][0]) {
						tmp.push_back(i);
						arr[i][0] = -1;
					}
				}
				if (tmp.size() > 1) {
					sort(tmp.begin(), tmp.end());
				}
				for (int i = 0; i < tmp.size(); i++) {
					pq.push(tmp[i]);
				}
				tmp.clear();
			}
		} //while

		//	cout << "time : " << current << endl;
		//	cout << "selectedProcess : " << temp << endl;

		for (i = 1;; i += 2) {
			if (arr[temp][i] != -1) {
				cputime = arr[temp][i];
				arr[temp][i] = -1;
				if (final[temp] % 2 == 0) {
					turnaround[temp] = current + cputime;
				}
				//cout << "cputime : " << cputime << endl;
				//turnaround[temp] = current + cputime;
				//cout << "turnaround : " << turnaround[temp] << endl;
				break;
			}
		}
		//cout << "���� cputime: " << cputime << endl;
		//cout << "time : " << current << " selectedProcess : " << temp << " idleTime : " << idletime << endl;
		while (true) {
			if (cputime == 0) {
				iotime[temp] = arr[temp][i + 1];
				arr[temp][i + 1] = -1;
				if (final[temp] % 2 != 0) {
					turnaround[temp] = current + iotime[temp] + 1;
				}
				else
					turnaround[temp] += iotime[temp];
				break;
			}

			cputime--;
			current++;
			for (int i = 0; i < pronum; i++) {
				iotime[i]--;
				if (current == arr[i][0]) {
					pq.push(i);
					arr[i][0] = -1;
					//	cout << "current : " << current << endl;
					//	cout << "current ���� ������ üũ: " << i << endl;
				}
				else if (iotime[i] == 0) {
					for (int j = 0; j < 100; j++) {
						if (arr[i][j] != -1) {
							pq.push(i);
							//	cout << "current : " << current << endl;
							//	cout << "iotime ���� ������ üũ: " << i << endl;
							break;
						}
					}

				}
			}
		}
		count--;
	}

	fout << idletime << endl;
	for (int i = 0; i < pronum; i++) {
		fout << turnaround[i] << endl;
	}
	fin.close();
	fout.close();
}//main
