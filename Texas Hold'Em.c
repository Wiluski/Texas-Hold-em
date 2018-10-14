// all the defined values and function prototypes are in the header file
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Texas Hold'em.h"


int main(int argc, char** argv) {
	int pointsPlayer = 0;
	int pointsComputer = 0;
	
	deal();
	
	pointsPlayer = checkPairAndThreePlayer() + checkStraightPlayer() + checkFlushPlayer() + checkFourPlayer() + checkFivePlayer();
	pointsComputer = checkPairAndThreeComputer() + checkStraightComputer() + checkFlushComputer() + checkFourComputer() + checkFiveComputer();
	
	if(pointsPlayer > pointsComputer){
		printf("The player wins! %d, %d", pointsPlayer, pointsComputer);
	}else if(pointsComputer > pointsPlayer){
		printf("The computer wins! %d, %d", pointsComputer, pointsPlayer);
	}else{
		printf("its a draw");
	}
	
	return 0;
}

//function takes random face character and suit and divides them to 3 files which are hands that will be delt and table cards which will be delt
void deal(){
	FILE *hand1, *hand2, *table;
	hand1 = fopen("hand1.txt", "w");
	hand2 = fopen("hand2.txt", "w");
	table = fopen("table.txt", "w");
	
	// takes the char values for face of the cards
	char face[FACE] = {
		'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'
	};
	
	// takes the char values for suit of the cards
	char suit [SUIT] = {
		'S', 'C', 'D', 'H'
	};
	
	//integers where randomised values of face and suit are stored
	int pullSuit;
	int pullCard;

	//integers to for loop which runs the amount of cards to every determined file 
	int h1, h2, tb;
	
	//initialises the random number generator
	time_t t;
	srand((unsigned) time(&t));
			
		//first for loop for first hand
		for(h1=1;h1<=HAND; h1++){
			pullCard = rand() % FACE;
			pullSuit = rand() % SUIT;
			fprintf(hand1,"%c%c ", face[pullCard], suit[pullSuit]);
		}
		
		//second for loop for second hand
		for(h2=1;h2<=HAND; h2++){
			pullCard = rand() % FACE;
			pullSuit = rand() % SUIT;
			fprintf(hand2,"%c%c ", face[pullCard], suit[pullSuit]);
		}
		
		//third for loop for the cards in table
		for(tb=1;tb<=TABLE; tb++){
			pullCard = rand() % FACE;
			pullSuit = rand() % SUIT;
			fprintf(table,"%c%c ", face[pullCard], suit[pullSuit]);
		}
	
	
	fclose(hand1);
	fclose(hand2);
	fclose(table);
	
	//runs the compare function after cards are delt
	compare();
}

