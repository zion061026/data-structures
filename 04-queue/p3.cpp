/*
 * 04-queue / p3.cpp
 * ------------------------------------------------------------
 * [문제] 큐 + average  (p1의 변형: 합 → 평균)
 *   - 명령: push v / pop / front / size / empty / average
 *   - average: 큐 원소들의 정수 평균(합 / 개수) 출력.
 * [핵심] p1과 동일, 마지막에 size로 나눔.
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
class Queue {
public:
	Queue() : front{ nullptr }, rear{ nullptr }, n{ 0 } {}
	bool empty() { return size() == 0; }
	int size() { return n; }
	void Front() {
		if (empty()) {
			cout << -1 << '\n';
			return;
		}
		cout << front->value << '\n';
	}
	void push(int value) {
		Node* newNode = new Node(value);
		if (empty()) {
			front = rear = newNode;
			n++;
		}
		else {
			rear->next = newNode;
			rear = newNode;
			n++;
		}
	}
	void pop() {
		if (empty()) {
			cout << -1 << '\n'; return;
		}
		if (front == rear) {
			Node* deleteNode = front;
			cout << front->value << '\n';
			delete deleteNode;
			n--;
			front = rear = nullptr;
		}
		else {
			Node* deleteNode = front;
			front = front->next;
			cout << deleteNode->value << '\n';
			delete deleteNode;
			n--;
		}
	}
	void average() {
		if (empty()) { cout << -1 << '\n'; return; }
		Node* tmp = front;
		int sum = 0;
		while (tmp != nullptr) {
			sum += tmp->value;
			tmp = tmp->next;
		}
		cout << sum / size() << '\n';
	}
private:
	int n;
	Node* front;
	Node* rear;
};
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string input;
	int T; cin >> T;
	while (T--) {
		Queue q;
		int Q; cin >> Q;
		for (int i = 0; i < Q; i++) {
			cin >> input;
			if (input == "push") {
				int value; cin >> value;
				q.push(value);
			}
			else if (input == "pop") {
				q.pop();
			}
			else if (input == "size") {
				cout << q.size() << '\n';
			}
			else if (input == "average") {
				q.average();
			}
			else if (input == "front") {
				q.Front();
			}
			else if (input == "empty") {
				if (q.empty()) {
					cout << 1 << '\n';
				}
				else cout << 0 << '\n';
			}
		}
	}
	cout << flush;
}	