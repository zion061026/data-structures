/*
 * 08-priority-queue / q4.cpp
 * ------------------------------------------------------------
 * [문제] 부호로 동작이 갈리는 PQ 게임 (q3의 변형)
 *   - 양수 v: 같은 값이 있으면 제거 후 v*2 재삽입(병합), 없으면 그냥 뒤에 추가(정렬 X).
 *   - 음수 v: |v|에 가장 가까운 원소 제거(동률이면 큰 값 제거).
 *   - 0     : 큐 전체 출력.
 * [핵심] q3와 같은 규칙이나, 일반 삽입은 정렬하지 않고 push_back 하는 점이 차이.
 */
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