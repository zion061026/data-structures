/*
 * 05-vector-doubly-list / doubly_list_p1.cpp
 * ------------------------------------------------------------
 * [문제] 센티넬(header/trailer) 양방향 리스트 + 커서 왕복 이동 게임
 *   - 0..N-1을 리스트에 넣고 커서를 begin에 둠.
 *   - 명령:
 *       rotate k : 커서를 k칸 이동. 끝(trailer 직전)에 닿으면 방향을 뒤집어
 *                  되돌아온다(원형이 아니라 양끝에서 튕기는 왕복 이동).
 *       eat      : 현재 커서 값을 출력하고 그 노드를 제거. 진행 방향으로 커서 이동.
 *       reverse  : 진행 방향 토글.
 *       check    : 현재 커서 값 출력.
 *       add x p  : begin에서 p칸 위치에 값 x 삽입.
 * [핵심] header/trailer 센티넬로 삽입/삭제 시 nullptr 분기를 없앰.
 *        reverse 플래그 + 끝 도달 시 방향 전환으로 왕복(bounce) 순회 구현.
 *        중첩 클래스 iterator로 std 스타일 순회를 흉내.
 */
#include <iostream>
#include <string>
using namespace std;
class Node {
public:
    int value;
    Node* next;
    Node* prev;
    Node(int value) : value{ value }, next{ nullptr }, prev{ nullptr } {}
};
class List {
private:
    int n;
    Node* header;
    Node* trailer;
public:
    class iterator {
    public:
        int& operator*() { return ref->value; }
        iterator& operator++() { ref = ref->next; return *this; }
        iterator& operator--() { ref = ref->prev; return *this; }
        bool operator==(const iterator& right) const { return ref == right.ref; }
        bool operator!=(const iterator& right) const { return ref != right.ref; }
    private:
        Node* ref;
        iterator() : ref{ nullptr } {}
        iterator(Node* right) : ref{ right } {}
        friend class List;
    };
    List() : n{ 0 }, header{ new Node(-1) }, trailer{ new Node(-1) } {
        header->next = trailer;
        trailer->prev = header;
    }
    ~List() {
        while (!empty()) pop_back();
        delete header;
        delete trailer;
    }
    iterator begin() { return iterator(header->next); }
    iterator end() { return iterator(trailer); }
    int size() { return n; }
    bool empty() { return size() == 0; }
    iterator insert(iterator pos, int value) {
        Node* newNode = new Node(value);
        newNode->next = pos.ref;
        newNode->prev = pos.ref->prev;
        pos.ref->prev->next = newNode;
        pos.ref->prev = newNode;
        n++;
        return iterator(newNode);
    }
    void push_back(int value) { insert(end(), value); }
    void pop_back() { erase(--end()); }
    iterator erase(iterator pos) {
        if (empty()) return end();
        if (pos == end()) return end();
        Node* deleteNode = pos.ref;
        deleteNode->prev->next = deleteNode->next;
        deleteNode->next->prev = deleteNode->prev;
        n--;
        Node* next_deleteNode = deleteNode->next;
        delete deleteNode;
        return iterator(next_deleteNode);
    }
};
int main() {
    string input;
    int T; cin >> T;
    while (T--) {
        List l;
        bool reverse = false;
        int N, Q; cin >> N >> Q;
        for (int i = 0; i < N; i++) l.push_back(i);
        List::iterator it = l.begin();
        for (int j = 0; j < Q; j++) {
            cin >> input;
            if (input == "rotate") {
                int k; cin >> k;
                if (l.empty() || l.size() == 1) continue;
                for (int i = 0; i < k; i++) {
                    if (!reverse) {
                        List::iterator nxt = it; ++nxt;
                        if (nxt == l.end()) {
                            reverse = true;
                            --it;
                        }
                        else {
                            it = nxt;
                        }
                    }
                    else {
                        if (it == l.begin()) {
                            reverse = false;
                            ++it;
                        }
                        else {
                            --it;
                        }
                    }
                }
            }
            else if (input == "eat") {
                if (l.empty()) { cout << -1 << '\n'; continue; }
                cout << *it << '\n';
                if (l.size() == 1) {
                    l.erase(it);
                    it = l.end();
                    continue;
                }
                if (!reverse) {
                    List::iterator nxt = it; ++nxt;
                    if (nxt == l.end()) {
                        List::iterator prv = it; --prv;
                        l.erase(it);
                        it = prv;
                        reverse = true;
                    }
                    else {
                        l.erase(it);
                        it = nxt;
                    }
                }
                else {
                    if (it == l.begin()) {
                        reverse = false;
                        it = l.erase(it);
                    }
                    else {
                        List::iterator prv = it; --prv;
                        l.erase(it);
                        it = prv;
                    }
                }
            }
            else if (input == "reverse") { reverse = !reverse; }
            else if (input == "check") {
                if (l.empty()) cout << -1 << '\n';
                else cout << *it << '\n';
            }
            else if (input == "add") {
                List::iterator temp = l.begin();
                int x, p; cin >> x >> p;
                for (int i = 0; i < p; i++) ++temp;
                l.insert(temp, x);
            }
        }
    }
}