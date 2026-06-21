/*
 * 03-stack / p3.cpp
 * ------------------------------------------------------------
 * [문제] 연결 리스트 기반 스택 + pop_odd  (p1의 변형: 짝수 → 홀수)
 *   - 명령: push v / pop / top / size / empty / pop_odd
 *   - pop_odd: 스택을 전부 비우면서 pop한 값 중 홀수의 개수를 출력.
 * [핵심] p1_basic과 동일, 세는 조건만 홀수로.
 */
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
	int value;
	Node* next;
	Node(int value) : value{ value }, next{ nullptr } {}
};
class Stack {
public:
	Stack() :top{ nullptr }, n{ 0 } {}
	int size() { return n; }
	bool empty() { return size() == 0; }
	void push(int value) {
		Node* newNode = new Node(value);
		if (empty()) {
			top = newNode;
			n++;
			return;
		}
		newNode->next = top;
		top = newNode;
		n++;
	}
	int pop() {
		if (empty()) { return -1; }
		Node* deleteNode = top;
		top = top->next;
		int result = deleteNode->value;
		n--;
		delete deleteNode;
		return result;
	}
	void pop_odd() {
		if (empty()) { cout << -1 << '\n'; return; }
		int count = 0;
		while (!empty()) {
			int temp = pop();
			if (temp % 2 != 0) {
				count++;
			}
		}
		cout << count << '\n';
	}
	void Top() {
		if (empty()) {
			cout << -1 << '\n';
			return;
		}
		cout << top->value << '\n';
	}
private:
	Node* top;
	int n;
};
int main() {
	string input;
	int T; cin >> T;
	while (T--) {
		Stack s;
		int Q; cin >> Q;
		for (int i = 0; i < Q; i++) {
			cin >> input;
			if (input == "push") {
				int value; cin >> value;
				s.push(value);
			}
			else if (input == "empty") {
				if (s.empty()) {
					cout << 1 << '\n';
				}
				else cout << 0 << '\n';
			}
			else if (input == "pop") {
				cout << s.pop() << '\n';
			}
			else if (input == "pop_odd") {
				s.pop_odd();
			}
			else if (input == "size") {
				cout << s.size() << '\n';
			}
			else if (input == "top") {
				s.Top();
			}
		}
	}
}