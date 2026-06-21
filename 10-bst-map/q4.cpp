/*
 * 10-bst-map / q4.cpp
 * ------------------------------------------------------------
 * [문제] 창고 재고 관리 (q3와 같은 문제, transfer 구현 차이)
 *   - 명령: import / export / transfer / check (의미는 q3와 동일).
 * [핵심] q3와 동일한 BST 맵 5개. transfer에서 이동 후 수량 0이면 erase 처리.
 */
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
	int key;
	int value;
	Node* left;
	Node* right;
	Node* parent;
	Node(int key, int value, Node* parent) : key{ key }, value{ value }, parent{ parent }, left{ nullptr }, right{ nullptr } {}
};
class BST {
private:
	int n;
	Node* root;
	Node* successor(Node* node) {
		if (node->right) {
			Node* cur = node->right;
			while (cur->left) cur = cur->left;
			return cur;
		}
		else {
			Node* cur = node;
			Node* parent = node->parent;
			while (parent && parent->right == cur) {
				cur = parent;
				parent = cur->parent;
			}
			return parent;
		}
	}
public:
	Node* find_entry(int key) {
		Node* cur = root;
		while (cur != nullptr) {
			if (key == cur->key) return cur;
			if (key < cur->key) cur = cur->left;
			else cur = cur->right;
		}
		return nullptr;
	}
	BST() : n{ 0 }, root{ nullptr } {}
	int size() { return n; }
	bool empty() { return size() == 0; }
	int find(int key) {
		Node* entry = find_entry(key);
		if (entry == nullptr)return -1;
		return entry->value;
	}
	bool insert(int key, int value) {
		if (empty()) {
			root = new Node(key, value, nullptr);
			n++;
			return true;
		}
		Node* cur = root;
		Node* parent = nullptr;
		while (cur != nullptr) {
			if (key == cur->key) return false;
			parent = cur;
			if (key < cur->key)cur = cur->left;
			else cur = cur->right;
		}
		Node* newNode = new Node(key, value, parent);
		if (key < parent->key) parent->left = newNode;
		else parent->right = newNode;
		n++;
		return true;
	}
	bool erase(int key) {
		return erase(find_entry(key));
	}
	bool erase(Node* node) {
		if (node == nullptr) { return false; }

		if (node->left != nullptr && node->right != nullptr) {
			Node* suc = successor(node);
			node->key = suc->key;
			node->value = suc->value;
			node = suc;
		}

		Node* child = node->left ? node->left : node->right;
		if (child) child->parent = node->parent;

		if (node == root) root = child;
		else if (node->parent->left == node) node->parent->left = child;
		else node->parent->right = child;
		n--;
		delete node;
		return true;
	}
};

int main() {
	int Q; cin >> Q;
	BST B[6]; //1번 인덱스부터 사용하겠음
	string input;
	for (int i = 0; i < Q; i++) {
		cin >> input;
		if (input == "import") {
			int N, ID, count; cin >> N >> ID >> count;
			if (B[N].find_entry(ID)) {
				B[N].find_entry(ID)->value += count;
			}
			else {
				B[N].insert(ID, count);
			}
		}
		else if (input == "export") {
			int N, ID, count; cin >> N >> ID >> count;
			if (B[N].find_entry(ID) == nullptr) {
				cout << "shortage" << '\n'; continue;
			}
			if (B[N].find_entry(ID)->value < count) {
				cout << "shortage" << '\n'; continue;
			}
			else {
				B[N].find_entry(ID)->value -= count;
				if (B[N].find_entry(ID)->value == 0) {
					B[N].erase(ID);
				}
			}
		}
		else if (input == "transfer") {
			int N, M, ID, count; cin >> N >> M >> ID >> count;
			if (B[N].find_entry(ID) == nullptr) {
				cout << "shortage" << '\n'; continue;
			}
			if (B[N].find_entry(ID)->value <= count) {
				if (!B[M].find_entry(ID)) {
					B[M].insert(ID, B[N].find_entry(ID)->value);
					B[N].find_entry(ID)->value = 0;
					if (B[N].find_entry(ID)->value == 0) {
						B[N].erase(ID);
					}
				}
				else {
					B[M].find_entry(ID)->value += B[N].find_entry(ID)->value;
					B[N].find_entry(ID)->value = 0;
					if (B[N].find_entry(ID)->value == 0) {
						B[N].erase(ID);
					}
				}
			}
			else {
				if (!B[M].find_entry(ID)) {
					B[M].insert(ID, count);
					B[N].find_entry(ID)->value -= count;
					if (B[N].find_entry(ID)->value == 0) {
						B[N].erase(ID);
					}
				}
				else {
					B[N].find_entry(ID)->value -= count;
					if (B[N].find_entry(ID)->value == 0) {
						B[N].erase(ID);
					}
					B[M].find_entry(ID)->value += count;
				}
			}
		}
		else if (input == "check") {
			int ID; cin >> ID;
			int sum = 0;
			for (int i = 1; i <= 5; i++) {
				if (B[i].find_entry(ID)) sum += B[i].find_entry(ID)->value;
			}
			cout << sum << '\n';
		}
	}
}