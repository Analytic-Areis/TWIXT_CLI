# 🔴🔵 Twixt — Terminal Strategy Board Game (C Edition)

A high-performance, interactive terminal implementation of the classic connection board game **Twixt**, written in pure C. Features dynamic ASCII/ANSI board rendering, knight's-move link generation, planar line-intersection physics to prevent cross-links, and pathfinding-based win condition detection.

---

## 🎮 Game Rules & Overview

Twixt is a two-player abstract strategy connection game:
* **Players:**
  * 🟡 **Player 1 (Yellow / O):** Connects the **Top border** to the **Bottom border**.
  * 🔵 **Player 2 (Blue / X):** Connects the **Left border** to the **Right border**.
* **Movement:** Players take alternating turns placing pegs on grid coordinates (e.g., `A5`, `C7`).
* **Links:** When two pegs of the same color are placed a **Knight's Move** apart (2 units along one axis, 1 along the other), a link is automatically forged.
* **Intersection Rules:** Links cannot cross opponent links (or existing friendly links). Intersecting links are strictly prevented.
* **Victory:** The first player to form an unbroken chain of connected pegs linking their respective opposite borders wins immediately.

---

## ⚡️ Key Features

* **ANSI Color Grid:** Real-time terminal board rendering with distinct colored pegs and links.
* **Knight-Move Auto-Linking:** Validates geometry and builds bridges between friendly pegs on valid knight jumps.
* **Planar Line-Intersection Check:** Computational geometry algorithms ensure no two links cross.
* **Graph Connectivity & Win Check:** Evaluates graph connectivity every turn to detect when a border-to-border bridge is completed.
* **Safe Exit:** Type `-1` at any prompt to safely forfeit and quit the game.

---

## 🛠️ How to Compile and Run

### Prerequisites
* GCC or Clang
* Make

### Build
```bash
make
```
This produces the `twixt` executable.

### Play
```bash
./twixt
```
*(Tip: Maximize or enlarge your terminal window for optimal board visibility).*

### Clean
```bash
make clean
```

---

## 📂 Source Code Layout

* **`main.c`**: Game entrypoint, player turn loop, game over checks, and coordinate parsing.
* **`board.c` / `board.h`**: Board state matrix, coordinate transformations, and ANSI terminal rendering.
* **`play.c` / `play.h`**: Move validation, knight-move vector calculations, and line-crossing intersection tests.
* **`game.c` / `game.h`**: Win condition path search (graph traversal between opposing borders).
* **`Makefile`**: Standard build and clean recipes.
