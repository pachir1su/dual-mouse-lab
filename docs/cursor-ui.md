# Cursor UI Design

Cursor visuals are part of the interaction model, not just decoration. A user must be able to identify the left-hand and right-hand pointer immediately while tracking both at once.

## Initial UI

Do not start with polished artwork. The first prototype should use simple geometry:

```text
Cursor A: circle + crosshair + label A
Cursor B: diamond/circle variant + crosshair + label B
```

Use both **shape and color** for identity so the system is not color-only.

## States

Each cursor UI should eventually support:

- idle
- hover
- primary pressed
- secondary pressed
- dragging
- disconnected / waiting
- linked to the other cursor
- constrained / invalid target

## Useful feedback

- short click pulse
- optional motion trail
- device label during setup
- visible drag anchor
- optional line between two cursors when their relationship matters
- distance/angle overlay only in diagnostic mode

## Configuration

Per-device settings should include:

- sensitivity
- acceleration mode
- cursor size
- cursor style
- left/right role reassignment

## Accessibility

- Never rely on red vs green alone.
- Provide different shapes.
- Keep a high-contrast outline.
- Test 100%, 125%, 150%, and 200% Windows scaling.
- Allow larger cursors without changing logical hitboxes.
