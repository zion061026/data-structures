/*
 * 05-vector-doubly-list / doubly_list_p2.cpp
 * ------------------------------------------------------------
 * [문제] 센티넬 양방향 리스트 + 커서 왕복 게임 (doubly_list_p1의 변형)
 *   - 0..N-1을 넣고 이번엔 커서를 "마지막 원소"(--end())에서 시작.
 *   - 명령: rotate k / check / reverse / add x p / eat
 *     (의미는 p1과 동일: 양끝에서 튕기는 왕복 이동, eat은 출력 후 제거)
 * [핵심] isReversed 플래그로 진행 방향 관리. 끝/처음 도달 시 방향 전환.
 */
#include <iostream>
using namespace std;

class Node {
public:
	int value;
	Node* next;
	Node* prev;
	Node(int value) : value{ value }, next{ nullptr }, prev{ nullptr } {}
};
class List {
public:
	class iterator {
	public:
		int& operator*() {
			return ref->value;
		}
		bool operator==(const iterator& right) const {
			return ref == right.ref;
		}
		bool operator!=(const iterator& right) const {
			return ref != right.ref;
		}
		iterator& operator++() {
			ref = ref->next;
			return *this;
		}
		iterator& operator--() {
			ref = ref->prev;
			return *this;
		}
	private:
		Node* ref;
		iterator() :ref{ nullptr } {}
		iterator(Node* input) :ref{ input } {}
		friend class List;
	};
	List() :n{ 0 }, header{ new Node(-1) }, trailer{ new Node(-1) } {
		header->next = trailer;
		trailer->prev = header;
	}
	~List() {
		while (!empty()) {
			pop_back();
		}
		delete header;
		delete trailer;
	}
	int size() { return n; }
	bool empty() { return size() == 0; }
	iterator begin() {
		return iterator(header->next);
	}
	iterator end() {
		return iterator(trailer);
	}
	iterator insert(iterator pos, int value) {
		Node* newNode = new Node(value);
		newNode->next = pos.ref;
		newNode->prev = pos.ref->prev;
		pos.ref->prev->next = newNode;
		pos.ref->prev = newNode;
		n++;
		return iterator(newNode);
	}
	iterator erase(iterator pos) {
		if (empty()) { return end(); }
		if (pos == end()) { return end(); }
		Node* deleteNode = pos.ref;
		deleteNode->prev->next = deleteNode->next;
		deleteNode->next->prev = deleteNode->prev;
		Node* next_deletenode = deleteNode->next;
		n--;
		delete deleteNode;
		return iterator(next_deletenode);
	}
	void push_back(int value) {
		insert(end(), value);
	}
	void pop_back() {
		erase(--end());
	}
	void check(iterator it) {
		cout << *it << '\n';
	}
	void print() {
		iterator it = begin();
		while (it != end()) {
			cout << *it << " ";
			++it;
		}
	}
private:
	bool isReversed = false;
	int n;
	Node* header;
	Node* trailer;
};

int main() {
	int T; cin >> T;
	while (T--) {
		string cmd;
		List l;
		int N, Q; cin >> N >> Q;
		for (int i = 0; i < N; i++) {
			l.push_back(i);
		}
		bool isReversed = false;
		List::iterator it = --l.end(); // 커서를 마지막 원소에서 시작
		for (int j = 0; j < Q; j++) {
			cin >> cmd;
			if (cmd == "rotate") {
				int value; cin >> value;
				for (int i = 0; i < value; i++) {
					if (isReversed) { // 역방향일 때
						if (it == l.begin()) {
							isReversed = false;
							++it;
							continue;
						}
						--it;
					}
					else if (!isReversed) {
						if (it == --l.end()) {
							isReversed = true;
							--it;
							continue;
						}
						++it;
					}
				}
			}
			else if (cmd == "check") {
				cout << *it << '\n';
			}
			else if (cmd == "reverse") {
				isReversed = !isReversed;
			}
			else if (cmd == "add") {
				int value; int index;
				cin >> value >> index;
				List::iterator temp = l.begin();
				for (int i = 0; i < index; i++) {
					++temp;
				}
				l.insert(temp, value);
			}
			else if (cmd == "eat") {
				if (l.empty()) {
					cout << "-1" << '\n';
					continue;
				}
				if (!isReversed) {
					cout << *it << '\n';
					it = l.erase(it);
					if (it == l.end()) {
						isReversed = !isReversed;
						it = --l.end();
						continue;
					}
				}
				else {
					cout << *it << '\n';
					if (it == l.begin()) {
						isReversed = !isReversed;
						it = l.erase(it);
						continue;
					}
					it = (--l.erase(it));
				}
			}
			//l.print();
		}
	}
}