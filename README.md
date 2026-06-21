# Data Structures in C++

자료구조 과목에서 **STL 컨테이너에 의존하지 않고 직접 구현**한 핵심 자료구조 모음입니다.
한 학기 전체(배열 ~ 그래프)를 다루며, 각 주제는 학습 의존 순서대로 번호가 매겨져 있고
중간 범위는 폴더마다 4개의 변형 문제(P1 ~ P4), 기말 범위는 시험 기출 기반으로 구성됩니다.

## 구현 목록

| # | 자료구조 | 핵심 개념 | 범위 | 코드 |
|---|---------|----------|------|------|
| 01 | Array | 동적 배열, at/set/insert/reverse/shuffle | 중간 | [폴더](./01-array) |
| 02 | Singly Linked List | head/tail 포인터, cursor 순회 | 중간 | [폴더](./02-singly-linked-list) |
| 03 | Stack | LIFO, 연결리스트 기반, 연속 중복 count 변형 | 중간 | [폴더](./03-stack) |
| 04 | Queue | FIFO, front/rear 포인터 | 중간 | [폴더](./04-queue) |
| 05 | Vector & Doubly Linked List | capacity doubling, 센티넬, 중첩 iterator | 중간 | [폴더](./05-vector-doubly-list) |
| 06 | General Tree | children 리스트, 노드 시퀀스 순회 | 중간 | [폴더](./06-general-tree) |
| 07 | Binary Tree | left/right 자식, 방향 enum | 중간 | [폴더](./07-binary-tree) |
| 08 | Priority Queue | 우선순위 큐 (list 기반, compare functor) | 기말 | [폴더](./08-priority-queue) |
| 09 | Heap | 배열 기반 이진 힙, up/down-heap | 기말 | [폴더](./09-heap) |
| 10 | BST Map | 이진탐색트리 기반 맵 (key→value) | 기말 | [폴더](./10-bst-map) |
| 11 | Hash Table | open addressing, 선형 탐사, 상태(enum) 관리 | 기말 | [폴더](./11-hash-table) |
| 12 | Graph — Adjacency Matrix | 인접 행렬 표현 | 기말 | [폴더](./12-graph-adjacency-matrix) |
| 13 | Graph — Adjacency List | 인접 리스트 + 탐색/최단경로 (BFS, queue) | 기말 | [폴더](./13-graph-adjacency-list) |

## 빌드 & 실행

각 `.cpp`는 독립 실행 가능한 단일 프로그램입니다.

```bash
g++ -std=c++17 -O2 01-array/p1_basic.cpp -o out && ./out
```

## 기술 스택

- **언어**: C++17
- **특징**: `std::stack`, `std::map` 등 표준 컨테이너에 의존하지 않고 자료구조를 밑바닥부터 직접 구현 (학습 목적)
- **메모리 관리**: `new`/`delete`로 노드 수명 직접 관리
- 전 파일 `g++ -std=c++17` 컴파일 검증 완료

## 디렉터리 구조

```
data-structures-cpp/
├─ 01-array/ ~ 07-binary-tree/      # 중간 범위: 배열·리스트·스택·큐·트리
└─ 08-priority-queue/ ~ 13-graph-*/  # 기말 범위: PQ·힙·BST·해시·그래프
```
