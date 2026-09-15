/**
 * Interaction.js
 * Handles mouse and touch drag-and-drop, smart click-to-move, right-click peek, and stock dealing.
 * Matches original Windows XP input messages:
 * - WM_LBUTTONDOWN (FUN_01005753 -> PlaySoundW 0x80 / 128.wav)
 * - WM_LBUTTONUP (FUN_01006732 -> PlaySoundW 0x7d / 125.wav)
 * - WM_RBUTTONDOWN / WM_RBUTTONUP (FUN_01003712 / FUN_010059a6 -> Peek card)
 */

export class Interaction {
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
