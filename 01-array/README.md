# 01. Array (동적 배열)

`new int[N]`로 메모리를 직접 관리하는 동적 배열 구현.

## 구현 기능
- `at` / `set` — 인덱스 접근·수정 (경계 검사)
- `insert` / `erase` — 임의 위치 삽입·삭제 (뒤 원소 시프트)
- `reverse` / `shuffle` — 구간 뒤집기, 두 원소 교환

## 파일별 문제
| 파일 | 문제 내용 |
|------|----------|
| p1_basic.cpp | 배열 명령 처리(`at/set/insert/erase/print`) + **count_max**: 최댓값과 같은 값의 개수 출력 |
| p2_reverse_shuffle.cpp | `0..N-1`로 초기화된 배열에 `reverse i j`(구간 뒤집기)·`shuffle i j`(두 원소 +1 후 swap) + **count_odd**: 홀수 개수 |
| p3.cpp | p1의 변형 — **count_min**: 최솟값과 같은 값의 개수 출력 |
| p4.cpp | p2의 변형 — **count_even**: 짝수 개수 출력 |

## 입력 형식
```
T                       (테스트케이스 수)
N Q                     (배열 크기, 명령 수)   ※ p1/p3
명령 ...                (Q줄)
```
