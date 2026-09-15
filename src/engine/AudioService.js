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

export class AudioService {
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
