# Architecture

## Reference model

```text
Physical Mouse A ----> device-specific input ----> Pointer A state --\
                                                               interaction layer ---> UI / demo
Physical Mouse B ----> device-specific input ----> Pointer B state --/
```

The system cursor and the application cursors are separate concepts. Early prototypes hide or ignore the ordinary system cursor inside the test window and draw two application-owned virtual cursors.

## Pointer state

A useful per-device state may contain:

```text
device_id
name
x, y
dx, dy
left / right / middle / extra buttons
wheel
sensitivity
cursor_style
connected
bound_role
```

## Derived bimanual state

Given cursor positions A and B, the interaction layer can derive:

```text
midpoint(A, B)
distance(A, B)
angle(A, B)
relative velocity
spread delta
rotation delta
crossing state
simultaneous-click timing
```

This derived state is where the project becomes more than simply placing two ordinary cursors on screen.

## Windows prototype path

```text
RegisterRawInputDevices
        |
      WM_INPUT
        |
   GetRawInputData
        |
RAWINPUTHEADER.hDevice
        |
per-device RAWMOUSE data
        |
Pointer A / Pointer B
```

Microsoft documents that Raw Input can distinguish input sources even when they are the same device type, such as two mice.
