/*
 * 02-singly-linked-list / p4.cpp
 * ------------------------------------------------------------
 * [문제] 커서 기반 단일 연결 리스트 — 뒤쪽 삽입/삭제 (p2의 변형)
 *   - 명령: addFront v / addBack v / print / size /
 *           find v / insertNext v / deleteNext
 *   - insertNext: 커서 노드 "바로 뒤"에 v 삽입(커서가 tail이면 tail 갱신).
 *   - deleteNext: 커서 노드 "바로 뒤" 노드 삭제.
 * [핵심] next 방향이라 prev 탐색이 필요 없어 p2보다 단순. tail 경계만 주의.
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
	LinkedList() :head{ nullptr }, tail{ nullptr }, n{ 0 }, cur{ nullptr } {}
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
	void find(int value) {
		Node* tmp = head;
		while (tmp->value != value) {
			tmp = tmp->next;
		}
		cur = tmp;
	}
	void insertNext(int value) {
		if (cur == nullptr) { return; }
		Node* newNode = new Node(value);
		if (cur == tail) {
			tail->next = newNode;
			tail = newNode;
			n++;
			return;
		}
		newNode->next = cur->next;
		cur->next = newNode;
		n++;
	}
	void deleteNext() {
		if (cur == nullptr || cur == tail) { return; }
		Node* deleteNode = cur->next;
		if (deleteNode == tail) {
			tail = cur;
			cur->next = nullptr;
			delete deleteNode;
			n--;
		}
		else {
			cur->next = deleteNode->next;
			delete deleteNode;
			n--;
		}
	}
private:
	int n;
	Node* head;
	Node* tail;
	Node* cur;
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
			else if (input == "print") {
				l.print();
			}
			else if (input == "insertNext") {
				int value; cin >> value;
				l.insertNext(value);
			}
			else if (input == "deleteNext") {
				l.deleteNext();
			}
			else if (input == "size") {
				cout << l.size() << '\n';
			}
			else if (input == "find") {
				int value; cin >> value;
				l.find(value);
			}
		}
	}
}