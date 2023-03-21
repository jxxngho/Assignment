#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("bst_input.txt");
ofstream fout("bst_output.txt");

class Node {
public:
	int data; // ��
	Node* left; // ����
	Node* right; // ������
	string num; // R,1,0
	Node(int val,string ch="") //������
	{
		data = val;
		left = NULL;
		right = NULL;
		num = ch;
	}
};
//void preorder(class Node* node) { //������ȸ
//	if (node == NULL) return;
//	cout << node->data << " ";
//	preorder(node->left);
//	preorder(node->right);
//}

void insert(Node *root,int k) { // ����
	if (root->data > k) { // �������� �����ϴ� ���
		if (root->left == NULL) { //���ٸ� �� �ڸ��� �־���
			Node* left_node = new Node(k);
			root->left = left_node;
		}
		else {
			insert(root->left, k);
			return;
		}
	}
	else if(root->data<k){ // ���������� �����ϴ� ���
		if (root->right == NULL) { //���ٸ� �� �ڸ��� �־���
			Node* right_node = new Node(k);
			root->right = right_node;
		}
		else {
			insert(root->right, k);
			return;
		}
	}
}

void search(Node* root, int k,string str) { // �˻�
	if (root->data == k) { 
		fout << str <<endl;
	}
	else if (root->data > k) {//���ʿ� ��ġ�ϴ� ���
		str += "0";
		search(root->left, k, str);
	}
	else if (root->data < k) { // �����ʿ� ��ġ�ϴ� ���
		str += "1";
		search(root->right, k, str);
	}
}

void dele(Node* root, int k) { // ����
	Node* tmp = root;
	Node* tmp2 = tmp;
	while (!(tmp->data == k)) { //�˻�
		if (tmp->data > k) {//���ʿ� ��ġ�ϴ� ���
			tmp2 = tmp;
			tmp = tmp->left;
		}
		else if (tmp->data < k) { // �����ʿ� ��ġ�ϴ� ���
			tmp2 = tmp;
			tmp = tmp->right;
		}
	} // �˻�
	 if (tmp->left == NULL && tmp->right == NULL) {  // �ڽ��� �� �� ���� ���
		if (tmp2->data> k) {
			tmp2->left = NULL;
		}
		else {
			tmp2->right = NULL;
		}
	}
	// �ڽ��� �ϳ��� �ִ°�� 
	else if(tmp->left != NULL && tmp->right == NULL){ //���� �ڽĸ� �ִ� ���
		if (tmp2->data > tmp->left->data) {
			tmp2->left = tmp->left;
		}
		else {	
			tmp2->right = tmp->left;
		}
	}
	else if(tmp->left == NULL && tmp->right != NULL) { //������ �ڽĸ� �ִ� ���
		if (tmp2->data > tmp->right->data) {
			tmp2->left = tmp->right;
		}
		else {
			tmp2->right = tmp->right;
		}
	}
	else if(tmp->left!=NULL&&tmp->right!=NULL) { // �ڽ��� ���� ���
		 Node* N = new Node(0); 
		 N= tmp->right;
		 if (N->left == NULL) { //�ٷ� ������ �ڽ��ΰ��
			 N->left = tmp->left;
			 if (tmp2->data < k) {
				 tmp2->right = N;
			 }
			 else {
				 tmp2->left = N;
			 }
		 }
		 else{ //������ �ڽ��� �� ���� �ڽ��� ���ؼ�
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
	fin >> test; // Test Case ����
	while (test--) {
		int in = 0; //������ Ű�� ����
		fin >> in;
		int rt; //��Ʈ��� 
		fin >> rt;
		Node* root = new Node(rt, "R");
		in--;
		while (in--) {
			int ins = 0;
			fin >> ins;
			insert(root, ins); //����
		} //����
		//preorder(root);
		//cout << endl;
		int se = 0; // �˻��� Ű�� ����
		fin >> se;
		while (se--) {
			int ser = 0; //�˻��� ��
			fin >> ser;
			string str = "";
			if (se == root->data) { //��Ʈ�� �ִ� ���̶� ���� ���
				fout << root->num <<endl;
			}
			else { //��Ʈ�� �ִ� ���̶� �ٸ� ���
				str += root->num;
				search(root, ser, str);
			}
		} // �˻�

		int de = 0;
		fin >> de; // ������ Ű�� ����
		while (de--) {
			int del = 0; //������ ��
			fin >> del;
			if (del == root->data) { //������ Ű�� ��Ʈ�ΰ��
				if (root->left == NULL && root->right != NULL) { // ������ �ڽĸ� ������������.
					root = root->right;
				}
				else if (root->left != NULL && root->right == NULL) { // ���� �ڽĸ� ������������.
					root = root->left;
				}
			}			
			else { //������ Ű�� ��Ʈ�� �ƴ� ���
				dele(root, del);
			} 
		} // ����

		fin >> se;
		while (se--) {
			int ser = 0;
			fin >> ser;
			string str = "";
			if (se == root->data) { //��Ʈ�� �ִ� ���̶� ���� ���
				fout << "R" <<endl;
			}
			else { //��Ʈ�� �ִ� ���̶� �ٸ� ���
				str += "R";
				search(root, ser, str);
			}
		} // �˻�
	}
	fout.close();
	fin.close();
	return 0;
}