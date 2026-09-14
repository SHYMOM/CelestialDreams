# Celestial Dreams

An OpenGL animation project built with C++ and GLUT, telling the story of a boy's dream journey through space to Jupiter's moon Europa.

## Story Flow

```
Bedroom → Deep Space → Journey to Jupiter → Europa Landing
    → Wake Up → Wall Zoom → Treehouse in Space → Thank You
```


## Requirements

- Linux (tested on Ubuntu)
- OpenGL, GLUT, GLU libraries

```bash
# Install dependencies (Ubuntu/Debian)
sudo apt-get install freeglut3-dev libgl-dev libglu1-mesa-dev
```

## How to Compile and Run

```bash
# Compile
g++ main.cpp -o celestial_dreams -lGL -lGLU -lglut

# Run
./celestial_dreams
```

## Keyboard Controls

| Key | Action |
|-----|--------|
| `1` - `8` | Jump to any scene |
| `R` | Restart animation |
| `F` | Toggle fan speed (Normal → Fast → Off) |
| `P` | Pause/Resume planet orbits |
| `E` | Instant wake up (Wake Up scene only) |

## Mouse Interactions

| Scene | Interaction |
|-------|-------------|
| Bedroom | Click lamp to toggle light |
| Bedroom | Mouse movement makes boy's eyes follow |
| Bedroom | Click dream cloud to pop it |
| Space | Click rocket for boost |
| Space | Mouse Y controls astronaut position |
| Landing | Click aliens to dodge them |
| Landing | Click anywhere to fire laser |
| Wake Up | Click boy to speed up waking |

## Scenes

| # | Scene | Developer | Key Features |
|---|-------|-----------|--------------|
| 0 | Bedroom | Dev1 | Room dims as boy sleeps, eye tracking, lamp toggle |
| 1 | Deep Space | Dev2 | 300 stars, orbiting planets, rocket boost |
| 2 | Journey | Dev3 | Jupiter grows, star speed lines, rocket wobble |
| 3 | Landing | Dev3 | 7 phases, alien encounter, laser battle |
| 5 | Wake Up | Dev4 | Head lift animation, eyes open, "just a dream" |
| 6 | Wall Zoom | Dev2 | Camera zoom into bedroom window |
| 7 | Treehouse | Dev1 | Floating in space, static tree (no air) |
| 8 | Thank You | Dev4 | Credits fade in, shooting stars |

## Developer Responsibilities

| Developer | Scenes | Variables |
|-----------|--------|-----------|
| Dev1 | Bedroom, Treehouse | fanSpin, clockTime, lampGlow, treehouseTimer |
| Dev2 | Space, Wall Zoom | stars, planets, rocketBoost, wallTimer |
| Dev3 | Journey, Landing | journeyTimer, jupiterSize, marsPhase, aliens |
| Dev4 | Wake Up, Thank You | wakeTimer, thankyouMode, dreamCloud |

## Technical Details

- **Rendering**: OpenGL immediate mode (GL_QUADS, GL_TRIANGLES, GL_TRIANGLE_FAN, GL_LINES)
- **Animation**: 60 FPS via glutTimerFunc
- **Coordinate System**: Orthographic 2D (-100 to 100)
- **State Machine**: Boolean flags control active scene
- **Collision**: Distance-based detection (dx² + dy² ≤ radius²)
- **Physics**: Simple easing (lampGlow += (target - current) * 0.08)

## Credits

Computer Graphics course final project.
