# 03. Stack (스택)

연결 리스트 기반 LIFO 스택.

## 구현 기능
- `push` / `pop` / `top` / `size` / `empty` — 모두 O(1)
- 동일 값 연속 push 시 count 누적 변형(p2_count, p4_count)

## 파일
| 파일 | 설명 |
|------|------|
| p1_basic.cpp | 기본 스택 |
| p2_count.cpp / p4_count.cpp | 연속 중복 카운트 변형 |
| p3.cpp | 추가 변형 |

## 핵심 코드
```cpp
void push(int value) {
    Node* newNode = new Node(value);
    newNode->next = top;   // 새 노드를 top 위에 연결
    top = newNode;
    n++;
}
```
