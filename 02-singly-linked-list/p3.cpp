/*
 * 02-singly-linked-list / p3.cpp
 * ------------------------------------------------------------
 * [문제] 단일 연결 리스트 + sum_odd  (p1의 변형: 짝수 → 홀수)
 *   - 명령: addFront v / addBack v / removeFront / print / sum_odd
 *   - sum_odd: 값이 홀수인 노드들의 합 출력(없으면 0).
 * [핵심] p1과 동일 구조, 합산 조건만 홀수로.
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
class LinkedList {
public:
	LinkedList() :head{ nullptr }, tail{ nullptr }, n{ 0 } {}
	void addFront(int value) {
		Node* newNode = new Node(value);
		if (empty()) {
			head = tail = newNode;
			n++;
			return;
		}
		newNode->next = head;
		head = newNode;
		n++;
	}
	void removeFront() {
		if (empty()) {
			cout << -1 << '\n'; return;
		}
		if (head == tail) {
			Node* deleteNode = head;
			head = tail = nullptr;
			delete deleteNode;
			n--;
			return;
		}
		Node* deleteNode = head;
		head = head->next;
		n--;
		delete deleteNode;
	}
	void addBack(int value) {
		Node* newNode = new Node(value);
		if (empty()) {
			head = tail = newNode;
			n++;
			return;
		}
		tail->next = newNode;
		tail = newNode;
		n++;
	}
	bool empty() {
		return size() == 0;
	}
	int size() { return n; }
	void print() {
		if (empty()) {
			cout << -1 << '\n'; return;
		}
		Node* tmp = head;
		while (tmp != nullptr) {
			cout << tmp->value << " ";
			tmp = tmp->next;
		}
		cout << '\n';
	}
	void sum_odd() {
		bool found = false;
		int sum = 0;
		Node* tmp = head;
		while (tmp != nullptr) {
			if (tmp->value % 2 != 0) {
				found = true;
				sum += tmp->value;
			}
			tmp = tmp->next;
		}
		if (!found) {
			cout << 0 << '\n';
		}
		else cout << sum << '\n';
	}
private:
	int n;
	Node* head;
	Node* tail;
};
int main() {
	int T; cin >> T;
	string input;
	while (T--) {
		int Q; cin >> Q;
		LinkedList l;
		for (int i = 0; i < Q; i++) {
			cin >> input;
			if (input == "addFront") {
				int value; cin >> value;
				l.addFront(value);
			}
			else if (input == "addBack") {
				int value; cin >> value;
				l.addBack(value);
			}
			else if (input == "removeFront") {
				l.removeFront();
			}
			else if (input == "print") {
				l.print();
			}
			else if (input == "sum_odd") {
				l.sum_odd();
			}
		}
	}
}