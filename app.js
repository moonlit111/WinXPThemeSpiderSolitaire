(() => {
  const STORAGE_KEYS = {
    save: "spider.xp.save",
    stats: "spider.xp.stats",
    difficulty: "spider.xp.difficulty",
    options: "spider.xp.options"
  };

  const DIFFICULTIES = {
    easy: { key: "easy", label: "初级（单色）", suits: ["spades"], copiesPerSuit: 8 },
    medium: { key: "medium", label: "中级（双色）", suits: ["spades", "hearts"], copiesPerSuit: 4 },
    hard: { key: "hard", label: "高级（四色）", suits: ["clubs", "diamonds", "hearts", "spades"], copiesPerSuit: 2 }
  };

  const SUIT_BASE = {
    clubs: 0,
    diamonds: 13,
    hearts: 26,
    spades: 39
  };

  const RANK_LABEL = {
    1: "A",
    11: "J",
    12: "Q",
    13: "K"
  };

  class FireworkParticle {
    constructor(x, y, color, options = {}) {
      const angle = Math.random() * Math.PI * 2;
      const speedMin = options.speedMin ?? 120;
      const speedMax = options.speedMax ?? 240;
      const sizeMin = options.sizeMin ?? 6;
      const sizeMax = options.sizeMax ?? 10;
      const lifeMin = options.lifeMin ?? 2.2;
      const lifeMax = options.lifeMax ?? 3.2;

      const speed = speedMin + Math.random() * (speedMax - speedMin);
      this.x = x;
      this.y = y;
      this.vx = Math.cos(angle) * speed;
      this.vy = Math.sin(angle) * speed + (options.initialVyOffset ?? -10);
      this.color = color;
      this.life = 0;
      this.lifeSpan = lifeMin + Math.random() * (lifeMax - lifeMin);
      this.size = sizeMin + Math.random() * (sizeMax - sizeMin);
      this.gravity = options.gravity ?? 90;
      this.drag = options.drag ?? 0.992;
    }

    update(dt) {
      this.life += dt;
      this.x += this.vx * dt;
      this.y += this.vy * dt;
      this.vy += this.gravity * dt;
      this.vx *= this.drag;
      this.vy *= this.drag;
    }

    get alpha() {
      return Math.max(0, 1 - this.life / this.lifeSpan);
    }
  }

  class FireworkRocket {
    constructor(startX, startY, targetX, targetY, color, speed) {
      this.x = startX;
      this.y = startY;
      this.targetX = targetX;
      this.targetY = targetY;
      this.color = color;
      this.trail = [];
      this.age = 0;
      this.maxAge = 3.2;
      this.alive = true;

      const dx = targetX - startX;
      const dy = targetY - startY;
      const dist = Math.max(1, Math.hypot(dx, dy));
      this.vx = (dx / dist) * speed;
      this.vy = (dy / dist) * speed;
    }

    update(dt) {
      if (!this.alive) {
        return false;
      }
      this.age += dt;

      this.trail.push({ x: this.x, y: this.y, a: 1 });
      if (this.trail.length > 14) {
        this.trail.shift();
      }
      for (const t of this.trail) {
        t.a *= 0.88;
      }

      this.x += this.vx * dt;
      this.y += this.vy * dt;

      const distToTarget = Math.hypot(this.targetX - this.x, this.targetY - this.y);
      if (distToTarget < 12 || this.age >= this.maxAge) {
        this.alive = false;
        return true;
      }
      return false;
    }

    draw(ctx) {
      if (!this.alive) {
        return;
      }
      ctx.save();
      ctx.globalCompositeOperation = "lighter";
      ctx.lineCap = "round";
      for (let i = 1; i < this.trail.length; i += 1) {
        const prev = this.trail[i - 1];
        const curr = this.trail[i];
        ctx.globalAlpha = 1;
        ctx.strokeStyle = this.color;
        ctx.lineWidth = 0.7;
        ctx.beginPath();
        ctx.moveTo(prev.x, prev.y);
        ctx.lineTo(curr.x, curr.y);
        ctx.stroke();
      }

      ctx.globalAlpha = 1;
      ctx.fillStyle = this.color;
      ctx.beginPath();
      ctx.arc(this.x, this.y, 1.4, 0, Math.PI * 2);
      ctx.fill();
      ctx.restore();
    }
  }

  class VictoryAnimator {
    constructor(boardEl) {
      this.boardEl = boardEl;
      this.canvas = document.createElement("canvas");
      this.canvas.id = "victory-canvas";
      this.canvas.width = 1;
      this.canvas.height = 1;
      this.canvas.style.position = "absolute";
      this.canvas.style.left = "0";
      this.canvas.style.top = "0";
      this.canvas.style.width = "100%";
      this.canvas.style.height = "100%";
      this.canvas.style.pointerEvents = "none";
      this.canvas.style.zIndex = "20";
      this.boardEl.appendChild(this.canvas);

      this.ctx = this.canvas.getContext("2d");
      this.particles = [];
      this.rockets = [];
      this.active = false;
      this.startTime = 0;
      this.lastFrame = 0;
      this.rafId = null;
      this.nextWaveAt = 0;
      this.colorCycle = ["#FF00FF", "#FFFF00", "#00FFFF", "#800080", "#00FF00"];
      this.colorIndex = 0;
      this.lastColorTick = 0;
      this.colorStepMs = 2600;

      window.addEventListener("resize", () => this.resize());
      this.resize();
    }

    resize() {
      const rect = this.boardEl.getBoundingClientRect();
      this.canvas.width = rect.width;
      this.canvas.height = rect.height;
    }

    start() {
      this.resize();
      this.particles = [];
      this.rockets = [];
      this.active = true;
      this.startTime = performance.now();
      this.lastFrame = this.startTime;
      this.lastColorTick = this.startTime;
      this.colorIndex = 0;
      this.nextWaveAt = this.startTime;
      this.canvas.style.opacity = "1";

      if (this.rafId) {
        cancelAnimationFrame(this.rafId);
      }
      this.rafId = requestAnimationFrame(() => this.frame());
    }

    stop() {
      this.active = false;
      if (this.rafId) {
        cancelAnimationFrame(this.rafId);
        this.rafId = null;
      }
      this.particles = [];
      this.rockets = [];
      this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
    }

    frame() {
      if (!this.active) {
        return;
      }
      const now = performance.now();
      const dt = Math.max(0.001, (now - this.lastFrame) / 1000);
      this.lastFrame = now;

      if (now - this.lastColorTick >= this.colorStepMs) {
        this.colorIndex = (this.colorIndex + 1) % this.colorCycle.length;
        this.lastColorTick = now;
      }

      this.updateLaunchSequence(now);
      this.updateRockets(dt);
      this.updateParticles(dt);
      this.draw(now);
      this.rafId = requestAnimationFrame(() => this.frame());
    }

    updateLaunchSequence(now) {
      if (now >= this.nextWaveAt && this.rockets.length === 0) {
        this.launchBottomPair(now);
        this.nextWaveAt = now + 1350 + Math.random() * 650;
      }
    }

    launchBottomPair(now) {
      const target = this.getVictoryPoint();
      const points = this.getBottomLaunchPoints();
      const leftColor = this.getCurrentColor(now);
      const rightColor = this.colorCycle[(this.colorIndex + 2) % this.colorCycle.length];

      this.rockets.push(new FireworkRocket(points.left.x, points.left.y, target.x, target.y, leftColor, 248));
      this.rockets.push(new FireworkRocket(points.right.x, points.right.y, target.x, target.y, rightColor, 248));
    }

    updateRockets(dt) {
      const bursts = [];
      for (const rocket of this.rockets) {
        const explode = rocket.update(dt);
        if (explode) {
          bursts.push({ x: rocket.targetX, y: rocket.targetY, color: rocket.color });
        }
      }
      this.rockets = this.rockets.filter((r) => r.alive);
      for (const burst of bursts) {
        this.createLargeBurst(burst.x, burst.y, burst.color);
      }
    }

    createLargeBurst(x, y, color) {
      const count = 72 + Math.floor(Math.random() * 28);
      for (let i = 0; i < count; i += 1) {
        this.particles.push(new FireworkParticle(x, y, color, {
          speedMin: 180,
          speedMax: 340,
          sizeMin: 7,
          sizeMax: 12,
          lifeMin: 2.6,
          lifeMax: 3.8,
          gravity: 86,
          drag: 0.992,
          initialVyOffset: -8
        }));
      }
    }

    updateParticles(dt) {
      this.particles.forEach((p) => p.update(dt));
      this.particles = this.particles.filter((p) => p.alpha > 0.03);
    }

    draw(now) {
      this.ctx.globalCompositeOperation = "source-over";
      this.ctx.fillStyle = "rgba(0, 0, 0, 0.17)";
      this.ctx.fillRect(0, 0, this.canvas.width, this.canvas.height);

      for (const rocket of this.rockets) {
        rocket.draw(this.ctx);
      }

      for (const p of this.particles) {
        this.ctx.globalCompositeOperation = "lighter";
        this.ctx.fillStyle = `${p.color}${this.toHexAlpha(p.alpha)}`;
        this.ctx.beginPath();
        this.ctx.arc(p.x, p.y, p.size * 0.5, 0, Math.PI * 2);
        this.ctx.fill();
      }

      this.ctx.globalCompositeOperation = "source-over";
      const color = this.getCurrentColor(now);
      this.drawVictoryText(color);
    }

    getVictoryPoint() {
      return {
        x: this.canvas.width / 2,
        y: this.canvas.height / 2
      };
    }

    getBottomLaunchPoints() {
      const baseY = this.canvas.height - (10 + Math.random() * 18);
      const minGap = this.canvas.width * 0.2;
      const leftX = this.canvas.width * (0.08 + Math.random() * 0.34);
      let rightX = this.canvas.width * (0.58 + Math.random() * 0.34);
      if (rightX - leftX < minGap) {
        rightX = Math.min(this.canvas.width * 0.94, leftX + minGap);
      }
      return {
        left: { x: leftX, y: baseY },
        right: { x: rightX, y: baseY }
      };
    }

    toHexAlpha(alpha) {
      const value = Math.max(0, Math.min(255, Math.round(alpha * 255)));
      return value.toString(16).padStart(2, "0");
    }

    getCurrentColor(now) {
      const nextIndex = (this.colorIndex + 1) % this.colorCycle.length;
      const t = Math.min(1, (now - this.lastColorTick) / this.colorStepMs);
      const a = this.hexToRgb(this.colorCycle[this.colorIndex]);
      const b = this.hexToRgb(this.colorCycle[nextIndex]);
      return this.rgbToHex({
        r: Math.round(a.r + (b.r - a.r) * t),
        g: Math.round(a.g + (b.g - a.g) * t),
        b: Math.round(a.b + (b.b - a.b) * t)
      });
    }

    hexToRgb(hex) {
      const v = hex.replace("#", "");
      return {
        r: parseInt(v.slice(0, 2), 16),
        g: parseInt(v.slice(2, 4), 16),
        b: parseInt(v.slice(4, 6), 16)
      };
    }

    rgbToHex({ r, g, b }) {
      const toHex = (n) => Math.max(0, Math.min(255, n)).toString(16).padStart(2, "0");
      return `#${toHex(r)}${toHex(g)}${toHex(b)}`;
    }

    drawVictoryText(color) {
      const ctx = this.ctx;
      const text = "你赢了！";
      ctx.save();
      ctx.font = "400 64px 'SimSun', 'SimHei', 'Songti SC', serif";
      ctx.textBaseline = "middle";
      ctx.textAlign = "center";
      ctx.shadowColor = "rgba(0, 0, 0, 0.75)";
      ctx.shadowBlur = 18;
      ctx.lineWidth = 3;
      ctx.strokeStyle = "rgba(0, 0, 0, 0.9)";
      ctx.fillStyle = color;
      const x = this.canvas.width / 2;
      const y = this.canvas.height / 2;
      ctx.strokeText(text, x, y);
      ctx.shadowBlur = 22;
      ctx.shadowColor = "rgba(255, 255, 255, 0.45)";
      ctx.fillText(text, x, y);
      ctx.restore();
    }
  }

  class SpiderGame {
    constructor() {
      this.appEl = document.getElementById("app");
      this.menuBarEl = document.querySelector(".menu-bar");
      this.menuHotspotEl = document.getElementById("menu-hotspot");
      this.boardEl = document.getElementById("board");
      this.columnsEl = document.getElementById("columns");
      this.stockEl = document.getElementById("stock");
      this.completedEl = document.getElementById("completed-area");
      this.statusEl = document.getElementById("status-text");
      this.scoreEl = document.getElementById("score");
      this.movesEl = document.getElementById("moves");
      this.timeEl = document.getElementById("time");
      this.scoreBoxEl = document.getElementById("score-box");
      this.statsDialogEl = document.getElementById("stats-dialog");
      this.difficultyDialogEl = document.getElementById("difficulty-dialog");
      this.optionsDialogEl = document.getElementById("options-dialog");
      this.aboutDialogEl = document.getElementById("about-dialog");
      this.victoryAnimator = new VictoryAnimator(this.boardEl);

      this.stats = this.loadStats();
      this.difficulty = this.loadDifficulty();
      this.options = this.loadOptions();

      this.state = this.newEmptyState();
      this.selected = null;
      this.hint = null;
      this.dragging = null;
      this.dragOverCol = null;
      this.dragPreviewEl = null;
      this.dealAnimationOrder = new Map();
      this.dealAnimationTimer = null;
      this.hintTimers = [];
      this.hintSequenceKey = "";
      this.hintChoiceIndex = 0;
      this.sounds = this.initSounds();
      this.nextCardId = 1;

      this.timeline = [];
      this.currentIndex = 0;
      this.minUndoIndex = 0;
      this.undoDisabled = false;
      this.timerId = null;

      this.installMenu();
      this.installAutoHideMenu();
      this.installBoardEvents();
      this.installKeyboard();
      this.startNewGame(this.difficulty, false);
      if (this.options.loadAtStart) {
        this.loadGame(false);
      }
      this.startTicker();
    }

    installAutoHideMenu() {
      if (!this.appEl || !this.menuBarEl || !this.menuHotspotEl) {
        return;
      }

      let hideTimer = null;
      const showMenu = () => {
        if (hideTimer) {
          clearTimeout(hideTimer);
          hideTimer = null;
        }
        this.appEl.classList.add("menu-visible");
      };

      const hideMenuSoon = () => {
        if (hideTimer) {
          clearTimeout(hideTimer);
        }
        hideTimer = window.setTimeout(() => {
          const menuActive = this.menuBarEl.matches(":hover") || this.menuBarEl.querySelector(":focus-within");
          if (!menuActive) {
            this.appEl.classList.remove("menu-visible");
          }
        }, 220);
      };

      this.appEl.classList.add("menu-autohide");
      this.appEl.classList.remove("menu-visible");

      this.menuHotspotEl.addEventListener("mouseenter", showMenu);
      this.menuBarEl.addEventListener("mouseenter", showMenu);
      this.menuBarEl.addEventListener("mouseleave", hideMenuSoon);

      this.menuBarEl.addEventListener("focusin", showMenu);
      this.menuBarEl.addEventListener("focusout", () => {
        window.setTimeout(() => {
          const menuActive = this.menuBarEl.matches(":hover") || this.menuBarEl.querySelector(":focus-within");
          if (!menuActive) {
            this.appEl.classList.remove("menu-visible");
          }
        }, 0);
      });

      window.addEventListener("mousemove", (event) => {
        if (event.clientY <= 10) {
          showMenu();
          return;
        }
        if (!this.menuBarEl.matches(":hover")) {
          hideMenuSoon();
        }
      });
    }

    newEmptyState() {
      return {
        columns: Array.from({ length: 10 }, () => []),
        stock: [],
        completedCount: 0,
        completedStacks: [],
        score: 500,
        moves: 0,
        elapsedSeconds: 0,
        difficulty: this.difficulty,
        hasUserAction: false,
        countedResult: false
      };
    }

    installMenu() {
      document.getElementById("new-game-btn").addEventListener("click", () => this.startNewGame(this.difficulty, true));
      document.getElementById("undo-btn").addEventListener("click", () => this.undo());
      document.getElementById("deal-btn").addEventListener("click", () => this.dealFromStock());
      document.getElementById("quick-deal-btn").addEventListener("click", () => this.dealFromStock());
      document.getElementById("hint-btn").addEventListener("click", () => this.showHint());
      document.getElementById("save-btn").addEventListener("click", () => this.saveGame());
      document.getElementById("load-btn").addEventListener("click", () => this.loadGame());
      document.getElementById("difficulty-btn").addEventListener("click", () => this.openDifficultyDialog());
      document.getElementById("stats-btn").addEventListener("click", () => this.openStatsDialog());
      document.getElementById("options-btn").addEventListener("click", () => this.openOptionsDialog());
      document.getElementById("help-content-btn").addEventListener("click", () => this.openHelpContent());
      document.getElementById("about-btn").addEventListener("click", () => this.openAboutDialog());
      document.getElementById("exit-btn").addEventListener("click", () => this.exitGame());
      document.getElementById("stats-close-btn").addEventListener("click", () => this.statsDialogEl.close());
      document.getElementById("stats-reset-btn").addEventListener("click", () => this.resetStats());
      document.getElementById("difficulty-ok-btn").addEventListener("click", () => this.applyDifficultySelection());
      document.getElementById("difficulty-cancel-btn").addEventListener("click", () => this.difficultyDialogEl.close());
      document.getElementById("options-ok-btn").addEventListener("click", () => this.applyOptionsSelection());
      document.getElementById("options-cancel-btn").addEventListener("click", () => this.optionsDialogEl.close());
      document.getElementById("about-ok-btn").addEventListener("click", () => this.aboutDialogEl.close());
      this.scoreBoxEl.addEventListener("click", () => this.showHint());
    }

    installBoardEvents() {
      this.stockEl.addEventListener("click", () => this.dealFromStock());

      this.columnsEl.addEventListener("dragstart", (event) => {
        const cardEl = event.target.closest("img.card");
        const columnEl = event.target.closest(".column");
        if (!cardEl || !columnEl) {
          return;
        }
        const fromCol = Number(columnEl.dataset.col);
        const start = Number(cardEl.dataset.index);
        if (Number.isNaN(fromCol) || Number.isNaN(start) || !this.canSelectCard(fromCol, start)) {
          event.preventDefault();
          return;
        }

        this.dragging = { col: fromCol, start };
        this.clearDragPreview();
        this.dragPreviewEl = this.buildDragPreview(fromCol, start);
        this.playSound("dragStart");
        if (event.dataTransfer) {
          const { cardWidth, faceUpSpacing } = this.getCardLayoutMetrics();
          event.dataTransfer.effectAllowed = "move";
          event.dataTransfer.setData("text/plain", `${fromCol}:${start}`);
          if (this.dragPreviewEl) {
            event.dataTransfer.setDragImage(this.dragPreviewEl, cardWidth / 2, faceUpSpacing);
          }
        }
        this.setStatus("拖动到目标列后松开即可落牌");
      });

      this.columnsEl.addEventListener("dragover", (event) => {
        if (!this.dragging) {
          return;
        }
        const columnEl = event.target.closest(".column");
        if (!columnEl) {
          this.setDragOverColumn(null);
          return;
        }
        const toCol = Number(columnEl.dataset.col);
        if (Number.isNaN(toCol)) {
          this.setDragOverColumn(null);
          return;
        }
        if (!this.canMove(this.dragging.col, this.dragging.start, toCol)) {
          this.setDragOverColumn(null);
          return;
        }
        event.preventDefault();
        if (event.dataTransfer) {
          event.dataTransfer.dropEffect = "move";
        }
        this.setDragOverColumn(toCol);
      });

      this.columnsEl.addEventListener("drop", (event) => {
        if (!this.dragging) {
          return;
        }
        const columnEl = event.target.closest(".column");
        this.setDragOverColumn(null);
        if (!columnEl) {
          this.clearDragPreview();
          this.dragging = null;
          this.selected = null;
          this.render();
          return;
        }
        const toCol = Number(columnEl.dataset.col);
        if (Number.isNaN(toCol)) {
          this.clearDragPreview();
          this.dragging = null;
          this.selected = null;
          this.render();
          return;
        }
        event.preventDefault();
        this.tryMove(this.dragging.col, this.dragging.start, toCol);
        this.clearDragPreview();
        this.dragging = null;
        this.selected = null;
        this.render();
      });

      this.columnsEl.addEventListener("dragend", () => {
        this.setDragOverColumn(null);
        this.clearDragPreview();
        this.dragging = null;
        this.selected = null;
        this.render();
      });

      this.columnsEl.addEventListener("click", (event) => {
        const cardEl = event.target.closest("img.card");
        const columnEl = event.target.closest(".column");
        if (!columnEl) {
          return;
        }
        const col = Number(columnEl.dataset.col);
        if (Number.isNaN(col)) {
          return;
        }
        if (cardEl) {
          const index = Number(cardEl.dataset.index);
          this.onCardClick(col, index);
        } else {
          this.onColumnClick(col);
        }
      });
    }

    installKeyboard() {
      window.addEventListener("keydown", (event) => {
        if (event.key === "F1") {
          event.preventDefault();
          this.openHelpContent();
          return;
        }
        if (event.key === "F2") {
          event.preventDefault();
          this.startNewGame(this.difficulty, true);
          return;
        }
        if (event.key === "F3") {
          event.preventDefault();
          this.openDifficultyDialog();
          return;
        }
        if (event.key === "F4") {
          event.preventDefault();
          this.openStatsDialog();
          return;
        }
        if (event.key === "F5") {
          event.preventDefault();
          this.openOptionsDialog();
          return;
        }
        if (event.ctrlKey && event.key.toLowerCase() === "z") {
          event.preventDefault();
          this.undo();
          return;
        }
        if (event.ctrlKey && event.key.toLowerCase() === "s") {
          event.preventDefault();
          this.saveGame();
          return;
        }
        if (event.ctrlKey && event.key.toLowerCase() === "o") {
          event.preventDefault();
          this.loadGame();
          return;
        }
        if (event.ctrlKey && event.key.toLowerCase() === "t") {
          event.preventDefault();
          this.forceWinForTest();
          return;
        }
        if (!event.ctrlKey && !event.metaKey && event.key.toLowerCase() === "d") {
          event.preventDefault();
          this.dealFromStock();
          return;
        }
        if (!event.ctrlKey && !event.metaKey && event.key.toLowerCase() === "m") {
          event.preventDefault();
          this.showHint();
        }
      });
    }

    loadDifficulty() {
      const value = localStorage.getItem(STORAGE_KEYS.difficulty);
      if (value && DIFFICULTIES[value]) {
        return value;
      }
      return "easy";
    }

    loadOptions() {
      const defaults = {
        animDeal: true,
        saveOnExit: false,
        loadAtStart: false,
        promptSave: true,
        promptLoad: true,
        sound: true
      };
      const raw = localStorage.getItem(STORAGE_KEYS.options);
      if (!raw) {
        return defaults;
      }
      try {
        return { ...defaults, ...JSON.parse(raw) };
      } catch (_err) {
        return defaults;
      }
    }

    persistOptions() {
      localStorage.setItem(STORAGE_KEYS.options, JSON.stringify(this.options));
    }

    initSounds() {
      const table = {
        deal: "resource/WAVE/WAVE124_deal_collect.wav",
        dragStart: "resource/WAVE/WAVE125_drag.wav",
        hintOk: "resource/WAVE/WAVE126_hint_available.wav",
        hintNone: "resource/WAVE/WAVE127_hint_unavailable.wav",
        drop: "resource/WAVE/WAVE128_drop_match.wav",
        win: "resource/WAVE/WAVE129_victory.wav"
      };
      const sounds = {};
      for (const [key, src] of Object.entries(table)) {
        const audio = new Audio(src);
        audio.preload = "auto";
        sounds[key] = audio;
      }
      return sounds;
    }

    playSound(name) {
      if (!this.options.sound) {
        return;
      }
      const audio = this.sounds[name];
      if (!audio) {
        return;
      }
      try {
        audio.currentTime = 0;
        const promise = audio.play();
        if (promise && typeof promise.catch === "function") {
          promise.catch(() => {});
        }
      } catch (_err) {
        // Ignore browser autoplay/runtime audio failures.
      }
    }

    loadStats() {
      const defaults = {
        highScore: 0,
        wins: 0,
        losses: 0,
        bestWinStreak: 0,
        bestLoseStreak: 0,
        currentWinStreak: 0,
        currentLoseStreak: 0
      };
      const raw = localStorage.getItem(STORAGE_KEYS.stats);
      if (!raw) {
        return defaults;
      }
      try {
        return { ...defaults, ...JSON.parse(raw) };
      } catch (_err) {
        return defaults;
      }
    }

    persistStats() {
      localStorage.setItem(STORAGE_KEYS.stats, JSON.stringify(this.stats));
    }

    openStatsDialog() {
      this.refreshStatsDialog();
      this.statsDialogEl.showModal();
    }

    openDifficultyDialog() {
      const radio = this.difficultyDialogEl.querySelector(`input[name='difficulty-choice'][value='${this.difficulty}']`);
      if (radio) {
        radio.checked = true;
      }
      this.difficultyDialogEl.showModal();
    }

    applyDifficultySelection() {
      const checked = this.difficultyDialogEl.querySelector("input[name='difficulty-choice']:checked");
      if (checked && DIFFICULTIES[checked.value]) {
        this.startNewGame(checked.value, true);
      }
      this.difficultyDialogEl.close();
    }

    openOptionsDialog() {
      document.getElementById("opt-anim-deal").checked = this.options.animDeal;
      document.getElementById("opt-save-on-exit").checked = this.options.saveOnExit;
      document.getElementById("opt-load-at-start").checked = this.options.loadAtStart;
      document.getElementById("opt-prompt-save").checked = this.options.promptSave;
      document.getElementById("opt-prompt-load").checked = this.options.promptLoad;
      document.getElementById("opt-sound").checked = this.options.sound;
      this.optionsDialogEl.showModal();
    }

    applyOptionsSelection() {
      this.options.animDeal = document.getElementById("opt-anim-deal").checked;
      this.options.saveOnExit = document.getElementById("opt-save-on-exit").checked;
      this.options.loadAtStart = document.getElementById("opt-load-at-start").checked;
      this.options.promptSave = document.getElementById("opt-prompt-save").checked;
      this.options.promptLoad = document.getElementById("opt-prompt-load").checked;
      this.options.sound = document.getElementById("opt-sound").checked;
      this.persistOptions();
      this.optionsDialogEl.close();
      this.setStatus("选项已更新");
    }

    openAboutDialog() {
      this.aboutDialogEl.showModal();
    }

    openHelpContent() {
      this.setStatus("帮助文件：spider.chm / spider.hlp");
    }

    exitGame() {
      if (this.options.saveOnExit) {
        this.saveGame(false);
      }
      this.setStatus("可直接关闭浏览器标签页退出游戏");
    }

    refreshStatsDialog() {
      const games = this.stats.wins + this.stats.losses;
      const rate = games === 0 ? 0 : ((this.stats.wins / games) * 100);
      document.getElementById("stats-high-score").textContent = String(this.stats.highScore);
      document.getElementById("stats-wins").textContent = String(this.stats.wins);
      document.getElementById("stats-losses").textContent = String(this.stats.losses);
      document.getElementById("stats-win-rate").textContent = `${rate.toFixed(1)}%`;
      document.getElementById("stats-best-win").textContent = String(this.stats.bestWinStreak);
      document.getElementById("stats-best-loss").textContent = String(this.stats.bestLoseStreak);
      document.getElementById("stats-current-win").textContent = String(this.stats.currentWinStreak);
      document.getElementById("stats-current-loss").textContent = String(this.stats.currentLoseStreak);
    }

    resetStats() {
      this.stats = {
        highScore: 0,
        wins: 0,
        losses: 0,
        bestWinStreak: 0,
        bestLoseStreak: 0,
        currentWinStreak: 0,
        currentLoseStreak: 0
      };
      this.persistStats();
      this.refreshStatsDialog();
      this.setStatus("统计已复位");
    }

    startTicker() {
      if (this.timerId) {
        clearInterval(this.timerId);
      }
      this.timerId = setInterval(() => {
        this.state.elapsedSeconds += 1;
        this.renderHud();
      }, 1000);
    }

    startNewGame(difficultyKey, announce) {
      this.victoryAnimator.stop();
      const difficulty = DIFFICULTIES[difficultyKey] ? difficultyKey : "easy";
      this.difficulty = difficulty;
      localStorage.setItem(STORAGE_KEYS.difficulty, difficulty);

      const deck = this.buildDeck(difficulty);
      this.shuffle(deck);

      this.state = this.newEmptyState();
      this.state.difficulty = difficulty;
      this.state.stock = deck;
      this.selected = null;
      this.clearHintState(false);
      this.undoDisabled = false;
      this.clearDealAnimationState();

      this.initialDeal();
      this.timeline = [this.serializeState()];
      this.currentIndex = 0;
      this.minUndoIndex = 0;
      this.render();
      if (announce) {
        this.setStatus(`已开始 ${DIFFICULTIES[difficulty].label}`);
      } else {
        this.setStatus(`当前难度：${DIFFICULTIES[difficulty].label}`);
      }
    }

    buildDeck(difficultyKey) {
      const config = DIFFICULTIES[difficultyKey];
      const deck = [];
      for (const suit of config.suits) {
        for (let c = 0; c < config.copiesPerSuit; c += 1) {
          for (let rank = 1; rank <= 13; rank += 1) {
            deck.push(this.createCard(suit, rank));
          }
        }
      }
      return deck;
    }

    createCard(suit, rank) {
      return {
        id: this.nextCardId++,
        suit,
        rank,
        faceUp: false,
        imageIndex: SUIT_BASE[suit] + rank
      };
    }

    shuffle(cards) {
      for (let i = cards.length - 1; i > 0; i -= 1) {
        const j = Math.floor(Math.random() * (i + 1));
        [cards[i], cards[j]] = [cards[j], cards[i]];
      }
    }

    initialDeal() {
      for (let c = 0; c < 10; c += 1) {
        const count = c < 4 ? 6 : 5;
        for (let i = 0; i < count; i += 1) {
          const card = this.state.stock.pop();
          if (!card) {
            continue;
          }
          card.faceUp = i === count - 1;
          this.state.columns[c].push(card);
        }
      }
    }

    serializeState() {
      return JSON.parse(JSON.stringify(this.state));
    }

    restoreState(snapshot) {
      this.state = JSON.parse(JSON.stringify(snapshot));
      if (!Array.isArray(this.state.completedStacks)) {
        const fallbackSuit = DIFFICULTIES[this.difficulty]?.suits?.[0] || "spades";
        this.state.completedStacks = Array.from({ length: this.state.completedCount || 0 }, () => ({ suit: fallbackSuit }));
      }
      this.state.completedCount = this.state.completedStacks.length;
      this.selected = null;
      this.clearHintState(false);
      this.clearDealAnimationState();
      this.victoryAnimator.stop();
      this.render();
    }

    buildDragPreview(fromCol, start) {
      const moving = this.state.columns[fromCol].slice(start);
      if (!moving.length) {
        return null;
      }
      const { cardWidth, cardHeight, faceUpSpacing } = this.getCardLayoutMetrics();
      const preview = document.createElement("div");
      preview.className = "drag-preview";
      preview.style.width = `${cardWidth}px`;
      const height = cardHeight + Math.max(0, moving.length - 1) * faceUpSpacing;
      preview.style.height = `${height}px`;

      for (let i = 0; i < moving.length; i += 1) {
        const card = moving[i];
        const img = document.createElement("img");
        img.className = "drag-preview-card";
        img.src = this.cardImage(card);
        img.alt = card.faceUp ? `${card.suit} ${this.formatRank(card.rank)}` : "背面";
        img.style.width = `${cardWidth}px`;
        img.style.height = `${cardHeight}px`;
        img.style.top = `${i * faceUpSpacing}px`;
        preview.appendChild(img);
      }

      document.body.appendChild(preview);
      return preview;
    }

    clearDragPreview() {
      if (!this.dragPreviewEl) {
        return;
      }
      this.dragPreviewEl.remove();
      this.dragPreviewEl = null;
    }

    clearDealAnimationState() {
      this.dealAnimationOrder.clear();
      if (this.dealAnimationTimer) {
        clearTimeout(this.dealAnimationTimer);
        this.dealAnimationTimer = null;
      }
    }

    clearHintState(shouldRender) {
      this.hint = null;
      if (this.hintTimers.length) {
        for (const timer of this.hintTimers) {
          clearTimeout(timer);
        }
      }
      this.hintTimers = [];
      if (shouldRender) {
        this.render();
      }
    }

    animateCollectToCompleted(col, column, start, removedCards, slotIndex) {
      const columnEl = this.columnsEl.querySelector(`.column[data-col='${col}']`);
      if (!columnEl || !removedCards.length) {
        return;
      }

      const columnRect = columnEl.getBoundingClientRect();
      const completedRect = this.completedEl.getBoundingClientRect();
      const { cardWidth, cardHeight } = this.getCardLayoutMetrics();
      const gap = parseFloat(window.getComputedStyle(this.completedEl).columnGap || window.getComputedStyle(this.completedEl).gap || "6") || 6;

      const targetX = completedRect.left + slotIndex * (cardWidth + gap);
      const targetY = completedRect.bottom - cardHeight;
      const cardLeft = columnRect.left + (columnRect.width - cardWidth) / 2;

      for (let i = 0; i < removedCards.length; i += 1) {
        const card = removedCards[i];
        const indexInColumn = start + i;
        const startY = columnRect.top + this.computeCardTop(column, indexInColumn);

        const flyer = document.createElement("img");
        flyer.className = "collect-fly-card";
        flyer.src = this.cardImage(card);
        flyer.alt = "collect";
        flyer.style.left = `${cardLeft}px`;
        flyer.style.top = `${startY}px`;
        flyer.style.width = `${cardWidth}px`;
        flyer.style.height = `${cardHeight}px`;
        document.body.appendChild(flyer);

        const animation = flyer.animate(
          [
            { transform: "translate3d(0, 0, 0)", opacity: 1 },
            { transform: `translate3d(${targetX - cardLeft}px, ${targetY - startY}px, 0)`, opacity: 1 }
          ],
          {
            duration: 130,
            delay: i * 24,
            easing: "cubic-bezier(0.2, 0.65, 0.25, 1)",
            fill: "forwards"
          }
        );
        animation.onfinish = () => {
          flyer.remove();
        };
      }
    }

    scheduleDealAnimationCleanup() {
      if (this.dealAnimationTimer) {
        clearTimeout(this.dealAnimationTimer);
      }
      this.dealAnimationTimer = window.setTimeout(() => {
        this.dealAnimationOrder.clear();
        this.dealAnimationTimer = null;
      }, 900);
    }

    animateDealFromStock() {
      const stockRect = this.stockEl.getBoundingClientRect();
      const { cardWidth, cardHeight } = this.getCardLayoutMetrics();
      const startX = stockRect.left + (stockRect.width - cardWidth) / 2;
      const startY = stockRect.top + (stockRect.height - cardHeight) / 2;

      for (const [cardId, order] of this.dealAnimationOrder.entries()) {
        const targetCard = this.columnsEl.querySelector(`img.card[data-card-id='${cardId}']`);
        if (!targetCard) {
          continue;
        }
        const targetRect = targetCard.getBoundingClientRect();
        const flyer = document.createElement("img");
        flyer.className = "deal-fly-card";
        flyer.src = targetCard.getAttribute("src") || "resource/FELT/CARDBACK.bmp";
        flyer.alt = "deal";
        flyer.style.left = `${startX}px`;
        flyer.style.top = `${startY}px`;
        document.body.appendChild(flyer);

        const endX = targetRect.left;
        const endY = targetRect.top;
        const animation = flyer.animate(
          [
            { transform: "translate3d(0, 0, 0)", opacity: 1 },
            { transform: `translate3d(${endX - startX}px, ${endY - startY}px, 0)`, opacity: 1 }
          ],
          {
            duration: 210,
            delay: order * 48,
            easing: "cubic-bezier(0.2, 0.65, 0.25, 1)",
            fill: "forwards"
          }
        );
        animation.onfinish = () => {
          targetCard.classList.remove("deal-hidden");
          this.dealAnimationOrder.delete(cardId);
          flyer.remove();
        };
      }
    }

    onCardClick(col, index) {
      const card = this.state.columns[col][index];
      if (!card || !card.faceUp) {
        return;
      }
      if (this.selected) {
        if (this.selected.col === col && this.selected.start === index) {
          this.selected = null;
          this.render();
          return;
        }
        if (this.tryMove(this.selected.col, this.selected.start, col)) {
          this.selected = null;
          this.render();
          return;
        }
      }
      if (this.canSelectCard(col, index)) {
        this.selected = { col, start: index };
        this.render();
      }
    }

    onColumnClick(col) {
      if (!this.selected) {
        return;
      }
      if (this.tryMove(this.selected.col, this.selected.start, col)) {
        this.selected = null;
        this.render();
      }
    }

    canSelectCard(col, start) {
      const column = this.state.columns[col];
      if (!column[start] || !column[start].faceUp) {
        return false;
      }
      return this.isDescending(column, start);
    }

    isDescending(column, start) {
      for (let i = start; i < column.length - 1; i += 1) {
        if (!column[i].faceUp || !column[i + 1].faceUp) {
          return false;
        }
        if (column[i].rank !== column[i + 1].rank + 1) {
          return false;
        }
      }
      return true;
    }

    canMove(fromCol, start, toCol) {
      if (fromCol === toCol) {
        return false;
      }
      const source = this.state.columns[fromCol];
      const target = this.state.columns[toCol];
      if (!source || !target || !source[start]) {
        return false;
      }
      if (!this.isDescending(source, start)) {
        return false;
      }

      const moving = source.slice(start);
      if (!target.length) {
        return true;
      }

      const movingBase = moving[0];
      const top = target[target.length - 1];
      return top.rank === movingBase.rank + 1;
    }

    setDragOverColumn(col) {
      if (this.dragOverCol !== null) {
        const prev = this.columnsEl.querySelector(`.column[data-col='${this.dragOverCol}']`);
        if (prev) {
          prev.classList.remove("drag-target");
        }
      }
      this.dragOverCol = col;
      if (col === null) {
        return;
      }
      const current = this.columnsEl.querySelector(`.column[data-col='${col}']`);
      if (current) {
        current.classList.add("drag-target");
      }
    }

    tryMove(fromCol, start, toCol) {
      if (!this.canMove(fromCol, start, toCol)) {
        return false;
      }

      this.clearHintState(false);

      const source = this.state.columns[fromCol];
      const target = this.state.columns[toCol];
      const moving = source.slice(start);

      source.splice(start, moving.length);
      target.push(...moving);
      this.playSound("drop");

      this.state.moves += 1;
      this.state.score -= 1;
      this.state.hasUserAction = true;

      this.revealTopIfNeeded(fromCol);
      const removed = this.removeCompletedSet(toCol);
      if (fromCol !== toCol) {
        this.removeCompletedSet(fromCol);
      }

      this.commitAction(removed ? "complete" : "move");
      this.checkWin();
      return true;
    }

    revealTopIfNeeded(col) {
      const column = this.state.columns[col];
      if (!column.length) {
        return;
      }
      const top = column[column.length - 1];
      if (!top.faceUp) {
        top.faceUp = true;
      }
    }

    removeCompletedSet(col) {
      const column = this.state.columns[col];
      if (column.length < 13) {
        return false;
      }
      const start = column.length - 13;
      const suit = column[start].suit;
      for (let i = start; i < column.length; i += 1) {
        const expected = 13 - (i - start);
        if (!column[i].faceUp) {
          return false;
        }
        if (column[i].suit !== suit || column[i].rank !== expected) {
          return false;
        }
      }

      const removedCards = column.slice(start);
      const slotIndex = this.state.completedCount;
      if (this.options.animDeal) {
        this.animateCollectToCompleted(col, column, start, removedCards, slotIndex);
      }

      column.splice(start, 13);
      this.state.completedStacks.push({ suit });
      this.state.completedCount += 1;
      this.state.score += 100;
      this.playSound("deal");
      this.revealTopIfNeeded(col);
      this.setStatus("完成一组同花色 K-A，+100 分");
      return true;
    }

    commitAction(type) {
      this.timeline = this.timeline.slice(0, this.currentIndex + 1);
      this.timeline.push(this.serializeState());
      this.currentIndex += 1;
      if (type === "deal" || type === "complete") {
        this.minUndoIndex = this.currentIndex;
      }
      this.render();
    }

    undo() {
      if (this.undoDisabled) {
        this.setStatus("已打开保存游戏，撤销不可用");
        return;
      }
      if (this.currentIndex <= this.minUndoIndex) {
        this.setStatus("已达到 XP 撤销边界");
        return;
      }
      if (this.currentIndex === 0) {
        this.setStatus("没有可撤销的操作");
        return;
      }
      const scoreBeforeUndo = this.state.score;
      this.currentIndex -= 1;
      const snapshot = this.timeline[this.currentIndex];
      this.restoreState(snapshot);
      this.state.moves += 1;
      if (scoreBeforeUndo < 0) {
        this.state.score = 0;
      } else {
        this.state.score -= 1;
      }
      if (this.state.score < 0) {
        this.state.score = 0;
      }
      this.state.hasUserAction = true;
      this.setStatus("已撤销一步");
      this.render();
    }

    canDeal() {
      if (this.state.stock.length < 10) {
        return false;
      }
      return this.state.columns.every((column) => column.length > 0);
    }

    dealFromStock() {
      if (!this.canDeal()) {
        this.setStatus("发牌失败：上方 10 列必须都有牌");
        return;
      }
      this.dealAnimationOrder.clear();
      for (let c = 0; c < 10; c += 1) {
        const card = this.state.stock.pop();
        if (!card) {
          continue;
        }
        card.faceUp = true;
        this.state.columns[c].push(card);
        if (this.options.animDeal) {
          this.dealAnimationOrder.set(card.id, c);
        }
      }

      let removedByDeal = false;
      for (let c = 0; c < 10; c += 1) {
        if (this.removeCompletedSet(c)) {
          removedByDeal = true;
        }
      }

      this.state.hasUserAction = true;
      this.commitAction("deal");
      if (this.options.animDeal) {
        this.animateDealFromStock();
        this.scheduleDealAnimationCleanup();
      } else {
        this.dealAnimationOrder.clear();
      }
      this.playSound("deal");
      this.setStatus(removedByDeal ? "已发牌，并自动移除完成序列" : "已发牌");
      this.checkWin();
    }

    findHintMoves() {
      const moves = [];
      for (let fromCol = 0; fromCol < 10; fromCol += 1) {
        const column = this.state.columns[fromCol];
        for (let start = 0; start < column.length; start += 1) {
          const card = column[start];
          if (!card || !card.faceUp) {
            continue;
          }
          if (!this.isDescending(column, start)) {
            continue;
          }
          const movingLength = column.length - start;
          const movingCard = column[start];
          for (let toCol = 0; toCol < 10; toCol += 1) {
            if (toCol === fromCol) {
              continue;
            }
            const target = this.state.columns[toCol];
            if (target.length > 0) {
              const top = target[target.length - 1];
              if (top.rank !== movingCard.rank + 1) {
                continue;
              }

              // XP hint behavior: if this move only relocates a card from one
              // support rank to another equal support rank, suppress the hint.
              const sourceSupport = start > 0 ? column[start - 1] : null;
              if (sourceSupport && sourceSupport.rank === top.rank) {
                continue;
              }

              if (top.suit === movingCard.suit) {
                moves.push({ fromCol, start, toCol, len: movingLength, priority: 1 });
              } else {
                const hasDifferentParent = start > 0 && column[start - 1].suit !== movingCard.suit;
                const bothDifferentSuit = top.suit !== movingCard.suit;
                if (hasDifferentParent && bothDifferentSuit) {
                  continue;
                }
                moves.push({ fromCol, start, toCol, len: movingLength, priority: 2 });
              }
            } else {
              moves.push({ fromCol, start, toCol, len: movingLength, priority: 3 });
            }
          }
        }
      }
      moves.sort((a, b) => {
        if (a.priority !== b.priority) {
          return a.priority - b.priority;
        }
        if (a.len !== b.len) {
          return b.len - a.len;
        }
        return a.fromCol - b.fromCol;
      });
      return moves;
    }

    showHint() {
      this.clearHintState(false);
      const moves = this.findHintMoves();
      if (!moves.length) {
        this.playSound("hintNone");
        this.setStatus("没有可提示的操作");
        this.clearHintState(true);
        return;
      }

      const moveKeys = moves.map((item) => `${item.fromCol}:${item.start}:${item.toCol}:${item.len}`).join("|");
      if (moveKeys !== this.hintSequenceKey) {
        this.hintSequenceKey = moveKeys;
        this.hintChoiceIndex = 0;
      }
      const move = moves[this.hintChoiceIndex % moves.length];
      this.hintChoiceIndex = (this.hintChoiceIndex + 1) % moves.length;

      const targetColumn = this.state.columns[move.toCol];
      const sourcePhaseMs = 500;
      const phaseGapMs = 250;
      const targetPhaseMs = 500;
      const totalMs = Math.max(sourcePhaseMs, phaseGapMs + targetPhaseMs);

      this.playSound("hintOk");
      this.hint = {
        ...move,
        targetIndex: targetColumn.length ? targetColumn.length - 1 : -1,
        phase: "source"
      };
      this.setStatus(`提示：第 ${move.fromCol + 1} 列 -> 第 ${move.toCol + 1} 列`);
      this.render();

      const toTargetTimer = window.setTimeout(() => {
        if (!this.hint) {
          return;
        }
        this.hint.phase = "target";
        this.render();
      }, phaseGapMs);

      const resetTimer = window.setTimeout(() => {
        this.clearHintState(true);
      }, totalMs);

      this.hintTimers.push(toTargetTimer, resetTimer);
    }

    recordWinIfNeeded() {
      if (this.state.countedResult) {
        return;
      }
      this.state.countedResult = true;
      this.stats.wins += 1;
      this.stats.currentWinStreak += 1;
      this.stats.currentLoseStreak = 0;
      if (this.stats.currentWinStreak > this.stats.bestWinStreak) {
        this.stats.bestWinStreak = this.stats.currentWinStreak;
      }
      if (this.state.score > this.stats.highScore) {
        this.stats.highScore = this.state.score;
      }
      this.persistStats();
    }

    recordLossIfNeeded(reason) {
      if (this.state.countedResult) {
        return;
      }
      this.state.countedResult = true;
      this.stats.losses += 1;
      this.stats.currentLoseStreak += 1;
      this.stats.currentWinStreak = 0;
      if (this.stats.currentLoseStreak > this.stats.bestLoseStreak) {
        this.stats.bestLoseStreak = this.stats.currentLoseStreak;
      }
      this.persistStats();
      if (reason === "save") {
        this.setStatus("已保存：按 XP 规则，此局计为负")
      }
    }

    forceWinForTest() {
      const suits = DIFFICULTIES[this.difficulty]?.suits || ["spades"];
      this.state.completedStacks = Array.from({ length: 8 }, (_, i) => ({ suit: suits[i % suits.length] }));
      this.state.completedCount = 8;
      this.state.score = Math.max(this.state.score, 800);
      this.state.hasUserAction = true;
      this.commitAction("complete");
      this.checkWin();
    }

    checkWin() {
      if (this.state.completedCount < 8) {
        return;
      }
      this.playSound("win");
      this.recordWinIfNeeded();
      this.victoryAnimator.start();
      this.setStatus("恭喜通关！本局计为胜")
    }

    saveGame(allowPrompt = true) {
      if (allowPrompt && this.options.promptSave && !window.confirm("保存的游戏已存在。是否用当前的游戏替换上次保存的游戏?")) {
        return;
      }
      const payload = {
        state: this.serializeState(),
        difficulty: this.difficulty,
        savedAt: Date.now()
      };
      localStorage.setItem(STORAGE_KEYS.save, JSON.stringify(payload));
      this.recordLossIfNeeded("save");
      this.setStatus("游戏已保存（单存档槽，覆盖旧档）");
    }

    loadGame(allowPrompt = true) {
      if (allowPrompt && this.options.promptLoad && !window.confirm("是否放弃当前正在玩的游戏，加载上次保存的游戏?")) {
        return;
      }
      const raw = localStorage.getItem(STORAGE_KEYS.save);
      if (!raw) {
        this.setStatus("没有已保存的游戏");
        return;
      }
      try {
        const payload = JSON.parse(raw);
        const snapshot = payload.state;
        if (!snapshot || !Array.isArray(snapshot.columns)) {
          this.setStatus("存档格式无效");
          return;
        }
        this.difficulty = payload.difficulty && DIFFICULTIES[payload.difficulty] ? payload.difficulty : this.difficulty;
        localStorage.setItem(STORAGE_KEYS.difficulty, this.difficulty);
        this.restoreState(snapshot);
        this.state.hasUserAction = false;
        this.timeline = [this.serializeState()];
        this.currentIndex = 0;
        this.minUndoIndex = 0;
        this.undoDisabled = true;
        this.setStatus("已打开上次保存的游戏（撤销不可用）");
      } catch (_err) {
        this.setStatus("打开存档失败");
      }
    }

    cardImage(card) {
      if (!card.faceUp) {
        return "resource/FELT/CARDBACK.bmp";
      }
      return `resource/FELT/CARD${card.imageIndex}.bmp`;
    }

    formatRank(rank) {
      return RANK_LABEL[rank] || String(rank);
    }

    render() {
      this.renderColumns();
      this.renderStock();
      this.renderCompleted();
      this.renderHud();
      this.updateDifficultyChecks();
      this.updateMenuStates();
    }

    updateMenuStates() {
      const undoBtn = document.getElementById("undo-btn");
      const dealBtn = document.getElementById("deal-btn");
      const quickDealBtn = document.getElementById("quick-deal-btn");
      const hintBtn = document.getElementById("hint-btn");
      const saveBtn = document.getElementById("save-btn");

      if (undoBtn) {
        const disabled = this.undoDisabled || this.currentIndex <= this.minUndoIndex;
        undoBtn.classList.toggle("disabled", disabled);
      }
      if (dealBtn) {
        dealBtn.classList.toggle("disabled", !this.canDeal());
      }
      if (quickDealBtn) {
        quickDealBtn.classList.toggle("disabled", !this.canDeal());
      }
      if (hintBtn) {
        hintBtn.classList.toggle("disabled", !this.findHintMoves().length);
      }
      if (saveBtn) {
        saveBtn.classList.toggle("disabled", !this.state.hasUserAction);
      }
    }

    renderColumns() {
      this.columnsEl.innerHTML = "";
      for (let col = 0; col < 10; col += 1) {
        const colEl = document.createElement("div");
        colEl.className = "column";
        colEl.dataset.col = String(col);

        const column = this.state.columns[col];
        if (!column.length) {
          colEl.classList.add("empty-target");
        }

        for (let i = 0; i < column.length; i += 1) {
          const card = column[i];
          const cardEl = document.createElement("img");
          cardEl.className = "card";
          cardEl.src = this.cardImage(card);
          cardEl.alt = card.faceUp ? `${card.suit} ${this.formatRank(card.rank)}` : "背面";
          cardEl.dataset.index = String(i);
          cardEl.dataset.cardId = String(card.id);
          cardEl.draggable = card.faceUp && this.canSelectCard(col, i);

          const top = this.computeCardTop(column, i);
          cardEl.style.top = `${top}px`;

          if (this.dealAnimationOrder.has(card.id)) {
            cardEl.classList.add("deal-hidden");
          }

          if (this.selected && this.selected.col === col && i >= this.selected.start) {
            cardEl.classList.add("selecting");
          }
          if (this.hint && this.hint.phase === "source" && this.hint.fromCol === col && i >= this.hint.start) {
            cardEl.classList.add("hint-flip-source");
          }
          if (this.hint && this.hint.phase === "target" && this.hint.toCol === col && i === this.hint.targetIndex) {
            cardEl.classList.add("hint-flip-target");
          }
          colEl.appendChild(cardEl);
        }

        if (this.hint && this.hint.phase === "target" && this.hint.toCol === col && column.length === 0) {
          colEl.classList.add("hint-flip-target-empty");
        }
        this.columnsEl.appendChild(colEl);
      }
    }

    computeCardTop(column, index) {
      const { faceUpSpacing, faceDownSpacing } = this.getCardLayoutMetrics();
      let top = 0;
      for (let i = 0; i < index; i += 1) {
        top += column[i].faceUp ? faceUpSpacing : faceDownSpacing;
      }
      return top;
    }

    getCardLayoutMetrics() {
      const probeCard = this.columnsEl.querySelector("img.card") || this.stockEl.querySelector(".stock-card");
      const cardWidth = probeCard ? probeCard.getBoundingClientRect().width : 88;
      const cardHeight = probeCard ? probeCard.getBoundingClientRect().height : 120;
      const faceUpSpacing = Math.max(20, Math.round(cardHeight * 0.2));
      const faceDownSpacing = Math.max(10, Math.round(cardHeight * 0.1));
      return { cardWidth, cardHeight, faceUpSpacing, faceDownSpacing };
    }

    renderStock() {
      this.stockEl.innerHTML = "";
      const packCount = Math.floor(this.state.stock.length / 10);
      for (let i = 0; i < packCount; i += 1) {
        const stackEl = document.createElement("div");
        stackEl.className = "stock-card";
        stackEl.style.right = `${(packCount - i - 1) * 8}px`;
        this.stockEl.appendChild(stackEl);
      }
    }

    renderCompleted() {
      this.completedEl.innerHTML = "";
      const stacks = Array.isArray(this.state.completedStacks) ? this.state.completedStacks : [];
      for (let i = 0; i < stacks.length; i += 1) {
        const suit = stacks[i].suit;
        const kingIndex = (SUIT_BASE[suit] || SUIT_BASE.spades) + 13;
        const slot = document.createElement("div");
        slot.className = "complete-slot";
        const cardEl = document.createElement("img");
        cardEl.className = "complete-slot-card";
        cardEl.src = `resource/FELT/CARD${kingIndex}.bmp`;
        cardEl.alt = `${suit} K`;
        slot.appendChild(cardEl);
        this.completedEl.appendChild(slot);
      }
      this.state.completedCount = stacks.length;
    }

    renderHud() {
      this.scoreEl.textContent = String(this.state.score);
      this.movesEl.textContent = String(this.state.moves);
      this.timeEl.textContent = this.formatTime(this.state.elapsedSeconds);
    }

    updateDifficultyChecks() {
      const radios = document.querySelectorAll("input[name='difficulty-choice']");
      for (const radio of radios) {
        radio.checked = radio.value === this.difficulty;
      }
    }

    formatTime(totalSeconds) {
      const minutes = Math.floor(totalSeconds / 60);
      const seconds = totalSeconds % 60;
      return `${String(minutes).padStart(2, "0")}:${String(seconds).padStart(2, "0")}`;
    }

    setStatus(message) {
      this.statusEl.textContent = message;
    }
  }

  window.addEventListener("DOMContentLoaded", () => {
    const game = new SpiderGame();
    window.spiderGame = game;
  });
})();
