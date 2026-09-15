/**
 * SpiderGame.js
 * Core state machine and rules engine for Windows Spider Solitaire.
 */

import { Card, SUITS } from './Card.js';

export const DIFFICULTY = {
  ONE_SUIT: 1,    // 初级 - 单色 (黑桃)
  TWO_SUITS: 2,   // 中级 - 双色 (黑桃 + 红桃)
  FOUR_SUITS: 4   // 高级 - 四色 (黑桃 + 红桃 + 梅花 + 方块)
};

export class SpiderGame {
  constructor(difficulty = DIFFICULTY.ONE_SUIT) {
    this.difficulty = difficulty;
    this.columns = Array.from({ length: 10 }, () => []);
    this.stock = [];
    this.stockDealsLeft = 5;
    this.completedSuits = []; // Array of completed suits (e.g. [SUITS.SPADES, ...])
    this.score = 500;
    this.moves = 0;
    this.undoStack = [];
    this.isWon = false;
    this.listeners = new Set();
    
    this.initGame();
  }

  onChange(listener) {
    this.listeners.add(listener);
    return () => this.listeners.delete(listener);
  }

  notify(event, data) {
    for (const listener of this.listeners) {
      listener(event, data);
    }
  }

  initGame() {
    this.columns = Array.from({ length: 10 }, () => []);
    this.stock = [];
    this.stockDealsLeft = 5;
    this.completedSuits = [];
    this.score = 500;
    this.moves = 0;
    this.undoStack = [];
    this.isWon = false;

    // 1. Build 104-card deck based on difficulty
    const deck = [];
    if (this.difficulty === DIFFICULTY.ONE_SUIT) {
      // 8 decks of Spades
      for (let d = 0; d < 8; d++) {
        for (let rank = 1; rank <= 13; rank++) {
          deck.push(new Card(SUITS.SPADES, rank, false));
        }
      }
    } else if (this.difficulty === DIFFICULTY.TWO_SUITS) {
      // 4 decks of Spades, 4 decks of Hearts
      for (let d = 0; d < 4; d++) {
        for (let rank = 1; rank <= 13; rank++) {
          deck.push(new Card(SUITS.SPADES, rank, false));
          deck.push(new Card(SUITS.HEARTS, rank, false));
        }
      }
    } else {
      // 2 decks each of 4 suits
      for (let d = 0; d < 2; d++) {
        for (let rank = 1; rank <= 13; rank++) {
          deck.push(new Card(SUITS.SPADES, rank, false));
          deck.push(new Card(SUITS.HEARTS, rank, false));
          deck.push(new Card(SUITS.CLUBS, rank, false));
          deck.push(new Card(SUITS.DIAMONDS, rank, false));
        }
      }
    }

    // 2. Shuffle using Fisher-Yates
    for (let i = deck.length - 1; i > 0; i--) {
      const j = Math.floor(Math.random() * (i + 1));
      [deck[i], deck[j]] = [deck[j], deck[i]];
    }

    // 3. Deal 54 cards into 10 columns:
    // Columns 0..3: 6 cards each (top 1 face-up)
    // Columns 4..9: 5 cards each (top 1 face-up)
    for (let c = 0; c < 10; c++) {
      const count = c < 4 ? 6 : 5;
      for (let i = 0; i < count; i++) {
        const card = deck.pop();
        card.faceUp = (i === count - 1);
        this.columns[c].push(card);
      }
    }

    // 4. Remaining 50 cards go to stock (5 deals x 10 cards)
    this.stock = deck;
    this.stockDealsLeft = 5;

    this.notify('init', { difficulty: this.difficulty });
  }

  saveSnapshot() {
    const snapshot = {
      columns: this.columns.map(col => col.map(c => c.clone())),
      stock: this.stock.map(c => c.clone()),
      stockDealsLeft: this.stockDealsLeft,
      completedSuits: [...this.completedSuits],
      score: this.score,
      moves: this.moves,
      isWon: this.isWon
    };
    this.undoStack.push(snapshot);
    if (this.undoStack.length > 50) {
      this.undoStack.shift();
    }
  }