void compare(){
	//open files where the cards are delt
	FILE *hand1, *hand2, *table;
	hand1 = fopen("hand1.txt", "r");
	hand2 = fopen("hand2.txt", "r");
	table = fopen("table.txt", "r");
	
	//used in for loops to run scan through the files to get every card for comparison
	int i;
	
	// hand and thand(table hand) are for scanning files in for loops and then the values are copied to every card one at a time
	char hand[TABLE],thand[TABLE2], card1[CARD], card2[CARD], card3[CARD], card4[CARD], card5[CARD], card6[CARD], card7[CARD], card8[CARD], card9[CARD];

	for(i=0; i<TABLE; i++){
		fscanf(hand1, "%c", &hand[i]);
	}

	// copying values of the hand array to determine first 2 cards
	strncpy(card1, hand, CARD);
	strncpy(card2, hand+3, CARD);
	card1[CARD] = '\0';
	card2[CARD] = '\0';
	
	for(i=0; i<TABLE; i++){
		fscanf(hand2, "%c", &hand[i]);
	}	
	// copying values of the hand array to determine next 2 cards
	strncpy(card3, hand, CARD);
	strncpy(card4, hand+3, CARD);
	card3[CARD] = '\0';
	card4[CARD] = '\0';
	
	for(i=0; i<TABLE2; i++){
		fscanf(table, "%c", &thand[i]);
	}
	
	// copying values of the table array to determine last 5 cards
	strncpy(card5, thand, CARD);
	strncpy(card6, thand+3, CARD);	
	strncpy(card7, thand+6, CARD);
	strncpy(card8, thand+9, CARD);
	strncpy(card9, thand+12, CARD);
	card5[CARD] = '\0';
	card6[CARD] = '\0';
	card7[CARD] = '\0';
	card8[CARD] = '\0';
	card9[CARD] = '\0';
	
	fclose(hand1);
	fclose(hand2);
	fclose(table);
	//compares the cards, if any of them have the same value as other, the cards are delt again
	if((strcmp(card1,card2) != 0) && (strcmp(card1,card3) != 0) && (strcmp(card1,card4) != 0) && (strcmp(card1,card5) != 0) && (strcmp(card1,card6) != 0) && 
		(strcmp(card1,card7) != 0) && (strcmp(card1,card8) != 0) && (strcmp(card1,card9) != 0) && (strcmp(card2,card3) != 0) && (strcmp(card2,card4) != 0) && 
		(strcmp(card2,card5) != 0) && (strcmp(card2,card6) != 0) && (strcmp(card2,card7) != 0) && (strcmp(card2,card8) != 0) && (strcmp(card2,card9) != 0) && 
		(strcmp(card3,card4) != 0) && (strcmp(card3,card5) != 0) && (strcmp(card3,card6) != 0) && (strcmp(card3,card7) != 0) && (strcmp(card3,card8) != 0) && 
		(strcmp(card3,card9) != 0) && (strcmp(card4,card5) != 0) && (strcmp(card4,card6) != 0) && (strcmp(card4,card7) != 0) && (strcmp(card4,card8) != 0) && 
		(strcmp(card4,card9) != 0) && (strcmp(card5,card6) != 0) && (strcmp(card7,card8) != 0) && (strcmp(card6,card7) != 0) && (strcmp(card6,card8) != 0) && 
		(strcmp(card6,card9) != 0) && (strcmp(card7,card8) != 0) && (strcmp(card7,card9) != 0) && (strcmp(card8,card9) != 0)){
			//runs the function for filling a file with cards which player uses
			fillPointCalculationPlayer();
			//runs the function for filling a file with cards which computer uses
			fillPointCalculationComputer();
	}else{
		//if any of the cards match eachother the cards are dealt again
		deal();
	}
}

//Fills players hand and the cards in the table to a new file for checking points
void fillPointCalculationPlayer(){
	FILE *hand, *table, *points;
	char tmp;
	hand = fopen("hand1.txt", "r");
	table = fopen("table.txt", "r");
	points = fopen("points1.txt", "w");
	
	while((tmp = fgetc(hand)) != EOF)
		fputc(tmp, points);
		
	while((tmp = fgetc(table)) != EOF)
		fputc(tmp,points);
	
	fclose(hand);
	fclose(table);
	fclose(points);
}

//Fills computers hand and the cards in the table to a new file for checking points
void fillPointCalculationComputer(){
	FILE *hand, *table, *points;
	char tmp;
	hand = fopen("hand2.txt", "r");
	table = fopen("table.txt", "r");
	points = fopen("points2.txt", "w");
	
	while((tmp = fgetc(hand)) != EOF)
		fputc(tmp, points);
		
	while((tmp = fgetc(table)) != EOF)
		fputc(tmp,points);
		
	fclose(hand);
	fclose(table);
	fclose(points);
}

