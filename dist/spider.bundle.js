(function() {
  "use strict";

  // --- src/engine/Card.js ---
/**
 * Card.js
 * Represents a single playing card in Spider Solitaire.
 */

const SUITS = {
  CLUBS: 0,     // 梅花 (Black)
  DIAMONDS: 1,  // 方块 (Red)
  HEARTS: 2,    // 红桃 (Red)
  SPADES: 3     // 黑桃 (Black)
};

const SUIT_NAMES = {
  [SUITS.CLUBS]: 'clubs',
  [SUITS.DIAMONDS]: 'diamonds',
  [SUITS.HEARTS]: 'hearts',
  [SUITS.SPADES]: 'spades'
};

const RANK_NAMES = {
  1: 'A', 2: '2', 3: '3', 4: '4', 5: '5', 6: '6',
  7: '7', 8: '8', 9: '9', 10: '10', 11: 'J', 12: 'Q', 13: 'K'
};

let nextCardId = 1;

class Card {
  /**
   * @param {number} suit - 0: Clubs, 1: Diamonds, 2: Hearts, 3: Spades
   * @param {number} rank - 1 (A) to 13 (K)
   * @param {boolean} faceUp - Whether card is face up
   */
  constructor(suit, rank, faceUp = false) {
    this.id = nextCardId++;
    this.suit = suit;
    this.rank = rank;
    this.faceUp = faceUp;
  }

  get isRed() {
    return this.suit === SUITS.DIAMONDS || this.suit === SUITS.HEARTS;
  }

  get suitName() {
    return SUIT_NAMES[this.suit];
  }

  get rankName() {
    return RANK_NAMES[this.rank];
  }

  /**
   * Returns the asset filename for the card face (CARD1.png - CARD52.png).
   * Windows cards.dll formula: 1 + suit * 13 + (rank - 1)
   */
  get faceImage() {
    const cardIndex = 1 + this.suit * 13 + (this.rank - 1);
    return `assets/cards/CARD${cardIndex}.png`;
  }

  get backImage() {
    return 'assets/ui/CARDBACK.png';
  }

  clone() {
    const c = new Card(this.suit, this.rank, this.faceUp);
    c.id = this.id;
    return c;
  }
}


  // --- src/engine/AudioService.js ---
/**
 * AudioService.js
 * 1:1 Windows XP Sound Service for Spider Solitaire
 * Mapped to original PE PlaySoundW IDs:
 * - 0x7c (124): deal / foundation run move
 * - 0x7d (125): card drop / ReleaseCapture
 * - 0x7e (126): hint move found swoop
 * - 0x7f (127): hint move not found / blocked alert
 * - 0x80 (128): card pickup / SetCapture
 * - 0x81 (129): game won fanfare
 */

class AudioService {
  constructor() {
    this.enabled = localStorage.getItem('spider_sound') !== 'false';
    this.sounds = {
      deal: 'assets/sounds/124.wav',
      drop: 'assets/sounds/125.wav',
      hint: 'assets/sounds/126.wav',
      noHint: 'assets/sounds/127.wav',
      grab: 'assets/sounds/128.wav',
      win: 'assets/sounds/129.wav'
    };
    this.preload();
  }

  preload() {
    for (const [key, src] of Object.entries(this.sounds)) {
      const a = new Audio(src);
      a.preload = 'auto';
    }
  }

  play(name) {
    if (!this.enabled) return;
    try {
      const src = this.sounds[name];
      if (!src) return;
      const audio = new Audio(src);
      audio.volume = 0.8;
      audio.play().catch(() => {});
    } catch (e) {}
  }

  toggleSound() {
    this.enabled = !this.enabled;
    localStorage.setItem('spider_sound', this.enabled ? 'true' : 'false');
    return this.enabled;
  }
}


  // --- src/engine/SpiderGame.js ---
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



const DIFFICULTY = {
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

class SpiderGame {
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
    col.splice(col.length - 13, 13);
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
      suit: targetSuit,
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

    // Check for complete runs in all 10 columns
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


  // --- src/ui/Renderer.js ---
/**
 * Renderer.js
 * Handles DOM rendering of the 10 tableau columns, cards, stock, foundation, and status bar.
 * Implements exact 250ms sequential flash hint animation (FUN_01004dfb).
 */

class Renderer {
  constructor(game, container) {
    this.game = game;
    this.container = container;
    
    this.tableauEl = container.querySelector('.tableau-area');
    this.stockEl = container.querySelector('.stock-area');
    this.foundationEl = container.querySelector('.foundation-area');
    this.scoreEl = document.getElementById('status-score');
    this.movesEl = document.getElementById('status-moves');
    
    this.columnEls = [];
    this.initTableauSlots();
  }

  initTableauSlots() {
    this.tableauEl.innerHTML = '';
    this.columnEls = [];
    for (let c = 0; c < 10; c++) {
      const colEl = document.createElement('div');
      colEl.className = 'tableau-column';
      colEl.dataset.col = c;

      const slot = document.createElement('div');
      slot.className = 'column-slot';
      colEl.appendChild(slot);

      this.tableauEl.appendChild(colEl);
      this.columnEls.push(colEl);
    }
  }

  render() {
    this.renderColumns();
    this.renderStock();
    this.renderFoundation();
    this.renderStatusBar();
  }

  renderColumns() {
    const availableHeight = this.tableauEl.clientHeight || 500;
    const cardHeight = parseInt(getComputedStyle(document.documentElement).getPropertyValue('--card-height')) || 96;

    for (let c = 0; c < 10; c++) {
      const colEl = this.columnEls[c];
      const cards = this.game.columns[c];
      
      // Clear previous card elements but retain the empty slot
      colEl.querySelectorAll('.card-element').forEach(el => el.remove());

      if (cards.length === 0) continue;

      let downCount = 0;
      let upCount = 0;
      for (const card of cards) {
        if (card.faceUp) upCount++;
        else downCount++;
      }

      let downStep = 13;
      let upStep = 23;

      // Auto-compress spacing if column overflows
      const requiredHeight = downCount * downStep + upCount * upStep + cardHeight;
      if (requiredHeight > availableHeight - 20 && cards.length > 1) {
        const scale = (availableHeight - cardHeight - 30) / (downCount * downStep + upCount * upStep);
        downStep = Math.max(7, Math.floor(downStep * scale));
        upStep = Math.max(14, Math.floor(upStep * scale));
      }

      let currentTop = 0;
      for (let i = 0; i < cards.length; i++) {
        const card = cards[i];
        const cardEl = document.createElement('div');
        cardEl.className = `card-element ${card.faceUp ? 'face-up' : 'face-down'}`;
        cardEl.dataset.col = c;
        cardEl.dataset.cardIdx = i;
        cardEl.dataset.cardId = card.id;
        cardEl.style.top = `${currentTop}px`;
        cardEl.style.zIndex = i + 1;

        const img = document.createElement('img');
        img.src = card.faceUp ? card.faceImage : card.backImage;
        img.alt = card.faceUp ? `${card.rankName} of ${card.suitName}` : 'Card Back';
        img.draggable = false;
        cardEl.appendChild(img);

        if (card.faceUp && this.game.isSequenceMovable(c, i)) {
          cardEl.classList.add('movable');
        }

        colEl.appendChild(cardEl);
        currentTop += card.faceUp ? upStep : downStep;
      }
    }
  }

  renderStock() {
    this.stockEl.innerHTML = '';
    const dealsLeft = this.game.stockDealsLeft;

    if (dealsLeft <= 0) {
      const emptyHint = document.createElement('div');
      emptyHint.className = 'stock-empty-hint';
      this.stockEl.appendChild(emptyHint);
      return;
    }

    for (let i = 0; i < dealsLeft; i++) {
      const cardEl = document.createElement('div');
      cardEl.className = 'stock-card';
      cardEl.style.left = `${i * 8}px`;
      cardEl.style.zIndex = i + 1;

      const img = document.createElement('img');
      img.src = 'assets/ui/CARDBACK.png';
      img.alt = 'Stock Pile';
      img.draggable = false;
      cardEl.appendChild(img);

      this.stockEl.appendChild(cardEl);
    }
  }

  renderFoundation() {
    this.foundationEl.innerHTML = '';
    const suits = this.game.completedSuits;

    for (let i = 0; i < 8; i++) {
      const slot = document.createElement('div');
      slot.className = 'foundation-slot';

      if (i < suits.length) {
        const suit = suits[i];
        const kingImgIndex = 1 + suit * 13 + 12; // King card index
        const img = document.createElement('img');
        img.src = `assets/cards/CARD${kingImgIndex}.png`;
        img.alt = `Completed Suit ${i + 1}`;
        img.draggable = false;
        slot.appendChild(img);
      }
      this.foundationEl.appendChild(slot);
    }
  }

  renderStatusBar() {
    if (this.scoreEl) this.scoreEl.textContent = `分数: ${this.game.score}`;
    if (this.movesEl) this.movesEl.textContent = `操作: ${this.game.moves}`;
  }

  /**
   * Exact 1:1 InvertRect hint animation from FUN_01004dfb:
   * 1. Invert/highlight source card for 250ms (Sleep 0xfa), un-invert.
   * 2. Invert/highlight destination card/slot for 250ms (Sleep 0xfa), un-invert.
   */
  async playHintAnimation(hint) {
    this.clearHints();
    if (!hint) return;

    const fromColEl = this.columnEls[hint.fromCol];
    const toColEl = this.columnEls[hint.toCol];
    if (!fromColEl || !toColEl) return;

    const sourceCardEl = fromColEl.querySelector(`[data-card-idx="${hint.cardIndex}"]`);
    const targetCards = toColEl.querySelectorAll('.card-element');
    const targetEl = targetCards.length > 0 ? targetCards[targetCards.length - 1] : toColEl.querySelector('.column-slot');

    if (sourceCardEl) {
      sourceCardEl.classList.add('hint-inverted');
      await new Promise(r => setTimeout(r, 250)); // 250ms
      sourceCardEl.classList.remove('hint-inverted');
    }

    if (targetEl) {
      targetEl.classList.add('hint-inverted');
      await new Promise(r => setTimeout(r, 250)); // 250ms
      targetEl.classList.remove('hint-inverted');
    }
  }

  clearHints() {
    this.tableauEl.querySelectorAll('.hint-inverted, .hinted').forEach(el => {
      el.classList.remove('hint-inverted', 'hinted');
    });
  }
}


  // --- src/ui/Dialogs.js ---
/**
 * Dialogs.js
 * 1:1 Windows XP Modal Dialogs for Spider Solitaire
 * Uses exact strings from spri.exe RT_STRING resource block.
 */

class Dialogs {
  constructor() {
    this.overlay = document.getElementById('dialog-overlay');
    this.dialogTitle = document.getElementById('dialog-title');
    this.dialogIcon = document.getElementById('dialog-icon');
    this.dialogContent = document.getElementById('dialog-content');
    this.dialogFooter = document.getElementById('dialog-footer');
    this.closeBtn = document.getElementById('dialog-close-btn');

    this.closeBtn.addEventListener('click', () => this.hide());
  }

  show({ title, icon, contentHtml, buttons }) {
    this.dialogTitle.textContent = title || '蜘蛛纸牌';
    this.dialogIcon.src = icon || 'assets/ui/spider_icon.png';
    this.dialogContent.innerHTML = contentHtml || '';
    this.dialogFooter.innerHTML = '';

    buttons.forEach(btn => {
      const b = document.createElement('button');
      b.className = `xp-btn ${btn.primary ? 'primary' : ''}`;
      b.textContent = btn.text;
      b.addEventListener('click', () => {
        if (btn.onClick) btn.onClick();
        this.hide();
      });
      this.dialogFooter.appendChild(b);
    });

    this.overlay.classList.add('show');
  }

  hide() {
    this.overlay.classList.remove('show');
  }

  showAlert(title, message) {
    this.show({
      title,
      contentHtml: `<div style="padding-top: 4px; font-size: 12px;">${message}</div>`,
      buttons: [
        { text: '确定', primary: true }
      ]
    });
  }

  showConfirm(title, message, onConfirm) {
    this.show({
      title,
      contentHtml: `<div style="padding-top: 4px; font-size: 12px;">${message}</div>`,
      buttons: [
        { text: '是', primary: true, onClick: onConfirm },
        { text: '否' }
      ]
    });
  }

  showDifficulty(currentDiff, onSelect) {
    const html = `
      <div style="display: flex; flex-direction: column; gap: 8px;">
        <div style="font-weight: bold; margin-bottom: 2px;">选择难度级别:</div>
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="radio" name="diff" value="1" ${currentDiff === 1 ? 'checked' : ''}>
          <span>初级: 单色 (黑桃)</span>
        </label>
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="radio" name="diff" value="2" ${currentDiff === 2 ? 'checked' : ''}>
          <span>中级: 双色 (黑桃和红桃)</span>
        </label>
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="radio" name="diff" value="4" ${currentDiff === 4 ? 'checked' : ''}>
          <span>高级: 四色 (全部四种花色)</span>
        </label>
      </div>
    `;

    this.show({
      title: '蜘蛛纸牌难度',
      contentHtml: html,
      buttons: [
        {
          text: '确定',
          primary: true,
          onClick: () => {
            const selected = document.querySelector('input[name="diff"]:checked');
            if (selected && onSelect) {
              onSelect(parseInt(selected.value));
            }
          }
        },
        { text: '取消' }
      ]
    });
  }

  showWin(score, moves, onPlayAgain) {
    const html = `
      <div style="display: flex; flex-direction: column; gap: 8px;">
        <div style="font-weight: bold; font-size: 13px; color: #004e98;">你赢了!</div>
        <div>最终得分: <strong>${score}</strong></div>
        <div>操作次数: <strong>${moves}</strong></div>
        <div style="margin-top: 6px;">是否开始新游戏?</div>
      </div>
    `;

    this.show({
      title: '你赢了!',
      contentHtml: html,
      buttons: [
        { text: '新游戏', primary: true, onClick: onPlayAgain },
        { text: '关闭' }
      ]
    });
  }

  /**
   * Exact Windows XP statistics modal (FUN_01004fa6):
   * Displays stats for current difficulty, with tabs/switch for Easy, Medium, Difficult.
   */
  showStats(allStats, currentDiff, onReset) {
    const diffKeys = { 1: 'Easy', 2: 'Medium', 4: 'Difficult' };
    const diffNames = { 1: '初级 (单色)', 2: '中级 (双色)', 4: '高级 (四色)' };
    
    let activeKey = diffKeys[currentDiff] || 'Easy';
    const s = allStats[activeKey] || {
      highScore: 0, wins: 0, losses: 0, streakWins: 0, streakLosses: 0, streakCurrent: 0, isWinStreak: true
    };

    const total = s.wins + s.losses;
    const rate = total > 0 ? Math.round((s.wins / total) * 100) : 0;
    const currentStatusText = s.isWinStreak ? `${s.streakCurrent} 胜` : `${s.streakCurrent} 负`;

    const html = `
      <div style="display: flex; flex-direction: column; gap: 8px; font-size: 11px;">
        <div style="font-weight: bold; border-bottom: 1px solid #d0d0d0; padding-bottom: 4px;">
          当前难度: ${diffNames[currentDiff]}
        </div>
        <div style="display: flex; justify-content: space-between;"><span>胜:</span> <strong>${s.wins}</strong></div>
        <div style="display: flex; justify-content: space-between;"><span>负:</span> <strong>${s.losses}</strong></div>
        <div style="display: flex; justify-content: space-between;"><span>获胜比率:</span> <strong>${rate} %</strong></div>
        <div style="display: flex; justify-content: space-between;"><span>最高得分:</span> <strong>${s.highScore}</strong></div>
        <div style="display: flex; justify-content: space-between;"><span>最高连胜:</span> <strong>${s.streakWins}</strong></div>
        <div style="display: flex; justify-content: space-between;"><span>最高连负:</span> <strong>${s.streakLosses}</strong></div>
        <div style="display: flex; justify-content: space-between;"><span>当前:</span> <strong>${currentStatusText}</strong></div>
      </div>
    `;

    this.show({
      title: '蜘蛛纸牌统计信息',
      contentHtml: html,
      buttons: [
        {
          text: '重置',
          onClick: () => {
            this.showConfirm('重置统计信息', '是否要重置所有游戏统计数据?', () => {
              if (onReset) onReset();
            });
          }
        },
        { text: '确定', primary: true }
      ]
    });
  }

  showAbout() {
    const html = `
      <div style="display: flex; flex-direction: column; gap: 6px; font-size: 11px;">
        <div style="font-weight: bold; font-size: 13px;">蜘蛛纸牌 (Spider Solitaire)</div>
        <div>Windows XP 原版 1:1 纯静态复刻版</div>
        <div style="color: #444; margin-top: 4px;">(C) 1998-2000 Microsoft Corporation. 保留所有权利。</div>
        <div style="color: #666; margin-top: 4px;">已完整逆向还原核心算法：MS LCG 洗牌、发牌规则、3级提示队列、原版位图与 6 个 WAV 原声。</div>
      </div>
    `;

    this.show({
      title: '关于 蜘蛛纸牌',
      contentHtml: html,
      buttons: [
        { text: '确定', primary: true }
      ]
    });
  }
}


  // --- src/ui/VictoryAnimation.js ---
/**
 * VictoryAnimation.js
 * Renders the iconic Windows Solitaire/Spider bouncing card cascade animation using HTML5 Canvas.
 */

class VictoryAnimation {
  constructor() {
    this.canvas = document.getElementById('victory-canvas');
    this.ctx = this.canvas ? this.canvas.getContext('2d') : null;
    this.isRunning = false;
    this.animationId = null;
    this.cardImages = [];
    this.cards = [];
    this.cardIndex = 0;
    this.spawnTimer = 0;

    this.preloadCardImages();
  }

  preloadCardImages() {
    // Preload several card images for the celebration
    for (let i = 1; i <= 52; i++) {
      const img = new Image();
      img.src = `assets/cards/CARD${i}.png`;
      this.cardImages.push(img);
    }
  }

  start() {
    if (!this.canvas || !this.ctx) return;
    this.isRunning = true;
    this.canvas.style.display = 'block';
    this.resize();

    this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
    this.cards = [];
    this.cardIndex = 0;
    this.spawnTimer = 0;

    window.addEventListener('resize', this.onResize);
    this.loop();
  }

  stop() {
    this.isRunning = false;
    if (this.animationId) {
      cancelAnimationFrame(this.animationId);
      this.animationId = null;
    }
    if (this.canvas) {
      this.canvas.style.display = 'none';
      if (this.ctx) {
        this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
      }
    }
    window.removeEventListener('resize', this.onResize);
  }

  resize() {
    if (!this.canvas) return;
    const parent = this.canvas.parentElement;
    this.canvas.width = parent.clientWidth;
    this.canvas.height = parent.clientHeight;
  }

  onResize = () => {
    if (this.isRunning) this.resize();
  };

  spawnCard() {
    if (this.cardImages.length === 0) return;

    const img = this.cardImages[this.cardIndex % this.cardImages.length];
    this.cardIndex++;

    const cardWidth = 71;
    const cardHeight = 96;

    // Spawn near foundation or random top column
    const startX = Math.random() * (this.canvas.width - cardWidth);
    const startY = 80 + Math.random() * 100;

    this.cards.push({
      img,
      x: startX,
      y: startY,
      vx: (Math.random() - 0.5) * 14,
      vy: -(Math.random() * 6 + 4),
      gravity: 0.45,
      bounce: -0.82,
      width: cardWidth,
      height: cardHeight,
      active: true
    });
  }

  loop = () => {
    if (!this.isRunning) return;

    this.spawnTimer++;
    // Spawn cards progressively
    if (this.spawnTimer % 6 === 0 && this.cards.length < 104) {
      this.spawnCard();
    }

    // Windows classic effect: we don't clear the background, so bouncing cards leave an iconic trail!
    // To keep it smooth, we can leave trails
    for (let i = 0; i < this.cards.length; i++) {
      const card = this.cards[i];
      if (!card.active) continue;

      // Draw card
      if (card.img.complete) {
        this.ctx.drawImage(card.img, Math.round(card.x), Math.round(card.y), card.width, card.height);
      }

      // Physics update
      card.x += card.vx;
      card.y += card.vy;
      card.vy += card.gravity;

      // Floor bounce
      if (card.y + card.height >= this.canvas.height) {
        card.y = this.canvas.height - card.height;
        card.vy *= card.bounce;

        // If bounce energy is depleted, let it roll off screen
        if (Math.abs(card.vy) < 1) {
          card.vy = 0;
        }
      }

      // Walls bounce or roll off
      if (card.x < -card.width || card.x > this.canvas.width + card.width) {
        card.active = false;
      }
    }

    this.animationId = requestAnimationFrame(this.loop);
  };
}


  // --- src/ui/Interaction.js ---
/**
 * Interaction.js
 * Handles mouse and touch drag-and-drop, smart click-to-move, right-click peek, and stock dealing.
 * Matches original Windows XP input messages:
 * - WM_LBUTTONDOWN (FUN_01005753 -> PlaySoundW 0x80 / 128.wav)
 * - WM_LBUTTONUP (FUN_01006732 -> PlaySoundW 0x7d / 125.wav)
 * - WM_RBUTTONDOWN / WM_RBUTTONUP (FUN_01003712 / FUN_010059a6 -> Peek card)
 */

class Interaction {
  constructor(game, renderer, audioService, dialogs, victoryAnim) {
    this.game = game;
    this.renderer = renderer;
    this.audio = audioService;
    this.dialogs = dialogs;
    this.victoryAnim = victoryAnim;

    this.dragLayer = document.getElementById('drag-layer');
    this.activeDrag = null;
    this.peekingEl = null;

    this.bindEvents();
  }

  bindEvents() {
    // 1. Stock pile click
    this.renderer.stockEl.addEventListener('click', () => this.handleStockClick());

    // 2. Prevent right-click context menu on tableau
    this.renderer.tableauEl.addEventListener('contextmenu', (e) => e.preventDefault());

    // 3. Pointer events
    this.renderer.tableauEl.addEventListener('pointerdown', (e) => this.onPointerDown(e));
    window.addEventListener('pointermove', (e) => this.onPointerMove(e));
    window.addEventListener('pointerup', (e) => this.onPointerUp(e));
    window.addEventListener('pointercancel', (e) => this.onPointerCancel(e));
  }

  handleStockClick() {
    const check = this.game.canDeal();
    if (!check.canDeal) {
      if (check.reason === 'EMPTY_COLUMN') {
        this.audio.play('noHint'); // 127.wav error thud
        this.dialogs.showAlert('蜘蛛纸牌', '有空位时不允许发牌。'); // String ID 5
      }
      return;
    }

    const result = this.game.dealRound();
    if (result.success) {
      this.audio.play('deal'); // 124.wav
      if (result.completedRuns.length > 0) {
        setTimeout(() => this.audio.play('deal'), 300); // 124.wav on run collection
      }
      this.renderer.render();

      if (result.isWin) {
        this.handleWin();
      }
    }
  }

  onPointerDown(e) {
    const cardEl = e.target.closest('.card-element');
    if (!cardEl) return;

    // Right-click peek (FUN_01003712)
    if (e.button === 2) {
      this.peekingEl = cardEl;
      cardEl.classList.add('peeking');
      return;
    }

    // Only left click starts drag
    if (e.button !== 0 && e.pointerType === 'mouse') return;

    const fromCol = parseInt(cardEl.dataset.col);
    const cardIdx = parseInt(cardEl.dataset.cardIdx);

    if (!this.game.isSequenceMovable(fromCol, cardIdx)) return;

    const cardRect = cardEl.getBoundingClientRect();
    const colEl = this.renderer.columnEls[fromCol];
    const movingEls = Array.from(colEl.querySelectorAll('.card-element')).filter(
      el => parseInt(el.dataset.cardIdx) >= cardIdx
    );

    this.activeDrag = {
      fromCol,
      cardIdx,
      startX: e.clientX,
      startY: e.clientY,
      grabOffsetX: e.clientX - cardRect.left,
      grabOffsetY: e.clientY - cardRect.top,
      cardWidth: cardRect.width,
      cardHeight: cardRect.height,
      movingEls,
      isDragging: false,
      dragGroup: null
    };

    // spri.exe WM_LBUTTONDOWN -> PlaySoundW 0x80 (128.wav, card pickup click)
    this.audio.play('grab');
    e.preventDefault();
  }

  onPointerMove(e) {
    if (!this.activeDrag) return;

    const dx = e.clientX - this.activeDrag.startX;
    const dy = e.clientY - this.activeDrag.startY;

    if (!this.activeDrag.isDragging) {
      if (Math.hypot(dx, dy) > 5) {
        this.activeDrag.isDragging = true;
        this.initDragGroup(e);
      }
    }

    if (this.activeDrag.isDragging && this.activeDrag.dragGroup) {
      const x = e.clientX - this.activeDrag.grabOffsetX;
      const y = e.clientY - this.activeDrag.grabOffsetY;
      this.activeDrag.dragGroup.style.transform = `translate3d(${x}px, ${y}px, 0)`;
    }
  }

  initDragGroup(e) {
    const dragGroup = document.createElement('div');
    dragGroup.className = 'drag-group';
    dragGroup.style.width = `${this.activeDrag.cardWidth}px`;
    dragGroup.style.height = `${this.activeDrag.cardHeight}px`;

    const firstRect = this.activeDrag.movingEls[0].getBoundingClientRect();

    this.activeDrag.movingEls.forEach((el) => {
      const rect = el.getBoundingClientRect();
      const clone = el.cloneNode(true);
      clone.style.position = 'absolute';
      clone.style.top = `${rect.top - firstRect.top}px`;
      clone.style.left = '0px';
      clone.style.transition = 'none';
      dragGroup.appendChild(clone);
      el.style.opacity = '0';
    });

    const x = e.clientX - this.activeDrag.grabOffsetX;
    const y = e.clientY - this.activeDrag.grabOffsetY;
    dragGroup.style.transform = `translate3d(${x}px, ${y}px, 0)`;

    this.dragLayer.appendChild(dragGroup);
    this.activeDrag.dragGroup = dragGroup;
  }

  onPointerUp(e) {
    // Release right click peek (FUN_010059a6)
    if (this.peekingEl) {
      this.peekingEl.classList.remove('peeking');
      this.peekingEl = null;
    }

    if (!this.activeDrag) return;

    const { fromCol, cardIdx, isDragging, dragGroup } = this.activeDrag;

    if (!isDragging) {
      // Smart Click-to-Move
      this.handleSmartClickMove(fromCol, cardIdx);
      this.activeDrag = null;
      return;
    }

    const targetCol = this.findDropTarget(e.clientX, e.clientY);

    if (targetCol !== null && this.game.canMove(fromCol, cardIdx, targetCol)) {
      const res = this.game.moveCards(fromCol, cardIdx, targetCol);
      if (res.success) {
        // spri.exe WM_LBUTTONUP -> PlaySoundW 0x7d (125.wav, drop snap)
        this.audio.play('drop');
        if (res.completedRun) {
          setTimeout(() => this.audio.play('deal'), 200); // 124.wav on run cleared
        }
        if (dragGroup) dragGroup.remove();
        this.renderer.render();

        if (res.isWin) {
          this.handleWin();
        }
      }
    } else {
      this.cancelDrag();
    }

    this.activeDrag = null;
  }

  onPointerCancel() {
    if (this.peekingEl) {
      this.peekingEl.classList.remove('peeking');
      this.peekingEl = null;
    }
    if (this.activeDrag) {
      this.cancelDrag();
      this.activeDrag = null;
    }
  }

  cancelDrag() {
    if (this.activeDrag && this.activeDrag.dragGroup) {
      this.activeDrag.dragGroup.remove();
      this.activeDrag.movingEls.forEach(el => el.style.opacity = '1');
    }
  }

  findDropTarget(clientX, clientY) {
    let bestCol = null;
    let minDistance = Infinity;

    for (let c = 0; c < 10; c++) {
      const colEl = this.renderer.columnEls[c];
      const rect = colEl.getBoundingClientRect();

      if (clientX >= rect.left - 10 && clientX <= rect.right + 10) {
        if (clientY >= rect.top - 20 && clientY <= rect.bottom + 100) {
          return c;
        }
      }

      const colCenterX = rect.left + rect.width / 2;
      const dist = Math.abs(clientX - colCenterX);
      if (dist < minDistance && dist < rect.width * 1.2) {
        minDistance = dist;
        bestCol = c;
      }
    }

    return bestCol;
  }

  handleSmartClickMove(fromCol, cardIdx) {
    const movingCard = this.game.columns[fromCol][cardIdx];
    let bestTarget = null;
    let highestPriority = -1;

    for (let toCol = 0; toCol < 10; toCol++) {
      if (fromCol === toCol) continue;
      if (this.game.canMove(fromCol, cardIdx, toCol)) {
        const targetCol = this.game.columns[toCol];
        let priority = 0;

        if (targetCol.length > 0) {
          const targetTop = targetCol[targetCol.length - 1];
          if (targetTop.suit === movingCard.suit) {
            priority = 100; // Same suit
          } else {
            priority = 50;  // Different suit
          }
        } else {
          if (cardIdx > 0 && !this.game.columns[fromCol][cardIdx - 1].faceUp) {
            priority = 30;
          } else {
            priority = 10;
          }
        }

        if (priority > highestPriority) {
          highestPriority = priority;
          bestTarget = toCol;
        }
      }
    }

    if (bestTarget !== null) {
      const res = this.game.moveCards(fromCol, cardIdx, bestTarget);
      if (res.success) {
        this.audio.play('drop');
        if (res.completedRun) {
          setTimeout(() => this.audio.play('deal'), 200);
        }
        this.renderer.render();

        if (res.isWin) {
          this.handleWin();
        }
      }
    }
  }

  handleWin() {
    this.audio.play('win'); // 129.wav
    this.victoryAnim.start();
    setTimeout(() => {
      this.dialogs.showWin(this.game.score, this.game.moves, () => {
        this.victoryAnim.stop();
        this.game.initGame();
        this.renderer.render();
      });
    }, 2500);
  }
}


  // --- src/main.js ---
/**
 * main.js
 * Application entry point: connects 1:1 reverse-engineered game engine, audio, UI,
 * per-difficulty statistics, and keyboard shortcuts.
 */








class App {
  constructor() {
    this.stats = this.loadStats();
    this.audio = new AudioService();
    this.dialogs = new Dialogs();
    this.victoryAnim = new VictoryAnimation();

    const savedDiff = parseInt(localStorage.getItem('spider_difficulty')) || DIFFICULTY.ONE_SUIT;
    this.game = new SpiderGame(savedDiff);

    const container = document.getElementById('game-container');
    this.renderer = new Renderer(this.game, container);
    this.interaction = new Interaction(this.game, this.renderer, this.audio, this.dialogs, this.victoryAnim);

    this.bindWindowControls();
    this.bindMenu();
    this.bindShortcuts();

    // Hook game events
    this.game.onChange((event, data) => {
      if (event === 'undo') {
        this.renderer.render();
      } else if (event === 'move' || event === 'deal') {
        if (data.isWin) {
          this.recordGameResult(true, this.game.score);
        }
      }
    });

    this.renderer.render();
  }

  getDiffKey(diff = this.game.difficulty) {
    if (diff === DIFFICULTY.ONE_SUIT) return 'Easy';
    if (diff === DIFFICULTY.TWO_SUITS) return 'Medium';
    return 'Difficult';
  }

  loadStats() {
    try {
      const data = localStorage.getItem('spider_registry_stats');
      if (data) return JSON.parse(data);
    } catch (e) {}

    const defaultDiff = () => ({
      highScore: 0,
      wins: 0,
      losses: 0,
      streakWins: 0,
      streakLosses: 0,
      streakCurrent: 0,
      isWinStreak: true
    });

    return {
      Easy: defaultDiff(),
      Medium: defaultDiff(),
      Difficult: defaultDiff()
    };
  }

  saveStats() {
    localStorage.setItem('spider_registry_stats', JSON.stringify(this.stats));
  }

  recordGameResult(isWin, score = 0) {
    const key = this.getDiffKey();
    const s = this.stats[key];

    if (isWin) {
      s.wins++;
      if (s.isWinStreak) {
        s.streakCurrent++;
      } else {
        s.isWinStreak = true;
        s.streakCurrent = 1;
      }
      if (s.streakCurrent > s.streakWins) {
        s.streakWins = s.streakCurrent;
      }
      if (score > s.highScore) {
        s.highScore = score;
      }
    } else {
      s.losses++;
      if (!s.isWinStreak) {
        s.streakCurrent++;
      } else {
        s.isWinStreak = false;
        s.streakCurrent = 1;
      }
      if (s.streakCurrent > s.streakLosses) {
        s.streakLosses = s.streakCurrent;
      }
    }

    this.saveStats();
  }

  startNewGame(diff = null) {
    if (diff !== null) {
      this.game.difficulty = diff;
      localStorage.setItem('spider_difficulty', diff);
    }

    this.game.initGame();
    this.renderer.render();
    this.audio.play('deal');
  }

  bindWindowControls() {
    const btnClose = document.getElementById('btn-close');
    const btnMax = document.getElementById('btn-max');
    const btnMin = document.getElementById('btn-min');
    const windowEl = document.querySelector('.xp-window');

    if (btnMin) {
      btnMin.addEventListener('click', () => {
        windowEl.classList.toggle('minimized');
      });
    }

    if (btnMax) {
      btnMax.addEventListener('click', () => {
        if (!document.fullscreenElement) {
          document.documentElement.requestFullscreen().catch(() => {});
        } else {
          document.exitFullscreen().catch(() => {});
        }
      });
    }

    if (btnClose) {
      btnClose.addEventListener('click', () => {
        this.dialogs.showConfirm('退出', '是否退出蜘蛛纸牌?', () => {
          window.close();
        });
      });
    }
  }

  bindMenu() {
    const menuItems = document.querySelectorAll('.xp-menu-item');
    
    menuItems.forEach(item => {
      item.addEventListener('click', (e) => {
        e.stopPropagation();
        const isActive = item.classList.contains('active');
        menuItems.forEach(m => m.classList.remove('active'));
        if (!isActive) item.classList.add('active');
      });
    });

    window.addEventListener('click', () => {
      menuItems.forEach(m => m.classList.remove('active'));
    });

    const actionMap = {
      // String ID 3: "是否开始新游戏?"
      'new-game': () => {
        if (this.game.moves > 0 && !this.game.isWon) {
          this.dialogs.showConfirm('新游戏', '是否开始新游戏?', () => {
            this.recordGameResult(false);
            this.startNewGame();
          });
        } else {
          this.startNewGame();
        }
      },
      // String ID 4: "是否从头开始这次游戏?"
      'restart': () => {
        this.dialogs.showConfirm('重新开始', '是否从头开始这次游戏?', () => {
          this.recordGameResult(false);
          this.game.initGame();
          this.renderer.render();
          this.audio.play('deal');
        });
      },
      'undo': () => {
        if (this.game.canUndo()) {
          this.game.undo();
          this.audio.play('drop');
        }
      },
      // FUN_01004dfb: Exact Hint logic & cycling
      'hint': async () => {
        const hint = this.game.getNextHint();
        if (hint) {
          this.audio.play('hint'); // 126.wav
          await this.renderer.playHintAnimation(hint);
        } else {
          this.audio.play('noHint'); // 127.wav
          this.dialogs.showAlert('提示', '没有可用的移动，请点击右下角发牌区发新牌。');
        }
      },
      'deal': () => {
        this.interaction.handleStockClick();
      },
      'difficulty': () => {
        this.dialogs.showDifficulty(this.game.difficulty, (newDiff) => {
          if (this.game.moves > 0 && !this.game.isWon) {
            this.recordGameResult(false);
          }
          this.startNewGame(newDiff);
        });
      },
      'stats': () => {
        this.dialogs.showStats(this.stats, this.game.difficulty, () => {
          const key = this.getDiffKey();
          this.stats[key] = {
            highScore: 0, wins: 0, losses: 0, streakWins: 0, streakLosses: 0, streakCurrent: 0, isWinStreak: true
          };
          this.saveStats();
          this.dialogs.hide();
        });
      },
      'sound-toggle': () => {
        const enabled = this.audio.toggleSound();
        const soundLabel = document.getElementById('menu-sound-check');
        if (soundLabel) soundLabel.textContent = enabled ? '✓ ' : '   ';
      },
      'rules': () => {
        this.dialogs.showAlert(
          '蜘蛛纸牌游戏规则',
          '目标是以最少的操作次数将所有牌按花色从 K 到 A 整理成组并消除。<br><br>' +
          '• 单色模式下所有牌为黑桃；双色为黑桃和红桃；四色包含所有四种花色。<br>' +
          '• 只有同花色的连续牌组才可以一起移动。<br>' +
          '• 任何牌或牌列都可移到空列上。<br>' +
          '• 当工作区所有 10 列均有牌时，方可从发牌区发新牌。'
        );
      },
      'about': () => {
        this.dialogs.showAbout();
      }
    };

    document.querySelectorAll('[data-action]').forEach(el => {
      el.addEventListener('click', (e) => {
        e.stopPropagation();
        menuItems.forEach(m => m.classList.remove('active'));
        const action = el.dataset.action;
        if (actionMap[action]) actionMap[action]();
      });
    });
  }

  bindShortcuts() {
    window.addEventListener('keydown', async (e) => {
      // F2: New Game
      if (e.key === 'F2') {
        e.preventDefault();
        const action = document.querySelector('[data-action="new-game"]');
        if (action) action.click();
      }
      // Ctrl+Z / Cmd+Z: Undo
      else if ((e.ctrlKey || e.metaKey) && (e.key === 'z' || e.key === 'Z')) {
        e.preventDefault();
        if (this.game.canUndo()) {
          this.game.undo();
          this.audio.play('drop');
        }
      }
      // H / M: Hint
      else if (e.key === 'h' || e.key === 'H' || e.key === 'm' || e.key === 'M') {
        e.preventDefault();
        const hint = this.game.getNextHint();
        if (hint) {
          this.audio.play('hint');
          await this.renderer.playHintAnimation(hint);
        } else {
          this.audio.play('noHint');
          this.dialogs.showAlert('提示', '没有可用的移动，请点击发牌区发新牌。');
        }
      }
      // D: Deal
      else if (e.key === 'd' || e.key === 'D') {
        e.preventDefault();
        this.interaction.handleStockClick();
      }
      // F4: Stats
      else if (e.key === 'F4') {
        e.preventDefault();
        const action = document.querySelector('[data-action="stats"]');
        if (action) action.click();
      }
      // Escape: Boss Key (FUN_01006db6) or close dialog
      else if (e.key === 'Escape') {
        if (this.dialogs.overlay.classList.contains('show')) {
          this.dialogs.hide();
        } else {
          // Classic Windows XP "Boss Key" minimize
          document.querySelector('.xp-window').classList.toggle('minimized');
        }
      }
    });
  }
}

document.addEventListener('DOMContentLoaded', () => {
  window.spiderApp = new App();
});


})();