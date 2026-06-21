# 03. Stack (스택)

연결 리스트 기반 LIFO 스택. 일부 문제는 노드에 **연속 개수(count)** 를 저장해 활용한다.

## 구현 기능
- `push` / `pop` / `top` / `size` / `empty` — 모두 O(1)
- 동일 값 연속 push 시 count 누적 변형(p2_count, p4_count)

## 파일별 문제
| 파일 | 문제 내용 |
|------|----------|
| p1_basic.cpp | 기본 스택(`push/pop/top/size/empty`) + **pop_even**: 스택을 모두 비우며 pop한 값 중 짝수 개수 |
| p2_count.cpp | **연속 K개 폭발 스택** — 같은 값이 연속 K개 쌓이면 한꺼번에 제거. 노드가 누적 연속 개수를 저장. 마지막에 바닥→top 출력(비면 `EMPTY`) |
| p3.cpp | p1의 변형 — **pop_odd**: pop한 값 중 홀수 개수 |
| p4_count.cpp | p2와 같은 "연속 K개 폭발" 문제의 다른 구현(먼저 push 후 K-1개 제거) |

## 핵심 코드
```cpp
void push(int value) {
    Node* newNode = new Node(value);
    newNode->next = top;   // 새 노드를 top 위에 연결
    top = newNode;
    n++;
}
```
