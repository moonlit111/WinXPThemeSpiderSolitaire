/**
 * Dialogs.js
 * Manages Windows XP style modal dialogs (Difficulty, Alerts, Win, Stats, About).
 */

export class Dialogs {
  constructor() {
    this.overlay = document.getElementById('dialog-overlay');
    this.dialogTitle = document.getElementById('dialog-title');
    this.dialogIcon = document.getElementById('dialog-icon');
    this.dialogContent = document.getElementById('dialog-content');
    this.dialogFooter = document.getElementById('dialog-footer');
    this.closeBtn = document.getElementById('dialog-close-btn');

    this.closeBtn.addEventListener('click', () => this.hide());
  }

  show({ title, icon, contentHtml, buttons }) {
    this.dialogTitle.textContent = title || '蜘蛛纸牌';
    this.dialogIcon.src = icon || 'assets/ui/spider_icon.png';
    this.dialogContent.innerHTML = contentHtml || '';
    this.dialogFooter.innerHTML = '';

    buttons.forEach(btn => {
      const b = document.createElement('button');
      b.className = `xp-btn ${btn.primary ? 'primary' : ''}`;
      b.textContent = btn.text;
      b.addEventListener('click', () => {
        if (btn.onClick) btn.onClick();
        this.hide();
      });
      this.dialogFooter.appendChild(b);
    });

    this.overlay.classList.add('show');
  }

  hide() {
    this.overlay.classList.remove('show');
  }

  showAlert(title, message) {
    this.show({
      title,
      contentHtml: `<div style="padding-top: 4px; font-size: 12px;">${message}</div>`,
      buttons: [
        { text: '确定', primary: true }
      ]
    });
  }

  showConfirm(title, message, onConfirm) {
    this.show({
      title,
      contentHtml: `<div style="padding-top: 4px; font-size: 12px;">${message}</div>`,
      buttons: [
        { text: '是', primary: true, onClick: onConfirm },
        { text: '否' }
      ]
    });
  }

  showDifficulty(currentDiff, onSelect) {
    const html = `
      <div style="display: flex; flex-direction: column; gap: 8px;">
        <div style="font-weight: bold; margin-bottom: 2px;">选择难度级别:</div>
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="radio" name="diff" value="1" ${currentDiff === 1 ? 'checked' : ''}>
          <span>初级: 单色 (黑桃)</span>
        </label>
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="radio" name="diff" value="2" ${currentDiff === 2 ? 'checked' : ''}>
          <span>中级: 双色 (黑桃和红桃)</span>
        </label>
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="radio" name="diff" value="4" ${currentDiff === 4 ? 'checked' : ''}>
          <span>高级: 四色 (全部四种花色)</span>
        </label>
      </div>
    `;

    this.show({
      title: '蜘蛛纸牌难度',
      contentHtml: html,
      buttons: [
        {
          text: '确定',
          primary: true,
          onClick: () => {
            const selected = document.querySelector('input[name="diff"]:checked');
            if (selected && onSelect) {
              onSelect(parseInt(selected.value));
            }
          }
        },
        { text: '取消' }
      ]
    });
  }

  showWin(score, moves, onPlayAgain) {
    const html = `
      <div style="display: flex; flex-direction: column; gap: 8px;">
        <div style="font-weight: bold; font-size: 13px; color: #004e98;">恭喜！你赢了！</div>
        <div>最终得分: <strong>${score}</strong></div>
        <div>操作次数: <strong>${moves}</strong></div>
        <div style="margin-top: 6px;">是否开始新游戏?</div>
      </div>
    `;

    this.show({
      title: '你赢了!',
      contentHtml: html,
      buttons: [
        { text: '新游戏', primary: true, onClick: onPlayAgain },
        { text: '关闭' }
      ]
    });
  }

  showStats(stats, onReset) {
    const rate = stats.played > 0 ? Math.round((stats.wins / stats.played) * 100) : 0;
    const html = `
      <div style="display: flex; flex-direction: column; gap: 6px; font-size: 12px;">
        <div style="display: flex; justify-content: space-between;"><span>已玩游戏:</span> <strong>${stats.played}</strong></div>
        <div style="display: flex; justify-content: space-between;"><span>获胜次数:</span> <strong>${stats.wins}</strong></div>
        <div style="display: flex; justify-content: space-between;"><span>获胜率:</span> <strong>${rate}%</strong></div>
        <div style="display: flex; justify-content: space-between;"><span>最高得分:</span> <strong>${stats.highScore}</strong></div>
        <div style="display: flex; justify-content: space-between;"><span>最高连胜:</span> <strong>${stats.maxStreak}</strong></div>
        <div style="display: flex; justify-content: space-between;"><span>当前连胜:</span> <strong>${stats.currentStreak}</strong></div>
      </div>
    `;

    this.show({
      title: '蜘蛛纸牌统计信息',
      contentHtml: html,
      buttons: [
        {
          text: '重置',
          onClick: () => {
            if (onReset) onReset();
          }
        },
        { text: '确定', primary: true }
      ]
    });
  }

  showAbout() {
    const html = `
      <div style="display: flex; flex-direction: column; gap: 6px; font-size: 11px;">
        <div style="font-weight: bold; font-size: 13px;">蜘蛛纸牌 (Spider Solitaire)</div>
        <div>版本 1.0 (macOS & Web 1:1 复刻版)</div>
        <div style="color: #666; margin-top: 4px;">基于 Windows 原版 PE 提取素材与逻辑复刻</div>
        <div style="color: #666;">支持离线运行与 GitHub Pages 静态托管</div>
      </div>
    `;

    this.show({
      title: '关于 蜘蛛纸牌',
      contentHtml: html,
      buttons: [
        { text: '确定', primary: true }
      ]
    });
  }
}
