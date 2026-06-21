/*
 * 09-heap / q3.cpp
 * ------------------------------------------------------------
 * [문제] 최대 힙 기반 작업 스케줄러 + 임의 원소 취소/수정
 *   - 명령: submit v(push) / execute(pop, 값 출력) / peek(top) / count(size) /
 *           cancel p(값 p인 원소 삭제, 없으면 "not_found") / update p q(값 p를 q로 변경)
 *   - 빈 힙에서 execute/peek는 "idle" 출력.
 * [핵심] cancel/update는 값으로 위치를 선형 탐색한 뒤, 힙 성질이 위·아래
 *        어느 쪽으로 깨질지 모르므로 upheap·downheap을 둘 다 호출해 복구.
 */
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
		if (empty()) { cout << "idle" << '\n'; return; }
		cout << elements[1] << '\n';
	}
	void pop() {
		if (empty()) { cout << "idle" << '\n'; return; }
		cout << elements[1] << '\n';
		swap(1, size());
		elements.pop_back();
		downheap(1);
	}
	void downheap(int index) {
		int left = index * 2;
		int right = index * 2 + 1;

		int child_index;
		if (left > size()) return;
		else if (left == size()) child_index = left;
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
	void cancel(int p) {
		int index = 0;
		bool found = false;
		for (int i = 1; i <= size(); i++) {
			if (elements[i] == p) {
				index = i;
				found = true;
				break;
			}
		}
		if (!found) {
			cout << "not_found" << '\n'; return;
		}
		else {
			swap(index, size());
			elements.pop_back();
			downheap(index);
			upheap(index);
		}
	}
	void update(int p, int q) {
		int index = 0;
		for (int i = 1; i <= size(); i++) {
			if (elements[i] == p) {
				index = i;
				break;
			}
		}
		elements[index] = q;
		upheap(index);
		downheap(index);
	}
};

int main() {
	int N; cin >> N;
	string input;
	Heap h;
	for (int i = 0; i < N; i++) {
		cin >> input;
		if (input == "submit") {
			int v; cin >> v;
			h.push(v);
		}
		else if (input == "execute") {
			h.pop();
		}
		else if (input == "peek") {
			h.top();
		}
		else if (input == "count") {
			cout << h.size() << '\n';
		}
		else if (input == "cancel") {
			int p; cin >> p;
			h.cancel(p);
		}
		else if (input == "update") {
			int p, q; cin >> p >> q;
			h.update(p, q);
		}
	}
}