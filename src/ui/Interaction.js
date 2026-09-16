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

export class Interaction {
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
