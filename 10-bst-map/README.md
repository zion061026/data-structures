# 10. BST Map (이진탐색트리 맵)

이진탐색트리(BST)로 구현한 key→value 맵. 키 비교로 좌/우로 내려가며 탐색·삽입하고, 중위 후속자(`successor`)로 오름차순 순회·두 자식 삭제를 처리한다.

## 구현 기능
- `find` / `insert` / `erase` — 평균 O(log n)
- `successor` 기반 in-order 순회, 두 자식 삭제

## 파일별 문제
| 파일 | 문제 내용 |
|------|----------|
| q1.cpp | key→**string** 맵 — `insert/find` + **height key**(노드 높이, 리프=0, 없으면 -2) + **range k1 k2**(구간 value 오름차순, 없으면 -3) |
| q2.cpp | q1의 변형 — **subtree_size key**(서브트리 노드 수) + range |
| q3.cpp | **창고 재고 관리** — BST 5개(`B[1..5]`, key=물품ID→수량). `import/export/transfer/check`, 수량 0이면 노드 삭제 |
| q4.cpp | q3와 같은 재고 관리 문제, `transfer` 구현 방식만 다름 |