  canUndo() {
    return this.undoStack.length > 0;
  }

  undo() {
    if (!this.canUndo()) return false;
    const snapshot = this.undoStack.pop();
    this.columns = snapshot.columns;
    this.stock = snapshot.stock;
    this.stockDealsLeft = snapshot.stockDealsLeft;
    this.completedSuits = snapshot.completedSuits;
    this.moves++;
    this.score = Math.max(0, snapshot.score - 1);
    this.isWon = snapshot.isWon;

    this.notify('undo', {
      columns: this.columns,
      stockDealsLeft: this.stockDealsLeft,
      completedSuits: this.completedSuits,
      score: this.score,
      moves: this.moves
    });
    return true;
  }

  /**
   * Checks if a card sequence in a column is movable.
   * A sequence is movable iff all cards are face up, consecutive descending, and SAME SUIT.
   */
  isSequenceMovable(colIndex, startIndex) {
    const col = this.columns[colIndex];
    if (!col || startIndex < 0 || startIndex >= col.length) return false;
    if (!col[startIndex].faceUp) return false;

    for (let i = startIndex; i < col.length - 1; i++) {
      const current = col[i];
      const next = col[i + 1];
      if (!next.faceUp) return false;
      if (current.rank !== next.rank + 1) return false;
      if (current.suit !== next.suit) return false; // Must be same suit!
    }
    return true;
  }

  /**
   * Checks if moving cards from fromCol[cardIndex..] to toCol is legal.
   */
  canMove(fromColIndex, cardIndex, toColIndex) {
    if (fromColIndex === toColIndex) return false;
    if (!this.isSequenceMovable(fromColIndex, cardIndex)) return false;

    const targetCol = this.columns[toColIndex];
    if (targetCol.length === 0) {
      // Empty column accepts any movable card or sequence
      return true;
    }

    const movingBottomCard = this.columns[fromColIndex][cardIndex];
    const targetTopCard = targetCol[targetCol.length - 1];

    // Must be exactly 1 rank higher (suit does NOT need to match)
    return targetTopCard.rank === movingBottomCard.rank + 1;
  }

  /**
   * Execute move cards from fromCol[cardIndex..] to toCol.
   */
  moveCards(fromColIndex, cardIndex, toColIndex) {
    if (!this.canMove(fromColIndex, cardIndex, toColIndex)) {
      return { success: false, reason: 'ILLEGAL_MOVE' };
    }

    this.saveSnapshot();

    const fromCol = this.columns[fromColIndex];
    const toCol = this.columns[toColIndex];

    const movingCards = fromCol.splice(cardIndex);
    toCol.push(...movingCards);

    let autoFlipped = false;
    // If fromCol now has a face-down top card, flip it
    if (fromCol.length > 0 && !fromCol[fromCol.length - 1].faceUp) {
      fromCol[fromCol.length - 1].faceUp = true;
      autoFlipped = true;
    }

    this.moves++;
    this.score = Math.max(0, this.score - 1);

    // Check if target column completed a run of 13
    const runResult = this.checkAndCollectRun(toColIndex);

    if (this.completedSuits.length === 8) {
      this.isWon = true;
    }

    const result = {
      success: true,
      fromCol: fromColIndex,
      toCol: toColIndex,
      cardsMoved: movingCards,
      autoFlipped,
      completedRun: runResult.completed,
      completedSuit: runResult.suit,
      isWin: this.isWon,
      score: this.score,
      moves: this.moves
    };

    this.notify('move', result);
    return result;
  }

  /**
   * Check if the column has a completed 13-card sequence (K..A) of same suit at the end.
   */
  checkAndCollectRun(colIndex) {
    const col = this.columns[colIndex];
    if (col.length < 13) return { completed: false };

    // Check last 13 cards: must be K (13) down to A (1), same suit, faceUp
    const last13 = col.slice(col.length - 13);
    const targetSuit = last13[0].suit;

    for (let i = 0; i < 13; i++) {
      const card = last13[i];
      if (!card.faceUp) return { completed: false };
      if (card.suit !== targetSuit) return { completed: false };
      if (card.rank !== 13 - i) return { completed: false };
    }

    // Valid complete run! Remove 13 cards from column
    col.splice(col.length - 13, 13);
    this.completedSuits.push(targetSuit);
    this.score += 100;

    let autoFlipped = false;
    // If remaining column has a face-down top card, flip it
    if (col.length > 0 && !col[col.length - 1].faceUp) {
      col[col.length - 1].faceUp = true;
      autoFlipped = true;
    }

    return {
      completed: true,
      suit: targetSuit,
      autoFlipped
    };
  }

