/**
 * SpiderGame.js
 * 1:1 Exact Re-implementation of Windows XP Spider Solitaire (spri.exe)
 * Reverse-engineered from binary functions:
 * - FUN_01005afb (Game initialization, row-by-row deal)
 * - FUN_0100746e (Deck generation, suit translation & LCG shuffle)
 * - FUN_0100936b (Microsoft CRT rand/srand LCG formula)
 * - FUN_01004c2d (Move execution, score decrement, auto-flip)
 * - FUN_010064d5 (Run completion, foundation placement, +100 score)
 * - FUN_010069b2 (Stock dealing, empty column block)
 * - FUN_01003a90, FUN_0100315b, FUN_010031ab (Exact 3-level Hint system & cycle queue)
 * - FUN_01003596 (Score clamping & per-difficulty high score)
 */

import { Card, SUITS } from './Card.js';

export const DIFFICULTY = {
  ONE_SUIT: 1,    // 初级 - Easy (8 sets of Spades)
  TWO_SUITS: 2,   // 中级 - Medium (4 sets of Spades + 4 sets of Hearts)
  FOUR_SUITS: 4   // 高级 - Difficult (2 sets each of 4 suits)
};

/**
 * Microsoft Visual C++ CRT LCG Pseudo-Random Number Generator
 * formula: seed = (seed * 214013 + 2531011) & 0xFFFFFFFF; rand = (seed >> 16) & 0x7FFF;
 */
class MS_LCG {
  constructor(seed = Date.now() & 0xFFFFFFFF) {
    this.seed = seed >>> 0;
  }

  srand(seed) {
    this.seed = seed >>> 0;
  }

  rand() {
    this.seed = (Math.imul(this.seed, 214013) + 2531011) >>> 0;
    return (this.seed >>> 16) & 0x7FFF;
  }
}

export class SpiderGame {
  constructor(difficulty = DIFFICULTY.ONE_SUIT, seed = null) {
    this.difficulty = difficulty;
    this.rng = new MS_LCG(seed !== null ? seed : (Date.now() & 0xFFFFFFFF));
    this.columns = Array.from({ length: 10 }, () => []);
    this.stock = [];
    this.stockDealsLeft = 5;
    this.completedSuits = [];
    this.score = 500;
    this.moves = 0;
    this.undoStack = [];
    this.isWon = false;
    
    // Hint queue state (FUN_01003a90 / FUN_0100313c)
    this.hintQueue = [];
    this.hintIndex = 0;
    this.hintNeedsUpdate = true;

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

  /**
   * FUN_0100746e & FUN_01005afb:
   * Recreates deck generation, difficulty suit mapping and row-by-row card dealing.
   */
  initGame() {
    this.columns = Array.from({ length: 10 }, () => []);
    this.stock = [];
    this.stockDealsLeft = 5;
    this.completedSuits = [];
    this.score = 500;
    this.moves = 0;
    this.undoStack = [];
    this.isWon = false;
    this.hintQueue = [];
    this.hintIndex = 0;
    this.hintNeedsUpdate = true;

    // 1. Generate 104 cards with exact MS suit mapping
    // Total decks = 2 standard 52-card sets = 104 cards
    const deck = [];
    for (let deckNum = 0; deckNum < 2; deckNum++) {
      for (let suitIdx = 0; suitIdx < 4; suitIdx++) {
        for (let rank = 1; rank <= 13; rank++) {
          let finalSuit = suitIdx;
          if (this.difficulty === DIFFICULTY.ONE_SUIT) {
            finalSuit = SUITS.SPADES; // All 104 cards become Spades
          } else if (this.difficulty === DIFFICULTY.TWO_SUITS) {
            // In spri.exe FUN_0100746e: 0 -> 3 (Spades), 1 -> 2 (Hearts)
            finalSuit = (suitIdx % 2 === 0) ? SUITS.SPADES : SUITS.HEARTS;
          }
          deck.push(new Card(finalSuit, rank, false));
        }
      }
    }

    // 2. Shuffle using spri.exe exact slot-picking algorithm (FUN_0100746e)
    const shuffledDeck = new Array(104);
    const occupied = new Array(104).fill(false);
    for (let i = 0; i < 104; i++) {
      let slot;
      do {
        slot = this.rng.rand() % 104;
      } while (occupied[slot]);
      occupied[slot] = true;
      shuffledDeck[slot] = deck[i];
    }

    // 3. Exact row-by-row dealing algorithm (FUN_01005afb):
    // Rows 0 to 3: all 10 columns receive 1 face-down card each (40 cards)
    // Row 4: columns 0 to 3 receive 1 face-down card each (4 cards)
    // Row 5: all 10 columns receive 1 face-up card each (10 cards)
    let cardPointer = 0;
    // Rows 0..4
    for (let row = 0; row < 5; row++) {
      for (let col = 0; col < 10; col++) {
        if (row !== 4 || col < 4) {
          const c = shuffledDeck[cardPointer++];
          c.faceUp = false;
          this.columns[col].push(c);
        }
      }
    }

    // Top face-up cards for all 10 columns
    for (let col = 0; col < 10; col++) {
      const c = shuffledDeck[cardPointer++];
      c.faceUp = true;
      this.columns[col].push(c);
    }

    // Remaining 50 cards go to the stock (5 deals x 10 cards)
    this.stock = shuffledDeck.slice(cardPointer);
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
    if (this.undoStack.length > 100) {
      this.undoStack.shift();
    }
  }

  canUndo() {
    return this.undoStack.length > 0;
  }

  /**
   * FUN_01004ef8 (Undo menu command 0x9c4a):
   * Moves cards back, moves++, and decrements score by 1 (minimum 0).
   */
  undo() {
    if (!this.canUndo()) return false;
    const snapshot = this.undoStack.pop();
    this.columns = snapshot.columns;
    this.stock = snapshot.stock;
    this.stockDealsLeft = snapshot.stockDealsLeft;
    this.completedSuits = snapshot.completedSuits;
    this.isWon = snapshot.isWon;

    // spri.exe increments operations and subtracts 1 from score on undo!
    this.moves++;
    this.score = Math.max(0, this.score - 1);
    this.hintNeedsUpdate = true;

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
   * FUN_0100396e: Checks if sequence is movable.
   * All cards from startIndex to end must be face-up, strictly descending rank by 1, AND SAME SUIT.
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
      if (current.suit !== next.suit) return false;
    }
    return true;
  }

