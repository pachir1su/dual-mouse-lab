# 01 — Dual Cursor Win32 Prototype

A minimal Windows proof of concept using **Win32 Raw Input**.

## Intended behavior

1. Start the program.
2. Move one physical mouse: it becomes **A**.
3. Move a different physical mouse: it becomes **B**.
4. The application draws two independent virtual cursors.
5. Each device updates only its own cursor.
6. Primary clicks change the corresponding cursor's visual state.
7. Press `R` to clear device bindings.
8. Press `Esc` to exit.

## Important distinction

This prototype does **not** create two native Windows system cursors. It maintains and renders two application-owned pointer states inside its own client area.

That is intentional and sufficient for the first research milestones.

## Build

```powershell
cmake -S . -B build
cmake --build build --config Release
```

## Known limitations / next work

- real-device testing has not yet been completed
- explicit Left/Right binding UI is better than “first two active devices”
- absolute pointing devices need separate coordinate handling
- device names should be shown in the UI
- disconnection should unbind/rebind cleanly
- right/middle/extra buttons and wheel need visualization
- per-device sensitivity is not implemented yet
