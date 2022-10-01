#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

int main(void) {
    ifstream fin("gain.inp");
    ofstream fout("gain.out");
    int count;
    fin >> count;
    while (count--) {
        vector <int> v;
        int answer = 0;
        int a;
        int tmp;
        fin >> a;
        while (a--) {
            fin >> tmp;
            v.push_back(tmp);
        }
        sort(v.begin(), v.end());
        auto minmax = minmax_element(v.begin() + 1, v.end() - 1); //min2 max2 구하기
        answer -= *minmax.first;
        answer += *minmax.second;
        v.erase(v.begin() + 1);
        v.erase(v.end() - 2);
        minmax = minmax_element(v.begin(), v.end()); //min1, max1 구하기
        answer -= *minmax.first;
        answer += *minmax.second;
        fout << answer << endl;
    }
    fout.close();
    fin.close();
    return 0;
}