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

      // Windows XP FUN_01005ca9: face-down cards step is 9px (7-9px visible strip)
      let downStep = 9;
      let upStep = 22;

      // Auto-compress spacing if column overflows
      const requiredHeight = downCount * downStep + upCount * upStep + cardHeight;
      if (requiredHeight > availableHeight - 20 && cards.length > 1) {
        const scale = (availableHeight - cardHeight - 30) / (downCount * downStep + upCount * upStep);
        downStep = Math.max(5, Math.floor(downStep * scale));
        upStep = Math.max(12, Math.floor(upStep * scale));
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
      cardEl.style.left = `${i * 12}px`; // 12px step (FUN_01002af5)
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

    for (let i = 0; i < suits.length; i++) {
      const suit = suits[i];
      const slot = document.createElement('div');
      slot.className = 'foundation-slot';
      slot.style.left = `${i * 12}px`; // 12px step (FUN_010038c3)
      slot.style.zIndex = i + 1;

      const kingImgIndex = 1 + suit * 13 + 12; // King card index
      const img = document.createElement('img');
      img.src = `assets/cards/CARD${kingImgIndex}.png`;
      img.alt = `Completed Suit ${i + 1}`;
      img.draggable = false;
      slot.appendChild(img);

      this.foundationEl.appendChild(slot);
    }
  }

  renderStatusBar() {
    if (this.scoreEl) this.scoreEl.textContent = this.game.score;
    if (this.movesEl) this.movesEl.textContent = this.game.moves;
  }

  /**
   * Exact 1:1 InvertRect hint animation from FUN_01004dfb:
   * 1. Invert/highlight moving card sequence for 250ms (Sleep 0xfa), un-invert.
   * 2. Invert/highlight destination card/slot for 250ms (Sleep 0xfa), un-invert.
   */
  async playHintAnimation(hint) {
    this.clearHints();
    if (!hint) return;

    const fromColEl = this.columnEls[hint.fromCol];
    const toColEl = this.columnEls[hint.toCol];
    if (!fromColEl || !toColEl) return;

    // Invert ALL cards in the moving sequence from fromCol (FUN_01002cf0)
    const sourceCardEls = Array.from(fromColEl.querySelectorAll('.card-element')).filter(
      el => parseInt(el.dataset.cardIdx) >= hint.cardIndex
    );
    const targetCards = toColEl.querySelectorAll('.card-element');
    const targetEl = targetCards.length > 0 ? targetCards[targetCards.length - 1] : toColEl.querySelector('.column-slot');

    if (sourceCardEls.length > 0) {
      sourceCardEls.forEach(el => el.classList.add('hint-inverted'));
      await new Promise(r => setTimeout(r, 250)); // 250ms
      sourceCardEls.forEach(el => el.classList.remove('hint-inverted'));
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
 * 1:1 Pixel-Perfect Windows XP Dialog Templates (RT_DIALOG: 107, 117, 118, 119, 130)
 * Reconstructed directly from PE DLGTEMPLATEEX structures in spri.exe.
 */

class Dialogs {
  constructor() {
    this.overlay = document.getElementById('dialog-overlay');
    this.dialogTitle = document.getElementById('dialog-title');
    this.dialogContent = document.getElementById('dialog-content');
    this.dialogFooter = document.getElementById('dialog-footer');
    this.closeBtn = document.getElementById('dialog-close-btn');

    this.closeBtn.addEventListener('click', () => this.hide());
  }

  show({ title, width, contentHtml, buttons }) {
    this.dialogTitle.textContent = title || '蜘蛛纸牌';
    const box = document.getElementById('xp-dialog-box');
    if (box) {
      box.style.width = width ? `${width}px` : 'auto';
    }
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
      width: 280,
      contentHtml: `<div style="padding: 6px 0; font-size: 12px;">${message}</div>`,
      buttons: [
        { text: '确定', primary: true }
      ]
    });
  }

  showConfirm(title, message, onConfirm) {
    this.show({
      title,
      width: 280,
      contentHtml: `<div style="padding: 6px 0; font-size: 12px;">${message}</div>`,
      buttons: [
        { text: '是(&Y)', primary: true, onClick: onConfirm },
        { text: '否(&N)' }
      ]
    });
  }

  /**
   * DIALOG 119: 难易级别 (Size: 197 x 109, Font: 宋体 9pt)
   * Items: 1008 (初级单色), 1009 (中级双色), 1010 (高级四色) with suit icons
   */
  showDifficulty(currentDiff, onSelect) {
    const html = `
      <div style="font-size: 12px; color: #000000; padding: 2px 0;">
        <div style="margin-bottom: 10px;">请选择游戏的难易级别:</div>
        <div style="display: flex; flex-direction: column; gap: 8px;">
          <!-- 初级: 单色 (黑桃 123) -->
          <label style="display: flex; align-items: center; gap: 8px; cursor: pointer;">
            <input type="radio" name="diff_choice" value="1" ${currentDiff === 1 ? 'checked' : ''}>
            <div style="display: flex; align-items: center; gap: 2px;">
              <img src="assets/ui/icon_123.png" style="width:16px;height:16px;" alt="黑桃">
            </div>
            <span>初级(&E): 单色</span>
          </label>

          <!-- 中级: 双色 (黑桃 123, 红桃 122) -->
          <label style="display: flex; align-items: center; gap: 8px; cursor: pointer;">
            <input type="radio" name="diff_choice" value="2" ${currentDiff === 2 ? 'checked' : ''}>
            <div style="display: flex; align-items: center; gap: 2px;">
              <img src="assets/ui/icon_123.png" style="width:16px;height:16px;" alt="黑桃">
              <img src="assets/ui/icon_122.png" style="width:16px;height:16px;" alt="红桃">
            </div>
            <span>中级(&M): 双色</span>
          </label>

          <!-- 高级: 四色 (黑桃 123, 红桃 122, 梅花 120, 方块 121) -->
          <label style="display: flex; align-items: center; gap: 8px; cursor: pointer;">
            <input type="radio" name="diff_choice" value="4" ${currentDiff === 4 ? 'checked' : ''}>
            <div style="display: flex; align-items: center; gap: 2px;">
              <img src="assets/ui/icon_123.png" style="width:16px;height:16px;" alt="黑桃">
              <img src="assets/ui/icon_122.png" style="width:16px;height:16px;" alt="红桃">
              <img src="assets/ui/icon_120.png" style="width:16px;height:16px;" alt="梅花">
              <img src="assets/ui/icon_121.png" style="width:16px;height:16px;" alt="方块">
            </div>
            <span>高级(&D): 四色</span>
          </label>
        </div>
      </div>
    `;

    this.show({
      title: '难易级别',
      width: 320,
      contentHtml: html,
      buttons: [
        {
          text: '确定',
          primary: true,
          onClick: () => {
            const selected = document.querySelector('input[name="diff_choice"]:checked');
            if (selected && onSelect) {
              onSelect(parseInt(selected.value));
            }
          }
        },
        { text: '取消' }
      ]
    });
  }

  /**
   * DIALOG 117: 蜘蛛选项 (Size: 199 x 140, Font: 宋体 9pt)
   * 6 checkboxes matching items 1001-1006
   */
  showOptions(options, onSave) {
    const html = `
      <div style="display: flex; flex-direction: column; gap: 8px; font-size: 12px; color: #000000;">
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="checkbox" id="opt-anim" ${options.animDeal ? 'checked' : ''}>
          <span>发牌时进行动画处理(&A)</span>
        </label>
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="checkbox" id="opt-save-exit" ${options.saveOnExit ? 'checked' : ''}>
          <span>退出时自动保存游戏(&S)</span>
        </label>
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="checkbox" id="opt-load-start" ${options.loadAtStart ? 'checked' : ''}>
          <span>启动时自动打开上次游戏(&O)</span>
        </label>
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="checkbox" id="opt-prompt-save" ${options.promptSave ? 'checked' : ''}>
          <span>保存游戏前提示(&P)</span>
        </label>
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="checkbox" id="opt-prompt-load" ${options.promptLoad ? 'checked' : ''}>
          <span>打开已保存的游戏前提示(&B)</span>
        </label>
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="checkbox" id="opt-sound" ${options.sound ? 'checked' : ''}>
          <span>使用声音效果(&E)</span>
        </label>
      </div>
    `;

    this.show({
      title: '蜘蛛选项',
      width: 290,
      contentHtml: html,
      buttons: [
        {
          text: '确定',
          primary: true,
          onClick: () => {
            const newOpts = {
              animDeal: document.getElementById('opt-anim').checked,
              saveOnExit: document.getElementById('opt-save-exit').checked,
              loadAtStart: document.getElementById('opt-load-start').checked,
              promptSave: document.getElementById('opt-prompt-save').checked,
              promptLoad: document.getElementById('opt-prompt-load').checked,
              sound: document.getElementById('opt-sound').checked
            };
            if (onSave) onSave(newOpts);
          }
        },
        { text: '取消' }
      ]
    });
  }

  /**
   * DIALOG 118: 蜘蛛统计数据 (Size: 167 x 198, Font: 宋体 9pt)
   * TabControl: 初级, 中级, 高级
   * GroupBoxes: 最高记录, 百分比, 连续
   */
  showStats(allStats, initialDiff, onReset) {
    const diffKeys = ['Easy', 'Medium', 'Difficult'];
    const diffTitles = ['初级', '中级', '高级'];
    let curIndex = initialDiff === 1 ? 0 : (initialDiff === 2 ? 1 : 2);

    const renderTabContent = (idx) => {
      const key = diffKeys[idx];
      const s = allStats[key] || { highScore: 0, wins: 0, losses: 0, streakWins: 0, streakLosses: 0, streakCurrent: 0, isWinStreak: true };
      const total = s.wins + s.losses;
      const rate = total > 0 ? Math.round((s.wins / total) * 100) : 0;
      const currentText = s.isWinStreak ? `${s.streakCurrent} 胜` : `${s.streakCurrent} 负`;

      return `
        <!-- Tabs -->
        <div class="xp-tabs">
          ${diffTitles.map((t, i) => `
            <div class="xp-tab ${i === idx ? 'active' : ''}" data-tab-idx="${i}">${t}</div>
          `).join('')}
        </div>

        <!-- Group 1: 最高记录 -->
        <div class="xp-groupbox">
          <span class="xp-groupbox-title">最高记录</span>
          <div style="display:flex; justify-content:space-between; margin-top:4px;">
            <span>得分:</span>
            <strong>${s.highScore}</strong>
          </div>
        </div>

        <!-- Group 2: 百分比 -->
        <div class="xp-groupbox">
          <span class="xp-groupbox-title">百分比</span>
          <div style="display:flex; justify-content:space-between; margin-top:2px;"><span>胜:</span> <strong>${s.wins}</strong></div>
          <div style="display:flex; justify-content:space-between; margin-top:2px;"><span>负:</span> <strong>${s.losses}</strong></div>
          <div style="display:flex; justify-content:space-between; margin-top:2px;"><span>获胜比率:</span> <strong>${rate} %</strong></div>
        </div>

        <!-- Group 3: 连续 -->
        <div class="xp-groupbox">
          <span class="xp-groupbox-title">连续</span>
          <div style="display:flex; justify-content:space-between; margin-top:2px;"><span>最高连胜:</span> <strong>${s.streakWins}</strong></div>
          <div style="display:flex; justify-content:space-between; margin-top:2px;"><span>最高连负:</span> <strong>${s.streakLosses}</strong></div>
          <div style="display:flex; justify-content:space-between; margin-top:2px;"><span>当前:</span> <strong>${currentText}</strong></div>
        </div>
      `;
    };

    const updateContainer = () => {
      this.dialogContent.innerHTML = renderTabContent(curIndex);
      this.dialogContent.querySelectorAll('.xp-tab').forEach(tab => {
        tab.addEventListener('click', (e) => {
          curIndex = parseInt(e.target.dataset.tabIdx);
          updateContainer();
        });
      });
    };

    this.show({
      title: '蜘蛛统计数据',
      width: 290,
      contentHtml: renderTabContent(curIndex),
      buttons: [
        {
          text: '确定',
          primary: true
        },
        {
          text: '复位(&R)',
          onClick: () => {
            this.showConfirm('重置统计信息', '是否要重置所有游戏统计数据?', () => {
              if (onReset) onReset();
            });
          }
        }
      ]
    });

    this.dialogContent.querySelectorAll('.xp-tab').forEach(tab => {
      tab.addEventListener('click', (e) => {
        curIndex = parseInt(e.target.dataset.tabIdx);
        updateContainer();
      });
    });
  }

  /**
   * DIALOG 130: 游戏结束 (Size: 166 x 69, Font: 宋体 9pt)
   */
  showWin(score, moves, onPlayAgain) {
    const html = `
      <div style="font-size: 12px; color: #000000; padding: 4px 0;">
        <div style="font-weight: bold; font-size: 13px; color: #003399; margin-bottom: 6px;">恭喜恭喜，你赢了!</div>
        <div>最终得分: <strong>${score}</strong></div>
        <div>操作次数: <strong>${moves}</strong></div>
        <div style="margin-top: 8px;">是否开始新一轮游戏?</div>
      </div>
    `;

    this.show({
      title: '游戏结束',
      width: 260,
      contentHtml: html,
      buttons: [
        { text: '是(&Y)', primary: true, onClick: onPlayAgain },
        { text: '否(&N)' }
      ]
    });
  }

  /**
   * DIALOG 107: 关于蜘蛛 (Size: 253 x 189, Font: 宋体 9pt)
   * Uses original 106.png bitmap graphic
   */
  showAbout() {
    const html = `
      <div style="display: flex; flex-direction: column; align-items: center; text-align: center; gap: 8px;">
        <img src="assets/ui/106.png" style="max-width: 100%; height: auto; border: 1px solid #716f64;" alt="蜘蛛">
        <div style="font-weight: bold; font-size: 13px; margin-top: 4px;">蜘蛛纸牌 (Spider Solitaire)</div>
        <div style="font-size: 11px; color: #333333;">Windows XP 经典 1:1 纯静态复刻版</div>
        <div style="font-size: 11px; color: #666666;">(C) 1998-2000 Microsoft Corporation. 保留所有权利。</div>
      </div>
    `;

    this.show({
      title: '关于蜘蛛',
      width: 320,
      contentHtml: html,
      buttons: [
        { text: '确定', primary: true }
      ]
    });
  }
}

  // --- src/ui/Interaction.js ---
