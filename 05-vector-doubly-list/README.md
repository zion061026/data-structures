# 05. Vector & Doubly Linked List

두 가지 시퀀스 구조를 함께 다룹니다.

## Vector (동적 배열)
- capacity가 차면 **2배 확장**(`resize(2*capacity)`)하는 amortized O(1) `push_back`
- 파일: `vector_p1.cpp`, `vector_p2.cpp`

## Doubly Linked List (이중 연결 리스트)
- header/trailer **센티넬 노드**와 중첩 `iterator` 클래스
- 양방향 삽입·삭제
- 파일: `doubly_list_p1.cpp`, `doubly_list_p2.cpp`
