#include <stdio.h>
#include <string.h>
#define HAND 2
#define FACE 13
#define SUIT 4
#define DECK 52
#define TABLE 5
#define CARD 2
#define TABLE2 14
#define RANK 13
#define CARDS 19
#define PAIR 100
#define THREE 300
#define STRAIGHT 400
#define FLUSH 500
#define FULLHOUSE 600
#define FOUR 700
#define FIVE 800
#define SPADE 10
#define CLUBS 20
#define DIAMONDS 30
#define HEARTS 40

void deal();
void menu();
void compare();
void fillPointCalculationPlayer();
void fillPointCalculationComputer();
int checkFourPlayer();
int checkFourComputer();
int checkFlushPlayer();
int checkFlushComputer();
int checkStraightPlayer();
int checkStraightComputer();
int checkPairAndThreePlayer();
int checkPairAndThreeComputer();
int checkHighCardPlayer();
int checkHighCardComputer();

