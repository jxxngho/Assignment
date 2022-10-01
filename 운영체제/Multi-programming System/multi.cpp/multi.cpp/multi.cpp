#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(void) {
	ifstream fin("C:\\Users\\admin\\Desktop\\�̰ɷ�����.txt");
	//ifstream fin("C:\\Users\\admin\\Desktop\\markingData1 (1)\\10.inp");
	ofstream fout("multi.out");

	string number; // N���� ���α׷�.
	getline(fin, number);
	int pronum = stoi(number);
	int current = 0; //���� �����
	int selectedProcess = 0; //���� �������� ���μ���.
	int idleTime = 0; //���޽ð�
	int cputime = 0; // �� cpu�ð�

	vector <vector<int>> arr(pronum, vector<int>(1000, 0)); // 2�����迭�� ������
	vector <int> iotime(pronum, 0);  // ����½ð�üũ.
	// 2�����迭�� ����
	for (int i = 0; i < pronum; i++) {
		for (int j = 0;; j++) {
			fin >> arr[i][j];
			if (arr[i][j] == -1) {
				arr[i][j] = 0;
				break;
			}
		}
	}
	int count = 0; // ¦��������ŭ ���� �ݺ�Ƚ�� ����.
	for (int i = 0; i < pronum; i++) {
		for (int j = 0;; j += 2) {
			if (arr[i][j] == 0) break;
			count++;
		}
	} //�ݺ�Ƚ�� ����.

	int count_process = pronum;
	int size = iotime.size();  // iotime ����
	//int i = 0;
	while (true) {
		if (count == 0) break;  // ��������
		//cout << "time: " << cputime << " selected number: " << selectedProcess << " idletime: " << idleTime << endl << endl;
		for (i = 0;; i += 2) {
			if (arr[selectedProcess][i] != 0) {
				current = arr[selectedProcess][i];
			//	cout << "���� current? " << current << "count_process: " << count_process << endl;
				arr[selectedProcess][i] = 0;
				break;
			}
		}

		while (true) {
			if (current == 0) break;
			current--; cputime++;
			for (int i_two = 0; i_two < size; i_two++) {
				iotime[i_two]--;
			//	cout << "iotime " << i_two << "��°" << iotime[i_two] << endl;
			} //����� �ð� �ϳ��� ����.
			//cout << endl;
		} // while	

		iotime[selectedProcess] = arr[selectedProcess][i + 1];
		arr[selectedProcess][i + 1] = 0;

		while (true) {

			for (int k = 0; k < 100; k++) {
				if (arr[selectedProcess][k] != 0)
					goto yogi; // 0�� �ƴѰ� �ϳ��� ������ �ƿ�.

			} //for
			if (count == 1) {
				for (int j = 0; j < iotime[selectedProcess]; j++) {
					cputime++;
				} //������ idleTime�� cpu���޽ð��� �ƴ�.
				goto EXIT;
			}
			if (iotime[selectedProcess] > 0) {
				iotime[selectedProcess] = 0;
			}
			//cout << "������ ���μ��� ��ȣ: " << selectedProcess << endl;
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
					//cout << "iotime " << i << "��°" << iotime[i] << endl;
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
