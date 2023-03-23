#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(void) {
	ifstream fin("multi.inp");
	//ifstream fin("C:\\Users\\admin\\Desktop\\markingData1 (1)\\10.inp");
	ofstream fout("multi.out");

	string number; // N개의 프로그램.
	getline(fin, number);
	int pronum = stoi(number);
	int current = 0; //현재 입출력
	int selectedProcess = 0; //현재 실행중인 프로세스.
	int idleTime = 0; //유휴시간
	int cputime = 0; // 총 cpu시간

	vector <vector<int>> arr(pronum, vector<int>(1000, 0)); // 2차원배열에 넣을것
	vector <int> iotime(pronum, 0);  // 입출력시간체크.
	// 2차원배열에 저장
	for (int i = 0; i < pronum; i++) {
		for (int j = 0;; j++) {
			fin >> arr[i][j];
			if (arr[i][j] == -1) {
				arr[i][j] = 0;
				break;
			}
		}
	}
	int count = 0; // 짝수개수만큼 세서 반복횟수 정함.
	for (int i = 0; i < pronum; i++) {
		for (int j = 0;; j += 2) {
			if (arr[i][j] == 0) break;
			count++;
		}
	} //반복횟수 정함.

	int count_process = pronum;
	int size = iotime.size();  // iotime 갯수
	//int i = 0;
	while (true) {
		if (count == 0) break;  // 종료조건
		//cout << "time: " << cputime << " selected number: " << selectedProcess << " idletime: " << idleTime << endl << endl;
		for (i = 0;; i += 2) {
			if (arr[selectedProcess][i] != 0) {
				current = arr[selectedProcess][i];
			//	cout << "현재 current? " << current << "count_process: " << count_process << endl;
				arr[selectedProcess][i] = 0;
				break;
			}
		}

		while (true) {
			if (current == 0) break;
			current--; cputime++;
			for (int i_two = 0; i_two < size; i_two++) {
				iotime[i_two]--;
			//	cout << "iotime " << i_two << "번째" << iotime[i_two] << endl;
			} //입출력 시간 하나씩 빼기.
			//cout << endl;
		} // while	

		iotime[selectedProcess] = arr[selectedProcess][i + 1];
		arr[selectedProcess][i + 1] = 0;

		while (true) {

			for (int k = 0; k < 100; k++) {
				if (arr[selectedProcess][k] != 0)
					goto yogi; // 0이 아닌게 하나라도 있으면 아웃.

			} //for
			if (count == 1) {
				for (int j = 0; j < iotime[selectedProcess]; j++) {
					cputime++;
				} //마지막 idleTime은 cpu유휴시간이 아님.
				goto EXIT;
			}
			if (iotime[selectedProcess] > 0) {
				iotime[selectedProcess] = 0;
			}
			//cout << "끝나는 프로세스 번호: " << selectedProcess << endl;
			count_process--;
		yogi:
			int count_amniotic = 0;
			for (int a = 0; a < size; a++) {
				if (iotime[a] > 0) {
					count_amniotic++;
				}//if
			}//for
			if (count_amniotic == count_process) {
				for (int i = 0; i < size; i++) {
					iotime[i]--;
					//cout << "iotime " << i << "번째" << iotime[i] << endl;
				}
				//cout << endl;
				idleTime++;
				cputime++;
				goto yogi;
			}
			else {
				goto out;
			}
			goto out;
		} // first_while																									

	out:
		for (int i_three = 0; i_three < size; i_three++) {
			for (int j = 0; j < 100; j++) {
				if (arr[i_three][j] != 0) {
					if (iotime[i_three] <= 0) {
						selectedProcess = i_three;
						goto EXIT;
					}//if
				}
			} //for
		} //for
	EXIT:

		count--;
	}  //while;
	fout << idleTime << " " << cputime;
	cout << idleTime << " " << cputime;
	fin.close();
	fout.close();

}//main
