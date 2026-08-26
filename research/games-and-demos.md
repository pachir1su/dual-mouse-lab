# Games and Interactive Demos

The table focuses on how closely each project matches **one player + two physical mice + two independent pointer-like controls**.

| Project | Year | Two physical mice | Independent pointer-like controls | One user | Notes |
|---|---:|:---:|:---:|:---:|---|
| DualOperation | 2026 | Yes | Yes | Yes | Unreal Engine dual-input framework with multiple playable implementations |
| Turnip Mountain | 2026 | Yes | Two independently controlled hands | Yes | Physics climbing game; each mouse controls one hand |
| 2 Mouse 4 U | — | Yes | Device-separated controls | Yes | Experimental Windows game explicitly requiring two mice |
| Shatterball | 2025 | Yes | Two separately controlled breakers | Yes | Dual-mouse roguelike brick-breaker |
| MouseMux Multi Mini Games | 2026 | Yes/N | Multiple colored cursors | Mostly multiple users | 24 shared-canvas mini-games including Asteroids |
| GI 2000 puzzle experiment | 2000 | Yes | Yes | No, two children | Research prototype with a two-mice/two-cursor condition |

## DualOperation

- Type: framework + playable demonstrations
- Platform: Unreal Engine 5
- Physical mice: two
- Users: one
- Independent cursors/operators: yes
- Official site: https://dualoperation.com/

The project describes two physical mice kept as independent input streams. Each stream drives an Operator with its own cursor, reticle, aim data, targeting rules, and bindings. This is currently one of the closest known references to the core Dual Mouse Lab concept.

## Turnip Mountain

- Type: commercial game
- Developer: Luke Sanderson
- Release: 2026-07-30
- Physical mice: two supported
- Users: one in single-player
- Official Steam page: https://store.steampowered.com/app/2138410/Turnip_Mountain/

The official description states that each hand can be controlled independently using two mice, one mouse per hand. It is a strong example of a finished game using two mice as a bimanual controller, though the controlled objects are hands rather than conventional cursors.

## 2 Mouse 4 U

- Type: experimental game
- Platform: Windows
- Physical mice: two required
- Users: one
- Page: https://teevy.itch.io/2-mouse-4-u

The developer explicitly describes the project as an experiment to see how a two-mouse game would work. The page states that it uses a GameMaker Raw Input extension for multi-mouse input.

## Shatterball

- Type: experimental / alpha game
- Release: 2025-04-25
- Physical mice: two supported
- Users: one
- Page: https://hyperlightresearch.itch.io/shatterball

Each breaker can be controlled by a mouse, and the instructions tell the player to use both mice at the same time.

## MouseMux Multi Mini Games

- Type: multi-user multi-cursor game collection
- Updated: 2026
- Independent cursors: yes
- Primary use: multiple users, one mouse each
- Page: https://www.mousemux.com/pages/apps/webapp-multi-games/

The collection has 24 mini-games on a shared canvas, with a colored cursor per player. Listed games include Cursor Tag, Tron, Asteroids, Sumo, Territory, and others. It is important adjacent prior art even though its primary model is multi-user rather than one person using both hands.

## Historical / research prototype

### Towards Seamless Support of Natural Collaborative Interactions

A Graphics Interface 2000 study compared a physical puzzle, a one-mouse/one-cursor condition, and a two-mice/two-cursor condition. It is multi-user rather than single-user bimanual interaction, but demonstrates that two independently controlled cursors on one display were already being studied in 2000.

Paper: https://graphicsinterface.org/wp-content/uploads/gi2000-15.pdf

## Leads to verify further

- older dual-mouse local multiplayer games
- cursor+cursor and other two-cursor games where the physical input devices are not clearly documented
- dual-mouse rhythm-game experiments
- light-gun/emulator multi-pointer projects
