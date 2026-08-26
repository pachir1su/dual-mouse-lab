# Terminology

## Dual mouse

Two physical mouse devices used by one system or application.

## Multi-mouse

A broader term for software that distinguishes multiple physical mice.

## Dual cursor

Two independently maintained pointer states. They may be native OS cursors, application-owned virtual cursors, reticles, or pointer-like game objects.

## Multi-pointer

More than one independently controlled pointer.

## Bimanual interaction

Interaction involving both hands.

## Two important categories

### Multi-user dual mouse

```text
Player A -> Mouse A -> Cursor A
Player B -> Mouse B -> Cursor B
```

### Single-user bimanual dual mouse

```text
             Left hand  -> Mouse A -> Cursor A
One player -+
             Right hand -> Mouse B -> Cursor B
```

The second category is the primary focus of Dual Mouse Lab, while the first is important prior art.

## Native cursor vs virtual cursor

A **native/system cursor** is managed by the operating system's normal pointer stack.

A **virtual/application cursor** is a pointer state maintained and rendered by the application itself. Two virtual cursors are sufficient for most experiments and games in this repository.
