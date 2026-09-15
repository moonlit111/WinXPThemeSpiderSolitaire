/**
 * Renderer.js
 * Handles DOM rendering of the 10 tableau columns, cards, stock, foundation, and status bar.
 */

import { Card, SUITS } from '../engine/Card.js';

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
      
      // Retain the empty slot
      colEl.querySelectorAll('.card-element').forEach(el => el.remove());

      if (cards.length === 0) continue;

      // Calculate dynamic vertical offsets
      let downCount = 0;
      let upCount = 0;
      for (const card of cards) {
        if (card.faceUp) upCount++;
        else downCount++;
      }

      // Default offsets
      let downStep = 13;
      let upStep = 23;

      // If cards exceed height, compress spacing smoothly
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

        // Advance top offset
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

    // Render up to 5 overlapping card backs
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
        // King of that completed suit: 1 + suit * 13 + 12
        const kingImgIndex = 1 + suit * 13 + 12;
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

  highlightHint(hint) {
    // Clear previous hints
    this.clearHints();
    if (!hint) return;

    const colEl = this.columnEls[hint.fromCol];
    if (!colEl) return;
    const cardEl = colEl.querySelector(`[data-card-idx="${hint.cardIndex}"]`);
    if (cardEl) {
      cardEl.classList.add('hinted');
      setTimeout(() => this.clearHints(), 2500);
    }
  }

  clearHints() {
    this.tableauEl.querySelectorAll('.hinted').forEach(el => el.classList.remove('hinted'));
  }
}
