# 06. General Tree (일반 트리)

자식 수 제한이 없는 일반 트리. 각 노드가 `list<Node*> children`과 `parent` 포인터를 보유하고, 전체 노드는 `node_seq`로 관리(값 탐색은 선형). 루트는 값 1.

## 구현 기능
- `insert p c` / `erase x`(서브트리 통째 삭제) / `parent` / `children`
- 깊이·조상·순회 질의

## 파일별 문제
| 파일 | 문제 내용 |
|------|----------|
| p1.cpp | 명령형 트리 조작 + **depth x**: 루트~x 깊이(루트=0) |
| p2.cpp | N-1개 간선으로 트리 구성 후 **preorder(전위 순회)** 출력 |
| p3.cpp | p1의 변형 + **ancestor x**: x의 부모부터 루트까지 조상 나열 |
| p4.cpp | 트리 구성 후 **postorder(후위 순회)** 출력 |
