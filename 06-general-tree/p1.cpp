/*
 * 06-general-tree / p1.cpp
 * ------------------------------------------------------------
 * [문제] 일반 트리(자식 수 제한 없음) + depth 질의
 *   - 루트는 값 1. 명령: insert p c / erase x / parent x / children x / depth x
 *   - insert p c: 부모 p 아래에 자식 c 추가(c가 이미 있거나 p가 없으면 -1).
 *   - erase x: x와 그 서브트리 전체 제거(루트는 제거 불가).
 *   - depth x: 루트에서 x까지의 깊이(루트=0) 출력.
 * [핵심] 각 노드는 children(list)과 parent 포인터를 가짐. node_seq(전체 노드
 *        리스트)에서 값으로 선형 탐색. erase는 자식부터 재귀 삭제.
 */
#include <iostream>
#include <list>
#include <vector>
using namespace std;

class Node {
	public:
		int value;
		Node* parent;
		list<Node*>::iterator seq_pos;
		list<Node*>::iterator pos_in_parent;
		list<Node*> children;
		Node(int value, Node* parent) : value{ value }, parent{ parent } {}
};
class Tree {
	public:
		Tree(int value) : root{ new Node(value,nullptr) } {
			node_seq.push_back(root);
			root->seq_pos = --node_seq.end();
		}
		~Tree() {
			for (Node* node : node_seq) {
				delete node;
			}
		}
		void insert(int parent, int value) {
			list<Node*>::iterator pos = find(node_seq, value);
			if (pos != node_seq.end()) { cout << -1 << '\n'; return; }
			list<Node*>::iterator parent_pos = find(node_seq, parent);
			if (parent_pos == node_seq.end()) { cout << -1 << '\n'; return; }

			Node* parent_node = *parent_pos;
			Node* newNode = new Node(value, parent_node);
			parent_node->children.push_back(newNode);
			newNode->pos_in_parent = --parent_node->children.end();
			node_seq.push_back(newNode);
			newNode->seq_pos = --node_seq.end();
		}
		void erase(int value) {
			list<Node*>::iterator pos = find(node_seq, value);
			if (pos == node_seq.end()) { cout << -1 << '\n'; return; }

			Node* erase_node = *pos;
			erase(erase_node);
		}
		void erase(Node* node) {
			if (node == root) { return; }

			while (!node->children.empty()) {
				erase(node->children.front());
			}

			Node* parent_node = node->parent;
			parent_node->children.erase(node->pos_in_parent);
			node_seq.erase(node->seq_pos);

			delete node;
		}
		void parent(int value) {
			list<Node*>::iterator it = find(node_seq, value);
			if (it == node_seq.end()) { cout << -1 << '\n'; return; }

			Node* node = *it;
			cout << node->parent->value << '\n';
		}
		void child(int value) {
			list<Node*>::iterator it = find(node_seq, value);
			if (it == node_seq.end()) { cout << -1 << '\n'; return; }

			Node* node = *it;
			if (node->children.empty()) {
				cout << 0 << '\n';
			}
			else {
				for (Node* child : node->children) {
					cout << child->value << " ";
				}
				cout << '\n';
			}
		}
		void depth(int value) {
			list<Node*>::iterator it = find(node_seq, value);
			if (it == node_seq.end()) { cout << -1 << '\n'; return; }

			Node* node = *it;
			int count = 0;
			while (node != root) {
				count++;
				node = node->parent;
			}
			cout << count << '\n';
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
			if (input == "insert") {
				int x, c; cin >> x >> c;
				t.insert(x, c);
			}
			else if (input == "erase") {
				int x; cin >> x;
				t.erase(x);
			}
			else if (input == "parent") {
				int x; cin >> x;
				t.parent(x);
			}
			else if (input == "children") {
				int x; cin >> x;
				t.child(x);
			}
			else if (input == "depth") {
				int x; cin >> x;
				t.depth(x);
			}
		}
	}
}