/**
 * Interaction.js
 * 1:1 Windows XP Spider Solitaire Interaction Engine
 * Implements:
 * - Iconic GDI InvertRect selection on card click / press
 * - Dual mode: Click-to-Select (inverted) -> Click-to-Place, OR Drag-and-Drop
 * - Double-click smart auto-move
 * - Right-click peek (FUN_01003712 / FUN_010059a6)
 * - Bottom area click to trigger Hint (FUN_01003811)
 * - Stock deal with sequential sound (FUN_010069b2 / AnimDeal)
 */

class Interaction {
  constructor(game, renderer, audioService, dialogs, victoryAnim) {
    this.game = game;
    this.renderer = renderer;
    this.audio = audioService;
    this.dialogs = dialogs;
    this.victoryAnim = victoryAnim;

    this.dragLayer = document.getElementById('drag-layer');
    this.bottomHintBtn = document.getElementById('board-scoreboard') || document.getElementById('bottom-hint-btn');

    this.activeDrag = null;
    this.peekingEl = null;
    this.selectedCards = null; // { col, cardIdx, elements }

    this.bindEvents();
  }

  bindEvents() {
    // 1. Stock pile click
    this.renderer.stockEl.addEventListener('click', () => this.handleStockClick());

    // 2. Bottom hint trigger (FUN_01003811 / FUN_01004a10)
    if (this.bottomHintBtn) {
      this.bottomHintBtn.addEventListener('click', (e) => {
        e.preventDefault();
        e.stopPropagation();
        this.triggerHint();
      });
      this.bottomHintBtn.addEventListener('pointerdown', (e) => {
        e.stopPropagation();
      });
    }

    // 3. Prevent context menu on tableau
    this.renderer.tableauEl.addEventListener('contextmenu', (e) => e.preventDefault());

    // 4. Pointer events
    this.renderer.tableauEl.addEventListener('pointerdown', (e) => this.onPointerDown(e));
    window.addEventListener('pointermove', (e) => this.onPointerMove(e));
    window.addEventListener('pointerup', (e) => this.onPointerUp(e));
    window.addEventListener('pointercancel', (e) => this.onPointerCancel(e));

    // 5. Double click for smart auto-move
    this.renderer.tableauEl.addEventListener('dblclick', (e) => this.onDoubleClick(e));

    // 6. Click on empty felt to deselect
    this.renderer.tableauEl.addEventListener('click', (e) => {
      if (!e.target.closest('.card-element') && this.selectedCards) {
        this.clearSelection();
        this.audio.play('drop');
      }
    });
  }

