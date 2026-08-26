# Roadmap

## Phase 0 — Knowledge base

- [x] Create repository structure
- [x] Add initial prior-art categories
- [ ] Verify every historical claim against a primary source
- [ ] Expand games and demos catalog
- [ ] Expand academic-paper catalog
- [ ] Expand tools/libraries catalog
- [ ] Expand patent/prior-art catalog
- [ ] Add verified videos and talks

## Phase 1 — Physical-device inspector

Goal: prove that individual physical mice can be identified reliably.

- [x] Add initial Win32 Raw Input inspector source
- [ ] Build on Windows with MSVC
- [ ] Test with two USB mice
- [ ] Record device names and handles
- [ ] Test button and wheel events
- [ ] Test Bluetooth mice
- [ ] Test laptop touchpad behavior
- [ ] Test hot-plug / unplug behavior

## Phase 2 — Dual virtual cursors

Goal: display two independently controlled pointers inside one application window.

- [x] Add initial Win32 prototype source
- [ ] Build and test with two real mice
- [ ] Add explicit Left / Right device binding flow
- [ ] Add diagnostics overlay
- [ ] Handle device disconnection cleanly
- [ ] Add absolute-device handling where useful

## Phase 3 — Pointer behavior

- [ ] Left / right / middle buttons
- [ ] Extra buttons
- [ ] Wheel
- [ ] Dragging
- [ ] Double-click timing
- [ ] Per-device sensitivity
- [ ] Optional acceleration
- [ ] Cursor confinement

## Phase 4 — Cursor UI

- [ ] Left/right identity system
- [ ] Idle / hover / pressed / dragging states
- [ ] Cursor trails
- [ ] Accessible high-contrast variants
- [ ] DPI/scaling checks
- [ ] Optional cursor-to-cursor connector visualization

## Phase 5 — Bimanual interaction primitives

- [ ] Midpoint
- [ ] Distance
- [ ] Angle
- [ ] Relative velocity
- [ ] Pinch/spread
- [ ] Rotation
- [ ] Crossing
- [ ] Two-point grab
- [ ] Symmetric and mirrored movement
- [ ] Simultaneous-click timing

## Phase 6 — Small demos

Candidate demos:

1. Two-point object manipulation
2. Dual-cursor rhythm / coordination
3. Asteroid / targeting test
4. Dual-reticle shooter test
5. Tether / rope physics test

A polished commercial game is not required.

## Phase 7 — Reusable package

- [ ] Separate input layer from demo code
- [ ] SDL3 reference implementation
- [ ] Developer-facing API documentation
- [ ] Example application
- [ ] CI build
- [ ] GitHub Releases

## Phase 8 — Optional OS-wide research

Only pursue this when there is a concrete use case.

- [ ] Compare application-local vs OS-level pointer behavior
- [ ] Study MouseMux and similar tools
- [ ] Investigate focus, security, accessibility, and multi-user implications
