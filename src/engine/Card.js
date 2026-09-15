/**
 * Card.js
 * Represents a single playing card in Spider Solitaire.
 */

export const SUITS = {
  CLUBS: 0,     // 梅花 (Black)
  DIAMONDS: 1,  // 方块 (Red)
  HEARTS: 2,    // 红桃 (Red)
  SPADES: 3     // 黑桃 (Black)
};

export const SUIT_NAMES = {
  [SUITS.CLUBS]: 'clubs',
  [SUITS.DIAMONDS]: 'diamonds',
  [SUITS.HEARTS]: 'hearts',
  [SUITS.SPADES]: 'spades'
};

export const RANK_NAMES = {
  1: 'A', 2: '2', 3: '3', 4: '4', 5: '5', 6: '6',
  7: '7', 8: '8', 9: '9', 10: '10', 11: 'J', 12: 'Q', 13: 'K'
};

let nextCardId = 1;

export class Card {
  /**
   * @param {number} suit - 0: Clubs, 1: Diamonds, 2: Hearts, 3: Spades
   * @param {number} rank - 1 (A) to 13 (K)
   * @param {boolean} faceUp - Whether card is face up
   */
  constructor(suit, rank, faceUp = false) {
    this.id = nextCardId++;
    this.suit = suit;
    this.rank = rank;
    this.faceUp = faceUp;
  }

  get isRed() {
    return this.suit === SUITS.DIAMONDS || this.suit === SUITS.HEARTS;
  }

  get suitName() {
    return SUIT_NAMES[this.suit];
  }

  get rankName() {
    return RANK_NAMES[this.rank];
  }

  /**
   * Returns the asset filename for the card face (CARD1.png - CARD52.png).
   * Windows cards.dll formula: 1 + suit * 13 + (rank - 1)
   */
  get faceImage() {
    const cardIndex = 1 + this.suit * 13 + (this.rank - 1);
    return `assets/cards/CARD${cardIndex}.png`;
  }

  get backImage() {
    return 'assets/ui/CARDBACK.png';
  }

  clone() {
    const c = new Card(this.suit, this.rank, this.faceUp);
    c.id = this.id;
    return c;
  }
}
