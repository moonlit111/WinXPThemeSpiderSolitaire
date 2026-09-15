import assert from 'node:assert';
import { SpiderGame, DIFFICULTY } from '../src/engine/SpiderGame.js';
import { Card, SUITS } from '../src/engine/Card.js';

console.log('Running Spider Solitaire Engine Automated Tests...');

// 1. Initial State Verification
{
  const game = new SpiderGame(DIFFICULTY.ONE_SUIT);
  const dealtCards = game.columns.reduce((sum, col) => sum + col.length, 0);
  assert.strictEqual(dealtCards, 54, 'Initial dealt card count must be exactly 54');
  assert.strictEqual(game.stock.length, 50, 'Stock card count must be exactly 50');
  assert.strictEqual(game.stockDealsLeft, 5, 'Must have 5 deals remaining');
  assert.strictEqual(game.score, 500, 'Initial score must be 500');
  assert.strictEqual(game.moves, 0, 'Initial moves must be 0');

  // Verify column card face states
  for (let c = 0; c < 10; c++) {
    const col = game.columns[c];
    const expectedCount = c < 4 ? 6 : 5;
    assert.strictEqual(col.length, expectedCount, `Column ${c} must have ${expectedCount} cards`);
    for (let i = 0; i < expectedCount - 1; i++) {
      assert.strictEqual(col[i].faceUp, false, `Card ${i} in column ${c} must be face-down`);
    }
    assert.strictEqual(col[expectedCount - 1].faceUp, true, `Top card in column ${c} must be face-up`);
  }
}

// 2. Multi-Suit Deck Configurations
{
  const g2 = new SpiderGame(DIFFICULTY.TWO_SUITS);
  const total2 = g2.stock.length + g2.columns.reduce((sum, col) => sum + col.length, 0);
  assert.strictEqual(total2, 104, 'Two-suit game must contain 104 cards');

  const g4 = new SpiderGame(DIFFICULTY.FOUR_SUITS);
  const total4 = g4.stock.length + g4.columns.reduce((sum, col) => sum + col.length, 0);
  assert.strictEqual(total4, 104, 'Four-suit game must contain 104 cards');
}

// 3. Move Validation Rules
{
  const g = new SpiderGame(DIFFICULTY.TWO_SUITS);
  // Prepare controlled column 0: Spades 9, Spades 8, Spades 7 (same suit descending)
  g.columns[0] = [
    new Card(SUITS.SPADES, 9, true),
    new Card(SUITS.SPADES, 8, true),
    new Card(SUITS.SPADES, 7, true)
  ];
  assert.strictEqual(g.isSequenceMovable(0, 0), true);
  assert.strictEqual(g.isSequenceMovable(0, 1), true);
  assert.strictEqual(g.isSequenceMovable(0, 2), true);

  // Column 1: Spades 9, Hearts 8, Hearts 7 (mixed suits)
  g.columns[1] = [
    new Card(SUITS.SPADES, 9, true),
    new Card(SUITS.HEARTS, 8, true),
    new Card(SUITS.HEARTS, 7, true)
  ];
  assert.strictEqual(g.isSequenceMovable(1, 0), false, 'Cannot move mixed suit sequence from start');
  assert.strictEqual(g.isSequenceMovable(1, 1), true, 'Can move same-suit tail');

  // Move onto non-empty column: Hearts 10
  g.columns[2] = [new Card(SUITS.HEARTS, 10, true)];
  assert.strictEqual(g.canMove(0, 0, 2), true, 'Spades 9 can be placed on Hearts 10');

  // Move onto invalid rank: Hearts 8
  g.columns[3] = [new Card(SUITS.HEARTS, 8, true)];
  assert.strictEqual(g.canMove(0, 0, 3), false, 'Spades 9 cannot be placed on Hearts 8');

  // Move onto empty column
  g.columns[4] = [];
  assert.strictEqual(g.canMove(0, 0, 4), true, 'Any valid sequence can be placed on an empty column');
}

// 4. Execution of Move & Auto-flip
{
  const g = new SpiderGame(DIFFICULTY.ONE_SUIT);
  g.columns[0] = [
    new Card(SUITS.SPADES, 10, false), // face down
    new Card(SUITS.SPADES, 5, true)    // face up
  ];
  g.columns[1] = [new Card(SUITS.SPADES, 6, true)];

  const moveRes = g.moveCards(0, 1, 1);
  assert.strictEqual(moveRes.success, true);
  assert.strictEqual(g.columns[1].length, 2);
  assert.strictEqual(g.columns[0].length, 1);
  assert.strictEqual(g.columns[0][0].faceUp, true, 'Underlying face-down card must auto-flip');
  assert.strictEqual(moveRes.autoFlipped, true);
  assert.strictEqual(g.score, 499);
  assert.strictEqual(g.moves, 1);
}

// 5. Run Completion & Scoring
{
  const g = new SpiderGame(DIFFICULTY.ONE_SUIT);
  g.columns[0] = [];
  for (let rank = 13; rank >= 1; rank--) {
    g.columns[0].push(new Card(SUITS.SPADES, rank, true));
  }
  assert.strictEqual(g.columns[0].length, 13);
  const runRes = g.checkAndCollectRun(0);
  assert.strictEqual(runRes.completed, true);
  assert.strictEqual(g.columns[0].length, 0, 'Completed run should be removed');
  assert.strictEqual(g.completedSuits.length, 1);
  assert.strictEqual(g.score, 600, 'Score should increase by 100 on run completion');
}

// 6. Dealing from Stock and Empty Column Block
{
  const g = new SpiderGame(DIFFICULTY.ONE_SUIT);
  // Column 0 is empty
  g.columns[0] = [];
  const check = g.canDeal();
  assert.strictEqual(check.canDeal, false);
  assert.strictEqual(check.reason, 'EMPTY_COLUMN');

  // Fill column 0
  g.columns[0] = [new Card(SUITS.SPADES, 2, true)];
  assert.strictEqual(g.canDeal().canDeal, true);

  const dealRes = g.dealRound();
  assert.strictEqual(dealRes.success, true);
  assert.strictEqual(g.stockDealsLeft, 4);
  assert.strictEqual(g.stock.length, 40);
  assert.strictEqual(g.columns[0].length, 2);
}

// 7. Undo Mechanism
{
  const g = new SpiderGame(DIFFICULTY.ONE_SUIT);
  g.columns[0] = [new Card(SUITS.SPADES, 4, true)];
  g.columns[1] = [new Card(SUITS.SPADES, 5, true)];

  g.moveCards(0, 0, 1);
  assert.strictEqual(g.columns[1].length, 2);
  assert.strictEqual(g.columns[0].length, 0);

  const undoRes = g.undo();
  assert.strictEqual(undoRes, true);
  assert.strictEqual(g.columns[0].length, 1);
  assert.strictEqual(g.columns[1].length, 1);
}

// 8. Hint Calculation
{
  const g = new SpiderGame(DIFFICULTY.TWO_SUITS);
  // Column 0 has face-down card and Spades 6
  g.columns[0] = [
    new Card(SUITS.SPADES, 12, false),
    new Card(SUITS.SPADES, 6, true)
  ];
  // Column 1 has Spades 7 (same suit target)
  g.columns[1] = [new Card(SUITS.SPADES, 7, true)];

  const hint = g.findHint();
  assert.notStrictEqual(hint, null);
  assert.strictEqual(hint.fromCol, 0);
  assert.strictEqual(hint.toCol, 1);
}

console.log('ALL ENGINE TESTS COMPLETED AND VERIFIED 100%! 🎉');
