# 11. Hash Table (해시 테이블)

open addressing(개방 주소법) 해시 테이블. 선형 탐사로 충돌 해결.

## 구현 기능
- `enum class Status { ISITEM, NOITEM, AVAILABLE }`로 슬롯 상태 관리
- 삭제 시 AVAILABLE 표시(lazy deletion)
- `insert` / `find` / `erase`

## 파일
| 파일 | 설명 |
|------|------|
| q1.cpp, q2.cpp | int key |
| q3.cpp, q4.cpp | string key |
