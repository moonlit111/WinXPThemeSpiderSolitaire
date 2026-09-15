/**
 * AudioService.js
 * Manages game sound effects using Web Audio API / Audio elements.
 */

export class AudioService {
  constructor() {
    this.enabled = localStorage.getItem('spider_sound') !== 'false';
    this.sounds = {
      deal: 'assets/sounds/deal.wav',
      drop: 'assets/sounds/drop.wav',
      click: 'assets/sounds/click.wav',
      complete: 'assets/sounds/complete.wav',
      dealRound: 'assets/sounds/deal_round.wav',
      win: 'assets/sounds/win.wav'
    };
    this.audioCache = {};
    this.preload();
  }

  preload() {
    for (const [key, src] of Object.entries(this.sounds)) {
      const audio = new Audio(src);
      audio.preload = 'auto';
      this.audioCache[key] = audio;
    }
  }

  play(name) {
    if (!this.enabled) return;
    try {
      const src = this.sounds[name];
      if (!src) return;
      // Use cloneNode or create a new Audio instance so sounds can overlap cleanly
      const audio = new Audio(src);
      audio.volume = 0.8;
      audio.play().catch(() => {
        // Autoplay policy or interaction needed
      });
    } catch (e) {
      console.warn('Audio playback failed:', e);
    }
  }

  toggleSound() {
    this.enabled = !this.enabled;
    localStorage.setItem('spider_sound', this.enabled ? 'true' : 'false');
    return this.enabled;
  }
}
