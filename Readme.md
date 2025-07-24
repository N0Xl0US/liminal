# 🕵️‍♂️ LIMINAL
**Solve the glitch. Unmask the ripple. Escape the noise.**

A terminal-based ASCII detective game set inside a decaying cyberpunk network.  
Navigate clues hidden across continents. Intercept signals. Decode poetic fragments.  
The Mask is watching.

---

## 📂 Project Structure

```
liminal/
├── ascii/         # ASCII art & clue text files (title.txt, intro.txt, clue files, etc.)
├── data/          # (Reserved for future save data, currently unused)
├── include/       # Header files (ascii.hpp, clue.hpp, game.hpp, etc.)
├── src/           # Game source files
├── main.cpp       # Entry point
├── Makefile       # Build instructions
├── LICENSE        # License info
└── Readme.md      # This file
```

---

## 🧠 Game Concept

- A mysterious entity known as **The Mask** has fragmented his presence into cryptic data traces.
- You must recover **3 narrative clues** from global nodes — each encoded in signal noise, audio logs, and timestamp anomalies.
- Each clue leads you closer to the final password.
- Decode it to unmask the truth.

---

## ✨ Features

- Full **ASCII UI** with colorful terminal rendering
- Mod-friendly architecture using external `.txt` files
- Modular C++17 codebase
- Runs entirely in your terminal — no graphics, just vibes

---

## 🛠️ Installation

### 🔧 Linux / macOS

1. Clone the repo:

   ```sh
   git clone https://github.com/N0Xl0US/liminal.git
   cd liminal
   ```

2. Build and run:

   ```sh
   make
   make run
   ```

3. Clean build files:

   ```sh
   make clean
   ```

### 🪟 Windows (MinGW / WSL)

**Option 1: Using WSL (Recommended)**

- Install Windows Subsystem for Linux
- Open WSL terminal and follow the Linux instructions above

**Option 2: Using MinGW**

- Install MinGW
- Add `g++` to PATH
- Open Command Prompt or PowerShell and run:

   ```sh
   mingw32-make
   liminal.exe
   ```

- You may need to manually replace `make` with `mingw32-make` in some shells.

---

## 🎮 How to Play

- Launch the game from your terminal after building.
- Follow the on-screen prompts and narrative.
- Read the ASCII art and clue files carefully—each contains hints or codes.
- Input answers or coordinates when prompted.
- Solve all 3 clues to unlock the final password and unmask The Mask.
- Press [Enter] to advance when prompted.

---

## 🧰 Requirements

- `g++` with C++17 support
- Terminal that supports ANSI escape codes (almost all modern terminals)

---

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.  
Feel free to use, modify, and share — just credit the original author.
