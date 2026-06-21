# 09. Heap (이진 힙)

`vector` 기반 완전 이진 힙. 배열 인덱스로 부모/자식을 계산.

## 구현 기능
- `up-heap`(삽입 시 상향) / `down-heap`(삭제 시 하향) 재정렬
- `compare` functor로 min-heap / max-heap 전환
- `push` / `pop` — O(log n)

## 파일
| 파일 | 설명 |
|------|------|
| q1.cpp ~ q4.cpp | 힙 구현 및 변형 |