//checks if player has 5 cards of the same value and returns an integer for checking points
int checkFivePlayer(){
	//opens the file where the cards are stored
	
	FILE *points;
	points = fopen("points1.txt", "r");
	char p;
	
	int f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	int i;
	int five = 0;
	while((p=fgetc(points)) != EOF){
		switch(p){
			case'2': f2++; break;
			case'3': f3++; break;
			case'4': f4++; break;
			case'5': f5++; break;
			case'6': f6++; break;
			case'7': f7++; break;
			case'8': f8++; break;
			case'9': f9++; break;
			case'T': f10++; break;
			case'J': f11++; break;
			case'Q': f12++; break;
			case'K': f13++; break;
			case'A': f14++; break;
		}
	}
	
	int rank[RANK] = {f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};
	
	for(i=0; i<RANK; i++){
		if(rank[i]==5){
			five++;
			
			if(five==1){
			
				return FIVE + i;
				
			}else{
					return 0;
			}
		}
	}
}

//checks if Computer has 5 cards of the same value and returns an integer for checking points
int checkFiveComputer(){
	
	FILE *points;
	points = fopen("points2.txt", "r");
	char p;
	
	int f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	int i;
	int five = 0;
	while((p=fgetc(points)) != EOF){
		switch(p){
			case'2': f2++; break;
			case'3': f3++; break;
			case'4': f4++; break;
			case'5': f5++; break;
			case'6': f6++; break;
			case'7': f7++; break;
			case'8': f8++; break;
			case'9': f9++; break;
			case'T': f10++; break;
			case'J': f11++; break;
			case'Q': f12++; break;
			case'K': f13++; break;
			case'A': f14++; break;
		}
	}
	
	int rank[RANK] = {f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};
	//printf("%d, %d %d, %d %d, %d %d, %d %d, %d %d, %d %d," , f2, f3, f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14);
	
	for(i=0; i<RANK; i++){
		if(rank[i]==5){
			five++;
			
			if(five==1){
			
				return FIVE + i;
				
			}else{
					return 0;
			}
		}
	}
}

//checks if player has 4 cards of the same value and returns an integer for checking points
int checkFourPlayer(){
		
	FILE *points;
	points = fopen("points1.txt", "r");
	char p;
	
	int f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	int i;
	int four = 0;
	while((p=fgetc(points)) != EOF){
		switch(p){
			case'2': f2++; break;
			case'3': f3++; break;
			case'4': f4++; break;
			case'5': f5++; break;
			case'6': f6++; break;
			case'7': f7++; break;
			case'8': f8++; break;
			case'9': f9++; break;
			case'T': f10++; break;
			case'J': f11++; break;
			case'Q': f12++; break;
			case'K': f13++; break;
			case'A': f14++; break;
		}
	}
	
	int rank[RANK] = {f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};
	//printf("%d, %d %d, %d %d, %d %d, %d %d, %d %d, %d %d," , f2, f3, f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14);
	
	for(i=0; i<RANK; i++){
		if(rank[i]==3){
			four++;
			
			if(four==1){
			
				return FOUR + i;
				
			}else{
					return 0;
			}
		}
	}
}

//checks if computer has 4 cards of the same value and returns an integer for checking points
int checkFourComputer(){
	
	FILE *points;
	points = fopen("points2.txt", "r");
	char p;
	
	int f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	int i;
	int four = 0;
	while((p=fgetc(points)) != EOF){
		switch(p){
			case'2': f2++; break;
			case'3': f3++; break;
			case'4': f4++; break;
			case'5': f5++; break;
			case'6': f6++; break;
			case'7': f7++; break;
			case'8': f8++; break;
			case'9': f9++; break;
			case'T': f10++; break;
			case'J': f11++; break;
			case'Q': f12++; break;
			case'K': f13++; break;
			case'A': f14++; break;
		}
	}
	
	int rank[RANK] = {f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};
	//printf("%d, %d %d, %d %d, %d %d, %d %d, %d %d, %d %d," , f2, f3, f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14);
	
	for(i=0; i<RANK; i++){
		if(rank[i]==3){
			four++;
			
			if(four==1){
			
				return FOUR + i;
				
			}else{
					return 0;
			}
		}
	}
}

