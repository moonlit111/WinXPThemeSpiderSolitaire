/**
 * main.js
 * Application entry point: connects 1:1 reverse-engineered game engine, audio, UI,
 * per-difficulty statistics, and keyboard shortcuts.
 */

import { SpiderGame, DIFFICULTY } from './engine/SpiderGame.js';
import { AudioService } from './engine/AudioService.js';
import { Renderer } from './ui/Renderer.js';
import { Dialogs } from './ui/Dialogs.js';
import { VictoryAnimation } from './ui/VictoryAnimation.js';
import { Interaction } from './ui/Interaction.js';

class App {
  constructor() {
    this.stats = this.loadStats();
    this.audio = new AudioService();
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

    // Hook game events
    this.game.onChange((event, data) => {
      if (event === 'undo') {
        this.renderer.render();
      } else if (event === 'move' || event === 'deal') {
        if (data.isWin) {
          this.recordGameResult(true, this.game.score);
        }
      }
    });

    this.renderer.render();
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

  startNewGame(diff = null) {
    if (diff !== null) {
      this.game.difficulty = diff;
      localStorage.setItem('spider_difficulty', diff);
    }

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
        if (!isActive) item.classList.add('active');
      });
    });

    window.addEventListener('click', () => {
      menuItems.forEach(m => m.classList.remove('active'));
    });

    const actionMap = {
      // String ID 3: "是否开始新游戏?"
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
      // String ID 4: "是否从头开始这次游戏?"
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
          this.game.undo();
          this.audio.play('drop');
        }
      },
      // FUN_01004dfb: Exact Hint logic & cycling
      'hint': async () => {
        const hint = this.game.getNextHint();
        if (hint) {
          this.audio.play('hint'); // 126.wav
          await this.renderer.playHintAnimation(hint);
        } else {
          this.audio.play('noHint'); // 127.wav
          this.dialogs.showAlert('提示', '没有可用的移动，请点击右下角发牌区发新牌。');
        }
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
      'sound-toggle': () => {
        const enabled = this.audio.toggleSound();
        const soundLabel = document.getElementById('menu-sound-check');
        if (soundLabel) soundLabel.textContent = enabled ? '✓ ' : '   ';
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
      // F2: New Game
      if (e.key === 'F2') {
        e.preventDefault();
        const action = document.querySelector('[data-action="new-game"]');
        if (action) action.click();
      }
      // Ctrl+Z / Cmd+Z: Undo
      else if ((e.ctrlKey || e.metaKey) && (e.key === 'z' || e.key === 'Z')) {
        e.preventDefault();
        if (this.game.canUndo()) {
          this.game.undo();
          this.audio.play('drop');
        }
      }
      // H / M: Hint
      else if (e.key === 'h' || e.key === 'H' || e.key === 'm' || e.key === 'M') {
        e.preventDefault();
        const hint = this.game.getNextHint();
        if (hint) {
          this.audio.play('hint');
          await this.renderer.playHintAnimation(hint);
        } else {
          this.audio.play('noHint');
          this.dialogs.showAlert('提示', '没有可用的移动，请点击发牌区发新牌。');
        }
      }
      // D: Deal
      else if (e.key === 'd' || e.key === 'D') {
        e.preventDefault();
        this.interaction.handleStockClick();
      }
      // F4: Stats
      else if (e.key === 'F4') {
        e.preventDefault();
        const action = document.querySelector('[data-action="stats"]');
        if (action) action.click();
      }
      // Escape: Boss Key (FUN_01006db6) or close dialog
      else if (e.key === 'Escape') {
        if (this.dialogs.overlay.classList.contains('show')) {
          this.dialogs.hide();
        } else {
          // Classic Windows XP "Boss Key" minimize
          document.querySelector('.xp-window').classList.toggle('minimized');
        }
      }
    });
  }
}

document.addEventListener('DOMContentLoaded', () => {
  window.spiderApp = new App();
});
