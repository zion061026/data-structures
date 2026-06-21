/*
 * 10-bst-map / q3.cpp
 * ------------------------------------------------------------
 * [문제] BST 맵 5개로 만드는 창고 재고 관리
 *   - 창고 B[1..5], 각 창고는 key=물품ID → value=수량인 BST.
 *   - import N ID c : N번 창고에 ID 물품 c개 입고(이미 있으면 수량 +c).
 *   - export N ID c : N번 창고에서 c개 출고. 부족하면 "shortage". 0이 되면 노드 삭제.
 *   - transfer N M ID c : N→M으로 c개 이동(N 부족 시 shortage, 가진 만큼만 옮기기도).
 *   - check ID : 모든 창고에 있는 ID 수량의 총합 출력.
 * [핵심] 수량 0이 되면 BST에서 erase. 두 자식 삭제는 successor로 키/값을 끌어와 처리.
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
	Node(int key, int value, Node* parent) : key(key), value(value), parent(parent), left(nullptr), right(nullptr) {}
};

class BST {
	private:
		int n;
		Node* root;
	public:
		BST() : n(0), root(nullptr) {}
		int size() { return n; }
		bool empty() { return size() == 0; }
		Node* find_entry(int key) {
			Node* cur = root;
			while (cur != nullptr) {
				if (cur->key == key) { return cur; }
				if (key < cur->key) cur = cur->left;
				else cur = cur->right;
			}
			return nullptr;
		}
		Node* successor(Node* node) {
			if (node->right) {
				Node* cur = node->right;
				while (cur->left) cur = cur->left;
				return cur;
			}

			Node* cur = node;
			Node* parent = node->parent;
			while (parent && parent->right == cur) {
				cur = parent;
				parent = cur->parent;
			}
			return parent;
		}
		void insert(int key, int value) {
			if (empty()) {
				root = new Node(key, value, nullptr);
				n++;
				return;
			}

			Node* cur = root;
			Node* parent = nullptr;
			while (cur != nullptr) {
				if (key == cur->key)return;
				parent = cur;
				if (key < cur->key) cur = cur->left;
				else cur = cur->right;
			}
			Node* newNode = new Node(key, value, parent);
			if (key < parent->key) parent->left = newNode;
			else parent->right = newNode;
			n++;
			return;
		}
		bool erase(int key) {
			return erase(find_entry(key));
		}
		bool erase(Node* node) {
			if (node == nullptr)return false;

			if (node->left != nullptr && node->right != nullptr) {
				Node* suc = successor(node);
				node->key = suc->key;
				node->value = suc->value;
				node = suc;
			}

			Node* child = node->left ? node->left : node->right;
			if (child) child->parent = node->parent;

			if (node == root) root = child;
			else if (node->parent->left == node) {
				node->parent->left = child;
			}
			else node->parent->right = child;

			delete node;
			n--;
			return true;
		}
};

int main() {
	int Q; cin >> Q;
	BST b[6];
	string input;
	for (int i = 0; i < Q; i++) {
		cin >> input;
		if (input == "import") {
			int N, ID, count;cin >> N >> ID >> count;
			if (b[N].find_entry(ID)) {
				b[N].find_entry(ID)->value += count;
			}
			else {
				b[N].insert(ID, count);
			}
		}
		else if (input == "export") {
			int N, ID, count;cin >> N >> ID >> count;
			if (!b[N].find_entry(ID)) {
				cout << "shortage" << '\n';
				continue;
			}
			if (b[N].find_entry(ID)->value < count) {
				cout << "shortage" << '\n';
				continue;
			}
			else {
				b[N].find_entry(ID)->value -= count;
				if (b[N].find_entry(ID)->value == 0) {
					b[N].erase(ID);
				}
			}
		}
		else if (input == "transfer") {
			int N, M, ID, count;cin >> N >> M >> ID >> count;
			if (!b[N].find_entry(ID)) {
				cout << "shortage" << '\n';
				continue;
			}
			if (b[N].find_entry(ID)->value <= count) {
				if (!b[M].find_entry(ID)) {
					b[M].insert(ID, b[N].find_entry(ID)->value);
					b[N].erase(ID);
				}
				else {
					b[M].find_entry(ID)->value += b[N].find_entry(ID)->value;
					b[N].erase(ID);
				}
			}
			else {
				if (!b[M].find_entry(ID)) {
					b[M].insert(ID, count);
					b[N].find_entry(ID)->value -= count;
				}
				else {
					b[M].find_entry(ID)->value += count;
					b[N].find_entry(ID)->value -= count;
				}
			}
		}
		else if (input == "check") {
			int sum = 0;
			int ID; cin >> ID;
			for (int i = 1; i <= 5; i++) {
				if (b[i].find_entry(ID)) {
					sum += b[i].find_entry(ID)->value;
				}
			}
			cout << sum << '\n';
		}
	}
}