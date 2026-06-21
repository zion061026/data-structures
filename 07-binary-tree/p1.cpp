/*
 * 07-binary-tree / p1.cpp
 * ------------------------------------------------------------
 * [문제] 이진 트리(left/right) 명령 처리 + Add
 *   - 루트=1. 명령: Insert x v left|right / Erase v / Find v / Add v
 *   - Insert: 부모 x의 지정 방향에 v 삽입(그 자리가 이미 차 있으면 -1).
 *   - Find v: 존재하면 1, 없으면 -1.
 *   - Add v: v의 (왼자식 + 오른자식 + 부모) 값의 합 출력(없는 쪽은 0).
 * [핵심] 노드는 left/right/parent 포인터 보유, 방향은 enum class side로 구분.
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
		void Find(int value) {
			list<Node*>::iterator it = find(node_seq, value);
			if (it == node_seq.end()) {
				cout << -1 << '\n'; return;
			}
			else cout << 1 << '\n';
		}
		void add(int value) {
			int right = 0, left = 0, parent = 0;
			list<Node*>::iterator it = find(node_seq, value);
			if (it == node_seq.end()) { cout << -1 << '\n'; return; }
			Node* node = *it;

			if (node != root) {
				parent = node->parent->value;
			}
			if (node->left != nullptr) {
				left = node->left->value;
			}
			if (node->right != nullptr) {
				right = node->right->value;
			}
			cout << right + left + parent << '\n';
		}
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
			else if (input == "Erase") {
				int v; cin >> v;
				t.erase(v);
			}
			else if (input == "Find") {
				int v; cin >> v;
				t.Find(v);
			}
			else if (input == "Add") {
				int v; cin >> v;
				t.add(v);
			}
		}
	}
}