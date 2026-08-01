# Ping-Pong

A classic Pong game written in C. Two players control paddles and try to score points by getting the ball past the opponent. The game is played to 21 points.

## Features

- Two game modes
- Simple keyboard controls
- Classic arcade gameplay

## Game Modes

### 1. Sequential Play (`pong.c`)
- The field is redrawn after each move
- You must press a key and then Enter for the next action
- Good for slower, step-by-step play
- Works better in terminals with limited performance

### 2. Interactive Play (`pong_interactive.c`)
- The field updates continuously in real time
- Keystrokes react instantly
- Faster and smoother gameplay
- Feels more like the original arcade game

## Controls

### Player 1 (left paddle)
- `Z` — move down
- `A` — move up
- `Space` — miss step
  
### Player 2 (right paddle)
- `M` — move down
- `K` — move up
- `Space` — miss step

## Installation

Clone the repository:

```bash
git clone https://github.com/UndertakerAI/ping-pong
cd ping-pong/src
```
Build:

Sequential Play:
```bash
gcc pong.c -o pong
```
Interactive Play:
```bash
gcc pong\_interactive.c -o pong -lncurses
```

Run:

```bash
./pong
```
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS%20%7C%20WSL-blue)
