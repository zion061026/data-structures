# 11. Hash Table (해시 테이블)

open addressing(개방 주소법) 해시 테이블. 선형 탐사로 충돌을 해결하고, 슬롯 상태를 `enum class Status { ISITEM, NOITEM, AVAILABLE }`로 관리한다. 삭제는 실제로 비우지 않고 `AVAILABLE`로 표시(lazy deletion)해 탐사 사슬을 유지한다.

## 파일별 문제
| 파일 | 문제 내용 |
|------|----------|
| q1.cpp | int 키 + **선형 탐사(전진, index+1)** — `stock`(삽입, 탐사 횟수 출력) / `release`(삭제) / `check` / `space`(빈 칸) / `probe`(탐사 횟수) |
| q2.cpp | q1의 변형 — **선형 탐사(후진, index-1)** |
| q3.cpp | string 키(base-26 다항식 해시) — **전파 집합 크기**: 시작 이름에서 한 쪽만 멤버인 쌍을 통해 전파, 최종 멤버 수 출력 |
| q4.cpp | q3의 변형 — 전파된 **멤버 목록**을 추가 순서대로 출력 |
