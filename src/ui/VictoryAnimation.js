/**
 * VictoryAnimation.js
 * 1:1 Windows XP Spider Solitaire Victory Celebration (FUN_01008b21 / FUN_010084c1 / FUN_01008309 / FUN_01008700)
 * Features:
 * - Dual-station continuous fireworks launching and radial particle bursts (100 particles per burst)
 * - Authentic GDI Ellipse sparks with gravity, drag, and glowing particle trails
 * - Centered "你赢了!" (YOU WIN! / String 0x2d) rainbow rotating text in bold SimSun
 */

export class VictoryAnimation {
  constructor() {
    this.canvas = document.getElementById('victory-canvas');
    this.ctx = this.canvas ? this.canvas.getContext('2d') : null;
    this.isRunning = false;
    this.animationId = null;

    this.rockets = [];
    this.particles = [];
    this.lastLaunch = 0;
    this.launchInterval = 450;
  }

  start() {
    if (!this.canvas || !this.ctx) return;
    this.isRunning = true;
    this.canvas.style.display = 'block';
    this.resize();

    this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
    this.rockets = [];
    this.particles = [];
    this.lastLaunch = 0;

    window.addEventListener('resize', this.onResize);

    // Initial dual launch stations (FUN_01008d21)
    this.launchRocket(this.canvas.width * 0.35);
    this.launchRocket(this.canvas.width * 0.65);

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
    this.rockets = [];
    this.particles = [];
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

  launchRocket(targetX = null) {
    const w = this.canvas.width;
    const h = this.canvas.height;
    const x = targetX !== null ? targetX : w * (0.2 + Math.random() * 0.6);
    const targetY = h * (0.15 + Math.random() * 0.35);
    const speed = Math.sqrt(2 * 0.25 * (h - targetY));

    const colors = [
      '#ff3b30', '#ff9500', '#ffcc00', '#34c759',
      '#00c7be', '#32ade6', '#007aff', '#5856d6',
      '#af52de', '#ff2d55', '#ffffff'
    ];
    const color = colors[Math.floor(Math.random() * colors.length)];

    this.rockets.push({
      x,
      y: h,
      vx: (Math.random() - 0.5) * 2,
      vy: -speed,
      targetY,
      color,
      trail: []
    });
  }

  explodeRocket(rocket) {
    const count = 100; // FUN_010084c1: exactly 100 particles!
    const colors = [
      rocket.color,
      '#ffffff',
      '#ffcc00',
      '#ff3b30',
      '#34c759',
      '#32ade6'
    ];

    for (let i = 0; i < count; i++) {
      const angle = Math.random() * Math.PI * 2;
      const speed = Math.random() * 5.5 + 1.2;
      const c = Math.random() < 0.7 ? rocket.color : colors[Math.floor(Math.random() * colors.length)];

      this.particles.push({
        x: rocket.x,
        y: rocket.y,
        vx: Math.cos(angle) * speed,
        vy: Math.sin(angle) * speed,
        color: c,
        radius: Math.random() * 2.5 + 1.5,
        alpha: 1.0,
        decay: Math.random() * 0.015 + 0.012,
        gravity: 0.12 // FUN_010084c1 gravity
      });
    }
  }

  loop = (timestamp = 0) => {
    if (!this.isRunning) return;

    // Semi-transparent fade to create authentic particle trails
    this.ctx.fillStyle = 'rgba(0, 70, 30, 0.22)';
    this.ctx.fillRect(0, 0, this.canvas.width, this.canvas.height);

    // Auto launch rockets
    if (!this.lastLaunch || timestamp - this.lastLaunch > this.launchInterval) {
      this.launchRocket();
      this.lastLaunch = timestamp;
      this.launchInterval = 380 + Math.random() * 400;
    }

    // Update and draw rockets
    for (let i = this.rockets.length - 1; i >= 0; i--) {
      const r = this.rockets[i];
      r.x += r.vx;
      r.y += r.vy;
      r.vy += 0.15; // rocket gravity deceleration

      // Draw spark
      this.ctx.beginPath();
      this.ctx.arc(r.x, r.y, 3, 0, Math.PI * 2);
      this.ctx.fillStyle = r.color;
      this.ctx.fill();

      // Smoke / flame trail
      r.trail.push({ x: r.x, y: r.y, alpha: 1.0 });
      if (r.trail.length > 8) r.trail.shift();

      for (const t of r.trail) {
        this.ctx.beginPath();
        this.ctx.arc(t.x, t.y, 2, 0, Math.PI * 2);
        this.ctx.fillStyle = `rgba(255, 200, 50, ${t.alpha})`;
        this.ctx.fill();
        t.alpha -= 0.12;
      }

      if (r.y <= r.targetY || r.vy >= 0) {
        this.explodeRocket(r);
        this.rockets.splice(i, 1);
      }
    }

    // Update and draw particles (FUN_01008700: Ellipse with GDI brush)
    for (let i = this.particles.length - 1; i >= 0; i--) {
      const p = this.particles[i];
      p.x += p.vx;
      p.y += p.vy;
      p.vx *= 0.985;
      p.vy *= 0.985;
      p.vy += p.gravity;
      p.alpha -= p.decay;

      if (p.alpha <= 0) {
        this.particles.splice(i, 1);
        continue;
      }

      this.ctx.save();
      this.ctx.globalAlpha = Math.max(0, p.alpha);
      this.ctx.beginPath();
      this.ctx.arc(p.x, p.y, p.radius, 0, Math.PI * 2);
      this.ctx.fillStyle = p.color;
      this.ctx.shadowBlur = 6;
      this.ctx.shadowColor = p.color;
      this.ctx.fill();
      this.ctx.restore();
    }

    // Draw central "你赢了!" text with rainbow cycling color (FUN_01008309)
    const cx = this.canvas.width / 2;
    const cy = this.canvas.height / 2 - 20;
    const hue = (Date.now() / 15) % 360;

    this.ctx.save();
    this.ctx.font = 'bold 56px "SimSun", "宋体", "Tahoma", sans-serif';
    this.ctx.textAlign = 'center';
    this.ctx.textBaseline = 'middle';

    // Black stroke shadow outline
    this.ctx.strokeStyle = '#000000';
    this.ctx.lineWidth = 6;
    this.ctx.strokeText('你赢了!', cx, cy);

    // Rainbow rotating fill
    this.ctx.fillStyle = `hsl(${hue}, 100%, 65%)`;
    this.ctx.fillText('你赢了!', cx, cy);
    this.ctx.restore();

    this.animationId = requestAnimationFrame(this.loop);
  };
}
