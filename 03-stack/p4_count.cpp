/*
 * 03-stack / p4_count.cpp
 * ------------------------------------------------------------
 * [문제] 연속 K개 폭발 스택 (p2_count와 같은 문제, 다른 구현)
 *   - N개를 push, 연속 같은 값이 K개가 되면 제거, 마지막에 바닥→top 출력.
 * [핵심] 새 노드를 먼저 push한 뒤 count==K이면 그 위 K-1개를 제거하는 방식.
 */
#include <iostream>
#include <string>
using namespace std;

class Node {
	public:
		Node* next;
		int value;
		int count;
		Node(int value) : value{ value }, next{ nullptr }, count{ 1 } {}
};
class Stack {
	public:
		Stack() : top{ nullptr }, n{ 0 } {}
		bool empty() const { return size() == 0; }
		int size() const { return n; }
		void push(int value, int k) {
			Node* newNode = new Node(value);
			if (empty()) {
				top = newNode;
				n++;
				newNode->count = 1;
			}
			else {
				if (top->value == value) {
					newNode->count = top->count + 1;
				}
				else {
					newNode->count = 1;
				}
				newNode->next = top;
				top = newNode;
				n++;
			}
	
			if (newNode->count == k) {
				for (int i = 0; i < k - 1; i++) {
					Node* deleteNode = top;
					top = top->next;
					delete deleteNode;
					n--;
				}
			}
		}
		void print() {
			int arr[1001] = {};
			if (empty()) { cout << "EMPTY" << '\n'; return; }
			Node* temp = top;
			for (int i = 0; i < n; i++) {
				arr[i] = temp->value;
				temp = temp->next;
			}
			for (int j = size() - 1; j >= 0; j--) {
				cout << arr[j] << " ";
			}
			cout << '\n';
		}
	private:
		int n;
		Node* top;
};
int main() {
	int T; cin >> T;
	while (T--) {
		Stack s;
		int N, K; cin >> N >> K;
		for (int i = 0; i < N; i++) {
			int temp; cin >> temp;
			s.push(temp, K);
		}
		s.print();
	}
}