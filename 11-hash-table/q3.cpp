/*
 * 11-hash-table / q3.cpp
 * ------------------------------------------------------------
 * [문제] 문자열 키 해시 테이블로 "전파(감염)" 집합 세기
 *   - 첫 입력 이름이 시작점(집합에 등록).
 *   - 이후 (name1, name2) 쌍이 주어질 때, 둘 중 정확히 한 명만 이미
 *     집합에 있으면 나머지 한 명도 집합에 추가(전파).
 *   - 최종 집합의 크기(size)를 출력.
 * [핵심] 멤버십을 해시 테이블로 O(1) 평균 조회. 문자열 해시는 base-26 다항식,
 *        충돌은 선형 탐사(역방향)로 해결.
 */
#include <iostream>
#include <string>
using namespace std;

enum class Status {
	ISITEM, NOITEM, AVAILABLE
};
class Entry {
public:
	string key;
	bool value;
	Status status;
	Entry() : value(false), status(Status::NOITEM) {}
	Entry(string key, bool value) : key(key), value(value), status(Status::ISITEM) {}
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
	int hash_code(string key) {
		int base = 1;
		int result = 0;
		for (int i = 0; i < key.length(); i++) {
			result += (key[i] - 'a') * base;
			base = base * 26;
		}
		return result;
	}
	int compress(int hash) { return hash % N; }
	Entry* find_entry(string key) {
		int hash = hash_code(key);
		int index = compress(hash);
		int probe = 1;

		while (probe <= N && bucket[index].status != Status::NOITEM) {
			if (bucket[index].status == Status::ISITEM && bucket[index].key == key) {
				return &bucket[index];
			}
			probe++;
			index = compress(index - 1 + N);
		}
		return nullptr;
	}
	bool insert(string key, bool value) {
		int hash = hash_code(key);
		int index = compress(hash);
		int probe = 1;

		while (probe <= N) {
			if (bucket[index].status == Status::AVAILABLE || bucket[index].status == Status::NOITEM) {
				bucket[index].key = key;
				bucket[index].value = value;
				bucket[index].status = Status::ISITEM;
				n++;
				return true;
			}
			if (bucket[index].status == Status::ISITEM && bucket[index].key == key) {
				return false;
			}
			probe++;
			index = compress(index - 1 + N);
		}
		return false;
	}
};

int main() {
	int T; cin >> T;
	while (T--) {
		int Q, N; cin >> Q >> N;
		Hash h(N);
		string name1, name2;
		for (int i = 0; i < Q; i++) {
			if (i == 0) {
				cin >> name1;
				h.insert(name1, true); //root 차단 전파 시작
				continue;
			}
			else {
				cin >> name1 >> name2;
			}
			if (name1 == name2) continue;
			Entry* entry1 = h.find_entry(name1);
			Entry* entry2 = h.find_entry(name2);
			if (entry1 == nullptr && entry2 != nullptr) {
				h.insert(name1, true);
			}
			else if (entry1 != nullptr && entry2 == nullptr) {
				h.insert(name2, true);
			}
		}
		cout << h.size() << '\n';
	}
}