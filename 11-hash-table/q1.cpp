/*
 * 11-hash-table / q1.cpp
 * ------------------------------------------------------------
 * [문제] 개방 주소법(open addressing) 해시 테이블 — 선형 탐사(전진)
 *   - 명령: stock key value(삽입, 탐사 횟수 출력) / release key(삭제, 값 출력) /
 *           check key(값 조회, 없으면 None) / space(빈 칸 수) / probe key(탐사 횟수)
 *   - 버킷 상태는 enum Status: ISITEM(사용중) / NOITEM(한 번도 안 씀) / AVAILABLE(삭제됨).
 * [핵심] 해시 위치에서 충돌하면 index+1로 한 칸씩 선형 탐사(원형). 삭제는
 *        실제로 비우지 않고 AVAILABLE로 표시(lazy deletion)해 탐사 사슬을 보존.
 */
#include <iostream>
#include <string>
using namespace std;

enum class Status {
	ISITEM,NOITEM,AVAILABLE
};
class Entry {
	public:
		int key;
		string value;
		Status status;
		Entry() : key(-1), status(Status::NOITEM) {}
		Entry(int key, string& value) : key(key), value(value), status(Status::ISITEM) {}
		void erase() { status = Status::AVAILABLE; }
};

class Hash {
	private:
		int n;
		int N;
		Entry* bucket;
	public:
		Hash(int N) : n(0), N(N), bucket(new Entry[N]) {}
		int size() { return n; }
		bool empty() { return size() == 0; }
		int hash_code(int key) { return key; }
		int compress(int hash) { return hash % N; }
		void check(int key) {
			Entry* entry = find_entry(key);
			if (entry == nullptr) { cout << "None" << '\n'; return; }
			else cout << entry->value << '\n';
		}
		Entry* find_entry(int key) {
			int hash = hash_code(key);
			int index = compress(hash);
			int probe = 1;
			
			while (probe <= N && bucket[index].status != Status::NOITEM) {
				if (bucket[index].status == Status::ISITEM && bucket[index].key == key) {
					return &bucket[index];
				}
				probe++;
				index = compress(index + 1);
			}
			return nullptr;
		}
		bool stock(int key, string value) {
			int hash = hash_code(key);
			int index = compress(hash);
			int probe = 1;

			while (probe <= N) {
				if (bucket[index].status == Status::AVAILABLE || bucket[index].status == Status::NOITEM) {
					bucket[index].key = key;
					bucket[index].value = value;
					bucket[index].status = Status::ISITEM;
					n++;
					cout << probe << '\n';
					return true;
				}
				if (bucket[index].status == Status::ISITEM && bucket[index].key == key) {
					cout << probe << '\n';
					return false;
				}
				probe++;	
				index = compress(index + 1);
			}
			cout << probe << '\n';
			return false;
		}
		void release(int key) {
			Entry* entry = find_entry(key);
			if (entry == nullptr) { cout << "None" << '\n'; return; }
			n--;
			cout << entry->value << '\n';
			entry->erase();
		}
		void space() {
			cout << N - n << '\n';
		}
		void probe(int key) {
			int hash = hash_code(key);
			int index = compress(hash);
			int probe = 0;
			while (probe < N) {
				if (bucket[index].status == Status::AVAILABLE) {
					probe++;
					index = compress(index + 1);
					continue;
				}
				if (bucket[index].status == Status::NOITEM) {
					probe++;
					cout << probe << '\n'; return;
				}
				if (bucket[index].status == Status::ISITEM && bucket[index].key == key) {
					probe++;
					cout << probe << '\n'; return;
				}
				else {
					probe++;
					index = compress(index + 1);
					continue;
				}
			}
			cout << probe << '\n';
		}
};

int main() {
	int T; cin >> T;
	while (T--) {
		int Q, N; cin >> Q >> N;
		Hash h(N);
		string input;
		for (int i = 0; i < Q; i++) {
			cin >> input;
			if (input == "stock") {
				int k; string value; cin >> k >> value;
				h.stock(k, value);
			}
			else if (input == "release") {
				int k; cin >> k;
				h.release(k);
			}
			else if (input == "space") {
				h.space();
			}
			else if (input == "check") {
				int k; cin >> k;
				h.check(k);
			}
			else if (input == "probe") {
				int k; cin >> k;
				h.probe(k);
			}
		}
	}
}