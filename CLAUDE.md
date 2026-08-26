# CLAUDE.md

Claude Code는 작업을 시작하기 전에 저장소 루트의 `AGENTS.md`를 **전부 읽고** 그 규칙을 따릅니다.
공통 정책은 이 파일에 복사하지 않습니다.

Claude Code에만 추가로 적용하는 규칙:

- 관련 GitHub issue의 본문과 모든 댓글을 먼저 읽습니다.
- `README.md`, `README_KO.md`, `ROADMAP.md`, 관련 `docs/`, `research/`, prototype 코드를 확인합니다.
- 구현 전에 변경할 정확한 파일, 함수/모듈, 입력 흐름, 오류 분기, 필요한 QA를 계획합니다.
- 모든 변경은 feature branch에서 수행하고 `main`에 직접 write하지 않습니다.
- **한 커밋은 정확히 한 파일만 변경**합니다.
- 완료 전에 자신의 diff를 다시 읽어 요구 누락, 범위 밖 변경, 잘못된 연구 주장, 로컬 장치 식별정보·비밀값 혼입이 없는지 자체 감사를 수행합니다.
- Draft PR까지만 만들고 자동 merge, tag, GitHub Release를 하지 않습니다.

## 역할

Claude Code는 DML의 **코딩 에이전트**입니다.

담당 가능 범위:

- C++ / Win32 Raw Input prototype 구현
- SDL3 등 대안 prototype 구현
- 리팩터링
- 테스트 코드 작성
- 문서 갱신
- 연구자료 구조화 보조
- Draft PR 생성

독립 검증과 머지 판단은 ChatGPT에 넘깁니다.

- 기존 테스트와 문서를 읽어 계약을 이해할 수 있습니다.
- 사용자가 같은 작업에서 명시적으로 실행을 지시하지 않았다면 자신이 만든 변경의 build/runtime/hardware validation을 최종 판정하지 않습니다.
- 완료 보고에는 ChatGPT 또는 사용자가 실행해야 할 정확한 검증 명령과 실기기 QA 항목을 남깁니다.
- 실행하지 않은 검증은 `실행하지 않음 — 독립 검증 대기`로 표시합니다.
- 자신의 변경을 `테스트 통과`, `두 마우스 검증 완료`, `머지 가능`, `stable`이라고 판정하지 않습니다.

## DML 구현 시 주의할 점

### Raw Input / device identity

- `hDevice` 또는 장치별 ID가 실제 입력 source를 구분하는 핵심이라는 점을 유지합니다.
- device handle, device path, VID/PID 등을 고정값으로 하드코딩하지 않습니다.
- touchpad, Bluetooth mouse, virtual HID, KVM 등이 mouse-like device로 보일 수 있음을 고려합니다.
- `첫 두 개의 enumerated device`보다 사용자가 실제로 움직인 장치를 바인딩하는 방식을 우선 검토합니다.
- disconnect/reconnect와 hot-plug을 오류가 아닌 정상 상태 전이로 설계합니다.

### Cursor

- native Windows system cursor와 application-local virtual cursor를 혼동하지 않습니다.
- 첫 목표는 application window 내부의 독립 Cursor A / Cursor B입니다.
- cursor rendering, device input, interaction state를 가능한 한 분리합니다.
- 시각 디자인보다 입력 신뢰성을 먼저 해결합니다.

### Research

`research/`를 수정할 때는:

- primary source를 우선합니다.
- 링크와 날짜를 확인합니다.
- `physical mice`, `independent cursors`, `users`를 구분합니다.
- 검증하지 못한 신규성 주장을 만들지 않습니다.
- 원문을 장문 복사하지 않고 요약합니다.

## PR 완료 보고

Draft PR 본문 또는 완료 보고에는 최소한 다음을 포함합니다.

```text
Related issue:
Goal:
Changed files:
Implementation / documentation summary:
Scope intentionally not changed:
Known risks:
Validation not run:
Suggested independent validation:
Real-hardware QA pending:
```

code PR이라면 가능한 검증 예시를 정확히 적습니다.

```powershell
cmake -S prototypes/00-device-inspector -B build/device-inspector
cmake --build build/device-inspector --config Release
```

단, 실제 환경에 맞지 않는 명령을 무조건 복사하지 말고 변경된 prototype에 맞게 조정합니다.

## 릴리스

- 사용자가 목표 버전/릴리스를 명시한 경우에만 릴리스 관련 파일을 만집니다.
- Windows build 또는 real two-mouse hardware QA를 수행하지 않은 상태에서 안정판 승격을 권고하지 않습니다.
- Git tag, GitHub Release, auto-merge를 하지 않습니다.
