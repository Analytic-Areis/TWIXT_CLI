# TWIXT GAME PROJECT

## Student Details
- Name: Lakshmi Sai Bhargav Vemparala
- Roll Number: 2025102061
- Course: M25 C-Programming
- Date: 3/12/25

---

## How to Compile and Run

1. Place all source files and the Makefile in one folder.
2. Open a terminal inside that folder.

### To Compile:

```
make
```

This creates the executable `twixt`.

### To Run the Game:
```
./twixt
```

(Adjust your terminal size to view the full board.)

### To Clean Build Files:
```
make clean
```

---

## What It Does

-What It Does
-Runs a fully interactive terminal-based TWIXT game.
-Players take alternating turns placing Yellow (O) and Blue (X) pegs.
-Accepts coordinate-based input (e.g., A5, C7).
-NEW FEATURE: Players can exit the game at any time by typing -1.
-Automatically forms valid knight-move links between pegs of the same color.
-Prevents illegal cross-links using line-intersection checks.
-Displays messages when new links are successfully formed.
-Continuously updates and redraws the board with colored output.
-Detects when the board has no valid moves left and declares a draw.
-Checks win conditions on every move:
  -Yellow wins by connecting top to bottom.
  -Blue wins by connecting left to right.
-Ends the game immediately when a winner is found or when the player exits with -1.

---

# End of README
