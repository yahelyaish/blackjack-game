# Blackjack Game (C Project)

A terminal-based **Blackjack** game written in **C** for the Embedded C Final Project.  
The game simulates a player versus a computer-controlled dealer, with betting, hand scoring, and standard Blackjack rules.

---

## Features
- Full deck of 52 cards with suits and ranks stored in a single byte (bitwise representation).
- Betting system:
  - Player starts with 1000 cash.
  - Bets in multiples of 10.
  - Pot handling with wins, losses, and ties.
- Gameplay:
  - Initial deal (dealer shows one card, the other hidden).
  - Player options: **Hit** or **Stand**.
  - Dealer draws until at least 17.
  - Automatic detection of **Blackjack**, **Bust**, **Tie**, and winner.
- Linked list representation for deck and hands.
- Dynamic allocation with proper memory cleanup.

---

## How to Compile & Run
Clone the repository and compile with `gcc`:

```bash
git clone https://github.com/your-username/blackjack-c.git
cd blackjack-c
gcc main.c game.c deck.c -o blackjack
./blackjack