  clearSelection() {
    if (this.selectedCards) {
      this.selectedCards.elements.forEach(el => el.classList.remove('selected-inverted'));
      this.selectedCards = null;
    }
  }

  setSelection(fromCol, cardIdx) {
    this.clearSelection();
    const colEl = this.renderer.columnEls[fromCol];
    if (!colEl) return;

    const movingEls = Array.from(colEl.querySelectorAll('.card-element')).filter(
      el => parseInt(el.dataset.cardIdx) >= cardIdx
    );

    // Apply iconic Windows GDI InvertRect selection
    movingEls.forEach(el => el.classList.add('selected-inverted'));

    this.selectedCards = {
      col: fromCol,
      cardIdx,
      elements: movingEls
    };

    this.audio.play('grab'); // 128.wav on select
  }

  async handleStockClick() {
    const check = this.game.canDeal();
    if (!check.canDeal) {
      if (check.reason === 'EMPTY_COLUMN') {
        this.audio.play('noHint'); // 127.wav
        this.dialogs.showAlert('蜘蛛纸牌', '有空位时不允许发牌。'); // String ID 5
      }
      return;
    }

    this.clearSelection();
    const result = this.game.dealRound();
    if (result.success) {
      this.audio.play('deal'); // 124.wav
      this.renderer.render();

      if (result.completedRuns.length > 0) {
        setTimeout(() => this.audio.play('deal'), 300);
      }

      if (result.isWin) {
        this.handleWin();
      }
    }
  }

