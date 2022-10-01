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

	string number; // n개의 프로그램
	getline(fin, number);
	int pronum = stoi(number);
	//cout << pronum << endl; 프로그램 갯수 체크
	vector <vector<int>> arr(pronum, vector<int>(100, -1)); // 2차원배열에 넣을것
	//vector<int> vrr(pronum); //시작시간 체크하는 벡터
	vector<int> turnaround(pronum); //종료시간 체크하는 벡터
	vector <int> iotime(pronum, 0);  // 입출력시간체크.
	//vector <int> cputime; //cpu시간 체크
	vector <int> tmp; //정렬하기.
	queue <int> pq;
	vector <int> final;

	// 2차원배열에 저장
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

	int count = 0; // 짝수개수만큼 세서 반복횟수 정함.
	for (int i = 0; i < pronum; i++) {
		for (int j = 1;; j += 2) {
			if (arr[i][j] == -1) break;
			count++;
		}
	} //반복횟수 정함.

	int current = 0; //현재시간
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
		if (count == 0) break; //탈출조건 
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
		//cout << "현재 cputime: " << cputime << endl;
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
					//	cout << "current 뭐가 들어가는지 체크: " << i << endl;
				}
				else if (iotime[i] == 0) {
					for (int j = 0; j < 100; j++) {
						if (arr[i][j] != -1) {
							pq.push(i);
							//	cout << "current : " << current << endl;
							//	cout << "iotime 뭐가 들어가는지 체크: " << i << endl;
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