//checks if Player has a Flush
int checkFlushPlayer(){
	FILE *points;
	points = fopen("points1.txt", "r");

	char p;
	int s=0, c=0, d=0, h=0;

	while((p = fgetc(points)) != EOF){
		switch(p){
			case 'S': s ++; break;
			case 'C': c ++; break;
			case 'D': d ++; break;
			case 'H': h ++; break;
		}

	}
	
	fclose(points);
	
	if(s==5){
		return FLUSH + SPADE;
	}
	else if(c==5){
		return FLUSH + CLUBS;
	}
	else if(d==5){
		return FLUSH + DIAMONDS;
	}
	else if(h==5){
		return FLUSH + HEARTS;
	}
	
	
}

//checks if computer has a Flush
int checkFlushComputer(){
	FILE *points;
	points = fopen("points2.txt", "r");

	char p;
	int s=0, c=0, d=0, h=0;

	while((p = fgetc(points)) != EOF){
		switch(p){
			//default: other++; break;
			case 'S': s ++; break;
			case 'C': c ++; break;
			case 'D': d ++; break;
			case 'H': h ++; break;
		}
	}

	fclose(points);
	
	if(s==5){
		return FLUSH + SPADE;
	}
	else if(c==5){
		return FLUSH + CLUBS;
	}
	else if(d==5){
		return FLUSH + DIAMONDS;
	}
	else if(h==5){
		return FLUSH + HEARTS;
	}
}

int checkStraightPlayer(){
	FILE *points;
	points = fopen("points1.txt", "r");
	char p;
	
	int f1=0, f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	while((p=fgetc(points)) != EOF){
		switch(p){
			case'2': f2++; break;
			case'3': f3++; break;
			case'4': f4++; break;
			case'5': f5++; break;
			case'6': f6++; break;
			case'7': f7++; break;
			case'8': f8++; break;
			case'9': f9++; break;
			case'T': f10++; break;
			case'J': f11++; break;
			case'Q': f12++; break;
			case'K': f13++; break;
			case'A': f1++; f14++; break;
		}
	}
	
	if(f1==1 && f2==1 && f3==1 && f4==1 && f5==1){
		return STRAIGHT + 5;
	}else if(f2==1 && f3==1 && f4==1 && f5==1 && f6==1){
		return STRAIGHT + 6;
	}else if(f3==1 && f4==1 && f5==1 && f6==1 && f7==1){
		return STRAIGHT + 7;
	}else if(f4==1 && f5==1 && f6==1 && f7==1 && f8==1){
		return STRAIGHT + 8;
	}else if(f5==1 && f6==1 && f7==1 && f8==1 && f9==1){
		return STRAIGHT + 9;
	}else if(f6==1 && f7==1 && f8==1 && f9==1 && f10==1){
		return STRAIGHT + 10;
	}else if(f7==1 && f8==1 && f9==1 && f10==1 && f11==1){
		return STRAIGHT + 11;
	}else if(f8==1 && f9==1 && f10==1 && f11==1 && f12==1){
		return STRAIGHT + 12;
	}else if(f9==1 && f10==1 && f11==1 && f12==1 && f13==1){
		return STRAIGHT + 13;
	}else if(f10==1 && f11==1 && f12==1 && f13==1 && f14==1){
		return STRAIGHT + 14;
	}else{
		return 0;
	}
	
	fclose(points);
}

