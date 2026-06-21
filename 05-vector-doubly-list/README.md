# 05. Vector & Doubly Linked List

두 가지 시퀀스 구조를 함께 다룬다.

## Vector (동적 배열)
- capacity가 차면 **2배 확장**(`resize(2*capacity)`)하는 분할상환 O(1) `push_back`
- 명령: `push_back / insert / erase / set / size / capacity / print`

| 파일 | 문제 내용 |
|------|----------|
| vector_p1.cpp | 동적 배열 명령 + **count_over v**: v보다 큰 원소 개수 |
| vector_p2.cpp | 변형 — **count_under v**: v보다 작은 원소 개수 |

## Doubly Linked List (이중 연결 리스트)
- header/trailer **센티넬 노드** + 중첩 `iterator` 클래스로 std 스타일 순회
- 커서가 양끝에서 튕기는 **왕복(bounce) 이동** 게임

| 파일 | 문제 내용 |
|------|----------|
| doubly_list_p1.cpp | `rotate k`(왕복 이동) / `eat`(현재 값 출력 후 제거) / `reverse` / `check` / `add x p`. 커서는 begin에서 시작 |
| doubly_list_p2.cpp | p1과 같은 게임, 커서를 마지막 원소에서 시작하는 변형 |
