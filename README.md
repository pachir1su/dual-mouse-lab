# Dual Mouse Lab

> A research and prototype lab for **two physical mice, two independent cursors, and bimanual interaction**.

[한국어 README](README_KO.md)

## Core idea

A conventional desktop normally merges motion from multiple mice into one system pointer. Dual Mouse Lab explores a different model:

```text
Left hand  -> Physical Mouse A -> Cursor A
Right hand -> Physical Mouse B -> Cursor B
```

Both pointers should be independently usable for movement, clicks, buttons, wheel input, dragging, and eventually higher-level two-hand gestures.

This repository is not primarily a full-game project. It is intended to become a **knowledge base + implementation lab** for anyone who has the same question: *What can we build if two mice behave like two independent hands?*

## Goals

1. **Build a curated prior-art archive**
   - games and playable experiments
   - academic papers and HCI research
   - libraries, APIs, engine plugins, and desktop tools
   - patents and historical systems
   - videos and developer write-ups

2. **Build small reference implementations**
   - enumerate physical mouse devices
   - identify the device that produced each input event
   - render two independent virtual cursors in one application window
   - support buttons, wheel, drag, hot-plug, and per-device settings

3. **Study dual-pointer interaction design**
   - symmetric vs. asymmetric bimanual tasks
   - distance, angle, midpoint, crossing, and relative motion between cursors
   - visual attention, cursor identity, left-hand learning, and sensitivity differences

4. **Create small demos, not a commercial game**
   - rhythm / coordination
   - targeting / shooting
   - two-point manipulation
   - physics / tether interactions

## Why application-local virtual cursors first?

The first milestone is **not** to replace Windows with two native OS cursors.

Instead:

```text
Mouse A --\
          -> device-specific input -> Cursor A state -> draw in our window
Mouse B --/                         -> Cursor B state -> draw in our window
```

Windows Raw Input can distinguish input sources even when they are the same device type, including two mouse devices. This is enough to prove the interaction model before attempting any OS-wide multi-pointer work.

## Current plan

```text
00  Research archive
01  Physical-device inspector
02  Two independent virtual cursors
03  Buttons / wheel / drag
04  Cursor UI and per-device settings
05  Bimanual interaction primitives
06  Small playable demos
07  Optional OS-wide experiments
```

See [ROADMAP.md](ROADMAP.md).

## Repository structure

```text
dual-mouse-lab/
├─ README.md
├─ README_KO.md
├─ ROADMAP.md
├─ CONTRIBUTING.md
├─ docs/
├─ research/
├─ prototypes/
├─ demos/
└─ .github/
```

## Prior-art note

Dual-mouse and multi-cursor interaction are **not new inventions**. Relevant work includes older HCI research, multi-user multi-cursor systems, libraries such as ManyMouse, desktop tools such as MouseMux, and recent games/experiments such as DualOperation, 2 Mouse 4 U, Shatterball, and Turnip Mountain.

The interesting open space is not “inventing the second mouse.” It is building better **single-user, two-hand, two-pointer interaction patterns** and making the existing knowledge easier to discover and reproduce.

See [`research/`](research/README.md).

## Implementation direction

The first reference implementation targets **Windows + Win32 Raw Input** because it exposes device-specific mouse input directly and requires no external runtime.

SDL3 is also tracked as a cross-platform path: SDL 3.2+ can enumerate connected mice and exposes per-mouse instance IDs on supported platforms.

## Status

Early research / bootstrap stage. APIs, references, and prototypes are being verified before the repository is made public.

## Project origin

The original project idea was to connect two mice to one computer, show two independent cursors, and use one mouse in each hand for games and other interaction experiments. The repository expands that idea into a reusable research and prototyping resource.
