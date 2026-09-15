/**
 * Dialogs.js
 * 1:1 Pixel-Perfect Windows XP Dialog Templates (RT_DIALOG: 107, 117, 118, 119, 130)
 * Reconstructed directly from PE DLGTEMPLATEEX structures in spri.exe.
 */

export class Dialogs {
  constructor() {
    this.overlay = document.getElementById('dialog-overlay');
    this.dialogTitle = document.getElementById('dialog-title');
    this.dialogContent = document.getElementById('dialog-content');
    this.dialogFooter = document.getElementById('dialog-footer');
    this.closeBtn = document.getElementById('dialog-close-btn');

    this.closeBtn.addEventListener('click', () => this.hide());
  }

  show({ title, width, contentHtml, buttons }) {
    this.dialogTitle.textContent = title || '蜘蛛纸牌';
    const box = document.getElementById('xp-dialog-box');
    if (box) {
      box.style.width = width ? `${width}px` : 'auto';
    }
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
      width: 280,
      contentHtml: `<div style="padding: 6px 0; font-size: 12px;">${message}</div>`,
      buttons: [
        { text: '确定', primary: true }
      ]
    });
  }

  showConfirm(title, message, onConfirm) {
    this.show({
      title,
      width: 280,
      contentHtml: `<div style="padding: 6px 0; font-size: 12px;">${message}</div>`,
      buttons: [
        { text: '是(&Y)', primary: true, onClick: onConfirm },
        { text: '否(&N)' }
      ]
    });
  }

  /**
   * DIALOG 119: 难易级别 (Size: 197 x 109, Font: 宋体 9pt)
   * Items: 1008 (初级单色), 1009 (中级双色), 1010 (高级四色) with suit icons
   */
  showDifficulty(currentDiff, onSelect) {
    const html = `
      <div style="font-size: 12px; color: #000000; padding: 2px 0;">
        <div style="margin-bottom: 10px;">请选择游戏的难易级别:</div>
        <div style="display: flex; flex-direction: column; gap: 8px;">
          <!-- 初级: 单色 (黑桃 123) -->
          <label style="display: flex; align-items: center; gap: 8px; cursor: pointer;">
            <input type="radio" name="diff_choice" value="1" ${currentDiff === 1 ? 'checked' : ''}>
            <div style="display: flex; align-items: center; gap: 2px;">
              <img src="assets/ui/icon_123.png" style="width:16px;height:16px;" alt="黑桃">
            </div>
            <span>初级(&E): 单色</span>
          </label>

          <!-- 中级: 双色 (黑桃 123, 红桃 122) -->
          <label style="display: flex; align-items: center; gap: 8px; cursor: pointer;">
            <input type="radio" name="diff_choice" value="2" ${currentDiff === 2 ? 'checked' : ''}>
            <div style="display: flex; align-items: center; gap: 2px;">
              <img src="assets/ui/icon_123.png" style="width:16px;height:16px;" alt="黑桃">
              <img src="assets/ui/icon_122.png" style="width:16px;height:16px;" alt="红桃">
            </div>
            <span>中级(&M): 双色</span>
          </label>

          <!-- 高级: 四色 (黑桃 123, 红桃 122, 梅花 120, 方块 121) -->
          <label style="display: flex; align-items: center; gap: 8px; cursor: pointer;">
            <input type="radio" name="diff_choice" value="4" ${currentDiff === 4 ? 'checked' : ''}>
            <div style="display: flex; align-items: center; gap: 2px;">
              <img src="assets/ui/icon_123.png" style="width:16px;height:16px;" alt="黑桃">
              <img src="assets/ui/icon_122.png" style="width:16px;height:16px;" alt="红桃">
              <img src="assets/ui/icon_120.png" style="width:16px;height:16px;" alt="梅花">
              <img src="assets/ui/icon_121.png" style="width:16px;height:16px;" alt="方块">
            </div>
            <span>高级(&D): 四色</span>
          </label>
        </div>
      </div>
    `;

    this.show({
      title: '难易级别',
      width: 320,
      contentHtml: html,
      buttons: [
        {
          text: '确定',
          primary: true,
          onClick: () => {
            const selected = document.querySelector('input[name="diff_choice"]:checked');
            if (selected && onSelect) {
              onSelect(parseInt(selected.value));
            }
          }
        },
        { text: '取消' }
      ]
    });
  }

  /**
   * DIALOG 117: 蜘蛛选项 (Size: 199 x 140, Font: 宋体 9pt)
   * 6 checkboxes matching items 1001-1006
   */
  showOptions(options, onSave) {
    const html = `
      <div style="display: flex; flex-direction: column; gap: 8px; font-size: 12px; color: #000000;">
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="checkbox" id="opt-anim" ${options.animDeal ? 'checked' : ''}>
          <span>发牌时进行动画处理(&A)</span>
        </label>
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="checkbox" id="opt-save-exit" ${options.saveOnExit ? 'checked' : ''}>
          <span>退出时自动保存游戏(&S)</span>
        </label>
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="checkbox" id="opt-load-start" ${options.loadAtStart ? 'checked' : ''}>
          <span>启动时自动打开上次游戏(&O)</span>
        </label>
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="checkbox" id="opt-prompt-save" ${options.promptSave ? 'checked' : ''}>
          <span>保存游戏前提示(&P)</span>
        </label>
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="checkbox" id="opt-prompt-load" ${options.promptLoad ? 'checked' : ''}>
          <span>打开已保存的游戏前提示(&B)</span>
        </label>
        <label style="display: flex; align-items: center; gap: 6px; cursor: pointer;">
          <input type="checkbox" id="opt-sound" ${options.sound ? 'checked' : ''}>
          <span>使用声音效果(&E)</span>
        </label>
      </div>
    `;

    this.show({
      title: '蜘蛛选项',
      width: 290,
      contentHtml: html,
      buttons: [
        {
          text: '确定',
          primary: true,
          onClick: () => {
            const newOpts = {
              animDeal: document.getElementById('opt-anim').checked,
              saveOnExit: document.getElementById('opt-save-exit').checked,
              loadAtStart: document.getElementById('opt-load-start').checked,
              promptSave: document.getElementById('opt-prompt-save').checked,
              promptLoad: document.getElementById('opt-prompt-load').checked,
              sound: document.getElementById('opt-sound').checked
            };
            if (onSave) onSave(newOpts);
          }
        },
        { text: '取消' }
      ]
    });
  }

  /**
   * DIALOG 118: 蜘蛛统计数据 (Size: 167 x 198, Font: 宋体 9pt)
   * TabControl: 初级, 中级, 高级
   * GroupBoxes: 最高记录, 百分比, 连续
   */
  showStats(allStats, initialDiff, onReset) {
    const diffKeys = ['Easy', 'Medium', 'Difficult'];
    const diffTitles = ['初级', '中级', '高级'];
    let curIndex = initialDiff === 1 ? 0 : (initialDiff === 2 ? 1 : 2);

    const renderTabContent = (idx) => {
      const key = diffKeys[idx];
      const s = allStats[key] || { highScore: 0, wins: 0, losses: 0, streakWins: 0, streakLosses: 0, streakCurrent: 0, isWinStreak: true };
      const total = s.wins + s.losses;
      const rate = total > 0 ? Math.round((s.wins / total) * 100) : 0;
      const currentText = s.isWinStreak ? `${s.streakCurrent} 胜` : `${s.streakCurrent} 负`;

      return `
        <!-- Tabs -->
        <div class="xp-tabs">
          ${diffTitles.map((t, i) => `
            <div class="xp-tab ${i === idx ? 'active' : ''}" data-tab-idx="${i}">${t}</div>
          `).join('')}
        </div>

        <!-- Group 1: 最高记录 -->
        <div class="xp-groupbox">
          <span class="xp-groupbox-title">最高记录</span>
          <div style="display:flex; justify-content:space-between; margin-top:4px;">
            <span>得分:</span>
            <strong>${s.highScore}</strong>
          </div>
        </div>

        <!-- Group 2: 百分比 -->
        <div class="xp-groupbox">
          <span class="xp-groupbox-title">百分比</span>
          <div style="display:flex; justify-content:space-between; margin-top:2px;"><span>胜:</span> <strong>${s.wins}</strong></div>
          <div style="display:flex; justify-content:space-between; margin-top:2px;"><span>负:</span> <strong>${s.losses}</strong></div>
          <div style="display:flex; justify-content:space-between; margin-top:2px;"><span>获胜比率:</span> <strong>${rate} %</strong></div>
        </div>

        <!-- Group 3: 连续 -->
        <div class="xp-groupbox">
          <span class="xp-groupbox-title">连续</span>
          <div style="display:flex; justify-content:space-between; margin-top:2px;"><span>最高连胜:</span> <strong>${s.streakWins}</strong></div>
          <div style="display:flex; justify-content:space-between; margin-top:2px;"><span>最高连负:</span> <strong>${s.streakLosses}</strong></div>
          <div style="display:flex; justify-content:space-between; margin-top:2px;"><span>当前:</span> <strong>${currentText}</strong></div>
        </div>
      `;
    };

    const updateContainer = () => {
      this.dialogContent.innerHTML = renderTabContent(curIndex);
      this.dialogContent.querySelectorAll('.xp-tab').forEach(tab => {
        tab.addEventListener('click', (e) => {
          curIndex = parseInt(e.target.dataset.tabIdx);
          updateContainer();
        });
      });
    };

    this.show({
      title: '蜘蛛统计数据',
      width: 290,
      contentHtml: renderTabContent(curIndex),
      buttons: [
        {
          text: '确定',
          primary: true
        },
        {
          text: '复位(&R)',
          onClick: () => {
            this.showConfirm('重置统计信息', '是否要重置所有游戏统计数据?', () => {
              if (onReset) onReset();
            });
          }
        }
      ]
    });

    this.dialogContent.querySelectorAll('.xp-tab').forEach(tab => {
      tab.addEventListener('click', (e) => {
        curIndex = parseInt(e.target.dataset.tabIdx);
        updateContainer();
      });
    });
  }

  /**
   * DIALOG 130: 游戏结束 (Size: 166 x 69, Font: 宋体 9pt)
   */
  showWin(score, moves, onPlayAgain) {
    const html = `
      <div style="font-size: 12px; color: #000000; padding: 4px 0;">
        <div style="font-weight: bold; font-size: 13px; color: #003399; margin-bottom: 6px;">恭喜恭喜，你赢了!</div>
        <div>最终得分: <strong>${score}</strong></div>
        <div>操作次数: <strong>${moves}</strong></div>
        <div style="margin-top: 8px;">是否开始新一轮游戏?</div>
      </div>
    `;

    this.show({
      title: '游戏结束',
      width: 260,
      contentHtml: html,
      buttons: [
        { text: '是(&Y)', primary: true, onClick: onPlayAgain },
        { text: '否(&N)' }
      ]
    });
  }

  /**
   * DIALOG 107: 关于蜘蛛 (Size: 253 x 189, Font: 宋体 9pt)
   * Uses original 106.png bitmap graphic
   */
  showAbout() {
    const html = `
      <div style="display: flex; flex-direction: column; align-items: center; text-align: center; gap: 8px;">
        <img src="assets/ui/106.png" style="max-width: 100%; height: auto; border: 1px solid #716f64;" alt="蜘蛛">
        <div style="font-weight: bold; font-size: 13px; margin-top: 4px;">蜘蛛纸牌 (Spider Solitaire)</div>
        <div style="font-size: 11px; color: #333333;">Windows XP 经典 1:1 纯静态复刻版</div>
        <div style="font-size: 11px; color: #666666;">(C) 1998-2000 Microsoft Corporation. 保留所有权利。</div>
      </div>
    `;

    this.show({
      title: '关于蜘蛛',
      width: 320,
      contentHtml: html,
      buttons: [
        { text: '确定', primary: true }
      ]
    });
  }
}
