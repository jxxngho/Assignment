#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;

int main() {
	ifstream fin("test.inp");
	ofstream fout("test.out");
	vector<pair<string, pair<string, string>>> v;
	vector <pair <string, int>> v1;
	int count; // test ����
	fin >> count;
	string n; // ������ȣ
	string first; //First name;
	string last; //Last name;
	int length = 0; //����
	for (int i = 0; i < count; i++) {
		fin >> n;
		fin >> first;
		fin >> last;
		v.push_back(pair<string, pair<string, string> >(n, pair<string, string>(first, last)));

		int cou = 1;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].second.second == last) {
				for (int i = 0; i < v1.size(); i++) {
					if (v1[i].first == last) { //���� �̸� �����ֱ�.
						v1[i].second += 1;
						break;
					}
				}
				break;
			}
			else {
				cou++;
			}
		}
		if (cou == v.size()) {
			v1.push_back(pair<string, int>(last, 1)); //���� �̸� ������ ���Ϳ� �߰� 1
		}
		//v1.push_back(pair<string, int>(first, 0));
	}

	for (int i = 0; i < v.size(); i++) {
		if (length < v[i].second.first.length()) {
			length = v[i].second.first.length();
		}
	} // �� ���߱� ���� ����ϴ� for��
	for (int i = 0; i < v.size(); i++) {
		if (length >= v[i].second.first.length()) {
			int a = length - v[i].second.first.length(); //���� ��ŭ ���ؼ�
			string st = "";
			for (int i = 0; i < a; i++) {
				st += " "; // �߰����ֱ�.
			}
			v[i].second.first += st; //�����߱�.
		}
	}
	sort(v.begin(), v.end());
	for (int i = 0; i < count; i++) {
		fout << v[i].first << ' ' << v[i].second.first << ' ' << v[i].second.second << endl;
	} //�� ���缭 ���

	sort(v1.begin(), v1.end());  //���� �̸� �ִ� �� ���
	fout << endl;
	for (int i = 0; i < v1.size(); i++) {
		if (v1[i].second >= 2) {
			fout << v1[i].first << " " << v1[i].second << endl;
		}
	}
	fin.close();
	fout.close();
	return 0;
} //main
