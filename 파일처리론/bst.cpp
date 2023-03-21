#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("bst_input.txt");
ofstream fout("bst_output.txt");

class Node {
public:
	int data; // 값
	Node* left; // 왼쪽
	Node* right; // 오른쪽
	string num; // R,1,0
	Node(int val,string ch="") //생성자
	{
		data = val;
		left = NULL;
		right = NULL;
		num = ch;
	}
};
//void preorder(class Node* node) { //전위순회
//	if (node == NULL) return;
//	cout << node->data << " ";
//	preorder(node->left);
//	preorder(node->right);
//}

void insert(Node *root,int k) { // 삽입
	if (root->data > k) { // 왼쪽으로 가야하는 경우
		if (root->left == NULL) { //없다면 그 자리에 넣어줌
			Node* left_node = new Node(k);
			root->left = left_node;
		}
		else {
			insert(root->left, k);
			return;
		}
	}
	else if(root->data<k){ // 오른쪽으로 가야하는 경우
		if (root->right == NULL) { //없다면 그 자리에 넣어줌
			Node* right_node = new Node(k);
			root->right = right_node;
		}
		else {
			insert(root->right, k);
			return;
		}
	}
}

void search(Node* root, int k,string str) { // 검색
	if (root->data == k) { 
		fout << str <<endl;
	}
	else if (root->data > k) {//왼쪽에 위치하는 경우
		str += "0";
		search(root->left, k, str);
	}
	else if (root->data < k) { // 오른쪽에 위치하는 경우
		str += "1";
		search(root->right, k, str);
	}
}

void dele(Node* root, int k) { // 삭제
	Node* tmp = root;
	Node* tmp2 = tmp;
	while (!(tmp->data == k)) { //검색
		if (tmp->data > k) {//왼쪽에 위치하는 경우
			tmp2 = tmp;
			tmp = tmp->left;
		}
		else if (tmp->data < k) { // 오른쪽에 위치하는 경우
			tmp2 = tmp;
			tmp = tmp->right;
		}
	} // 검색
	 if (tmp->left == NULL && tmp->right == NULL) {  // 자식이 둘 다 없는 경우
		if (tmp2->data> k) {
			tmp2->left = NULL;
		}
		else {
			tmp2->right = NULL;
		}
	}
	// 자식이 하나만 있는경우 
	else if(tmp->left != NULL && tmp->right == NULL){ //왼쪽 자식만 있는 경우
		if (tmp2->data > tmp->left->data) {
			tmp2->left = tmp->left;
		}
		else {	
			tmp2->right = tmp->left;
		}
	}
	else if(tmp->left == NULL && tmp->right != NULL) { //오른쪽 자식만 있는 경우
		if (tmp2->data > tmp->right->data) {
			tmp2->left = tmp->right;
		}
		else {
			tmp2->right = tmp->right;
		}
	}
	else if(tmp->left!=NULL&&tmp->right!=NULL) { // 자식이 둘인 경우
		 Node* N = new Node(0); 
		 N= tmp->right;
		 if (N->left == NULL) { //바로 오른쪽 자식인경우
			 N->left = tmp->left;
			 if (tmp2->data < k) {
				 tmp2->right = N;
			 }
			 else {
				 tmp2->left = N;
			 }
		 }
		 else{ //오른쪽 자식의 맨 왼쪽 자식을 향해서
			while (N->left != NULL) {
				N = N->left;
			}
			tmp->data = N->data;
			delete(N);
		 }
	}
}

int main() {
	int test = 0;
	fin >> test; // Test Case 개수
	while (test--) {
		int in = 0; //삽입할 키의 개수
		fin >> in;
		int rt; //루트노드 
		fin >> rt;
		Node* root = new Node(rt, "R");
		in--;
		while (in--) {
			int ins = 0;
			fin >> ins;
			insert(root, ins); //삽입
		} //삽입
		//preorder(root);
		//cout << endl;
		int se = 0; // 검색할 키의 개수
		fin >> se;
		while (se--) {
			int ser = 0; //검색할 값
			fin >> ser;
			string str = "";
			if (se == root->data) { //루트에 있는 값이랑 같은 경우
				fout << root->num <<endl;
			}
			else { //루트에 있는 값이랑 다른 경우
				str += root->num;
				search(root, ser, str);
			}
		} // 검색

		int de = 0;
		fin >> de; // 삭제할 키의 개수
		while (de--) {
			int del = 0; //삭제할 값
			fin >> del;
			if (del == root->data) { //삭제할 키가 루트인경우
				if (root->left == NULL && root->right != NULL) { // 오른쪽 자식만 가지고있을때.
					root = root->right;
				}
				else if (root->left != NULL && root->right == NULL) { // 왼쪽 자식만 가지고있을때.
					root = root->left;
				}
			}			
			else { //삭제할 키가 루트가 아닌 경우
				dele(root, del);
			} 
		} // 삭제

		fin >> se;
		while (se--) {
			int ser = 0;
			fin >> ser;
			string str = "";
			if (se == root->data) { //루트에 있는 값이랑 같은 경우
				fout << "R" <<endl;
			}
			else { //루트에 있는 값이랑 다른 경우
				str += "R";
				search(root, ser, str);
			}
		} // 검색
	}
	fout.close();
	fin.close();
	return 0;
}