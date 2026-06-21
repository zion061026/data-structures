/*
 * 03-stack / p2_count.cpp
 * ------------------------------------------------------------
 * [문제] "연속 K개 같은 값이 쌓이면 폭발" 스택  (뿌요뿌요 류)
 *   - 입력: N개의 값을 순서대로 push, 임계값 K.
 *   - 각 노드는 "현재 위치에서 같은 값이 연속으로 몇 개째인지(count)"를 저장.
 *     top과 같은 값을 push하면 count = top->count + 1, 다르면 1.
 *   - count가 K에 도달하면 그 K개를 한꺼번에 제거(pop).
 *   - 모든 push 후 남은 스택을 바닥→top 순서로 출력(비면 "EMPTY").
 * [핵심] 각 노드가 누적 연속 개수를 들고 있어 매번 세지 않아도 O(1) 판정.
 */
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int value;
    int count;
    Node* next;
    Node(int v, int c) : value{ v }, count{ c }, next{ nullptr } {}
};

class Stack {
private:
    Node* top;
    int n;
public:
    Stack() : top{ nullptr }, n{ 0 } {}
    bool empty() { return top == nullptr; }

    void push(int value, int K) {
        int newCount = 1;
        if (!empty() && top->value == value) {
            newCount = top->count + 1;
        }
        Node* newNode = new Node(value, newCount);
        newNode->next = top;
        top = newNode;
        n++;

        if (newCount == K) {
            for (int i = 0; i < K; i++) {
                Node* del = top;
                top = top->next;
                delete del;
                n--;
            }
        }
    }

    void print() {
        if (empty()) {
            cout << "EMPTY" << '\n';
            return;
        }
        int arr[1000];
        int idx = 0;
        Node* cur = top;
        while (cur) {
            arr[idx++] = cur->value;
            cur = cur->next;
        }
        for (int i = idx - 1; i >= 0; i--) {
            cout << arr[i];
            if (i > 0) cout << " ";
        }
        cout << '\n';
    }
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