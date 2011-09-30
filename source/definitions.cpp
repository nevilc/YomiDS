//#include "deck.h"
#include "fighter.h"

#include <cstdlib>

// Use this array to pass the card list to a deck constructor
// (Is there really no efficient way to do this (even with g++'s partial
// C++0B implementation?)
//const Card* cardlist[rule::max_decksize];


// (Almost) every block/dodge/burst is the same, so reuse those sides
const Side SDodge(Side::Dodge);
const Side SBlock(Side::Block);
const Side SBurst(Side::Burst);


// Grave
const Side SGrave2T(Side::Attack, "", 26, 1, 2);
const Side SGrave3B(Side::Attack, "", 36, 1, 3);
const Side SGrave4T(Side::Attack, "", 46, 1, 4);
const Side SGrave5B(Side::Attack, "", 56, 1, 5);
const Side SGrave6T(Side::Attack, "", 66, 1, 6);
const Side SGrave7T(Side::Throw, "", 76, 2, 7, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SGrave8B(Side::Throw, "", 86, 2, 7, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SGrave9T(Side::Throw, "", 96, 2, 7, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SGrave10B(Side::Throw, "", 106, 2, 7, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SGraveJ(Side::Attack, "Lightning Cloud", 24, 1, 8, 3, 0, 0, 0, Side::Ender);
const Side SGraveQ(Side::Attack, "Dragonheart", 0, 3, 10, 2, 0, 0, 0, Side::Ender);
const Side SGraveK(Side::Attack, "Whirlwind", 22, 2, 7, 1, 7, 1, 0, Side::Linker);
const Side SGraveAT(Side::Attack, "True-Spark Arc", 10, 2, 12, 3, 0, 0, 0, Side::Ender);
const Side SGraveAB(Side::Attack, "True Power of Storms", 4, 3, 45, 1, 0, 0, 3, Side::Ender);

const Card CGrave2H(Card::Two, Card::Heart, SGrave2T, SDodge);
const Card CGrave2D(Card::Two, Card::Diamond, SGrave2T, SDodge);
const Card CGrave2C(Card::Two, Card::Club, SGrave2T, SDodge);
const Card CGrave2S(Card::Two, Card::Spade, SGrave2T, SDodge);

const Card CGrave3H(Card::Three, Card::Heart, SDodge, SGrave3B);
const Card CGrave3D(Card::Three, Card::Diamond, SDodge, SGrave3B);
const Card CGrave3C(Card::Three, Card::Club, SDodge, SGrave3B);
const Card CGrave3S(Card::Three, Card::Spade, SDodge, SGrave3B);

const Card CGrave4H(Card::Four, Card::Heart, SGrave4T, SDodge);
const Card CGrave4D(Card::Four, Card::Diamond, SGrave4T, SDodge);
const Card CGrave4C(Card::Four, Card::Club, SGrave4T, SDodge);
const Card CGrave4S(Card::Four, Card::Spade, SGrave4T, SDodge);

const Card CGrave5H(Card::Five, Card::Heart, SBlock, SGrave5B);
const Card CGrave5D(Card::Five, Card::Diamond, SBlock, SGrave5B);
const Card CGrave5C(Card::Five, Card::Club, SBlock, SGrave5B);
const Card CGrave5S(Card::Five, Card::Spade, SBlock, SGrave5B);

const Card CGrave6H(Card::Six, Card::Heart, SGrave6T, SBlock);
const Card CGrave6D(Card::Six, Card::Diamond, SGrave6T, SBlock);
const Card CGrave6C(Card::Six, Card::Club, SGrave6T, SBlock);
const Card CGrave6S(Card::Six, Card::Spade, SGrave6T, SBlock);

const Card CGrave7H(Card::Seven, Card::Heart, SGrave7T, SBlock);
const Card CGrave7D(Card::Seven, Card::Diamond, SGrave7T, SBlock);
const Card CGrave7C(Card::Seven, Card::Club, SGrave7T, SBlock);
const Card CGrave7S(Card::Seven, Card::Spade, SGrave7T, SBlock);

const Card CGrave8H(Card::Eight, Card::Heart, SBlock, SGrave8B);
const Card CGrave8D(Card::Eight, Card::Diamond, SBlock, SGrave8B);
const Card CGrave8C(Card::Eight, Card::Club, SBlock, SGrave8B);
const Card CGrave8S(Card::Eight, Card::Spade, SBlock, SGrave8B);

const Card CGrave9H(Card::Nine, Card::Heart, SGrave9T, SBlock);
const Card CGrave9D(Card::Nine, Card::Diamond, SGrave9T, SBlock);
const Card CGrave9C(Card::Nine, Card::Club, SGrave9T, SBlock);
const Card CGrave9S(Card::Nine, Card::Spade, SGrave9T, SBlock);

const Card CGrave10H(Card::Ten, Card::Heart, SBlock, SGrave10B);
const Card CGrave10D(Card::Ten, Card::Diamond, SBlock, SGrave10B);
const Card CGrave10C(Card::Ten, Card::Club, SBlock, SGrave10B);
const Card CGrave10S(Card::Ten, Card::Spade, SBlock, SGrave10B);

const Card CGraveJH(Card::Jack, Card::Heart, SGraveJ, SGraveJ);
const Card CGraveJD(Card::Jack, Card::Diamond, SGraveJ, SGraveJ);
const Card CGraveJC(Card::Jack, Card::Club, SGraveJ, SGraveJ);
const Card CGraveJS(Card::Jack, Card::Spade, SGraveJ, SGraveJ);

const Card CGraveQH(Card::Queen, Card::Heart, SGraveQ, SGraveQ);
const Card CGraveQD(Card::Queen, Card::Diamond, SGraveQ, SGraveQ);
const Card CGraveQC(Card::Queen, Card::Club, SGraveQ, SGraveQ);
const Card CGraveQS(Card::Queen, Card::Spade, SGraveQ, SGraveQ);

const Card CGraveKH(Card::King, Card::Heart, SGraveK, SGraveK);
const Card CGraveKD(Card::King, Card::Diamond, SGraveK, SGraveK);
const Card CGraveKC(Card::King, Card::Club, SGraveK, SGraveK);
const Card CGraveKS(Card::King, Card::Spade, SGraveK, SGraveK);

const Card CGraveAH(Card::Ace, Card::Heart, SGraveAT, SGraveAB);
const Card CGraveAD(Card::Ace, Card::Diamond, SGraveAT, SGraveAB);
const Card CGraveAC(Card::Ace, Card::Club, SGraveAT, SGraveAB);
const Card CGraveAS(Card::Ace, Card::Spade, SGraveAT, SGraveAB);

const Card CGraveJoker1(Card::Joker, Card::None, SBurst, SBurst);
const Card CGraveJoker2(Card::Joker, Card::None, SBurst, SBurst);

const Card *const DLGrave[rule::max_decksize] =
					{&CGrave2H, &CGrave2D, &CGrave2C, &CGrave2S,
					 &CGrave3H, &CGrave3D, &CGrave3C, &CGrave3S,
					 &CGrave4H, &CGrave4D, &CGrave4C, &CGrave4S,
					 &CGrave5H, &CGrave5D, &CGrave5C, &CGrave5S,
					 &CGrave6H, &CGrave6D, &CGrave6C, &CGrave6S,
					 &CGrave7H, &CGrave7D, &CGrave7C, &CGrave7S,
					 &CGrave8H, &CGrave8D, &CGrave8C, &CGrave8S,
					 &CGrave9H, &CGrave9D, &CGrave9C, &CGrave9S,
					 &CGrave10H, &CGrave10D, &CGrave10C, &CGrave10S,
					 &CGraveJH, &CGraveJD, &CGraveJC, &CGraveAS,
					 &CGraveQH, &CGraveQD, &CGraveQC, &CGraveQS,
					 &CGraveKH, &CGraveKD, &CGraveKC, &CGraveKS,
					 &CGraveAH, &CGraveAD, &CGraveAC, &CGraveAS,
					 &CGraveJoker1, &CGraveJoker2};

const Deck DGrave(DLGrave);

// Midori
const Side SMidori2B(Side::Throw, "", 28, 2, 8, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SMidori3T(Side::Throw, "", 38, 2, 8, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SMidori4T(Side::Throw, "", 42, 1, 4);
const Side SMidori4B(Side::Throw, "", 48, 2, 8, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SMidori5T(Side::Throw, "", 58, 2, 8, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SMidori5B(Side::Attack, "", 52, 1, 5);
const Side SMidori6T(Side::Attack, "", 62, 1, 6);
const Side SMidori7B(Side::Attack, "", 72, 1, 7);
const Side SMidori8T(Side::Attack, "", 82, 1, 8);
const Side SMidori9T(Side::Throw, "", 98, 2, 8, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SMidori10B(Side::Throw, "", 108, 2, 8, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SMidoriJT(Side::Attack, "Whirlwind", 24, 1, 8, 2, 8, 1, 0, Side::Ender);
const Side SMidoriJB(Side::Attack, "Toxic Breath", 24, 1, 9, 2, 0, 0, 0, Side::Tag(Side::Starter | Side::Dragon));
const Side SMidoriQT(Side::Attack, "Rising Mountain", 12, 2, 10, 1, 0, 0, 0, Side::Ender);
const Side SMidoriQB(Side::Attack, "Dragon Mountain", 6, 2, 14, 2, 0, 0, 0, Side::Tag(Side::Linker | Side::Dragon));
const Side SMidoriKT(Side::Throw, "Rushing River", 44, 0, 12, 0, 0, 0, 0);
const Side SMidoriKB(Side::Throw, "Talon Swoop", 22, 0, 17, 0, 0, 0, 0, Side::Dragon);
const Side SMidoriAT(Side::Attack, "Wrath of Earth", 12, 2, 20, 2, 0, 0, 1, Side::Ender);
const Side SMidoriAB(Side::Throw, "Final Dragon Buster", 0, 0, 20, 0, 16, 2, 1, Side::Dragon);

const Card CMidori2H(Card::Two, Card::Heart, SBlock, SMidori2B);
const Card CMidori2D(Card::Two, Card::Diamond, SBlock, SMidori2B);
const Card CMidori2C(Card::Two, Card::Club, SBlock, SMidori2B);
const Card CMidori2S(Card::Two, Card::Spade, SBlock, SMidori2B);

const Card CMidori3H(Card::Three, Card::Heart, SMidori3T, SBlock);
const Card CMidori3D(Card::Three, Card::Diamond, SMidori3T, SBlock);
const Card CMidori3C(Card::Three, Card::Club, SMidori3T, SBlock);
const Card CMidori3S(Card::Three, Card::Spade, SMidori3T, SBlock);

const Card CMidori4H(Card::Four, Card::Heart, SMidori4T, SMidori4B);
const Card CMidori4D(Card::Four, Card::Diamond, SMidori4T, SMidori4B);
const Card CMidori4C(Card::Four, Card::Club, SMidori4T, SMidori4B);
const Card CMidori4S(Card::Four, Card::Spade, SMidori4T, SMidori4B);

const Card CMidori5H(Card::Five, Card::Heart, SMidori5T, SMidori5B);
const Card CMidori5D(Card::Five, Card::Diamond, SMidori5T, SMidori5B);
const Card CMidori5C(Card::Five, Card::Club, SMidori5T, SMidori5B);
const Card CMidori5S(Card::Five, Card::Spade, SMidori5T, SMidori5B);

const Card CMidori6H(Card::Six, Card::Heart, SMidori6T, SBlock);
const Card CMidori6D(Card::Six, Card::Diamond, SMidori6T, SBlock);
const Card CMidori6C(Card::Six, Card::Club, SMidori6T, SBlock);
const Card CMidori6S(Card::Six, Card::Spade, SMidori6T, SBlock);

const Card CMidori7H(Card::Seven, Card::Heart, SBlock, SMidori7B);
const Card CMidori7D(Card::Seven, Card::Diamond, SBlock, SMidori7B);
const Card CMidori7C(Card::Seven, Card::Club, SBlock, SMidori7B);
const Card CMidori7S(Card::Seven, Card::Spade, SBlock, SMidori7B);

const Card CMidori8H(Card::Eight, Card::Heart, SMidori8T, SBlock);
const Card CMidori8D(Card::Eight, Card::Diamond, SMidori8T, SBlock);
const Card CMidori8C(Card::Eight, Card::Club, SMidori8T, SBlock);
const Card CMidori8S(Card::Eight, Card::Spade, SMidori8T, SBlock);

const Card CMidori9H(Card::Nine, Card::Heart, SMidori9T, SDodge);
const Card CMidori9D(Card::Nine, Card::Diamond, SMidori9T, SDodge);
const Card CMidori9C(Card::Nine, Card::Club, SMidori9T, SDodge);
const Card CMidori9S(Card::Nine, Card::Spade, SMidori9T, SDodge);

const Card CMidori10H(Card::Ten, Card::Heart, SDodge, SMidori10B);
const Card CMidori10D(Card::Ten, Card::Diamond, SDodge, SMidori10B);
const Card CMidori10C(Card::Ten, Card::Club, SDodge, SMidori10B);
const Card CMidori10S(Card::Ten, Card::Spade, SDodge, SMidori10B);

const Card CMidoriJH(Card::Jack, Card::Heart, SMidoriJT, SMidoriJB);
const Card CMidoriJD(Card::Jack, Card::Diamond, SMidoriJT, SMidoriJB);
const Card CMidoriJC(Card::Jack, Card::Club, SMidoriJT, SMidoriJB);
const Card CMidoriJS(Card::Jack, Card::Spade, SMidoriJT, SMidoriJB);

const Card CMidoriQH(Card::Queen, Card::Heart, SMidoriQT, SMidoriQB);
const Card CMidoriQD(Card::Queen, Card::Diamond, SMidoriQT, SMidoriQB);
const Card CMidoriQC(Card::Queen, Card::Club, SMidoriQT, SMidoriQB);
const Card CMidoriQS(Card::Queen, Card::Spade, SMidoriQT, SMidoriQB);

const Card CMidoriKH(Card::King, Card::Heart, SMidoriKT, SMidoriKB);
const Card CMidoriKD(Card::King, Card::Diamond, SMidoriKT, SMidoriKB);
const Card CMidoriKC(Card::King, Card::Club, SMidoriKT, SMidoriKB);
const Card CMidoriKS(Card::King, Card::Spade, SMidoriKT, SMidoriKB);

const Card CMidoriAH(Card::Ace, Card::Heart, SMidoriAT, SMidoriAB);
const Card CMidoriAD(Card::Ace, Card::Diamond, SMidoriAT, SMidoriAB);
const Card CMidoriAC(Card::Ace, Card::Club, SMidoriAT, SMidoriAB);
const Card CMidoriAS(Card::Ace, Card::Spade, SMidoriAT, SMidoriAB);

const Card CMidoriJoker1(Card::Joker, Card::None, SBurst, SBurst);
const Card CMidoriJoker2(Card::Joker, Card::None, SBurst, SBurst);

const Card *const DLMidori[rule::max_decksize] =
					{&CMidori2H, &CMidori2D, &CMidori2C, &CMidori2S,
					 &CMidori3H, &CMidori3D, &CMidori3C, &CMidori3S,
					 &CMidori4H, &CMidori4D, &CMidori4C, &CMidori4S,
					 &CMidori5H, &CMidori5D, &CMidori5C, &CMidori5S,
					 &CMidori6H, &CMidori6D, &CMidori6C, &CMidori6S,
					 &CMidori7H, &CMidori7D, &CMidori7C, &CMidori7S,
					 &CMidori8H, &CMidori8D, &CMidori8C, &CMidori8S,
					 &CMidori9H, &CMidori9D, &CMidori9C, &CMidori9S,
					 &CMidori10H, &CMidori10D, &CMidori10C, &CMidori10S,
					 &CMidoriJH, &CMidoriJD, &CMidoriJC, &CMidoriAS,
					 &CMidoriQH, &CMidoriQD, &CMidoriQC, &CMidoriQS,
					 &CMidoriKH, &CMidoriKD, &CMidoriKC, &CMidoriKS,
					 &CMidoriAH, &CMidoriAD, &CMidoriAC, &CMidoriAS,
					 &CMidoriJoker1, &CMidoriJoker2};
const Deck DMidori(DLMidori);


const Side SRook2B(Side::Throw, "", 20, 0, 10, 0, 0, 0, 0, Side::Knockdown);
const Side SRook3T(Side::Block, "Entangling Vines");
const Side SRook3B(Side::Throw, "", 30, 0, 10, 0, 0, 0, 0, Side::Knockdown);
const Side SRook4B(Side::Attack, "", 48, 1, 4);
const Side SRook5T(Side::Block, "Stone Wall");
const Side SRook5B(Side::Attack, "", 58, 1, 5);
const Side SRook6T(Side::Attack, "", 68, 1, 6);
const Side SRook6B(Side::Throw, "", 60, 0, 10, 0, 0, 0, 0, Side::Knockdown);
const Side SRook7T(Side::Throw, "", 70, 0, 10, 0, 0, 0, 0, Side::Knockdown);
const Side SRook7B(Side::Attack, "", 78, 1, 7);
const Side SRook8T(Side::Attack, "", 88, 1, 8);
const Side SRook9T(Side::Throw, "", 90, 0, 10, 0, 0, 0, 0, Side::Knockdown);
const Side SRook10T(Side::Attack, "", 108, 1, 10);
const Side SRook10B(Side::Throw, "", 100, 0, 10);
const Side SRookJ(Side::Attack, "Thunderclap", 22, 1, 4, 2, 0, 0, 0, Side::Linker);
const Side SRookQT(Side::Attack, "Hammerfist", 26, 2, 9, 1, 5, 1, 0, Side::Ender);
const Side SRookQB(Side::Throw, "Rolling Stone", 84, 2, 10, 0, 0, 0, 0, Side::Ender);
const Side SRookK(Side::Throw, "Windmill Crusher", 24, 0, 15, 0, 0, 0, 0);
const Side SRookAT(Side::Attack, "Wall of Vines", 8, 0, 20, 3, 0, 0, 1);
const Side SRookAB(Side::Throw, "Checkmate Buster", 0, 0, 50, 0, 0, 0, 3);

const Card CRook2H(Card::Two, Card::Heart, SBlock, SRook2B);
const Card CRook2D(Card::Two, Card::Diamond, SBlock, SRook2B);
const Card CRook2C(Card::Two, Card::Club, SBlock, SRook2B);
const Card CRook2S(Card::Two, Card::Spade, SBlock, SRook2B);

const Card CRook3H(Card::Three, Card::Heart, SRook3T, SRook3B);
const Card CRook3D(Card::Three, Card::Diamond, SRook3T, SRook3B);
const Card CRook3C(Card::Three, Card::Club, SRook3T, SRook3B);
const Card CRook3S(Card::Three, Card::Spade, SRook3T, SRook3B);

const Card CRook4H(Card::Four, Card::Heart, SBlock, SRook4B);
const Card CRook4D(Card::Four, Card::Diamond, SBlock, SRook4B);
const Card CRook4C(Card::Four, Card::Club, SBlock, SRook4B);
const Card CRook4S(Card::Four, Card::Spade, SBlock, SRook4B);

const Card CRook5H(Card::Five, Card::Heart, SRook5T, SRook5B);
const Card CRook5D(Card::Five, Card::Diamond, SRook5T, SRook5B);
const Card CRook5C(Card::Five, Card::Club, SRook5T, SRook5B);
const Card CRook5S(Card::Five, Card::Spade, SRook5T, SRook5B);

const Card CRook6H(Card::Six, Card::Heart, SRook6T, SRook6B);
const Card CRook6D(Card::Six, Card::Diamond, SRook6T, SRook6B);
const Card CRook6C(Card::Six, Card::Club, SRook6T, SRook6B);
const Card CRook6S(Card::Six, Card::Spade, SRook6T, SRook6B);

const Card CRook7H(Card::Seven, Card::Heart, SRook7T, SRook7B);
const Card CRook7D(Card::Seven, Card::Diamond, SRook7T, SRook7B);
const Card CRook7C(Card::Seven, Card::Club, SRook7T, SRook7B);
const Card CRook7S(Card::Seven, Card::Spade, SRook7T, SRook7B);

const Card CRook8H(Card::Eight, Card::Heart, SRook8T, SBlock);
const Card CRook8D(Card::Eight, Card::Diamond, SRook8T, SBlock);
const Card CRook8C(Card::Eight, Card::Club, SRook8T, SBlock);
const Card CRook8S(Card::Eight, Card::Spade, SRook8T, SBlock);

const Card CRook9H(Card::Nine, Card::Heart, SRook9T, SBlock);
const Card CRook9D(Card::Nine, Card::Diamond, SRook9T, SBlock);
const Card CRook9C(Card::Nine, Card::Club, SRook9T, SBlock);
const Card CRook9S(Card::Nine, Card::Spade, SRook9T, SBlock);

const Card CRook10H(Card::Ten, Card::Heart, SRook10T, SRook10B);
const Card CRook10D(Card::Ten, Card::Diamond, SRook10T, SRook10B);
const Card CRook10C(Card::Ten, Card::Club, SRook10T, SRook10B);
const Card CRook10S(Card::Ten, Card::Spade, SRook10T, SRook10B);

const Card CRookJH(Card::Jack, Card::Heart, SRookJ, SRookJ);
const Card CRookJD(Card::Jack, Card::Diamond, SRookJ, SRookJ);
const Card CRookJC(Card::Jack, Card::Club, SRookJ, SRookJ);
const Card CRookJS(Card::Jack, Card::Spade, SRookJ, SRookJ);

const Card CRookQH(Card::Queen, Card::Heart, SRookQT, SRookQB);
const Card CRookQD(Card::Queen, Card::Diamond, SRookQT, SRookQB);
const Card CRookQC(Card::Queen, Card::Club, SRookQT, SRookQB);
const Card CRookQS(Card::Queen, Card::Spade, SRookQT, SRookQB);

const Card CRookKH(Card::King, Card::Heart, SRookK, SRookK);
const Card CRookKD(Card::King, Card::Diamond, SRookK, SRookK);
const Card CRookKC(Card::King, Card::Club, SRookK, SRookK);
const Card CRookKS(Card::King, Card::Spade, SRookK, SRookK);

const Card CRookAH(Card::Ace, Card::Heart, SRookAT, SRookAB);
const Card CRookAD(Card::Ace, Card::Diamond, SRookAT, SRookAB);
const Card CRookAC(Card::Ace, Card::Club, SRookAT, SRookAB);
const Card CRookAS(Card::Ace, Card::Spade, SRookAT, SRookAB);

const Card CRookJoker1(Card::Joker, Card::None, SBurst, SBurst);
const Card CRookJoker2(Card::Joker, Card::None, SBurst, SBurst);

const Card *const DLRook[rule::max_decksize] = 
					{&CRook2H, &CRook2D, &CRook2C, &CRook2S,
					 &CRook3H, &CRook3D, &CRook3C, &CRook3S,
					 &CRook4H, &CRook4D, &CRook4C, &CRook4S,
					 &CRook5H, &CRook5D, &CRook5C, &CRook5S,
					 &CRook6H, &CRook6D, &CRook6C, &CRook6S,
					 &CRook7H, &CRook7D, &CRook7C, &CRook7S,
					 &CRook8H, &CRook8D, &CRook8C, &CRook8S,
					 &CRook9H, &CRook9D, &CRook9C, &CRook9S,
					 &CRook10H, &CRook10D, &CRook10C, &CRook10S,
					 &CRookJH, &CRookJD, &CRookJC, &CRookAS,
					 &CRookQH, &CRookQD, &CRookQC, &CRookQS,
					 &CRookKH, &CRookKD, &CRookKC, &CRookKS,
					 &CRookAH, &CRookAD, &CRookAC, &CRookAS,
					 &CRookJoker1, &CRookJoker2};
const Deck DRook(DLRook);


const Side SValerie2T(Side::Attack, "", 24, 1, 2);
const Side SValerie3B(Side::Attack, "", 34, 1, 3);
const Side SValerie4T(Side::Attack, "", 44, 1, 4);
const Side SValerie5B(Side::Attack, "", 54, 1, 5);
const Side SValerie6T(Side::Attack, "", 64, 1, 6);
const Side SValerie7T(Side::Throw, "", 72, 3, 6, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SValerie8B(Side::Throw, "", 82, 3, 6, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SValerie9T(Side::Throw, "", 92, 3, 6, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SValerie10B(Side::Throw, "", 102, 3, 6, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SValerieJ(Side::Attack, "Three Colors", 22, 2, 7, 3, 7, 2, 0, Side::Ender);
const Side SValerieQ(Side::Attack, "Crimson Passion", 2, 3, 8, 1, 3, 2, 0, Side::Ender);
const Side SValerieK(Side::Attack, "Flying Rainbow Strike", 34, 1, 6, 2, 0, 0, 0, Side::Linker);
const Side SValerieAT(Side::Attack, "Masterpiece", 12, 2, 16, 3, 0, 0, 1, Side::Ender);
const Side SValerieAB(Side::Attack, "Chromatic Orb", 10, 0, 10, 3);

const Card CValerie2H(Card::Two, Card::Heart, SValerie2T, SDodge);
const Card CValerie3H(Card::Three, Card::Heart, SDodge, SValerie3B);
const Card CValerie4H(Card::Four, Card::Heart, SValerie4T, SDodge);
const Card CValerie5H(Card::Five, Card::Heart, SBlock, SValerie5B);
const Card CValerie6H(Card::Six, Card::Heart, SValerie6T, SBlock);
const Card CValerie7H(Card::Seven, Card::Heart, SValerie7T, SBlock);
const Card CValerie8H(Card::Eight, Card::Heart, SBlock, SValerie8B);
const Card CValerie9H(Card::Nine, Card::Heart, SValerie9T, SBlock);
const Card CValerie10H(Card::Ten, Card::Heart, SBlock, SValerie10B);
const Card CValerieJH(Card::Jack, Card::Heart, SValerieJ, SValerieJ);
const Card CValerieQH(Card::Queen, Card::Heart, SValerieQ, SValerieQ);
const Card CValerieKH(Card::King, Card::Heart, SValerieK, SValerieK);
const Card CValerieAH(Card::Ace, Card::Heart, SValerieAT, SValerieAB);

const Card CValerie2D(Card::Two, Card::Diamond, SValerie2T, SDodge);
const Card CValerie3D(Card::Three, Card::Diamond, SDodge, SValerie3B);
const Card CValerie4D(Card::Four, Card::Diamond, SValerie4T, SDodge);
const Card CValerie5D(Card::Five, Card::Diamond, SBlock, SValerie5B);
const Card CValerie6D(Card::Six, Card::Diamond, SValerie6T, SBlock);
const Card CValerie7D(Card::Seven, Card::Diamond, SValerie7T, SBlock);
const Card CValerie8D(Card::Eight, Card::Diamond, SBlock, SValerie8B);
const Card CValerie9D(Card::Nine, Card::Diamond, SValerie9T, SBlock);
const Card CValerie10D(Card::Ten, Card::Diamond, SBlock, SValerie10B);
const Card CValerieJD(Card::Jack, Card::Diamond, SValerieJ, SValerieJ);
const Card CValerieQD(Card::Queen, Card::Diamond, SValerieQ, SValerieQ);
const Card CValerieKD(Card::King, Card::Diamond, SValerieK, SValerieK);
const Card CValerieAD(Card::Ace, Card::Diamond, SValerieAT, SValerieAB);

const Card CValerie2C(Card::Two, Card::Club, SValerie2T, SDodge);
const Card CValerie3C(Card::Three, Card::Club, SDodge, SValerie3B);
const Card CValerie4C(Card::Four, Card::Club, SValerie4T, SDodge);
const Card CValerie5C(Card::Five, Card::Club, SBlock, SValerie5B);
const Card CValerie6C(Card::Six, Card::Club, SValerie6T, SBlock);
const Card CValerie7C(Card::Seven, Card::Club, SValerie7T, SBlock);
const Card CValerie8C(Card::Eight, Card::Club, SBlock, SValerie8B);
const Card CValerie9C(Card::Nine, Card::Club, SValerie9T, SBlock);
const Card CValerie10C(Card::Ten, Card::Club, SBlock, SValerie10B);
const Card CValerieJC(Card::Jack, Card::Club, SValerieJ, SValerieJ);
const Card CValerieQC(Card::Queen, Card::Club, SValerieQ, SValerieQ);
const Card CValerieKC(Card::King, Card::Club, SValerieK, SValerieK);
const Card CValerieAC(Card::Ace, Card::Club, SValerieAT, SValerieAB);

const Card CValerie2S(Card::Two, Card::Spade, SValerie2T, SDodge);
const Card CValerie3S(Card::Three, Card::Spade, SDodge, SValerie3B);
const Card CValerie4S(Card::Four, Card::Spade, SValerie4T, SDodge);
const Card CValerie5S(Card::Five, Card::Spade, SBlock, SValerie5B);
const Card CValerie6S(Card::Six, Card::Spade, SValerie6T, SBlock);
const Card CValerie7S(Card::Seven, Card::Spade, SValerie7T, SBlock);
const Card CValerie8S(Card::Eight, Card::Spade, SBlock, SValerie8B);
const Card CValerie9S(Card::Nine, Card::Spade, SValerie9T, SBlock);
const Card CValerie10S(Card::Ten, Card::Spade, SBlock, SValerie10B);
const Card CValerieJS(Card::Jack, Card::Spade, SValerieJ, SValerieJ);
const Card CValerieQS(Card::Queen, Card::Spade, SValerieQ, SValerieQ);
const Card CValerieKS(Card::King, Card::Spade, SValerieK, SValerieK);
const Card CValerieAS(Card::Ace, Card::Spade, SValerieAT, SValerieAB);

const Card CValerieJoker1(Card::Joker, Card::None, SBurst, SBurst);
const Card CValerieJoker2(Card::Joker, Card::None, SBurst, SBurst);

const Card *const DLValerie[rule::max_decksize] =
					{&CValerie2H, &CValerie2D, &CValerie2C, &CValerie2S,
					 &CValerie3H, &CValerie3D, &CValerie3C, &CValerie3S,
					 &CValerie4H, &CValerie4D, &CValerie4C, &CValerie4S,
					 &CValerie5H, &CValerie5D, &CValerie5C, &CValerie5S,
					 &CValerie6H, &CValerie6D, &CValerie6C, &CValerie6S,
					 &CValerie7H, &CValerie7D, &CValerie7C, &CValerie7S,
					 &CValerie8H, &CValerie8D, &CValerie8C, &CValerie8S,
					 &CValerie9H, &CValerie9D, &CValerie9C, &CValerie9S,
					 &CValerie10H, &CValerie10D, &CValerie10C, &CValerie10S,
					 &CValerieJH, &CValerieJD, &CValerieJC, &CValerieAS,
					 &CValerieQH, &CValerieQD, &CValerieQC, &CValerieQS,
					 &CValerieKH, &CValerieKD, &CValerieKC, &CValerieKS,
					 &CValerieAH, &CValerieAD, &CValerieAC, &CValerieAS,
					 &CValerieJoker1, &CValerieJoker2};
const Deck DValerie(DLValerie);

const Side SLum3B(Side::Attack, "", 34, 1, 3);
const Side SLum4T(Side::Attack, "", 44, 1, 4);
const Side SLum5B(Side::Attack, "", 54, 1, 5);
const Side SLum6T(Side::Attack, "", 64, 1, 6);
const Side SLum6B(Side::Throw, "", 64, 0, 6, 0, 3, 3);
const Side SLum7B(Side::Attack, "", 74, 1, 7);
const Side SLum8T(Side::Attack, "", 84, 1, 8);
const Side SLum8B(Side::Throw, "", 84, 0, 8, 0, 3, 3);
const Side SLum9T(Side::Throw, "", 94, 0, 9, 0, 3, 3);
const Side SLum10B(Side::Throw, "", 104, 0, 10, 0, 3, 3);
const Side SLumJ(Side::Attack, "Coin Toss", 14, 1, 4, 1, 0, 0, 0, Side::Linker);
const Side SLumQ(Side::Attack, "Rolling Panda", 4, 3, 8, 2, 8, 1, 0, Side::Ender);
const Side SLumK(Side::Attack, "Polar Cartwheel", 30, 3, 6, 3, 8, 3, 0, Side::Ender);
const Side SLumAT(Side::Dodge, "Blackjack");
const Side SLumAB(Side::Attack, "Great Pandamonium", 8, 0, 10, 4, 12, 3, 0);

const Card CLum2H(Card::Two, Card::Heart, SBlock, SDodge);
const Card CLum3H(Card::Three, Card::Heart, SDodge, SLum3B);
const Card CLum4H(Card::Four, Card::Heart, SLum4T, SDodge);
const Card CLum5H(Card::Five, Card::Heart, SBlock, SLum5B);
const Card CLum6H(Card::Six, Card::Heart, SLum6T, SLum6B);
const Card CLum7H(Card::Seven, Card::Heart, SBlock, SLum7B);
const Card CLum8H(Card::Eight, Card::Heart, SLum8T, SLum8B);
const Card CLum9H(Card::Nine, Card::Heart, SLum9T, SBlock);
const Card CLum10H(Card::Ten, Card::Heart, SBlock, SLum10B);
const Card CLumJH(Card::Jack, Card::Heart, SLumJ, SLumJ);
const Card CLumQH(Card::Queen, Card::Heart, SLumQ, SLumQ);
const Card CLumKH(Card::King, Card::Heart, SLumK, SLumK);
const Card CLumAH(Card::Ace, Card::Heart, SLumAT, SLumAB);

const Card CLum2D(Card::Two, Card::Heart, SBlock, SDodge);
const Card CLum3D(Card::Three, Card::Heart, SDodge, SLum3B);
const Card CLum4D(Card::Four, Card::Heart, SLum4T, SDodge);
const Card CLum5D(Card::Five, Card::Heart, SBlock, SLum5B);
const Card CLum6D(Card::Six, Card::Heart, SLum6T, SLum6B);
const Card CLum7D(Card::Seven, Card::Heart, SBlock, SLum7B);
const Card CLum8D(Card::Eight, Card::Heart, SLum8T, SLum8B);
const Card CLum9D(Card::Nine, Card::Heart, SLum9T, SBlock);
const Card CLum10D(Card::Ten, Card::Heart, SBlock, SLum10B);
const Card CLumJD(Card::Jack, Card::Heart, SLumJ, SLumJ);
const Card CLumQD(Card::Queen, Card::Heart, SLumQ, SLumQ);
const Card CLumKD(Card::King, Card::Heart, SLumK, SLumK);
const Card CLumAD(Card::Ace, Card::Heart, SLumAT, SLumAB);

const Card CLum2C(Card::Two, Card::Heart, SBlock, SDodge);
const Card CLum3C(Card::Three, Card::Heart, SDodge, SLum3B);
const Card CLum4C(Card::Four, Card::Heart, SLum4T, SDodge);
const Card CLum5C(Card::Five, Card::Heart, SBlock, SLum5B);
const Card CLum6C(Card::Six, Card::Heart, SLum6T, SLum6B);
const Card CLum7C(Card::Seven, Card::Heart, SBlock, SLum7B);
const Card CLum8C(Card::Eight, Card::Heart, SLum8T, SLum8B);
const Card CLum9C(Card::Nine, Card::Heart, SLum9T, SBlock);
const Card CLum10C(Card::Ten, Card::Heart, SBlock, SLum10B);
const Card CLumJC(Card::Jack, Card::Heart, SLumJ, SLumJ);
const Card CLumQC(Card::Queen, Card::Heart, SLumQ, SLumQ);
const Card CLumKC(Card::King, Card::Heart, SLumK, SLumK);
const Card CLumAC(Card::Ace, Card::Heart, SLumAT, SLumAB);

const Card CLum2S(Card::Two, Card::Heart, SBlock, SDodge);
const Card CLum3S(Card::Three, Card::Heart, SDodge, SLum3B);
const Card CLum4S(Card::Four, Card::Heart, SLum4T, SDodge);
const Card CLum5S(Card::Five, Card::Heart, SBlock, SLum5B);
const Card CLum6S(Card::Six, Card::Heart, SLum6T, SLum6B);
const Card CLum7S(Card::Seven, Card::Heart, SBlock, SLum7B);
const Card CLum8S(Card::Eight, Card::Heart, SLum8T, SLum8B);
const Card CLum9S(Card::Nine, Card::Heart, SLum9T, SBlock);
const Card CLum10S(Card::Ten, Card::Heart, SBlock, SLum10B);
const Card CLumJS(Card::Jack, Card::Heart, SLumJ, SLumJ);
const Card CLumQS(Card::Queen, Card::Heart, SLumQ, SLumQ);
const Card CLumKS(Card::King, Card::Heart, SLumK, SLumK);
const Card CLumAS(Card::Ace, Card::Heart, SLumAT, SLumAB);

const Card CLumJoker1(Card::Joker, Card::None, SBurst, SBurst);
const Card CLumJoker2(Card::Joker, Card::None, SBurst, SBurst);

const Card *const DLLum[rule::max_decksize] =
				{&CLum2H, &CLum2D, &CLum2C, &CLum2S,
				 &CLum3H, &CLum3D, &CLum3C, &CLum3S,
				 &CLum4H, &CLum4D, &CLum4C, &CLum4S,
				 &CLum5H, &CLum5D, &CLum5C, &CLum5S,
				 &CLum6H, &CLum6D, &CLum6C, &CLum6S,
				 &CLum7H, &CLum7D, &CLum7C, &CLum7S,
				 &CLum8H, &CLum8D, &CLum8C, &CLum8S,
				 &CLum9H, &CLum9D, &CLum9C, &CLum9S,
				 &CLum10H, &CLum10D, &CLum10C, &CLum10S,
				 &CLumJH, &CLumJD, &CLumJC, &CLumAS,
				 &CLumQH, &CLumQD, &CLumQC, &CLumQS,
				 &CLumKH, &CLumKD, &CLumKC, &CLumKS,
				 &CLumAH, &CLumAD, &CLumAC, &CLumAS,
				 &CLumJoker1, &CLumJoker2};

const Deck DLum(DLLum);

const Side SJaina2T(Side::Attack, "", 26, 1, 2, 3);
const Side SJaina3B(Side::Attack, "", 36, 1, 3, 3);
const Side SJaina4T(Side::Attack, "", 46, 1, 4, 3);
const Side SJaina5B(Side::Attack, "", 56, 1, 5, 3);
const Side SJaina6T(Side::Attack, "", 66, 1, 6, 3);
const Side SJaina6B(Side::Throw, "Knee Bash", 86, 0, 7, 0, 4, 2, 0);
const Side SJaina7T(Side::Throw, "", 76, 2, 7, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SJaina8B(Side::Throw, "", 86, 2, 7, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SJaina9T(Side::Throw, "", 96, 2, 7, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SJaina10B(Side::Throw, "", 106, 2, 7, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SJainaJT(Side::Attack, "Flame Arrow", 26, 1, 6, 5, 0, 0, 0, Side::Ender);
const Side SJainaJB(Side::Attack, "Charged Shot", 86, 0, 8, 7, 0, 0, 0);
const Side SJainaQ(Side::Attack, "Dragonheart", 2, 3, 8, 1, 5, 1, 0, Side::Ender);
const Side SJainaK(Side::Attack, "Crossfire Kick", 24, 2, 6, 3, 7, 3, 0, Side::Linker);
const Side SJainaAT(Side::Attack, "Letter J", 2, 2, 18, 4, 0, 0, 1, Side::Ender);
const Side SJainaAB(Side::Attack, "Red Dragon", 8, 0, 10, 2, 9, 3, 0);

const Card CJaina2H(Card::Two, Card::Heart, SJaina2T, SDodge);
const Card CJaina3H(Card::Three, Card::Heart, SDodge, SJaina3B);
const Card CJaina4H(Card::Four, Card::Heart, SJaina4T, SDodge);
const Card CJaina5H(Card::Five, Card::Heart, SDodge, SJaina5B);
const Card CJaina6H(Card::Six, Card::Heart, SJaina6T, SJaina6B);
const Card CJaina7H(Card::Seven, Card::Heart, SJaina7T, SBlock);
const Card CJaina8H(Card::Eight, Card::Heart, SBlock, SJaina8B);
const Card CJaina9H(Card::Nine, Card::Heart, SJaina9T, SBlock);
const Card CJaina10H(Card::Ten, Card::Heart, SBlock, SJaina10B);
const Card CJainaJH(Card::Jack, Card::Heart, SJainaJT, SJainaJB);
const Card CJainaQH(Card::Queen, Card::Heart, SJainaQ, SJainaQ);
const Card CJainaKH(Card::King, Card::Heart, SJainaK, SJainaK);
const Card CJainaAH(Card::Ace, Card::Heart, SJainaAT, SJainaAB);

const Card CJaina2D(Card::Two, Card::Diamond, SJaina2T, SDodge);
const Card CJaina3D(Card::Three, Card::Diamond, SDodge, SJaina3B);
const Card CJaina4D(Card::Four, Card::Diamond, SJaina4T, SDodge);
const Card CJaina5D(Card::Five, Card::Diamond, SDodge, SJaina5B);
const Card CJaina6D(Card::Six, Card::Diamond, SJaina6T, SJaina6B);
const Card CJaina7D(Card::Seven, Card::Diamond, SJaina7T, SBlock);
const Card CJaina8D(Card::Eight, Card::Diamond, SBlock, SJaina8B);
const Card CJaina9D(Card::Nine, Card::Diamond, SJaina9T, SBlock);
const Card CJaina10D(Card::Ten, Card::Diamond, SBlock, SJaina10B);
const Card CJainaJD(Card::Jack, Card::Diamond, SJainaJT, SJainaJB);
const Card CJainaQD(Card::Queen, Card::Diamond, SJainaQ, SJainaQ);
const Card CJainaKD(Card::King, Card::Diamond, SJainaK, SJainaK);
const Card CJainaAD(Card::Ace, Card::Diamond, SJainaAT, SJainaAB);

const Card CJaina2C(Card::Two, Card::Club, SJaina2T, SDodge);
const Card CJaina3C(Card::Three, Card::Club, SDodge, SJaina3B);
const Card CJaina4C(Card::Four, Card::Club, SJaina4T, SDodge);
const Card CJaina5C(Card::Five, Card::Club, SDodge, SJaina5B);
const Card CJaina6C(Card::Six, Card::Club, SJaina6T, SJaina6B);
const Card CJaina7C(Card::Seven, Card::Club, SJaina7T, SBlock);
const Card CJaina8C(Card::Eight, Card::Club, SBlock, SJaina8B);
const Card CJaina9C(Card::Nine, Card::Club, SJaina9T, SBlock);
const Card CJaina10C(Card::Ten, Card::Club, SBlock, SJaina10B);
const Card CJainaJC(Card::Jack, Card::Club, SJainaJT, SJainaJB);
const Card CJainaQC(Card::Queen, Card::Club, SJainaQ, SJainaQ);
const Card CJainaKC(Card::King, Card::Club, SJainaK, SJainaK);
const Card CJainaAC(Card::Ace, Card::Club, SJainaAT, SJainaAB);

const Card CJaina2S(Card::Two, Card::Spade, SJaina2T, SDodge);
const Card CJaina3S(Card::Three, Card::Spade, SDodge, SJaina3B);
const Card CJaina4S(Card::Four, Card::Spade, SJaina4T, SDodge);
const Card CJaina5S(Card::Five, Card::Spade, SDodge, SJaina5B);
const Card CJaina6S(Card::Six, Card::Spade, SJaina6T, SJaina6B);
const Card CJaina7S(Card::Seven, Card::Spade, SJaina7T, SBlock);
const Card CJaina8S(Card::Eight, Card::Spade, SBlock, SJaina8B);
const Card CJaina9S(Card::Nine, Card::Spade, SJaina9T, SBlock);
const Card CJaina10S(Card::Ten, Card::Spade, SBlock, SJaina10B);
const Card CJainaJS(Card::Jack, Card::Spade, SJainaJT, SJainaJB);
const Card CJainaQS(Card::Queen, Card::Spade, SJainaQ, SJainaQ);
const Card CJainaKS(Card::King, Card::Spade, SJainaK, SJainaK);
const Card CJainaAS(Card::Ace, Card::Spade, SJainaAT, SJainaAB);

const Card CJainaJoker1(Card::Joker, Card::None, SBurst, SBurst);
const Card CJainaJoker2(Card::Joker, Card::None, SBurst, SBurst);

const Card *const DLJaina[rule::max_decksize] =
				{&CJaina2H, &CJaina2D, &CJaina2C, &CJaina2S,
				 &CJaina3H, &CJaina3D, &CJaina3C, &CJaina3S,
				 &CJaina4H, &CJaina4D, &CJaina4C, &CJaina4S,
				 &CJaina5H, &CJaina5D, &CJaina5C, &CJaina5S,
				 &CJaina6H, &CJaina6D, &CJaina6C, &CJaina6S,
				 &CJaina7H, &CJaina7D, &CJaina7C, &CJaina7S,
				 &CJaina8H, &CJaina8D, &CJaina8C, &CJaina8S,
				 &CJaina9H, &CJaina9D, &CJaina9C, &CJaina9S,
				 &CJaina10H, &CJaina10D, &CJaina10C, &CJaina10S,
				 &CJainaJH, &CJainaJD, &CJainaJC, &CJainaAS,
				 &CJainaQH, &CJainaQD, &CJainaQC, &CJainaQS,
				 &CJainaKH, &CJainaKD, &CJainaKC, &CJainaKS,
				 &CJainaAH, &CJainaAD, &CJainaAC, &CJainaAS,
				 &CJainaJoker1, &CJainaJoker2};
const Deck DJaina(DLJaina);


const Side SSetsuki2T(Side::Attack, "", 22, 1, 2);
const Side SSetsuki3B(Side::Attack, "", 32, 1, 3);
const Side SSetsuki4T(Side::Attack, "", 42, 1, 4);
const Side SSetsuki5B(Side::Attack, "", 52, 1, 5);
const Side SSetsuki6T(Side::Attack, "", 62, 1, 6);
const Side SSetsuki7T(Side::Throw, "", 72, 3, 6, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SSetsuki8B(Side::Throw, "", 82, 3, 6, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SSetsuki9T(Side::Throw, "", 92, 3, 6, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SSetsuki10B(Side::Throw, "", 102, 3, 6, 0, 0, 0, 0, Side::Tag(Side::Starter | Side::Knockdown));
const Side SSetsukiJ(Side::Attack, "Esper Dash", 14, 1, 5, 1, 0, 0, 0, Side::Linker);
const Side SSetsukiQ(Side::Attack, "Ninpo Dash", 0, 3, 1, 0, 4, 2, 0, Side::Starter);
const Side SSetsukiKT(Side::Attack, "Starlight Kick", 22, 2, 5, 2, 3, 2, 0, Side::Linker);
const Side SSetsukiKB(Side::Throw, "Starlight Tumbler", 92, 2, 6, 0, 0, 0, 0, Side::Tag(Side::Ender | Side::Knockdown));
const Side SSetsukiAT(Side::Attack, "Surprise Gift", 12, 2, 17, 3, 0, 0, 1, Side::Ender);
const Side SSetsukiAB(Side::Attack, "Shuriken Hail", 10, 0, 9, 3, 9, 3, 0);

const Card CSetsuki2H(Card::Two, Card::Heart, SSetsuki2T, SDodge);
const Card CSetsuki3H(Card::Three, Card::Heart, SDodge, SSetsuki3B);
const Card CSetsuki4H(Card::Four, Card::Heart, SSetsuki4T, SDodge);
const Card CSetsuki5H(Card::Five, Card::Heart, SDodge, SSetsuki5B);
const Card CSetsuki6H(Card::Six, Card::Heart, SSetsuki6T, SBlock);
const Card CSetsuki7H(Card::Seven, Card::Heart, SSetsuki7T, SBlock);
const Card CSetsuki8H(Card::Eight, Card::Heart, SBlock, SSetsuki8B);
const Card CSetsuki9H(Card::Nine, Card::Heart, SSetsuki9T, SBlock);
const Card CSetsuki10H(Card::Ten, Card::Heart, SDodge, SSetsuki10B);
const Card CSetsukiJH(Card::Jack, Card::Heart, SSetsukiJ, SSetsukiJ);
const Card CSetsukiQH(Card::Queen, Card::Heart, SSetsukiQ, SSetsukiQ);
const Card CSetsukiKH(Card::King, Card::Heart, SSetsukiKT, SSetsukiKB);
const Card CSetsukiAH(Card::Ace, Card::Heart, SSetsukiAT, SSetsukiAB);

const Card CSetsuki2D(Card::Two, Card::Diamond, SSetsuki2T, SDodge);
const Card CSetsuki3D(Card::Three, Card::Diamond, SDodge, SSetsuki3B);
const Card CSetsuki4D(Card::Four, Card::Diamond, SSetsuki4T, SDodge);
const Card CSetsuki5D(Card::Five, Card::Diamond, SDodge, SSetsuki5B);
const Card CSetsuki6D(Card::Six, Card::Diamond, SSetsuki6T, SBlock);
const Card CSetsuki7D(Card::Seven, Card::Diamond, SSetsuki7T, SBlock);
const Card CSetsuki8D(Card::Eight, Card::Diamond, SBlock, SSetsuki8B);
const Card CSetsuki9D(Card::Nine, Card::Diamond, SSetsuki9T, SBlock);
const Card CSetsuki10D(Card::Ten, Card::Diamond, SDodge, SSetsuki10B);
const Card CSetsukiJD(Card::Jack, Card::Diamond, SSetsukiJ, SSetsukiJ);
const Card CSetsukiQD(Card::Queen, Card::Diamond, SSetsukiQ, SSetsukiQ);
const Card CSetsukiKD(Card::King, Card::Diamond, SSetsukiKT, SSetsukiKB);
const Card CSetsukiAD(Card::Ace, Card::Diamond, SSetsukiAT, SSetsukiAB);

const Card CSetsuki2C(Card::Two, Card::Club, SSetsuki2T, SDodge);
const Card CSetsuki3C(Card::Three, Card::Club, SDodge, SSetsuki3B);
const Card CSetsuki4C(Card::Four, Card::Club, SSetsuki4T, SDodge);
const Card CSetsuki5C(Card::Five, Card::Club, SDodge, SSetsuki5B);
const Card CSetsuki6C(Card::Six, Card::Club, SSetsuki6T, SBlock);
const Card CSetsuki7C(Card::Seven, Card::Club, SSetsuki7T, SBlock);
const Card CSetsuki8C(Card::Eight, Card::Club, SBlock, SSetsuki8B);
const Card CSetsuki9C(Card::Nine, Card::Club, SSetsuki9T, SBlock);
const Card CSetsuki10C(Card::Ten, Card::Club, SDodge, SSetsuki10B);
const Card CSetsukiJC(Card::Jack, Card::Club, SSetsukiJ, SSetsukiJ);
const Card CSetsukiQC(Card::Queen, Card::Club, SSetsukiQ, SSetsukiQ);
const Card CSetsukiKC(Card::King, Card::Club, SSetsukiKT, SSetsukiKB);
const Card CSetsukiAC(Card::Ace, Card::Club, SSetsukiAT, SSetsukiAB);

const Card CSetsuki2S(Card::Two, Card::Spade, SSetsuki2T, SDodge);
const Card CSetsuki3S(Card::Three, Card::Spade, SDodge, SSetsuki3B);
const Card CSetsuki4S(Card::Four, Card::Spade, SSetsuki4T, SDodge);
const Card CSetsuki5S(Card::Five, Card::Spade, SDodge, SSetsuki5B);
const Card CSetsuki6S(Card::Six, Card::Spade, SSetsuki6T, SBlock);
const Card CSetsuki7S(Card::Seven, Card::Spade, SSetsuki7T, SBlock);
const Card CSetsuki8S(Card::Eight, Card::Spade, SBlock, SSetsuki8B);
const Card CSetsuki9S(Card::Nine, Card::Spade, SSetsuki9T, SBlock);
const Card CSetsuki10S(Card::Ten, Card::Spade, SDodge, SSetsuki10B);
const Card CSetsukiJS(Card::Jack, Card::Spade, SSetsukiJ, SSetsukiJ);
const Card CSetsukiQS(Card::Queen, Card::Spade, SSetsukiQ, SSetsukiQ);
const Card CSetsukiKS(Card::King, Card::Spade, SSetsukiKT, SSetsukiKB);
const Card CSetsukiAS(Card::Ace, Card::Spade, SSetsukiAT, SSetsukiAB);

const Card CSetsukiJoker1(Card::Joker, Card::None, SBurst, SBurst);
const Card CSetsukiJoker2(Card::Joker, Card::None, SBurst, SBurst);

const Card *const DLSetsuki[rule::max_decksize] =
				{&CSetsuki2H, &CSetsuki2D, &CSetsuki2C, &CSetsuki2S,
				 &CSetsuki3H, &CSetsuki3D, &CSetsuki3C, &CSetsuki3S,
				 &CSetsuki4H, &CSetsuki4D, &CSetsuki4C, &CSetsuki4S,
				 &CSetsuki5H, &CSetsuki5D, &CSetsuki5C, &CSetsuki5S,
				 &CSetsuki6H, &CSetsuki6D, &CSetsuki6C, &CSetsuki6S,
				 &CSetsuki7H, &CSetsuki7D, &CSetsuki7C, &CSetsuki7S,
				 &CSetsuki8H, &CSetsuki8D, &CSetsuki8C, &CSetsuki8S,
				 &CSetsuki9H, &CSetsuki9D, &CSetsuki9C, &CSetsuki9S,
				 &CSetsuki10H, &CSetsuki10D, &CSetsuki10C, &CSetsuki10S,
				 &CSetsukiJH, &CSetsukiJD, &CSetsukiJC, &CSetsukiAS,
				 &CSetsukiQH, &CSetsukiQD, &CSetsukiQC, &CSetsukiQS,
				 &CSetsukiKH, &CSetsukiKD, &CSetsukiKC, &CSetsukiKS,
				 &CSetsukiAH, &CSetsukiAD, &CSetsukiAC, &CSetsukiAS,
				 &CSetsukiJoker1, &CSetsukiJoker2};
const Deck DSetsuki(DLSetsuki);

Fighter FGrave(		"Grave",			"Wind Warrior",			4, 3, 3, 4, 3, "Knowing the Opponent",	"My skills increase every day. Do yours?",														90, DGrave);
Fighter FMidori(	"Master Midori",	"Mentor Dragon",		3, 2, 5, 3, 1, "Aspect of the Dragon",	"Learning respect for others is as important as learning to fight honorably.",					90, DMidori);
Fighter FRook(		"Rook",				"Stone Golem",			3, 4, 5, 4, 0, "Rock Armor",			"The Fantasy-Strike tournament will go on, no matter what armies Flagstone sends to stop it.",	100, DRook);
Fighter FValerie(	"Valerie",			"Manic Painter",		6, 4, 4, 3, 3, "Agile Hands",			"I can love whoever I want in Rook's land of Do-As-You-Please.",								80, DValerie);
Fighter FLum(		"Lum",				"Gambling Panda",		4, 3, 2, 3, 4, "Roll the Dice",			"Can we spice this up a little? I'm itching for some action... and some bamboo!",				90, DLum);
Fighter FJaina(		"Jaina",			"Phoenix Archer",		5, 5, 4, 2, 4, "Burning Vigor",			"You think I'm hot? You have no idea...",														85, DJaina);
Fighter FSetsuki(	"Setsuki",			"Ninja Student",		6, 5, 4, 2, 4, "Speed of the Fox",		"Whatever Grave says is probably right! He'll kick the Blood Guard's ass any day!",				70, DSetsuki);
/*
Fighter FDeGrey(	"DeGrey",			"Ghostly Diplomat",		4, 3, 3, 3, 5, "Moral High Ground",		"By silver tongue or blood-letting, I will get justice for all.",								90, DDeGrey);
Fighter FGeiger(	"Geiger",			"Precise Watchmaker",	4, 4, 3, 3, 2, "Time Stop",				"Once time is lost, you can't get it back... or can you?",										90, DGeiger);
Fighter FArgagarg(	"Argagarg",			"Water Shaman",			3, 1, 2, 5, 2, "Hex of Murkwood",		"Savages? We have more heart than other races... and usually less temper.",						85, DArgagarg);
*/

