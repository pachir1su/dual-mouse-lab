# Tools, APIs, and Libraries

## Windows Raw Input

Primary documentation:

- https://learn.microsoft.com/windows/win32/inputdev/about-raw-input
- https://learn.microsoft.com/windows/win32/inputdev/raw-input

Relevant APIs/messages:

- `RegisterRawInputDevices`
- `GetRawInputData`
- `GetRawInputDeviceList`
- `GetRawInputDeviceInfo`
- `WM_INPUT`
- `WM_INPUT_DEVICE_CHANGE`

Microsoft explicitly documents that Raw Input can distinguish the source of input even when it comes from devices of the same type, giving two mouse devices as an example. `RAWINPUTHEADER.hDevice` identifies the device that generated a raw-input packet.

This is the first implementation path for Dual Mouse Lab on Windows.

## SDL3

Primary documentation:

- https://wiki.libsdl.org/SDL3/SDL_GetMice
- https://wiki.libsdl.org/SDL3/SDL_MouseID
- https://wiki.libsdl.org/SDL3/CategoryMouse

SDL 3.2+ can enumerate connected mice on supported platforms. `SDL_MouseID` identifies a mouse while it remains connected. SDL also warns that the list can include virtual devices, KVMs, and controllers that expose mouse functionality, so actual input activity should be used before assuming a listed device is an active physical mouse.

SDL3 is a strong candidate for a later cross-platform reference implementation.

## ManyMouse

- Repository: https://github.com/icculus/manymouse

ManyMouse is a small cross-platform C library designed specifically to read multiple input devices separately. Its documentation recommends hiding the system cursor and drawing application-specific cursors when supporting multiple mice. It has backends for Windows, Linux/XInput2/evdev, and macOS HID APIs.

## MouseMux

- Manual: https://www.mousemux.com/pages/manual/
- App library: https://www.mousemux.com/pages/apps/

MouseMux is an OS/application ecosystem for multiple independent cursors on Windows. Its current documentation describes extra mice, keyboards, pens, and touchscreens each receiving their own cursor, color, speed, and behavior.

It is important prior art for OS-wide/multi-user multi-cursor behavior. Dual Mouse Lab should not duplicate MouseMux as its first goal.

## GameMaker Raw Input extension

The 2 Mouse 4 U project reports using YellowAfterLife's GameMaker Raw Input extension for multi-mouse input:

https://yellowafterlife.itch.io/gamemaker-raw-input

## Engine notes

### Unreal Engine

DualOperation reports using a custom C++ plugin to keep two physical mice separate and expose device-specific events to Unreal/Blueprint gameplay systems.

### Unity

Needs a dedicated, source-backed investigation. Do not assume that connecting two physical mice automatically produces two separate `Mouse` devices in Unity's high-level input APIs.

### Godot

Research pending.