  /**
   * Exact 1:1 Hint trigger from FUN_01004dfb:
   * Plays 126.wav and animates if move exists, or plays 127.wav if no moves available.
   * No alert dialog is shown on no hint (matches authentic Windows XP behavior).
   */
  async triggerHint() {
    this.clearSelection();
    const hint = this.game.getNextHint();
    if (hint) {
      this.audio.play('hint'); // 126.wav
      await this.renderer.playHintAnimation(hint);
    } else {
      this.audio.play('noHint'); // 127.wav
    }
  }

  onPointerDown(e) {
    const cardEl = e.target.closest('.card-element');

    // Right-click peek (FUN_01003712)
    if (e.button === 2) {
      if (cardEl) {
        this.peekingEl = cardEl;
        cardEl.classList.add('peeking');
      }
      return;
    }

    if (e.button !== 0 && e.pointerType === 'mouse') return;

    // Clicked on empty column slot
    const emptyColEl = e.target.closest('.tableau-column');
    if (!cardEl && emptyColEl) {
      const colIdx = parseInt(emptyColEl.dataset.col);
      if (this.selectedCards && this.game.canMove(this.selectedCards.col, this.selectedCards.cardIdx, colIdx)) {
        this.executeMove(this.selectedCards.col, this.selectedCards.cardIdx, colIdx);
        return;
      }
    }

    if (!cardEl) return;

    const fromCol = parseInt(cardEl.dataset.col);
    const cardIdx = parseInt(cardEl.dataset.cardIdx);

    // Check if player has an existing selection and clicked a different column
    if (this.selectedCards && this.selectedCards.col !== fromCol) {
      if (this.game.canMove(this.selectedCards.col, this.selectedCards.cardIdx, fromCol)) {
        this.executeMove(this.selectedCards.col, this.selectedCards.cardIdx, fromCol);
        return;
      }
    }

    if (!this.game.isSequenceMovable(fromCol, cardIdx)) {
      if (this.selectedCards) {
        this.clearSelection();
        this.audio.play('noHint');
      }
      return;
    }

    // Prepare drag & immediate inverted visual feedback
    const cardRect = cardEl.getBoundingClientRect();
    const colEl = this.renderer.columnEls[fromCol];
    const movingEls = Array.from(colEl.querySelectorAll('.card-element')).filter(
      el => parseInt(el.dataset.cardIdx) >= cardIdx
    );

    // Show immediate InvertRect on press!
    movingEls.forEach(el => el.classList.add('selected-inverted'));

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
      dragGroup: null,
      wasAlreadySelected: this.selectedCards && this.selectedCards.col === fromCol && this.selectedCards.cardIdx === cardIdx
    };