  /**
   * FUN_01003a06: Checks if moving fromCol[startIndex..] onto toCol is legal.
   */
  canMove(fromColIndex, startIndex, toColIndex) {
    if (fromColIndex === toColIndex) return false;
    if (!this.isSequenceMovable(fromColIndex, startIndex)) return false;

    const targetCol = this.columns[toColIndex];
    if (targetCol.length === 0) return true; // Empty column accepts anything movable

    const movingBottomCard = this.columns[fromColIndex][startIndex];
    const targetTopCard = targetCol[targetCol.length - 1];

    // Must be exactly 1 rank higher (suit does not need to match to land)
    return targetTopCard.rank === movingBottomCard.rank + 1;
  }

  /**
   * FUN_01004c2d: Executes move.
   */
  moveCards(fromColIndex, startIndex, toColIndex) {
    if (!this.canMove(fromColIndex, startIndex, toColIndex)) {
      return { success: false, reason: 'ILLEGAL_MOVE' };
    }

    this.saveSnapshot();

    const fromCol = this.columns[fromColIndex];
    const toCol = this.columns[toColIndex];

    const movingCards = fromCol.splice(startIndex);
    toCol.push(...movingCards);

    let autoFlipped = false;
    // If fromCol now has a face-down top card, flip it
    if (fromCol.length > 0 && !fromCol[fromCol.length - 1].faceUp) {
      fromCol[fromCol.length - 1].faceUp = true;
      autoFlipped = true;
    }

    this.moves++;
    this.score = Math.max(0, this.score - 1); // FUN_01003596(this, -1)
    this.hintNeedsUpdate = true;

    // Check all columns for any completed run of 13 cards (FUN_010064d5)
    const completedRuns = [];
    for (let c = 0; c < 10; c++) {
      const runResult = this.checkAndCollectRun(c);
      if (runResult.completed) {
        completedRuns.push(runResult);
      }
    }

    if (this.completedSuits.length === 8) {
      this.isWon = true;
    }

    const result = {
      success: true,
      fromCol: fromColIndex,
      toCol: toColIndex,
      cardsMoved: movingCards,
      autoFlipped,
      completedRuns,
      completedRun: completedRuns.length > 0,
      completedSuit: completedRuns.length > 0 ? completedRuns[0].suit : null,
      isWin: this.isWon,
      score: this.score,
      moves: this.moves
    };

    this.notify('move', result);
    return result;
  }

