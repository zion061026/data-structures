/*
 * 08-priority-queue / q3.cpp
 * ------------------------------------------------------------
 * [문제] 부호로 동작이 갈리는 PQ 게임 (입력은 정수 한 개씩)
 *   - 양수 v: 같은 값이 이미 있으면 그것을 제거하고 v*2를 다시 push(2048식 병합).
 *            없으면 정렬 위치에 삽입.
 *   - 음수 v: |v|에 "가장 가까운" 원소를 제거(거리가 같으면 더 큰 값을 제거).
 *   - 0     : 현재 큐 전체를 출력(비면 "empty").
 * [핵심] push 하나로 삽입/병합/근접 삭제/출력을 모두 분기 처리. 병합은 재귀 push.
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
			it = elements.begin();
			while (it != elements.end() && comp(*it, value)) {
				++it;
			}
			elements.insert(it, value);
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