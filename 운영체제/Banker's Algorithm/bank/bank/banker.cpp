#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <deque>
using namespace std;
int main() {
    string str; //request , release;
   // ifstream fin("C:\\Users\\admin\\Desktop\\1234.txt");
    ifstream fin("banker.inp");

    //C:\\Users\\admin\\Desktop\\sampleData4\\2.inp
    ofstream fout("banker.out");
    int number = 0; //  총 프로그램 개수
    int resource = 0; // 자원의 종류
    fin >> number >> resource;
    //cout << number << " " << resource << endl<<endl;

    vector <int> available; // 각 자원에 대해 사용가능한 개수
    vector <int> sum; // 시스템이 얼마만큼의 자원을 보유하고 있는지.
    for (int i = 0; i < resource; i++) {
        int j = 0;
        fin >> j;
        sum.push_back(j);
        available.push_back(j);
        // cout << sum[i] << " ";
    }
    // cout << endl << endl;

    vector<vector <int>> max(number, vector<int>(resource, 0)); //각 프로세스가 최대 몇개의 자원을 요청할 것인지.
    for (int i = 0; i < number; i++) {
        for (int j = 0; j < resource; j++) {
            fin >> max[i][j];
            //    cout << max[i][j] << " ";
        }
        // cout << endl;
    }
    // cout << endl;
    vector<vector <int>> ALLOCATION(number, vector<int>(resource, 0)); // 각 프로세스에 현재 할당된 자원의 수

    for (int i = 0; i < number; i++) {
        for (int j = 0; j < resource; j++) {
            fin >> ALLOCATION[i][j];
            //  cout << ALLOCATION[i][j] << " ";
            available[j] -= ALLOCATION[i][j];

        }
        //   cout << endl;
    }


    vector<vector <int>> NEED(number, vector<int>(resource, 0));
    // 각 프로세스가 앞으로 사용할 자원의 수 (NEED=MAX-ALLOCATION)
    for (int i = 0; i < number; i++) {
        for (int j = 0; j < resource; j++) {
            NEED[i][j] = max[i][j] - ALLOCATION[i][j];
            //   cout << NEED[i][j] << " ";
        }
        //   cout << endl;
    }
    vector <int> tmp;
    deque <int> que; //자원 n개
    deque <int> que2; //프로세스 번호
    while (true) {
        fin >> str;
        if (str == "quit") break;// 끝나는 조건
        else if (str == "request") {
            int pronum = 0; //프로세스 번호.
            fin >> pronum;
            for (int i = 0; i < resource; i++) {
                int j = 0;
                fin >> j;
                tmp.push_back(j);
            }
            int count = 0;
            for (int i = 0; i < resource; i++) {
                if (available[i] >= tmp[i]) count++;
            }
            int count2 = 0;
            for (int i = 0; i < resource; i++) {
                if (NEED[pronum][i] <tmp[i]) {
                        count2++;
                }
            }
            if (count2!= 0) continue;
            if (count < resource) { // 자원이 부족하므로 큐에넣음.
                que2.push_back(pronum);
                for (int i = 0; i < resource; i++) {
                    que.push_back(tmp[i]);
                }
                for (int i = 0; i < resource; i++) {
                    fout << available[i] << " ";
                }
                fout << endl;
                tmp.clear();
            }
            else { //    자원통과 // 안정, 불안정 상태 검사.
                vector <int>work(resource, 0);
                vector <int>finish(number, 0);
                vector<vector <int>> NEED2(number, vector<int>(resource, 0));
                vector<vector <int>> ALLOCATION2(number, vector<int>(resource, 0)); // 각 프로세스에 현재 할당된 자원의 수
                int pro_num2 = 0;

                for (int i = 0; i < number; i++) {
                    for (int j = 0; j < resource; j++) {
                        NEED2[i][j] = NEED[i][j];
                        ALLOCATION2[i][j] = ALLOCATION[i][j];
                    }
                } //NEED 초기화

                for (int i = 0; i < resource; i++) {
                    work[i] = available[i] - tmp[i];
                    NEED2[pronum][i] -= tmp[i];
                    ALLOCATION2[pronum][i] += tmp[i];
                }
                while (true) {

                    for (int i = 0; i < number; i++) {
                        for (int j = 0; j < number; j++) {
                            int count2 = 0;
                            if (finish[j] == 0) {
                                for (int k = 0; k < resource; k++) {
                                    if (NEED2[j][k] <= work[k]) count2++;
                                }
                                if (count2 == resource) {
                                    pro_num2 = j;
                                    finish[j] = 1;

                                    for (int i = 0; i < resource; i++)
                                        work[i] += ALLOCATION2[pro_num2][i];
                                    break;
                                }
                            }
                        } //break 여기 빠져나감.

                    } //for
                    int count3 = resource;
                    for (int i = 0; i < number; i++) {
                        if (finish[i] == 0) {//불안정한 상태
                            count3--;
                            que2.push_back(pronum);
                            for (int i = 0; i < resource; i++) {
                                que.push_back(tmp[i]);
                            }
                            for (int i = 0; i < resource; i++) {
                                fout << available[i] << " ";
                            }
                            break;
                        }
                    } // break 시 여기 빠져나감
                    if (count3 == resource) {
                        for (int i = 0; i < resource; i++) {
                            NEED[pronum][i] -= tmp[i];
                            ALLOCATION[pronum][i] += tmp[i];
                            available[i] -= tmp[i];
                            fout << available[i] << " ";
                        }
                    }
                    fout << endl;
                    tmp.clear();
                    break;
                }
            }
        } //else if "request"
        else if (str == "release") {
            vector <int> v;
            int pronum = 0;
            int count = 0;
            int tmp2 = 0;
            fin >> pronum;
            for (int i = 0; i < resource; i++) {
                int j = 0;
                fin >> j;
                tmp.push_back(j);
                available[i] += tmp[i];
                ALLOCATION[pronum][i] -= tmp[i];
                NEED[pronum][i] += tmp[i];
            } 
            //release 처리완료.

            deque <int> q;
            deque <int> q_num;
           //대기큐에서 들고옴.
            while (true) {

                if (que.empty()||que2.empty()) break;
                int ans = que2.front();
                que2.pop_front();
                int  count = 0;
                int count2 = 0;
               // cout << "tmp" << endl;
                for (int i = 0; i < resource; i++) {
                    int tmp2 = que.front();
                  //  cout << tmp2 << " ";
                    v.push_back(tmp2);
                    que.pop_front();
                    if (available[i] >= tmp2) {
                        count++;
                    }
                    if (NEED[ans][i] < tmp2)
                        count2++;
                    //count가 resource개수랑 같으면 safe 검사 실시.
                    //
                } // for
                if (count2 != 0) continue;
                if(count!=resource) {
                   // cout << "여기";
                    q_num.push_back(ans);
                    for (int i = 0; i < resource; i++) {
                        int t = v[0];
                     //  cout << t<<" ";
                        q.push_back(t);
                        v.erase(v.begin());
                    }
                 //      cout << endl;
                }
                else{ //여기에 safe  체크 해줘야함.

                    vector <int>work(resource, 0);
                    vector <int>finish(number, 0);
                    vector<vector <int>> NEED2(number, vector<int>(resource, 0));
                    vector<vector <int>> ALLOCATION2(number, vector<int>(resource, 0)); // 각 프로세스에 현재 할당된 자원의 수
                    int pro_num2 = 0;

                    for (int i = 0; i < number; i++) {
                        for (int j = 0; j < resource; j++) {
                            NEED2[i][j] = NEED[i][j];
                            ALLOCATION2[i][j] = ALLOCATION[i][j];
                        }
                    } //NEED 초기화

                    for (int i = 0; i < resource; i++) {
                        work[i] = available[i] - v[i];
                        NEED2[ans][i] -= v[i];
                        ALLOCATION2[ans][i] += v[i];
                    }
                    while (true) {
                        for (int i = 0; i < number; i++) {
                            for (int j = 0; j < number; j++) {
                                int count2 = 0;
                                if (finish[j] == 0) {
                                    for (int k = 0; k < resource; k++) {
                                        if (NEED2[j][k] <= work[k]) count2++;
                                    }
                                    if (count2 == resource) {
                                        pro_num2 = j;
                                        finish[j] = 1;

                                        for (int i = 0; i < resource; i++)
                                            work[i] += ALLOCATION2[pro_num2][i];
                                        break;
                                    }
                                }
                            } //break 여기 빠져나감.

                        } //for
                        int count3 = resource;
                        for (int i = 0; i < number; i++) {
                            if (finish[i] == 0) {//불안정한 상태
                                count3--;
                                q_num.push_back(ans);                               
                                for (int i = 0; i < resource; i++) {
                                    int t = v[0];
                                    //cout << t;
                                    q.push_back(t);
                                    v.erase(v.begin());
                                }
                                for (int i = 0; i < resource; i++) {
                                   // cout << available[i] << " ";
                                }
                                break;
                            }
                        } // break 시 여기 빠져나감
                        if (count3 == resource) {
                            for (int i = 0; i < resource; i++) {
                                NEED[ans][i] -= v[i];
                                ALLOCATION[ans][i] += v[i];
                                available[i] -= v[i];                            
                            }
                        }
                        v.clear();
                        break;
                    }
                }               
            } //while

            while (!q_num.empty()) {
                int i = q_num.back();
                que2.push_front(i);
                q_num.pop_back();
            }
          //  cout << endl;
            while (!q.empty()) {
                int t = q.back();   
              //  cout << t;
                que.push_front(t);
                q.pop_back();
            }          
            for (int i = 0; i < resource; i++) {
                fout << available[i] << " ";
            }
            fout << endl;
            tmp.clear();

        } // else if "release"

    } // while
    fin.close();
    fout.close();
    return 0;
}//main