  /**
   * FUN_010064d5: Check and collect complete 13-card suit sequence (K..A).
   */
  checkAndCollectRun(colIndex) {
    const col = this.columns[colIndex];
    if (col.length < 13) return { completed: false };

    const last13 = col.slice(col.length - 13);
    const targetSuit = last13[0].suit;

    for (let i = 0; i < 13; i++) {
      const card = last13[i];
      if (!card.faceUp || card.suit !== targetSuit || card.rank !== 13 - i) {
        return { completed: false };
      }
    }

    // Complete run of 13 found! Remove cards from column
    const removedCards = col.splice(col.length - 13, 13);
    this.completedSuits.push(targetSuit);
    this.score += 100; // FUN_01003596(this, 100)
    this.hintNeedsUpdate = true;

    let autoFlipped = false;
    if (col.length > 0 && !col[col.length - 1].faceUp) {
      col[col.length - 1].faceUp = true;
      autoFlipped = true;
    }

    return {
      completed: true,
      colIndex,
      suit: targetSuit,
      cards: removedCards,
      autoFlipped
    };
  }

  /**
   * FUN_010069b2: Deal cards from stock.
   */
  canDeal() {
    if (this.stockDealsLeft <= 0 || this.stock.length < 10) {
      return { canDeal: false, reason: 'NO_CARDS_LEFT' };
    }

    // In spri.exe FUN_01007dd3: check if any column is empty
    const hasEmptyColumn = this.columns.some(col => col.length === 0);
    if (hasEmptyColumn) {
      return { canDeal: false, reason: 'EMPTY_COLUMN' }; // String ID 5
    }

    return { canDeal: true };
  }

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
    this.hintNeedsUpdate = true;

    // Check for complete runs in all 10 columns (FUN_010069b2)
    const completedRuns = [];
    for (let c = 0; c < 10; c++) {
      const run = this.checkAndCollectRun(c);
      if (run.completed) {
        completedRuns.push(run);
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
      completedRun: completedRuns.length > 0,
      completedSuit: completedRuns.length > 0 ? completedRuns[0].suit : null,
      isWin: this.isWon,
      score: this.score,
      moves: this.moves
    };

    this.notify('deal', result);
    return result;
  }

  debugTriggerWin() {
    this.completedSuits = [0, 1, 2, 3, 0, 1, 2, 3];
    this.isWon = true;
    for (let c = 0; c < 10; c++) this.columns[c] = [];
    this.stock = [];
    this.stockDealsLeft = 0;
    this.notify('move', {
      success: true,
      completedRuns: [],
      completedRun: false,
      isWin: true,
      score: this.score,
      moves: this.moves
    });
    return true;
  }

  /**
   * FUN_01003a90, FUN_0100315b, FUN_010031ab, FUN_0100313c:
   * Exact reverse-engineered 3-level Hint calculation & cycling queue.
   * Priority:
   * - 3: Same-suit move onto another card
   * - 2: Different-suit move onto another card
   * - 1: Move onto empty column
   */
  updateHintQueue() {
    this.hintQueue = [];
    this.hintIndex = 0;

    for (let fromCol = 0; fromCol < 10; fromCol++) {
      const col = this.columns[fromCol];
      if (col.length === 0) continue;

      // Find movable sequence start in this column
      for (let idx = col.length - 1; idx >= 0; idx--) {
        if (!col[idx].faceUp) break;
        if (!this.isSequenceMovable(fromCol, idx)) break;

        const movingCard = col[idx];
        const isFullFaceUpRun = (idx === 0 || !col[idx - 1].faceUp);

        for (let toCol = 0; toCol < 10; toCol++) {
          if (fromCol === toCol) continue;
          if (this.canMove(fromCol, idx, toCol)) {
            const targetCol = this.columns[toCol];
            let priority;

            if (targetCol.length === 0) {
              // Only suggest the first empty column to avoid redundant hints
              const firstEmpty = this.columns.findIndex(c => c.length === 0);
              if (firstEmpty !== -1 && toCol !== firstEmpty) continue;
              // If moving an entire face-up column onto an empty column with nothing revealed, skip
              if (isFullFaceUpRun && idx === 0) continue;
              priority = 1;
            } else {
              const targetTop = targetCol[targetCol.length - 1];
              // Priority 3: same suit; Priority 2: diff suit
              priority = (targetTop.suit === movingCard.suit) ? 3 : 2;
            }

            this.hintQueue.push({
              fromCol,
              cardIndex: idx,
              toCol,
              targetCardIndex: targetCol.length > 0 ? targetCol.length - 1 : 0,
              priority,
              card: movingCard
            });
          }
        }
      }
    }

    // Sort descending by priority (insertion sort from FUN_010031ab)
    this.hintQueue.sort((a, b) => b.priority - a.priority);
    this.hintNeedsUpdate = false;
  }

  getNextHint() {
    if (this.hintNeedsUpdate) {
      this.updateHintQueue();
    }
    if (this.hintQueue.length === 0) return null;

    const hint = this.hintQueue[this.hintIndex];
    this.hintIndex = (this.hintIndex + 1) % this.hintQueue.length; // Cycle through
    return hint;
  }
}
