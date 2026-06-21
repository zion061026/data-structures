/*
 * 01-array / p3.cpp
 * ------------------------------------------------------------
 * [문제] 동적 배열 + count_min  (p1의 변형: 최댓값 → 최솟값)
 *   - 명령: at i / set i v / insert i v / erase i / print / count_min
 *   - count_min: 배열의 최솟값과 같은 값이 몇 개인지 출력.
 * [핵심] p1_basic과 동일 구조, 비교 방향만 반대.
 */
#include <iostream>
#include <string>
using namespace std;

class Array {
public:
	Array(int N) {
		element = new int[N];
		for (int i = 0; i < N; i++) {
			element[i] = 0;
		}
		this->N = N;
	}
	~Array() {
		delete element;
	}
	void at(int index) {
		if (index < 0 || index >= N) { return; }
		cout << element[index] << '\n';
	}
	void set(int index, int value) {
		if (index < 0 || index >= N) { return; }
		element[index] = value;
	}
	void insert(int index, int value) {
		if (index < 0 || index >= N) { return; }
		for (int i = N - 1; i > index; i--) {
			element[i] = element[i - 1];
		}
		element[index] = value;
	}
	void erase(int index) {
		if (index < 0 || index >= N) { return; }
		for (int i = index; i < N - 1; i++) {
			element[i] = element[i + 1];
		}
		element[N - 1] = 0;
	}
	void print() {
		for (int i = 0; i < N; i++) {
			cout << element[i] << " ";
		}
		cout << '\n';
	}
	void count_min() {
		int min = element[0];
		int count = 0;
		for (int i = 0; i < N; i++) {
			if (min > element[i]) {
				min = element[i];
				count = 1;
			}
			else if (min == element[i]) {
				count++;
			}
		}
		cout << count << '\n';
	}
private:
	int N;
	int* element;
};
int main() {
	string input;
	int T; cin >> T;
	while (T--) {
		int N, Q; cin >> N >> Q;
		Array a(N);
		for (int i = 0; i < Q; i++) {
			cin >> input;
			if (input == "at") {
				int index; cin >> index;
				a.at(index);
			}
			else if (input == "set") {
				int index, value; cin >> index >> value;
				a.set(index, value);
			}
			else if (input == "insert") {
				int index, value; cin >> index >> value;
				a.insert(index, value);
			}
			else if (input == "erase") {
				int index; cin >> index;
				a.erase(index);
			}
			else if (input == "print") {
				a.print();
			}
			else if (input == "count_min") {
				a.count_min();
			}
		}
	}
}