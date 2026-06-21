# 07. Binary Tree (이진 트리)

`left`/`right` 두 자식 + `parent` 포인터로 구현한 이진 트리. 삽입 방향은 `enum class side { LEFT, RIGHT }`로 지정. 루트는 값 1.

## 구현 기능
- `Insert x v left|right` / `Erase v`(서브트리 삭제) / `Find v`
- 전위·중위 순회, 누적합, LCA(최소 공통 조상)

## 파일별 문제
| 파일 | 문제 내용 |
|------|----------|
| p1.cpp | 삽입/삭제/탐색 + **Add v**: (왼자식 + 오른자식 + 부모) 값의 합 |
| p2.cpp | **Inorder_sum**(중위 누적합이 x 초과하는 노드) / **Preorder_travel**(전위로 x까지 경로) / **LCA x y** |
| p3.cpp | p1의 변형 — **Subtract v**: (왼자식 + 오른자식 − 부모) |
| p4.cpp | **Inorder_travel**(중위로 x까지) / **Preorder_sum**(전위 누적합) / **LCA** |

> 순회 함수는 `bool`을 반환해 목표 노드 도달 시 재귀를 조기 종료한다.