    this.audio.play('grab'); // 128.wav
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
    dragGroup.className = 'drag-group selected-inverted';
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
      clone.classList.add('selected-inverted');
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
    if (this.peekingEl) {
      this.peekingEl.classList.remove('peeking');
      this.peekingEl = null;
    }

    if (!this.activeDrag) return;

    const { fromCol, cardIdx, isDragging, dragGroup, movingEls, wasAlreadySelected } = this.activeDrag;

    if (!isDragging) {
      // User tapped / clicked!
      if (wasAlreadySelected) {
        // Clicked the same selected card -> Deselect!
        this.clearSelection();
        this.audio.play('drop');
      } else {
        // Keep selected & INVERTED!
        this.setSelection(fromCol, cardIdx);
      }
      this.activeDrag = null;
      return;
    }

    // Drag release: find target column
    const targetCol = this.findDropTarget(e.clientX, e.clientY);

    if (targetCol !== null && this.game.canMove(fromCol, cardIdx, targetCol)) {
      if (dragGroup) dragGroup.remove();
      this.executeMove(fromCol, cardIdx, targetCol);
    } else {
      // Invalid drop: snap back and remove inversion
      movingEls.forEach(el => {
        el.classList.remove('selected-inverted');
        el.style.opacity = '1';
      });
      if (dragGroup) dragGroup.remove();
      this.clearSelection();
      this.audio.play('noHint');
    }

