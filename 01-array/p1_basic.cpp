/*
 * 01-array / p1_basic.cpp
 * ------------------------------------------------------------
 * [문제] 동적 배열(Array) 직접 구현 + count_max
 *   - T개의 테스트케이스. 각 케이스: 크기 N 배열을 만들고 Q개의 명령 처리.
 *   - 명령: at i / set i v / insert i v / erase i / print / count_max
 *   - count_max: 배열의 최댓값과 같은 값이 몇 개인지 출력.
 * [핵심] new int[N]로 메모리 직접 관리, insert/erase는 뒤 원소 시프트 → O(N).
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
		void count_max() {
			int max = element[0];
			int count = 0;
			for (int i = 0; i < N; i++) {
				if (max < element[i]) {   // 더 큰 값 발견 → 최댓값 갱신, 개수 1로 리셋
					max = element[i];
					count = 1;
				}
				else if (max == element[i]) {  // 현재 최댓값과 같으면 개수 증가
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
			else if (input == "count_max") {
				a.count_max();
			}
		}
	}
}