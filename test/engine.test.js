import assert from 'node:assert';
import { SpiderGame, DIFFICULTY } from '../src/engine/SpiderGame.js';
import { Card, SUITS } from '../src/engine/Card.js';

console.log('Running 1:1 Reverse-Engineered Spider Solitaire Automated Tests...');

// 1. Initial State & Exact Row-by-Row Dealing Verification (FUN_01005afb)
{
  const game = new SpiderGame(DIFFICULTY.ONE_SUIT, 12345);
  const dealtCards = game.columns.reduce((sum, col) => sum + col.length, 0);
  assert.strictEqual(dealtCards, 54, 'Initial dealt card count must be exactly 54');
  assert.strictEqual(game.stock.length, 50, 'Stock card count must be exactly 50');
  assert.strictEqual(game.stockDealsLeft, 5, 'Must have 5 deals remaining');
  assert.strictEqual(game.score, 500, 'Initial score must be 500 (FUN_01003596)');
  assert.strictEqual(game.moves, 0, 'Initial moves must be 0');

  // Verify columns 0..3 have 6 cards, 4..9 have 5 cards
  for (let c = 0; c < 10; c++) {
    const col = game.columns[c];
    const expectedCount = c < 4 ? 6 : 5;
    assert.strictEqual(col.length, expectedCount, `Column ${c} count`);
    for (let i = 0; i < expectedCount - 1; i++) {
      assert.strictEqual(col[i].faceUp, false, `Card ${i} in column ${c} face-down`);
    }
    assert.strictEqual(col[expectedCount - 1].faceUp, true, `Top card in column ${c} face-up`);
  }
}

// 2. Deterministic MS LCG PRNG verification (FUN_0100936b)
{
  const gA = new SpiderGame(DIFFICULTY.ONE_SUIT, 99999);
  const gB = new SpiderGame(DIFFICULTY.ONE_SUIT, 99999);
  for (let c = 0; c < 10; c++) {
    for (let i = 0; i < gA.columns[c].length; i++) {
      assert.strictEqual(gA.columns[c][i].rank, gB.columns[c][i].rank, 'LCG must be deterministic');
      assert.strictEqual(gA.columns[c][i].suit, gB.columns[c][i].suit, 'LCG must be deterministic');
    }
  }
}

// 3. Multi-Suit Suit Mapping verification (FUN_0100746e)
{
  const g1 = new SpiderGame(DIFFICULTY.ONE_SUIT, 1);
  const allCards1 = [...g1.stock, ...g1.columns.flat()];
  assert.ok(allCards1.every(c => c.suit === SUITS.SPADES), 'All cards must be Spades in 1-suit mode');

  const g2 = new SpiderGame(DIFFICULTY.TWO_SUITS, 1);
  const allCards2 = [...g2.stock, ...g2.columns.flat()];
  assert.ok(allCards2.every(c => c.suit === SUITS.SPADES || c.suit === SUITS.HEARTS), 'Must be Spades and Hearts in 2-suit mode');

  const g4 = new SpiderGame(DIFFICULTY.FOUR_SUITS, 1);
  const allCards4 = [...g4.stock, ...g4.columns.flat()];
  assert.strictEqual(allCards4.length, 104);
}

// 4. Move Rules & Sequence Constraints (FUN_0100396e & FUN_01003a06)
{
  const g = new SpiderGame(DIFFICULTY.TWO_SUITS);
  // Column 0: Spades 9, Spades 8, Spades 7 (same suit)
  g.columns[0] = [
    new Card(SUITS.SPADES, 9, true),
    new Card(SUITS.SPADES, 8, true),
    new Card(SUITS.SPADES, 7, true)
  ];
  assert.strictEqual(g.isSequenceMovable(0, 0), true);

  // Column 1: Spades 9, Hearts 8, Hearts 7 (diff suit sequence cannot move together)
  g.columns[1] = [
    new Card(SUITS.SPADES, 9, true),
    new Card(SUITS.HEARTS, 8, true),
    new Card(SUITS.HEARTS, 7, true)
  ];
  assert.strictEqual(g.isSequenceMovable(1, 0), false);
  assert.strictEqual(g.isSequenceMovable(1, 1), true);

  // Column 2: Hearts 10 (can receive Spades 9)
  g.columns[2] = [new Card(SUITS.HEARTS, 10, true)];
  assert.strictEqual(g.canMove(0, 0, 2), true);

  // Column 3: Empty (can receive Spades 9)
  g.columns[3] = [];
  assert.strictEqual(g.canMove(0, 0, 3), true);
}

