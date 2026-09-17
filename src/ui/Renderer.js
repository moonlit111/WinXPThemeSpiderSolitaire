/**
 * Renderer.js
 * Handles DOM rendering of the 10 tableau columns, cards, stock, foundation, and status bar.
 * Implements exact 250ms sequential flash hint animation (FUN_01004dfb).
 */

export class Renderer {
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

  /**
   * 1:1 Windows XP Complete Run Slide-to-Foundation Animation (FUN_010062ae / FUN_010047bd)
   * Glides the completed 13-card suit down to the foundation pile at bottom-left over 320ms.
   */
  async animateCollectRun(run, targetSlotIdx) {
    const colEl = this.columnEls[run.colIndex];
    if (!colEl || !this.foundationEl) return;

    const foundationRect = this.foundationEl.getBoundingClientRect();
    const targetX = foundationRect.left + targetSlotIdx * 12;
    const targetY = foundationRect.top;

    const colRect = colEl.getBoundingClientRect();
    const cardEls = colEl.querySelectorAll('.card-element');
    let startX = colRect.left + (colRect.width - 71) / 2;
    let startY = colRect.top + Math.max(0, colEl.clientHeight - 120);

    if (cardEls.length > 0) {
      const topRect = cardEls[cardEls.length - 1].getBoundingClientRect();
      startX = topRect.left;
      startY = topRect.top;
    }

    const dragLayer = document.getElementById('drag-layer') || document.body;
    const flyer = document.createElement('div');
    flyer.className = 'collect-flyer';
    flyer.style.position = 'fixed';
    flyer.style.left = `${startX}px`;
    flyer.style.top = `${startY}px`;
    flyer.style.width = '71px';
    flyer.style.height = '96px';
    flyer.style.zIndex = '99999';
    flyer.style.transition = 'all 320ms cubic-bezier(0.2, 0.8, 0.4, 1)';
    flyer.style.pointerEvents = 'none';

    // Show King of that suit
    const kingImgIdx = 1 + run.suit * 13 + 12;
    const img = document.createElement('img');
    img.src = `assets/cards/CARD${kingImgIdx}.png`;
    img.style.width = '100%';
    img.style.height = '100%';
    img.style.borderRadius = '3px';
    img.style.boxShadow = '2px 4px 12px rgba(0, 0, 0, 0.6)';
    flyer.appendChild(img);

    dragLayer.appendChild(flyer);

    // Force layout reflow
    void flyer.offsetWidth;

    flyer.style.left = `${targetX}px`;
    flyer.style.top = `${targetY}px`;

    await new Promise(r => setTimeout(r, 330));
    flyer.remove();
  }
}
