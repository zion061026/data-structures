/*
 * 02-singly-linked-list / p2.cpp
 * ------------------------------------------------------------
 * [문제] 커서(cursor) 기반 단일 연결 리스트 — 앞쪽 삽입/삭제
 *   - 명령: addFront v / addBack v / print / size /
 *           find v(값 v인 노드를 커서로 지정) / insertPrev v / deletePrev
 *   - insertPrev: 커서 노드 "바로 앞"에 v 삽입.
 *   - deletePrev: 커서 노드 "바로 앞" 노드 삭제.
 * [핵심] 단일 연결 리스트라 prev 포인터가 없어, head부터 따라가며
 *        커서 직전 노드를 찾는다. 커서가 head인 경계 상황 별도 처리.
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
	void insertPrev(int value) {
		if (cur == nullptr) { return; }
		Node* newNode = new Node(value);
		if (cur == head) { // 커서가 head면 그 앞(prev)이 존재하지 않으므로 예외로 따로 처리
			newNode->next = head;
			head = newNode;
			n++;
			return;
		}
		Node* prev = head;
		while (prev->next != cur) {
			prev = prev->next; // prev가 커서 바로 앞 노드가 될 때까지 전진
		}
		prev->next = newNode;
		newNode->next = cur;
		n++;
	}
	void deletePrev() {
		if (cur == nullptr || cur == head) { return; }
		Node* deleteNode = head;
		while (deleteNode->next != cur) {
			deleteNode = deleteNode->next;
		}
		if (deleteNode == head) {
			head = head->next;
			n--;
			delete deleteNode;
		}
		else {
			Node* prev = head;
			while (prev->next != deleteNode) {
				prev = prev->next;
			}
			prev->next = cur;
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
			else if (input == "size") {
				cout << l.size() << '\n';
			}
			else if (input == "insertPrev") {
				int value; cin >> value;
				l.insertPrev(value);
			}
			else if (input == "deletePrev") {
				l.deletePrev();
			}
			else if (input == "find") {
				int value; cin >> value;
				l.find(value);
			}
		}
	}
}