    this.activeDrag = null;
  }

  onPointerCancel() {
    if (this.peekingEl) {
      this.peekingEl.classList.remove('peeking');
      this.peekingEl = null;
    }
    if (this.activeDrag) {
      if (this.activeDrag.dragGroup) this.activeDrag.dragGroup.remove();
      this.activeDrag.movingEls.forEach(el => {
        el.classList.remove('selected-inverted');
        el.style.opacity = '1';
      });
      this.clearSelection();
      this.activeDrag = null;
    }
  }

  findDropTarget(clientX, clientY) {
    let bestCol = null;
    let minDistance = Infinity;

    for (let c = 0; c < 10; c++) {
      const colEl = this.renderer.columnEls[c];
      const rect = colEl.getBoundingClientRect();

      if (clientX >= rect.left - 15 && clientX <= rect.right + 15) {
        if (clientY >= rect.top - 20 && clientY <= rect.bottom + 100) {
          return c;
        }
      }

      const colCenterX = rect.left + rect.width / 2;
      const dist = Math.abs(clientX - colCenterX);
      if (dist < minDistance && dist < rect.width * 1.3) {
        minDistance = dist;
        bestCol = c;
      }
    }

    return bestCol;
  }

  executeMove(fromCol, cardIdx, toCol) {
    this.clearSelection();
    const res = this.game.moveCards(fromCol, cardIdx, toCol);
    if (res.success) {
      this.audio.play('drop'); // 125.wav
      if (res.completedRun) {
        setTimeout(() => this.audio.play('deal'), 200); // 124.wav on run cleared
      }
      this.renderer.render();

      if (res.isWin) {
        this.handleWin();
      }
    }
  }

  /**
   * Double-click on card: instantly smart-move to best column
   */
  onDoubleClick(e) {
    const cardEl = e.target.closest('.card-element');
    if (!cardEl) return;

    const fromCol = parseInt(cardEl.dataset.col);
    const cardIdx = parseInt(cardEl.dataset.cardIdx);

    if (!this.game.isSequenceMovable(fromCol, cardIdx)) return;

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
          priority = (targetTop.suit === movingCard.suit) ? 100 : 50;
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
      this.executeMove(fromCol, cardIdx, bestTarget);
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
 * Save/Load (spider.sav), per-difficulty statistics, and keyboard shortcuts.
 */


class App {
  constructor() {
    this.stats = this.loadStats();
    this.options = this.loadOptions();
    this.audio = new AudioService();
    this.audio.soundEnabled = this.options.sound;
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
    this.bindPersistence();

    // Check if auto-saved game exists on launch (if enabled in options)
    if (this.options.loadAtStart) {
      this.tryRestoreAutoSavedGame();
    }

    // Hook game events
    this.game.onChange((event, data) => {
      if (event === 'undo') {
        this.renderer.render();
      } else if (event === 'move' || event === 'deal') {
        if (data.isWin) {
          this.recordGameResult(true, this.game.score);
          localStorage.removeItem('spider_saved_game');
        }
      }
    });

    this.renderer.render();
  }

  loadOptions() {
    try {
      const data = localStorage.getItem('spider_options');
      if (data) return JSON.parse(data);
    } catch (e) {}
    return {
      animDeal: true,
      saveOnExit: true,
      loadAtStart: true,
      promptSave: true,
      promptLoad: true,
      sound: true
    };
  }

  saveOptions() {
    localStorage.setItem('spider_options', JSON.stringify(this.options));
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

  saveCurrentGame() {
    try {
      const data = {
        difficulty: this.game.difficulty,
        columns: this.game.columns.map(col => col.map(c => ({ suit: c.suit, rank: c.rank, faceUp: c.faceUp, id: c.id }))),
        stock: this.game.stock.map(c => ({ suit: c.suit, rank: c.rank, faceUp: c.faceUp, id: c.id })),
        stockDealsLeft: this.game.stockDealsLeft,
        completedSuits: [...this.game.completedSuits],
        score: this.game.score,
        moves: this.game.moves,
        isWon: this.game.isWon
      };
      localStorage.setItem('spider_saved_game', JSON.stringify(data));
      return true;
    } catch (e) {
      return false;
    }
  }

  loadSavedGame() {
    try {
      const json = localStorage.getItem('spider_saved_game');
      if (!json) return false;
      const data = JSON.parse(json);

      this.game.difficulty = data.difficulty;
      this.game.columns = data.columns.map(col => col.map(c => {
        const card = new Card(c.suit, c.rank, c.faceUp);
        card.id = c.id;
        return card;
      }));
      this.game.stock = data.stock.map(c => {
        const card = new Card(c.suit, c.rank, c.faceUp);
        card.id = c.id;
        return card;
      });
      this.game.stockDealsLeft = data.stockDealsLeft;
      this.game.completedSuits = data.completedSuits;
      this.game.score = data.score;
      this.game.moves = data.moves;
      this.game.isWon = data.isWon;
      this.game.undoStack = [];
      this.game.hintNeedsUpdate = true;

      this.renderer.render();
      this.audio.play('deal');
      return true;
    } catch (e) {
      return false;
    }
  }

  tryRestoreAutoSavedGame() {
    const json = localStorage.getItem('spider_saved_game');
    if (json) {
      this.loadSavedGame();
    }
  }

  bindPersistence() {
    // Auto-save on page close / refresh (FUN_0100411f: SaveOnExit)
    window.addEventListener('beforeunload', () => {
      if (this.options.saveOnExit && this.game.moves > 0 && !this.game.isWon) {
        this.saveCurrentGame();
      }
    });
  }

  startNewGame(diff = null) {
    if (diff !== null) {
      this.game.difficulty = diff;
      localStorage.setItem('spider_difficulty', diff);
    }
    localStorage.removeItem('spider_saved_game');
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
          if (this.options.saveOnExit && this.game.moves > 0 && !this.game.isWon) {
            this.saveCurrentGame();
          }
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
        if (!isActive && !item.hasAttribute('data-action')) {
          item.classList.add('active');
        }
      });
    });

    window.addEventListener('click', () => {
      menuItems.forEach(m => m.classList.remove('active'));
    });

    const actionMap = {
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
          this.interaction.clearSelection();
          this.game.undo();
          this.audio.play('drop');
        }
      },
      'save-game': () => {
        const doSave = () => {
          const ok = this.saveCurrentGame();
          if (ok) {
            this.dialogs.showAlert('保存游戏', '游戏已成功保存。');
          } else {
            this.dialogs.showAlert('保存游戏', '无法保存游戏。');
          }
        };

        if (this.options.promptSave) {
          this.dialogs.showConfirm('保存游戏', '是否保存当前游戏进度?', () => {
            doSave();
          });
        } else {
          doSave();
        }
      },
      'load-game': () => {
        if (localStorage.getItem('spider_saved_game')) {
          const doLoad = () => {
            const ok = this.loadSavedGame();
            if (!ok) this.dialogs.showAlert('打开游戏', '无法加载游戏。');
          };

          if (this.options.promptLoad) {
            this.dialogs.showConfirm('打开游戏', '是否放弃当前正在玩的游戏，加载上次保存的游戏?', () => {
              doLoad();
            });
          } else {
            doLoad();
          }
        } else {
          this.dialogs.showAlert('打开游戏', '没有找到保存的游戏。');
        }
      },
      'hint': () => {
        this.interaction.triggerHint();
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
      'options': () => {
        this.dialogs.showOptions(this.options, (newOpts) => {
          this.options = { ...this.options, ...newOpts };
          this.saveOptions();
          this.audio.soundEnabled = this.options.sound;
        });
      },
      'sound-toggle': () => {
        const enabled = this.audio.toggleSound();
        this.options.sound = enabled;
        this.saveOptions();
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
      },
      'exit': () => {
        this.dialogs.showConfirm('退出', '是否退出蜘蛛纸牌?', () => {
          if (this.options.saveOnExit && this.game.moves > 0 && !this.game.isWon) {
            this.saveCurrentGame();
          }
          window.close();
        });
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
      // F1: Rules / Help Topics
      if (e.key === 'F1') {
        e.preventDefault();
        const action = document.querySelector('[data-action="rules"]');
        if (action) action.click();
      }
      // F2: New Game
      else if (e.key === 'F2') {
        e.preventDefault();
        const action = document.querySelector('[data-action="new-game"]');
        if (action) action.click();
      }
      // F3: Difficulty
      else if (e.key === 'F3') {
        e.preventDefault();
        const action = document.querySelector('[data-action="difficulty"]');
        if (action) action.click();
      }
      // F4: Stats
      else if (e.key === 'F4') {
        e.preventDefault();
        const action = document.querySelector('[data-action="stats"]');
        if (action) action.click();
      }
      // F5: Options
      else if (e.key === 'F5') {
        e.preventDefault();
        const action = document.querySelector('[data-action="options"]');
        if (action) action.click();
      }
      // Ctrl+Z / Cmd+Z: Undo
      else if ((e.ctrlKey || e.metaKey) && (e.key === 'z' || e.key === 'Z')) {
        e.preventDefault();
        if (this.game.canUndo()) {
          this.interaction.clearSelection();
          this.game.undo();
          this.audio.play('drop');
        }
      }
      // Ctrl+S / Cmd+S: Save Game
      else if ((e.ctrlKey || e.metaKey) && (e.key === 's' || e.key === 'S')) {
        e.preventDefault();
        const action = document.querySelector('[data-action="save-game"]');
        if (action) action.click();
      }
      // Ctrl+O / Cmd+O: Load Game
      else if ((e.ctrlKey || e.metaKey) && (e.key === 'o' || e.key === 'O')) {
        e.preventDefault();
        const action = document.querySelector('[data-action="load-game"]');
        if (action) action.click();
      }
      // H / M: Hint
      else if (e.key === 'h' || e.key === 'H' || e.key === 'm' || e.key === 'M') {
        e.preventDefault();
        this.interaction.triggerHint();
      }
      // D: Deal
      else if (e.key === 'd' || e.key === 'D') {
        e.preventDefault();
        this.interaction.handleStockClick();
      }
      // Escape: Boss Key (FUN_01006db6) or close dialog
      else if (e.key === 'Escape') {
        if (this.dialogs.overlay.classList.contains('show')) {
          this.dialogs.hide();
        } else {
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
