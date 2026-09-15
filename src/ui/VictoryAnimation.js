/**
 * VictoryAnimation.js
 * Renders the iconic Windows Solitaire/Spider bouncing card cascade animation using HTML5 Canvas.
 */

export class VictoryAnimation {
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
