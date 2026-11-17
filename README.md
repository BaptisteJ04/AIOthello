# Othello AI

A networked Othello (Reversi) player written in C, built as a university course project. It can play online against another player or against an AI. At its core, the AI uses the Minimax algorithm with alpha-beta pruning to make strategic decisions.

**Result:** in the internal tournament organised by our instructor, every student wrote an AI and all of them played each other. This one won the tournament. 🏆

## Features

- Othello game logic: board initialisation and valid-move detection.
- Minimax with alpha-beta pruning to pick the best move.
- Client/server play over the network, with authentication and game management.
- Tournament mode: automated matches between several AIs.

The player authenticates with a user ID and a password, then joins an online game against another player or the AI.

## Project layout

| File | Role |
|------|------|
| `fonction_othello.c/.h` | Game rules: board, valid moves, captures, display |
| `MinMax.c/.h` | AI: Minimax, alpha-beta pruning, evaluation functions |
| `main_othello.c/.h` | Entry point: network connection, game loop |
| `userNetwork.h` | Header of the network library provided by the instructor |
| `userSimple.c` | Minimal example client provided by the instructor |

> **Note:** `userNetwork.h` and `userSimple.c` were provided by the course (author: Q. Giorgi). The closed-source `libothello` library they depend on is **not** included in this repository, so the project cannot be linked or run without it. The code is published to showcase the game logic and the AI.

## `fonction_othello.c`: game logic

This file contains the functions needed to set up and run an Othello game. The board is an 8x8 matrix (`0` = black, `1` = white, `2` = empty).

1. **`init_grille(int mat[8][8])`**
   Fills the matrix with empty cells (`2`), then places the four starting discs in the centre: two black (`0`) and two white (`1`), at `(3,3)`, `(4,3)`, `(3,4)` and `(4,4)`.

2. **`print_grille(int mat[8][8])`**
   Prints the board to the console with row and column indices. Black discs are yellow (`\033[33m`), white discs are cyan (`\033[36m`), and empty cells are blank.

3. **`coup_valide(int mat[8][8], int line, int col, int player)`**
   Checks whether a move at a given position is valid for the given player. A move is valid if:
   - the cell is empty (`2`);
   - it captures at least one opposing disc, which is checked through `evolution_grille`.

4. **`evolution_grille(int mat[8][8], int line, int col, int player)`**
   Checks whether a move captures opposing discs in any of the 8 directions (up, down, left, right and the 4 diagonals), by calling `test_valide` for each direction.

5. **`test_valide(int mat[8][8], int player, int x, int y, int i, int a, int b)`**
   Tests a single direction from a given cell: looks for a run of opposing discs closed by one of the player's own discs, and flips them if the move is played.

## `MinMax.c`: the AI

This file implements the AI using Minimax search with alpha-beta pruning. It evaluates candidate moves down to a given search depth and picks the best one.

1. **`numberone(int best[2], int grille[8][8], int joueur, int curent, int profondeur)`**
   Scans the board for the best move. Each valid move is scored with Minimax, and the best one is stored in `best` as (row, column).

2. **`inter(int grille[8][8], int joueur, int curent, int profondeur, int alpha, int beta)`**
   Recursive Minimax with alpha-beta pruning. It simulates successive moves by both players and estimates the value of each position.
   - `alpha` is the best value the maximising player can guarantee so far.
   - `beta` is the best value the minimising player can guarantee so far.
   - When a branch cannot influence the final decision (score beyond `beta` for the minimiser, or below `alpha` for the maximiser), it is pruned.

3. **`evaluation_1(int grille[8][8], int joueur)`**
   Simple disc count: +1 for each of the player's discs, -1 for each opposing disc. Fast but basic.

4. **`evaluation_2(int grille[8][8], int joueur)`**
   Positional evaluation using a weight table `teval`, where each cell has its own value (corners are worth much more than central cells).

5. **`evaluation_3(int grille[8][8], int joueur)`**
   An improvement on the previous one that takes into account both disc positions and the number of empty cells remaining, favouring positions that give more long-term control.

6. **`copie(int grille[8][8], int p[8][8])`**
   Copies the board into another array, so simulations do not modify the real game state.

## `main_othello.c`: networked game

The main program plays Othello over the network by connecting to a server. It relies on `fonction_othello.h`, `main_othello.h`, `MinMax.h` and `userNetwork.h`.

### Initialisation and authentication

- **Global variables:** `V`, `D`, `nulle` (win/loss/draw counters), `grille[8][8]` (the board), `best[2]` (best move computed by the AI) and `g` (pointer to the `game` structure).
- The program allocates a new game with `allocateGameOthello()`.
- It reads the user ID, IP address and password from the command line, and exits with an error if any is missing.
- It registers with the server through `registerGameOthello()`, then calls `startGameOthello()`, which blocks until an opponent is found.

### Game loop

The loop runs while the game is in progress (`g->state == PLAYING`) and stdin has not reached end of file.

- **Opponent's turn:** if it is not the local player's turn (`g->myColor` vs `g->currentPlayer`), the program waits for the opponent's move with `waitMoveOthello(g)`, then validates and applies it with `coup_valide()`.
- **Local turn:** the program calls `numberone()` to compute the best move with Minimax, plays it with `coup_valide()`, and sends it to the server with `doMoveOthello()`.

### End of game

When the game is no longer in progress, the final status (`g->state`) is displayed, the win/loss/draw counters are updated, and the game is released with `freeGameOthello(g)`.

## Building and running

### Requirements

- **GCC**
- **Make**
- The instructor-provided `libothello` library (not included), placed in the project root.

### Build

```bash
make
```

### Run

```bash
./jothello <userPasswd> <ip address> <userId>
```

## About the project

Building this project deepened our knowledge of algorithms, artificial intelligence and network programming, and was a good exercise in working in a team while competing against other groups.
