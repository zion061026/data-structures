/*
 * 07-binary-tree / p4.cpp
 * ------------------------------------------------------------
 * [문제] 이진 트리 순회 + 누적합 + LCA  (p2의 변형: 순회 순서가 다름)
 *   - 명령:
 *       Insert x v left|right
 *       Inorder_travel x : 중위 순서로 방문 노드를 출력하며 x에서 멈춤(없으면 -1).
 *       Preorder_sum x : 전위 순서로 누적합이 x를 처음 초과하는 노드 출력(없으면 -1).
 *       LCA x y : 최소 공통 조상.
 * [핵심] p2와 동일 기법(bool 반환 조기 종료), travel/sum의 순회 순서만 교차.
 */
#include <iostream>
#include <list>
#include <vector>
using namespace std;

class Node {
public:
	int value;
	Node* parent;
	Node* left;
	Node* right;
	list<Node*>::iterator seq_pos;
	Node(int value, Node* parent) : value{ value }, parent{ parent }, left{ nullptr }, right{ nullptr } {}
};
class Tree {
public:
	enum class side {
		LEFT, RIGHT
	};
	Tree(int value) : root{ new Node(value,nullptr) } {
		node_seq.push_back(root);
		root->seq_pos = --node_seq.end();
	}
	~Tree() {
		for (Node* node : node_seq) {
			delete node;
		}
	}
	void insert(int parent, int value, side side) {
		list<Node*>::iterator parent_pos = find(node_seq, parent);
		if (parent_pos == node_seq.end()) { cout << -1 << '\n'; return; }

		Node* parent_node = *parent_pos;

		if (side == side::LEFT && parent_node->left != nullptr || side == side::RIGHT && parent_node->right != nullptr) {
			cout << -1 << '\n'; return;
		}
		Node* newNode = new Node(value, parent_node);

		if (side == side::LEFT) parent_node->left = newNode;
		else parent_node->right = newNode;
		node_seq.push_back(newNode);
		newNode->seq_pos = --node_seq.end();
	}
	void erase(int value) {
		list<Node*>::iterator it = find(node_seq, value);
		if (it == node_seq.end()) { return; }
		if (*it == root) { return; }

		Node* node = *it;
		erase(node);
	}
	void erase(Node* node) {
		if (node->left != nullptr) erase(node->left);
		if (node->right != nullptr) erase(node->right);

		Node* parent_node = node->parent;
		node_seq.erase(node->seq_pos);
		if (parent_node->left == node) parent_node->left = nullptr;
		else parent_node->right = nullptr;

		delete node;
	}
	bool inorder_travel(int value, Node* node) {
		if (node->left != nullptr) {
			if (inorder_travel(value, node->left)) return true;
		}
		cout << node->value << " ";
		if (node->value == value) {
			return true;
		}
		if (node->right != nullptr) {
			if (inorder_travel(value, node->right)) return true;
		}
		return false;
	}
	bool preorder_sum(int value, Node* node, int& sum) {
		sum += node->value;
		if (sum > value) {
			cout << node->value;
			return true;
		}
		if (node->left != nullptr) {
			if (preorder_sum(value, node->left, sum)) return true;
		}
		if (node->right != nullptr) {
			if (preorder_sum(value, node->right, sum)) return true;
		}
		return false;
	}
	void LCA(int x, int y) {
		vector<int> v1, v2;
		list<Node*>::iterator pos_x = find(node_seq, x);
		list<Node*>::iterator pos_y = find(node_seq, y);
		if (pos_x == node_seq.end() || pos_y == node_seq.end()) {
			cout << -1 << '\n'; return;
		}

		Node* cur_x = *pos_x;
		Node* cur_y = *pos_y;
		while (cur_x != nullptr) {
			v1.push_back(cur_x->value);
			cur_x = cur_x->parent;
		}
		while (cur_y != nullptr) {
			v2.push_back(cur_y->value);
			cur_y = cur_y->parent;
		}
		for (int valueX : v1) {
			for (int valueY : v2) {
				if (valueX == valueY) {
					cout << valueX << '\n';
					return;
				}
			}
		}
	}
	Node* getRoot() { return root; }
private:
	Node* root;
	list<Node*> node_seq;
	list<Node*>::iterator find(list<Node*>& seq, int value) {
		list<Node*>::iterator it = seq.begin();
		while (it != seq.end()) {
			if ((*it)->value == value) break;
			++it;
		}
		return it;
	}
};

int main() {
	string input;
	int T; cin >> T;
	while (T--) {
		Tree t(1);
		int Q; cin >> Q;
		for (int i = 0; i < Q; i++) {
			cin >> input;
			if (input == "Insert") {
				int x, v; string direction;
				cin >> x >> v >> direction;
				if (direction == "left") {
					t.insert(x, v, Tree::side::LEFT);
				}
				else t.insert(x, v, Tree::side::RIGHT);
			}
			else if (input == "Inorder_travel") {
				int x; cin >> x;
				if (!t.inorder_travel(x, t.getRoot())) {
					cout << -1 << '\n';
				}
				else {
					cout << '\n';
				}
			}
			else if (input == "Preorder_sum") {
				int x; cin >> x;
				int sum = 0;
				if (!t.preorder_sum(x, t.getRoot(), sum)) {
					cout << -1 << '\n';
				}
				else {
					cout << '\n';
				}
			}
			else if (input == "LCA") {
				int x, y; cin >> x >> y;
				t.LCA(x, y);
			}
		}
	}
}