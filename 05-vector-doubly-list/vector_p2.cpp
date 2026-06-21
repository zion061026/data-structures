#include <iostream>
#include <string>
using namespace std;

class Vector {
public:
	Vector() : n{ 0 }, capacity{ 1 }, elements{ new int[1] } {}
	~Vector() {
		delete elements;
	}
	int getCap() { return capacity; }
	int size() { return n; }
	bool empty() { return size() == 0; }
	void push_back(int value) {
		if (n == capacity) {
			resize(2 * capacity);
		}
		elements[n] = value;
		n++;
	}
	void set(int index, int value) {
		if (index < 0 || index >= n) {
			return;
		}
		elements[index] = value;
	}
	void insert(int index, int value) {
		if (index<0 || index>n) { return; }
		if (n == capacity) {
			resize(2 * capacity);
		}
		for (int i = n; i > index; i--) {
			elements[i] = elements[i - 1];
		}
		elements[index] = value;
		n++;
	}
	void erase(int index) {
		if (index < 0 || index >= n) { return; }
		for (int i = index; i < n - 1; i++) {
			elements[i] = elements[i + 1];
		}
		n--;
	}
	void print() {
		if (empty()) { cout << "empty" << '\n';return; }
		for (int i = 0; i < n; i++) {
			cout << elements[i] << " ";
		}
		cout << '\n';
	}
	void count_under(int value) {
		int count = 0;
		for (int i = 0; i < n; i++) {
			if (elements[i] < value) count++;
		}
		cout << count << '\n';
	}
private:
	int n;
	int capacity;
	int* elements;
	void resize(int new_capacity) {
		if (new_capacity <= capacity) { return; }
		int* new_elements = new int[new_capacity];
		for (int i = 0; i < n; i++) {
			new_elements[i] = elements[i];
		}
		delete elements;
		elements = new_elements;
		capacity = new_capacity;
	}

};

int main() {
	int T; cin >> T;
	string input;
	while (T--) {
		Vector v;
		int Q; cin >> Q;
		for (int i = 0; i < Q; i++) {
			cin >> input;
			if (input == "push_back") {
				int value; cin >> value;
				v.push_back(value);
			}
			else if (input == "insert") {
				int index, value; cin >> index >> value;
				v.insert(index, value);
			}
			else if (input == "print") {
				v.print();
			}
			else if (input == "count_under") {
				int value; cin >> value;
				v.count_under(value);
			}
			else if (input == "erase") {
				int index; cin >> index;
				v.erase(index);
			}
			else if (input == "size") {
				cout << v.size() << '\n';
			}
			else if (input == "capacity") {
				cout << v.getCap() << '\n';
			}
			else if (input == "set") {
				int index, value; cin >> index >> value;
				v.set(index, value);
			}
		}
	}
}