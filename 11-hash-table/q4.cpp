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
		string seen[50001];
		int Q, N; cin >> Q >> N;
		Hash h(N);
		string name1, name2;
		int cnt = 0;
		for (int i = 0; i < Q; i++) {
			if (i == 0) {
				cin >> name1;
				h.insert(name1, true); //root 차단 전파 시작
				seen[cnt] = name1;
				cnt++;
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
				seen[cnt] = name1;
				cnt++;
			}
			else if (entry1 != nullptr && entry2 == nullptr) {
				h.insert(name2, true);
				seen[cnt] = name2;
				cnt++;
			}
		}
		for (string x : seen) {
			if(x != "") cout << x << '\n';
		}
	}
}