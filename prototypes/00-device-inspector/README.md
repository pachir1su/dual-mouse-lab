# 00 — Raw Input Device Inspector

## Goal

Before drawing two cursors, verify that Windows reports individual physical mice separately and inspect what each device actually emits.

The inspector should show/log:

```text
Device handle / path
Device type
Relative dx / dy
Left / right / middle buttons
Wheel
Connect / disconnect events
```

## Build

Open a **Developer Command Prompt for Visual Studio**:

```powershell
cmake -S . -B build
cmake --build build --config Release
```

Run the executable from the generated configuration directory.

## Expected result

Moving two different physical mice should produce raw-input events with different non-null device handles on ordinary mouse hardware.

Some touchpad/virtual-device cases can behave differently. The purpose of this program is to expose those details instead of hiding them behind the cursor layer.

## Status

Source added; real-device Windows testing still required.
