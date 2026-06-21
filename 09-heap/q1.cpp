#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct compare {
	bool operator()(int left, int right) {
		return left > right;
	}
};
class Heap {
	private:
		compare comp;
		vector<int> elements;
	public:
		Heap() {
			elements.push_back(-1);
		}
		int size() { return elements.size() - 1; }
		bool empty() { return size() == 0; }
		void push(int value) {
			elements.push_back(value);
			upheap(size());
		}
		void upheap(int index) {
			if (index == 1) { return; }

			int parent_index = index / 2;
			if (!comp(elements[parent_index], elements[index])) {
				swap(parent_index, index);
				upheap(parent_index);
			}
		}
		void swap(int index1, int index2) {
			int temp = elements[index1];
			elements[index1] = elements[index2];
			elements[index2] = temp;
		}
		void top() {
			if (empty()) { cout << "empty" << '\n'; return; }
			cout << elements[1] << '\n';
		}
		void pop() {
			if (empty()) { cout << "empty" << '\n'; return; }
			swap(1, size());
			elements.pop_back();
			downheap(1);
		}
		void downheap(int index) {
			int left = index * 2;
			int right = index * 2 + 1;
			
			int child_index;
			if (left > size()) return;
			else if(left == size()) child_index = left;
			else {
				if (comp(elements[left], elements[right])) {
					child_index = left;
				}
				else child_index = right;
			}
			if (!comp(elements[index], elements[child_index])) {
				swap(index, child_index);
				downheap(child_index);
			}
		}
		void print_size() {
			cout << size() << '\n';
		}
		void print() {
			if (empty()) { cout << "empty" << '\n'; return; }
			for (int i = 1; i <= size(); i++) { //0번 index는 사용 안 함
				cout << elements[i] << " ";
			}
			cout << '\n';
		}
};

int main() {
	Heap h;
	int N; cin >> N;
	string input;
	for (int i = 0; i < N; i++) {
		cin >> input;
		if (input == "push") {
			int v; cin >> v;
			h.push(v);
		}
		else if (input == "pop") {
			h.pop();
		}
		else if (input == "top") {
			h.top();
		}
		else if (input == "size") {
			h.print_size();
		}
		else if(input == "print"){
			h.print();
		}
	}
}