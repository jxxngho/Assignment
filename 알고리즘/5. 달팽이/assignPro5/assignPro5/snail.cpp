#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <utility> 
using namespace std;
ifstream fin("snail.inp");
ofstream fout("snail.out");
void ans(long  num, long point1, pair<long, long>& p1) { //point1
    long i = 1;
    long n = num - 1; //가야하는것
    long cnt = 2;

    if (point1 > num) {
        p1.second += num;
        i += n;
    }
    else {
        p1.second += point1;
        return;
    }
    // 행 늘리고 열 줄이고 행 줄이고 열 늘리고.
    while (num * num > i) {
        if (point1 > i + n) {
            p1.first += n;
            i += n;
        }
        else {
            p1.first += point1 - i;
            return;
        }
        if (point1 > i + n) {
            p1.second -= n;
            i += n;
        }
        else {
            p1.second -= point1 - i;
            return;
        }
        n--;
        if (point1 > i + n) {
            p1.first -= n;
            i += n;
        }
        else {
            p1.first -= point1 - i;
            return;
        }
        if (point1 > i + n) {
            p1.second += n;
            i += n;
        }
        else {
            p1.second += point1 - i;
            return;
        }
        n--;
    }
}
int main() {

    int count;// 출력케이스
    fin >> count;
    while (count--) {
        long num; //n*n;
        long point1;
        long point2;
        pair <long, long> p1;
        pair <long, long> p2;
        fin >> num >> point1 >> point2;
        ans(num, point1, p1);
        ans(num, point2, p2);
        long a = (p1.first - p2.first > 0) ? p1.first - p2.first : p2.first - p1.first;
        long b = (p1.second - p2.second > 0) ? p1.second - p2.second : p2.second - p1.second;

        if (a == b) {
            fout << "YES" << endl;
        }
        else {
            fout << "NO" << endl;
        }
    } //while.
    fin.close();
    fout.close();
    return 0;

}