int checkStraightComputer(){
	FILE *points;
	points = fopen("points2.txt", "r");
	char p;
	
	int f1=0, f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	while((p=fgetc(points)) != EOF){
		switch(p){
			case'2': f2++; break;
			case'3': f3++; break;
			case'4': f4++; break;
			case'5': f5++; break;
			case'6': f6++; break;
			case'7': f7++; break;
			case'8': f8++; break;
			case'9': f9++; break;
			case'T': f10++; break;
			case'J': f11++; break;
			case'Q': f12++; break;
			case'K': f13++; break;
			case'A': f1++; f14++; break;
		}
	}
	
	if(f1==1 && f2==1 && f3==1 && f4==1 && f5==1){
		return STRAIGHT + 5;
	}else if(f2==1 && f3==1 && f4==1 && f5==1 && f6==1){
		return STRAIGHT + 6;
	}else if(f3==1 && f4==1 && f5==1 && f6==1 && f7==1){
		return STRAIGHT + 7;
	}else if(f4==1 && f5==1 && f6==1 && f7==1 && f8==1){
		return STRAIGHT + 8;
	}else if(f5==1 && f6==1 && f7==1 && f8==1 && f9==1){
		return STRAIGHT + 9;
	}else if(f6==1 && f7==1 && f8==1 && f9==1 && f10==1){
		return STRAIGHT + 10;
	}else if(f7==1 && f8==1 && f9==1 && f10==1 && f11==1){
		return STRAIGHT + 11;
	}else if(f8==1 && f9==1 && f10==1 && f11==1 && f12==1){
		return STRAIGHT + 12;
	}else if(f9==1 && f10==1 && f11==1 && f12==1 && f13==1){
		return STRAIGHT + 13;
	}else if(f10==1 && f11==1 && f12==1 && f13==1 && f14==1){
		return STRAIGHT + 14;
	}else{
		return 0;
	}
	
	fclose(points);
}

int checkPairAndThreePlayer(){
	FILE *points;
	points = fopen("points1.txt", "r");
	char p;
	
	int f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	int i;
	int pair = 0;
	int three = 0;
	while((p=fgetc(points)) != EOF){
		switch(p){
			case'2': f2++; break;
			case'3': f3++; break;
			case'4': f4++; break;
			case'5': f5++; break;
			case'6': f6++; break;
			case'7': f7++; break;
			case'8': f8++; break;
			case'9': f9++; break;
			case'T': f10++; break;
			case'J': f11++; break;
			case'Q': f12++; break;
			case'K': f13++; break;
			case'A': f14++; break;
		}
	}
	
	int rank[RANK] = {f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};
	//printf("%d, %d %d, %d %d, %d %d, %d %d, %d %d, %d %d," , f2, f3, f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14);
	for(i=0; i<RANK; i++){
		if(rank[i]==2){
			pair++;
		}else if(rank[i]==3){
			three++;	
		}
		
	}
	
	if(pair>=2 && three==0){
			
		return 2*PAIR;
				
	}else if(pair==1 && three == 0){
			
		return PAIR;
		
	}else if(pair == 0 && three == 1){
		
		return THREE;
			
	}else if((pair >= 1 && three == 1) || (three == 2)){
		
		return FULLHOUSE;
		
	}else{
		return 0;
	}
	
}

int checkPairAndThreeComputer(){
	
	FILE *points;
	points = fopen("points2.txt", "r");
	char p;
	
	int f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	int i;
	int pair = 0;
	int three = 0;
	while((p=fgetc(points)) != EOF){
		switch(p){
			case'2': f2++; break;
			case'3': f3++; break;
			case'4': f4++; break;
			case'5': f5++; break;
			case'6': f6++; break;
			case'7': f7++; break;
			case'8': f8++; break;
			case'9': f9++; break;
			case'T': f10++; break;
			case'J': f11++; break;
			case'Q': f12++; break;
			case'K': f13++; break;
			case'A': f14++; break;
		}
	}
	
	int rank[RANK] = {f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};
	
	for(i=0; i<RANK; i++){
		if(rank[i]==2){
			pair++;
		}else if(rank[i]==3){
			three++;	
		}
		
	}
	
	if(pair>=2 && three==0){
		
		return 2*PAIR;
		
	}else if(pair==1 && three == 0){
			
		return PAIR;
		
	}else if(pair == 0 && three == 1){
		
		return THREE;
			
	}else if((pair >= 1 && three == 1) || (three == 2)){
		
		return FULLHOUSE;
		
	}else{
		return 0;
	}
		
}

void menu(){
	
}
