/*
 * 06-general-tree / p2.cpp
 * ------------------------------------------------------------
 * [문제] 일반 트리 전위 순회(preorder)
 *   - 입력: N(노드 수)과 N-1개의 간선(자식 x, 부모 p)으로 트리 구성(루트=1).
 *   - 트리를 preorder(루트 먼저, 그 다음 자식들 순서대로)로 출력.
 * [핵심] 노드 방문 → 자식들 재귀. 자식은 insert된 순서대로 방문.
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
	void preorder(Node* node) {
		cout << node->value << " ";
		for (Node* child : node->children) {
			preorder(child);
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
		int N; cin >> N;
		for (int i = 0; i < N - 1; i++) {
			int x, p; cin >> x >> p;
			t.insert(p, x);
		}
		t.preorder(t.getRoot());
	}
}