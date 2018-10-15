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
#define PAIR 100	//sets return values of points from pairs
#define THREE 300	
#define STRAIGHT 400
#define FLUSH 500
#define FULLHOUSE 600
#define FOUR 700	//all the way to royal flush (900 straight + flush)
#define SPADE 10	//sets return values of flush from spades
#define CLUBS 20
#define DIAMONDS 30
#define HEARTS 40	//to hearts

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

