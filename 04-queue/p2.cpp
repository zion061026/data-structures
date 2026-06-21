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
		for (int i = 0; i < M; i++) { //rule 원소 subQ에 추가
			int temp; cin >> temp;
			subq.push(temp);
		}
		for (int j = 0; j < N - 1; j++) {
			int rule = subq.pop();
			subq.push(rule);
			for (int k = 0; k < rule; k++) { //rule 번 만큼 뒤로 보내기
				int back = q.pop();
				q.push(back);
			}
			q.pop();
		}
		cout << q.pop() << '\n';
	}
	cout << flush;
}