#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;
ifstream fin("1.inp");
ofstream fout("permutation.out");
class Node {
public:
	int data; // ��
	Node* left; // ����
	Node* right; // ������
	int depth; // ����
	Node(int val) //������
	{
		data = val;
		left = NULL;
		right = NULL;
		depth = NULL;
	}
};

void inorder(class Node* node) {
	if (node == NULL) return;
	inorder(node->left);
	fout << node->depth << " ";
	inorder(node->right);
}

void bin(Node* root, vector<int> v, int max, int max_ele) {
	vector<int> left(v.begin(), v.begin() + max); //���� ��
	vector<int> right(v.begin() + 1 + max, v.end()); //�����ʹ�
	if (left.size() == 0) {
		//��
	}
	else if (left.size() == 1) {
		Node* left_node = new Node(left[0]);
		root->left = left_node;
		left_node->depth = root->depth + 1;
	}
	else {
		max = max_element(left.begin(), left.end()) - left.begin(); //���ʿ��� ���� ū��
		max_ele = *max_element(left.begin(), left.end());
		Node* left_node = new Node(max_ele);
		root->left = left_node;
		left_node->depth = root->depth + 1;
		bin(left_node, left, max, max_ele);
	}

	if (right.size() == 0) {
		//��
	}
	else if (right.size() == 1) {
		Node* right_node = new Node(right[0]);
		root->right = right_node;
		right_node->depth = root->depth + 1;
	}
	else {
		max = max_element(right.begin(), right.end()) - right.begin(); //�����ʿ��� ���� ū��
		max_ele = *max_element(right.begin(), right.end());
		Node* right_node = new Node(max_ele);
		root->right = right_node;
		right_node->depth = root->depth + 1;
		bin(right_node, right, max, max_ele);
	}
}

int main() {
	int count;
	fin >> count;
	while (count--) {
		int cnt;
		fin >> cnt;
		vector <int> v;
		int tmp;
		for (int i = 0; i < cnt; i++) {
			fin >> tmp;
			v.push_back(tmp);
		}
		int max = max_element(v.begin(), v.end()) - v.begin(); //��Ʈ ��Ʈ ã��
		int max_ele = *max_element(v.begin(), v.end());
		Node* root = new Node(max_ele);
		root->depth = 0;
		bin(root, v, max, max_ele);
		inorder(root);
		fout << endl;
	}
}