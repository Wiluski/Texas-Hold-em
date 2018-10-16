#include <stdio.h>
#include <string.h>
#define CARD 2	// fills hand arrays of cards (deal) defines the size of cards (compare)
#define SUIT 4	// used to determine size of suit array
#define TABLE 5	// size of hands mainly for the size of table suit and face
#define SUITSUM 7 //amount of max of same suit
#define CARDS 19 // Used to fill arrays which use point files
#define TABLE2 14 // sets the size for array which stores values of table file
#define FACE 13	// size for array containing face characters
#define RANK 13	// used for arrays handling face values
#define PAIR 1000	//sets return values of points from pairs
#define THREE 3000
#define STRAIGHT 4000
#define FLUSH 5000
#define FULLHOUSE 6000
#define FOUR 7000	//all the way to royal flush (9000 straight + flush)
#define SPADE 100	//sets return values of flush from spades
#define CLUBS 200
#define DIAMONDS 300
#define HEARTS 400	//to hearts

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

