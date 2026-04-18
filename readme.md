# 🎰 Casino Launcher

A terminal-based game launcher for casino simulations, featuring an ASCII art title, arrow-key navigation, and background music.

```
 $$$$$$\   $$$$$$\   $$$$$$\  $$$$$$\ $$\   $$\  $$$$$$\
$$  __$$\ $$  __$$\ $$  __$$\ \_$$  _|$$$\  $$ |$$  __$$\
$$ /  \__|$$ /  $$ |$$ /  \__|  $$ |  $$$$\ $$ |$$ /  $$ |
$$ |      $$$$$$$$ |\$$$$$$\    $$ |  $$ $$\$$ |$$ |  $$ |
$$ |      $$  __$$ | \____$$\   $$ |  $$ \$$$$ |$$ |  $$ |
$$ |  $$\ $$ |  $$ |$$\   $$ |  $$ |  $$ |\$$$ |$$ |  $$ |
\$$$$$$  |$$ |  $$ |\$$$$$$  |$$$$$$\ $$ | \$$ | $$$$$$  |
 \______/ \__|  \__| \______/ \______|\__|  \__| \______/
```

---

## Features

- Arrow-key menu navigation — no typing required
- ANSI colored terminal UI with highlighted selection
- Looping background music via [miniaudio](https://miniaud.io/)
- Launches external `.exe` game builds directly

---

## Requirements

- **OS:** Windows (uses `<conio.h>` and `_getch()`)
- **Compiler:** C++17 or later (e.g. MSVC, MinGW/GCC)
- **Library:** [miniaudio](https://miniaud.io/) — single-header, no install needed
- **Audio file:** `sound.wav` placed in the same directory as the launcher executable

---

## Project Structure

```
casino-launcher/
├── main.cpp
├── miniaudio.h
├── sound.wav
└── README.md
```

The launcher expects your game builds to live under a shared directory. By default this is set to:

```
Z:\! coding\C++\! builds\
```

Edit the `FILES_DIR` variable in `main.cpp` to match your own path.

---

## Games

| # | Name | Path |
|---|------|------|
| 1 | Blackjack | `Black-Jack-sim\blackjack.exe` |
| 2 | Poker | `Poker-sim\Poker-sim.exe` |
| 3 | Texas Hold'em | `Texas_holdem-sim\poker-sim.exe` |

To add more games, append entries to the `options` array in `main.cpp` and update the array size:

```cpp
std::array<std::string, 4> options = {
    "Black-Jack-sim\\blackjack.exe",
    "Poker-sim\\Poker-sim.exe",
    "Texas_holdem-sim\\poker-sim.exe",
    "YourGame-sim\\yourgame.exe"   // <-- add here
};
```

---

## Controls

| Key | Action |
|-----|--------|
| `↑` / `↓` | Navigate menu |
| `Enter` | Launch selected game |

---

## Building

### With MinGW (GCC)

```bash
g++ -std=c++17 -o casino main.cpp -lwinmm
```

### With MSVC

```bash
cl /std:c++17 main.cpp
```

> miniaudio is a single-header library — just make sure `miniaudio.h` is in the same folder as `main.cpp`.

---

## Audio

Background music plays automatically on launch. If `sound.wav` is missing or fails to load, the launcher continues silently without crashing.

To use a different audio file, change the filename in the `BGM()` function:

```cpp
ma_sound_init_from_file(&engine, "your_music.wav", ...);
```

miniaudio supports `.wav`, `.mp3`, and `.flac`.

---

## License

MIT — do whatever you want with it.