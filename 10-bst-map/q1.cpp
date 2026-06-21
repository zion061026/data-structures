#include <iostream>
#include <string>
using namespace std;

class Node {
	public:
		int key;
		string value;
		Node* left;
		Node* right;
		Node* parent;
		Node(int key, string& value, Node* parent) : key{ key }, value{ value }, parent{ parent }, left{ nullptr }, right{ nullptr } {}
};
class BST {
	private:
		int n;
		Node* root;
		Node* find_entry(int key) {
			Node* cur = root;
			while (cur != nullptr) {
				if (key == cur->key) return cur;
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
		BST() : n{ 0 }, root{ nullptr } {}
		int size() { return n; }
		bool empty() { return size() == 0; }
		string find(int key) {
			Node* entry = find_entry(key);
			if (entry == nullptr)return "-1";
			return entry->value;
		}
		bool insert(int key, string value) {
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
		void heignt(int key) {
			Node* node = find_entry(key);
			if (node == nullptr) {
				cout << -2 << '\n'; return;
			}
			cout << Height(node) << '\n';
		}
		int Height(Node* node) {
			if (node == nullptr) return -1;
			if (node->left == nullptr && node->right == nullptr) {
				return 0; //외부노드의 높이는 0
			}
			int height = 0;
			int left = Height(node->left);
			int right = Height(node->right);

			if (left > right) return left + 1;
			else return right + 1;
		}
		void range(int k1, int k2) {
			Node* start = nullptr;
			Node* cur = root;
			while (cur != nullptr) {
				if (k1 <= cur->key) {
					start = cur;
					cur = cur->left;
				}
				else cur = cur->right;
			}
			bool found = false;
			while (start != nullptr && start->key <= k2) {
				cout << start->value << " ";
				found = true;
				start = successor(start);
			}
			if (!found) {
				cout << -3 << '\n'; return;
			}
			else cout << '\n';
		}
};

int main() {
	int T; cin >> T;
	while (T--) {
		int Q; cin >> Q;
		BST b;
		string input;
		for (int i = 0; i < Q; i++) {
			cin >> input;
			if (input == "insert") {
				int key; string value; cin >> key >> value;
				b.insert(key, value);
			}
			else if (input == "find") {
				int k; cin >> k;
				cout << b.find(k) << '\n';
			}
			else if (input == "height") {
				int k; cin >> k;
				b.heignt(k);
			}
			else if (input == "range") {
				int k1, k2; cin >> k1 >> k2;
				b.range(k1, k2);
			}
		}
	}
}