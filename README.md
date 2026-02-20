# Asteroids

A clone of the classic Asteroids arcade game built in C++23 using SFML 3.

## Features

- Fly your ship, shoot asteroids, and survive as long as possible
- Asteroids spawn every few seconds and bounce off screen edges
- Each asteroid destroyed is worth **10 points**
- Your **high score is saved** between sessions
- Colliding with an asteroid ends the game

## Screenshots
<img width="1200" height="895" alt="Screenshot from 2026-02-20 09-06-31" src="https://github.com/user-attachments/assets/916b292a-c229-460e-a3d5-7bb52dd6ac97" />
<img width="1198" height="893" alt="Screenshot from 2026-02-20 09-12-47" src="https://github.com/user-attachments/assets/06c1c19d-a405-4ca3-a0cd-d976f64ad305" />
<img width="1198" height="893" alt="Screenshot from 2026-02-20 09-12-59" src="https://github.com/user-attachments/assets/8c52781d-2791-4f7e-bf0b-10d5b9864d4c" />



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