  /**
   * Check if player can deal a round from stock.
   */
  canDeal() {
    if (this.stockDealsLeft <= 0 || this.stock.length < 10) {
      return { canDeal: false, reason: 'NO_CARDS_LEFT' };
    }

    // Windows classic rule: NO column may be empty!
    const hasEmptyColumn = this.columns.some(col => col.length === 0);
    if (hasEmptyColumn) {
      return { canDeal: false, reason: 'EMPTY_COLUMN' };
    }

    return { canDeal: true };
  }

  /**
   * Deal 1 card onto each of the 10 columns.
   */
  dealRound() {
    const check = this.canDeal();
    if (!check.canDeal) {
      return { success: false, reason: check.reason };
    }

    this.saveSnapshot();

    const dealtCards = [];
    for (let c = 0; c < 10; c++) {
      const card = this.stock.pop();
      card.faceUp = true;
      this.columns[c].push(card);
      dealtCards.push({ col: c, card });
    }

    this.stockDealsLeft--;
    this.moves++;
    this.score = Math.max(0, this.score - 1);

    // Check for any newly formed complete runs across all 10 columns
    const completedRuns = [];
    for (let c = 0; c < 10; c++) {
      const run = this.checkAndCollectRun(c);
      if (run.completed) {
        completedRuns.push({ col: c, suit: run.suit });
      }
    }

    if (this.completedSuits.length === 8) {
      this.isWon = true;
    }

    const result = {
      success: true,
      dealtCards,
      stockDealsLeft: this.stockDealsLeft,
      completedRuns,
      isWin: this.isWon,
      score: this.score,
      moves: this.moves
    };

    this.notify('deal', result);
    return result;
  }

  /**
   * Find the best valid move for the Hint system.
   */
  findHint() {
    const validMoves = [];

    for (let fromCol = 0; fromCol < 10; fromCol++) {
      const col = this.columns[fromCol];
      if (col.length === 0) continue;

      // Find all movable sequence starting indices in this column
      for (let idx = col.length - 1; idx >= 0; idx--) {
        if (!col[idx].faceUp) break;
        if (!this.isSequenceMovable(fromCol, idx)) break;

        const movingCard = col[idx];
        const isFullSequenceInCol = (idx === 0 || !col[idx - 1].faceUp);

        for (let toCol = 0; toCol < 10; toCol++) {
          if (fromCol === toCol) continue;
          if (this.canMove(fromCol, idx, toCol)) {
            const targetCol = this.columns[toCol];
            let priority = 0;

            if (targetCol.length === 0) {
              // Moving onto empty column
              if (isFullSequenceInCol && idx === 0) {
                // Moving an entire column from one empty space to another is pointless
                priority = -10;
              } else if (idx > 0 && !col[idx - 1].faceUp) {
                // Moving exposes a face-down card! High value!
                priority = 50;
              } else {
                priority = 10;
              }
            } else {
              const targetTop = targetCol[targetCol.length - 1];
              // Same suit match is much better!
              if (targetTop.suit === movingCard.suit) {
                priority = 100;
              } else {
                priority = 20;
              }

              // Bonus if this move uncovers a face-down card
              if (idx > 0 && !col[idx - 1].faceUp) {
                priority += 40;
              }
            }

            if (priority > 0) {
              validMoves.push({
                fromCol,
                cardIndex: idx,
                toCol,
                priority,
                card: movingCard
              });
            }
          }
        }
      }
    }

    if (validMoves.length === 0) return null;

    // Sort descending by priority
    validMoves.sort((a, b) => b.priority - a.priority);
    return validMoves[0];
  }
}
