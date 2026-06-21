#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

struct compare {
	bool operator()(int left, int right) {
		return left > right;
	}
};

class PQ {
	private:
		int n;
		list<int> elements;
		compare comp;
	public:
		PQ() : n{ 0 } {}
		int size() { return n; }
		bool empty() { return size() == 0; }
		void push(int value) {
			list<int>::iterator it = elements.begin();
			while (it != elements.end() && comp(*it, value)) {
				++it;
			}
			n++;
			elements.insert(it, value);
		}
		void top() {
			if (empty()) { cout << "empty" << '\n'; return; }
			cout << elements.front() << '\n';
		}
		void pop() {
			if (empty()) { cout << "empty" << '\n'; return; }
			n--;
			elements.pop_front();
		}
		void print_top(int k) {
			if (empty()) { cout << "empty" << '\n'; return; }
			int cnt = 0;
			list<int>::iterator it = elements.begin();
			while (it != elements.end() && cnt < k) {
				cout << *it << " ";
				++it;
				cnt++;
			}
			cout << '\n';
		}
		void print_med() {
			if (empty()) { cout << "empty" << '\n'; return; }
			int pq_size = size();
			list<int>::iterator it = elements.begin();
			if (pq_size % 2 == 0) { //짝수
				for (int i = 0; i < pq_size / 2 - 1; i++) {
					++it;
				}
				int a = *it; ++it;
				int b = *it;
				cout << (a + b) / 2 << '\n'; return;
			}
			else {
				for (int i = 0; i < pq_size/2; i++) {
					++it;
				}
				int a = *it;
				cout << a << '\n'; return;
			}
		}
		void sum_over() {
			if (empty()) { cout << 0 << '\n'; return; }
			int pq_size = size();
			list<int>::iterator it = elements.begin();
			int median;
			int sum = 0;
			if (pq_size % 2 == 0) { //짝수
				for (int i = 0; i < pq_size / 2 - 1; i++) {
					++it;
				}
				int a = *it; ++it;
				int b = *it;
				median = (a + b) / 2;
			}
			else {
				for (int i = 0; i < pq_size/2; i++) {
					++it;
				}
				int a = *it;
				median = a;
			}
			for (int x : elements) {
				if (x > median) sum += x;
			}
			cout << sum << '\n';
		}
};
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N; cin >> N;
	PQ p;
	string input;
	for (int i = 0; i < N; i++) {
		cin >> input;
		if (input == "Push") {
			int x; cin >> x;
			p.push(x);
		}
		else if (input == "Pop") {
			p.pop();
		}
		else if (input == "Top") {
			p.top();
		}
		else if (input == "Print_Med") {
			p.print_med();
		}
		else if (input == "Sum_Over") {
			p.sum_over();
		}
		else if (input == "Print_Top") {
			int k; cin >> k;
			p.print_top(k);
		}
	}
}