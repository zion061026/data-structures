/*
 * 04-queue / p2.cpp
 * ------------------------------------------------------------
 * [문제] 요세푸스 변형 — 가변 스텝으로 마지막 생존자 찾기
 *   - 1..N이 원형으로 큐에 들어있음. 규칙 수열 M개(subq)가 주어짐.
 *   - 매 라운드: subq에서 다음 규칙 rule을 꺼내(다시 뒤로 넣어 순환),
 *     큐 맨 앞 rule명을 한 명씩 뒤로 보낸 뒤, 그 다음 사람을 제거.
 *   - N-1명을 제거하면 마지막 한 명이 남고, 그 번호를 출력.
 * [핵심] "앞에서 빼서 뒤로 넣기"로 원형 회전을 구현. subq도 같은 방식으로 순환.
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
		Queue q;
		Queue subq;
		int N, M; cin >> N >> M;
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
			q.pop();
		}
		cout << q.pop() << '\n';
	}
	cout << flush;
}