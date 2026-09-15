/**
 * main.js
 * Application entry point: initializes state, connects UI, menus, shortcuts and stats.
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

    // Hook game changes
    this.game.onChange((event, data) => {
      if (event === 'undo') {
        this.renderer.render();
      } else if (event === 'move' || event === 'deal') {
        if (data.isWin) {
          this.recordWin(this.game.score);
        }
      }
    });

    // Initial render
    this.renderer.render();
  }

  loadStats() {
    try {
      const data = localStorage.getItem('spider_stats');
      if (data) return JSON.parse(data);
    } catch (e) {}
    return {
      played: 0,
      wins: 0,
      highScore: 0,
      maxStreak: 0,
      currentStreak: 0
    };
  }

  saveStats() {
    localStorage.setItem('spider_stats', JSON.stringify(this.stats));
  }

  recordWin(score) {
    this.stats.played++;
    this.stats.wins++;
    this.stats.currentStreak++;
    if (this.stats.currentStreak > this.stats.maxStreak) {
      this.stats.maxStreak = this.stats.currentStreak;
    }
    if (score > this.stats.highScore) {
      this.stats.highScore = score;
    }
    this.saveStats();
  }

  startNewGame(diff = null) {
    if (diff !== null) {
      this.game.difficulty = diff;
      localStorage.setItem('spider_difficulty', diff);
    }
    this.stats.played++;
    this.saveStats();

    this.game.initGame();
    this.renderer.render();
    this.audio.play('dealRound');
  }

  bindWindowControls() {
    const btnClose = document.getElementById('btn-close');
    const btnMax = document.getElementById('btn-max');
    const btnMin = document.getElementById('btn-min');

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
    
    // Toggle menu dropdowns
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

    // Menu Actions
    const actionMap = {
      'new-game': () => {
        if (this.game.moves > 0 && !this.game.isWon) {
          this.dialogs.showConfirm('新游戏', '是否开始新游戏?', () => this.startNewGame());
        } else {
          this.startNewGame();
        }
      },
      'restart': () => {
        this.dialogs.showConfirm('重新开始', '是否从头开始这次游戏?', () => {
          this.game.initGame();
          this.renderer.render();
          this.audio.play('dealRound');
        });
      },
      'undo': () => {
        if (this.game.canUndo()) {
          this.game.undo();
          this.audio.play('click');
        }
      },
      'hint': () => {
        const hint = this.game.findHint();
        if (hint) {
          this.renderer.highlightHint(hint);
        } else {
          this.dialogs.showAlert('提示', '没有可用的移动，请点击右下角发牌区发新牌。');
        }
      },
      'deal': () => {
        this.interaction.handleStockClick();
      },
      'difficulty': () => {
        this.dialogs.showDifficulty(this.game.difficulty, (newDiff) => {
          this.startNewGame(newDiff);
        });
      },
      'stats': () => {
        this.dialogs.showStats(this.stats, () => {
          this.stats = { played: 0, wins: 0, highScore: 0, maxStreak: 0, currentStreak: 0 };
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
    window.addEventListener('keydown', (e) => {
      // F2: New Game
      if (e.key === 'F2') {
        e.preventDefault();
        this.startNewGame();
      }
      // Ctrl+Z / Cmd+Z: Undo
      else if ((e.ctrlKey || e.metaKey) && (e.key === 'z' || e.key === 'Z')) {
        e.preventDefault();
        if (this.game.canUndo()) {
          this.game.undo();
          this.audio.play('click');
        }
      }
      // H or M: Hint
      else if (e.key === 'h' || e.key === 'H' || e.key === 'm' || e.key === 'M') {
        e.preventDefault();
        const hint = this.game.findHint();
        if (hint) {
          this.renderer.highlightHint(hint);
        } else {
          this.dialogs.showAlert('提示', '没有可用的移动，请点击发牌区发新牌。');
        }
      }
      // D: Deal
      else if (e.key === 'd' || e.key === 'D') {
        e.preventDefault();
        this.interaction.handleStockClick();
      }
      // F4: Statistics
      else if (e.key === 'F4') {
        e.preventDefault();
        this.dialogs.showStats(this.stats);
      }
      // Escape: close dialogs
      else if (e.key === 'Escape') {
        this.dialogs.hide();
      }
    });
  }
}

// Bootstrap on DOM ready
document.addEventListener('DOMContentLoaded', () => {
  window.spiderApp = new App();
});
