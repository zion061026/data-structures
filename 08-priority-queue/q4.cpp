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
	int size() { return elements.size(); }
	bool empty() { return size() == 0; }
	void push(int value) {
		if (value > 0) {
			if (empty()) {
				elements.push_back(value);
				return;
			}
			list<int>::iterator it = elements.begin();
			for (int i = 0; i < elements.size(); i++) {
				if (*it == value) {
					elements.erase(it);
					push(value * 2);
					return;
				}
				++it;
			}
			elements.push_back(value);
		}
		else if (value < 0) {
			if (empty()) { return; }
			value = -value;
			list<int>::iterator it = elements.begin();
			int distance;
			int min = 10e9;
			int cnt = 0;
			list<int>::iterator res1, res2 = elements.begin();
			for (int i = 0; i < elements.size(); i++) {
				if (*it > value) {
					distance = *it - value;
				}
				else distance = value - *it;

				if (distance < min) {
					min = distance;
					cnt = 1;
					res1 = it;
				}
				else if (distance == min) {
					res2 = it;
					cnt = 2;
				}
				++it;
			}
			if (cnt == 1) {
				elements.erase(res1);
			}
			else {
				if (*res1 > *res2) {
					elements.erase(res2);
				}
				else elements.erase(res1);
			}
		}
		else {
			if (empty()) { cout << "empty" << '\n'; return; }
			for (int x : elements) {
				cout << x << " ";
			}
			cout << '\n';
		}
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N; cin >> N;
	PQ p;
	for (int i = 0; i < N; i++) {
		int v; cin >> v;
		p.push(v);
	}
}