// 5. Exact 3-Level Hint Priority & Queue Cycling (FUN_01003a90, FUN_0100315b, FUN_010031ab)
{
  const g = new SpiderGame(DIFFICULTY.TWO_SUITS);
  g.columns = Array.from({ length: 10 }, () => []);
  
  // Source: Spades 5 on top of a face-down card
  g.columns[0] = [new Card(SUITS.SPADES, 10, false), new Card(SUITS.SPADES, 5, true)];
  // Target 1: Spades 6 (Same suit -> Priority 3)
  g.columns[1] = [new Card(SUITS.SPADES, 6, true)];
  // Target 2: Hearts 6 (Different suit -> Priority 2)
  g.columns[2] = [new Card(SUITS.HEARTS, 6, true)];
  // Target 3: Empty (Empty slot -> Priority 1)
  g.columns[3] = [];

  const hint1 = g.getNextHint();
  assert.strictEqual(hint1.priority, 3, 'Highest priority hint must be Priority 3 (same suit)');
  assert.strictEqual(hint1.toCol, 1);

  const hint2 = g.getNextHint();
  assert.strictEqual(hint2.priority, 2, 'Second priority hint must be Priority 2 (different suit)');
  assert.strictEqual(hint2.toCol, 2);

  const hint3 = g.getNextHint();
  assert.strictEqual(hint3.priority, 1, 'Third priority hint must be Priority 1 (empty slot)');
  assert.strictEqual(hint3.toCol, 3);

  // Cycling test
  const hintCycle = g.getNextHint();
  assert.strictEqual(hintCycle.priority, 3, 'Hint queue must cycle back to first hint');
}

// 6. Score & Moves on Move, Deal, Undo (FUN_01004c2d, FUN_01003596, FUN_01004ef8)
{
  const g = new SpiderGame(DIFFICULTY.ONE_SUIT);
  g.columns[0] = [new Card(SUITS.SPADES, 5, true)];
  g.columns[1] = [new Card(SUITS.SPADES, 6, true)];

  g.moveCards(0, 0, 1);
  assert.strictEqual(g.score, 499, 'Score decrements by 1 on move');
  assert.strictEqual(g.moves, 1, 'Moves increment by 1 on move');

  g.undo();
  assert.strictEqual(g.score, 498, 'Score decrements by 1 on undo');
  assert.strictEqual(g.moves, 2, 'Moves increment by 1 on undo');

  // Score clamp test (cannot go below 0)
  g.score = 0;
  g.moveCards(0, 0, 1);
  assert.strictEqual(g.score, 0, 'Score must clamp at 0');
}

// 7. Run Completion & Scoring (FUN_010064d5)
{
  const g = new SpiderGame(DIFFICULTY.ONE_SUIT);
  g.columns[0] = [];
  for (let r = 13; r >= 1; r--) {
    g.columns[0].push(new Card(SUITS.SPADES, r, true));
  }
  const prevScore = g.score;
  const res = g.checkAndCollectRun(0);
  assert.strictEqual(res.completed, true);
  assert.strictEqual(g.completedSuits.length, 1);
  assert.strictEqual(g.score, prevScore + 100, 'Run completion awards +100 points');
}

// 8. Multi-Column Run Collection on Move (Uncovering a run in fromCol or landing on toCol)
{
  const g = new SpiderGame(DIFFICULTY.ONE_SUIT);
  // Col 0 has a complete run (K..2) with a stray 1 on Col 1 that moves to Col 0
  g.columns[0] = [];
  for (let r = 13; r >= 2; r--) {
    g.columns[0].push(new Card(SUITS.SPADES, r, true));
  }
  g.columns[1] = [new Card(SUITS.SPADES, 1, true)];

  const moveRes = g.moveCards(1, 0, 0);
  assert.strictEqual(moveRes.success, true);
  assert.strictEqual(moveRes.completedRuns.length, 1);
  assert.strictEqual(moveRes.completedRuns[0].colIndex, 0);
  assert.strictEqual(g.completedSuits.length, 1);
  assert.strictEqual(g.columns[0].length, 0, 'Completed run must be removed from column 0');
}

// 9. Win Condition Verification: Strictly when all 8 suits are cleared (FUN_010061f0)
{
  const g = new SpiderGame(DIFFICULTY.ONE_SUIT);
  assert.strictEqual(g.isWon, false);
  
  // Set 7 completed suits
  g.completedSuits = [0, 0, 0, 0, 0, 0, 0];
  g.columns[0] = [];
  for (let r = 13; r >= 2; r--) {
    g.columns[0].push(new Card(SUITS.SPADES, r, true));
  }
  g.columns[1] = [new Card(SUITS.SPADES, 1, true)];

  const winMove = g.moveCards(1, 0, 0);
  assert.strictEqual(winMove.isWin, true);
  assert.strictEqual(g.isWon, true);
  assert.strictEqual(g.completedSuits.length, 8);

  // Test debugTriggerWin
  const gDebug = new SpiderGame(DIFFICULTY.TWO_SUITS);
  gDebug.debugTriggerWin();
  assert.strictEqual(gDebug.isWon, true);
  assert.strictEqual(gDebug.completedSuits.length, 8);
}

console.log('ALL REVERSE-ENGINEERED TESTS VERIFIED 100%! 🎉');

