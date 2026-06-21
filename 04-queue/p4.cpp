/*
 * 04-queue / p4.cpp
 * ------------------------------------------------------------
 * [문제] 요세푸스 변형 — 특정 사람 X가 몇 번째로 제거되는가 (p2의 변형)
 *   - 1..N 원형, 규칙 수열 M개, 그리고 찾을 대상 번호 X.
 *   - p2와 같은 방식으로 제거를 진행하되, X가 제거되는 "순서(count)"를 출력.
 *   - X가 끝까지 살아남아 마지막 1명이면 -1 출력.
 * [핵심] 제거할 때마다 count 증가, 제거된 사람이 X면 그 count를 출력.
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
	int pop() {
		if (empty()) {
			return -1;
		}
		if (front == rear) {
			Node* deleteNode = front;
			int result = deleteNode->value;
			delete deleteNode;
			n--;
			front = rear = nullptr;
			return result;
		}
		else {
			Node* deleteNode = front;
			front = front->next;
			int result = deleteNode->value;
			delete deleteNode;
			n--;
			return result;
		}
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
		int count = 1;
		Queue q;
		Queue subq;
		int N, M, X; cin >> N >> M >> X;
		for (int i = 0; i < N; i++) {
			q.push(i + 1);
		}
		for (int i = 0; i < M; i++) { // 규칙 수열을 subq에 추가
			int temp; cin >> temp;
			subq.push(temp);
		}
		for (int j = 0; j < N - 1; j++) {
			int rule = subq.pop();
			subq.push(rule);
			for (int k = 0; k < rule; k++) { // 앞에서 rule명을 빼서 뒤로 보냄(회전)
				int back = q.pop();
				q.push(back);
			}
			if (q.pop() == X) {
				cout << count << '\n';
				continue;
			}
			else count++;
		}
		if (q.pop() == X) cout << -1 << '\n';
	}
	cout << flush;
}