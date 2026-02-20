# Asteroids

A classic Asteroids arcade game built in C++23 using SFML 3.

![Game Screenshot](https://via.placeholder.com/800x400?text=Asteroids+Game)

## Gameplay

- Fly your ship, shoot asteroids, and survive as long as possible
- Asteroids spawn every few seconds and bounce off screen edges
- Each asteroid destroyed is worth **10 points**
- Your **high score is saved** between sessions
- Colliding with an asteroid ends the game

## Controls

| Key | Action |
|-----|--------|
| `W` / `↑` | Thrust forward |
| `A` / `←` | Rotate left |
| `D` / `→` | Rotate right |
| `Space` | Shoot |
| `Enter` | Start / Restart |
| `Escape` | Return to menu |

## Building

**Requirements:**
- CMake 4.0+
- A C++23 compatible compiler (GCC 13+, Clang 16+, MSVC 2022+)
- Internet connection (SFML is fetched automatically via CMake FetchContent)

**Steps:**

```bash
# Clone the repository
git clone https://github.com/yourusername/Asteroids.git
cd Asteroids

# Configure and build
cmake -B build
cmake --build build
```

The compiled executable and all required assets are placed in `build/bin/`.

**Running:**

```bash
./build/bin/Asteroids
```

## Project Structure

```
Asteroids/
├── assets/
│   ├── fonts/font.ttf
│   └── sounds/shoot.wav
├── include/
│   ├── global.h        # Screen dimensions and constants
│   ├── entity.h        # Abstract base class for game objects
│   ├── player.h        # Player ship
│   ├── bullet.h        # Projectiles
│   ├── asteroid.h      # Asteroid enemies
│   ├── game.h          # Game state manager
│   └── physics.h       # Collision detection
└── src/
    ├── main.cpp
    ├── game.cpp
    ├── player.cpp
    ├── bullet.cpp
    ├── asteroid.cpp
    └── physics.cpp
```

## Technical Details

- **Language:** C++23
- **Graphics/Audio:** [SFML 3.0.1](https://www.sfml-dev.org/)
- **Collision detection:**
  - Player vs asteroids: Separating Axis Theorem (SAT) on polygon shapes
  - Bullets vs asteroids: Ray casting point-in-polygon test
- **High score** persisted to a local `score.dat` binary file
- Frame-independent movement using delta time
