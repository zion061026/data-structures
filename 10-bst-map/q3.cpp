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