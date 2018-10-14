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
	
	if(checkStraightPlayer()==0){
		pointsPlayer = checkPairAndThreePlayer() + checkStraightPlayer() + checkFlushPlayer() + checkFourPlayer() + checkHighCardPlayer();
	}else{
		pointsPlayer = checkPairAndThreePlayer() + checkStraightPlayer() + checkFlushPlayer() + checkFourPlayer();
	}
	
	if(checkStraightComputer()==0){
		pointsComputer = checkPairAndThreeComputer() + checkStraightComputer() + checkFlushComputer() + checkFourComputer() + checkHighCardComputer();
	}else{
		pointsComputer == checkPairAndThreeComputer() + checkStraightComputer() + checkFlushComputer() + checkFourComputer();
	}
	
	
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
	
	fclose(points);
	
	for(i=0; i<RANK; i++){
		if(rank[i]==4){
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
	
	fclose(points);
	
	for(i=0; i<RANK; i++){
		if(rank[i]==4){
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
	int i,j;
	
	while((p=fgetc(points)) != EOF){
		switch(p){
			case'2': f2=2; break;
			case'3': f3=3; break;
			case'4': f4=4; break;
			case'5': f5=5; break;
			case'6': f6=6; break;
			case'7': f7=7; break;
			case'8': f8=8; break;
			case'9': f9=9; break;
			case'T': f10=10; break;
			case'J': f11=11; break;
			case'Q': f12=12; break;
			case'K': f13=13; break;
			case'A': f1=1; f14=14; break;
		}
	}
	int rank[RANK+1] = {f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};
	
	fclose(points);

	for(i=0; i<RANK+1; i++){
		for(j=0; j<RANK+1; j++){
			if(rank[i]>rank[j]){
				int tmp=rank[i];
				rank[i]=rank[j];
				rank[j]=tmp;
			}
		}
	}

	if		(rank[0]-1 == rank[1] && rank[1]-1 == rank[2] && rank[2]-1 == rank[3] && rank[3]-1 == rank[4]){
		return STRAIGHT + rank[0];
	}else if(rank[1]-1 == rank[2] && rank[2]-1 == rank[3] && rank[3]-1 == rank[4] && rank[4]-1 == rank[5]){
		return STRAIGHT + rank[1];
	}else if(rank[2]-1 == rank[3] && rank[3]-1 == rank[4] && rank[4]-1 == rank[5] && rank[5]-1 == rank[6]){
		return STRAIGHT + rank[2];
	}else if(rank[3]-1 == rank[4] && rank[4]-1 == rank[5] && rank[5]-1 == rank[6] && rank[6]-1 == rank[7]){
		return STRAIGHT + rank[3];
	}else{
		return 0;
	}


}

int checkStraightComputer(){
	FILE *points;
	points = fopen("points2.txt", "r");
	char p;
	
	int f1=0, f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	int i,j;
	
	while((p=fgetc(points)) != EOF){
		switch(p){
			case'2': f2=2; break;
			case'3': f3=3; break;
			case'4': f4=4; break;
			case'5': f5=5; break;
			case'6': f6=6; break;
			case'7': f7=7; break;
			case'8': f8=8; break;
			case'9': f9=9; break;
			case'T': f10=10; break;
			case'J': f11=11; break;
			case'Q': f12=12; break;
			case'K': f13=13; break;
			case'A': f1=1; f14=14; break;
		}
	}
	int rank[RANK+1] = {f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};
	
	fclose(points);

	for(i=0; i<RANK+1; i++){
		for(j=0; j<RANK+1; j++){
			if(rank[i]>rank[j]){
				int tmp=rank[i];
				rank[i]=rank[j];
				rank[j]=tmp;
			}
		}
	}

	if		(rank[0]-1 == rank[1] && rank[1]-1 == rank[2] && rank[2]-1 == rank[3] && rank[3]-1 == rank[4]){
		return STRAIGHT + rank[0];
	}else if(rank[1]-1 == rank[2] && rank[2]-1 == rank[3] && rank[3]-1 == rank[4] && rank[4]-1 == rank[5]){
		return STRAIGHT + rank[1];
	}else if(rank[2]-1 == rank[3] && rank[3]-1 == rank[4] && rank[4]-1 == rank[5] && rank[5]-1 == rank[6]){
		return STRAIGHT + rank[2];
	}else if(rank[3]-1 == rank[4] && rank[4]-1 == rank[5] && rank[5]-1 == rank[6] && rank[6]-1 == rank[7]){
		return STRAIGHT + rank[3];
	}else{
		return 0;
	}

}

int checkPairAndThreePlayer(){
	FILE *points;
	points = fopen("points1.txt", "r");
	char p;
	int count2=0, count3=0, count4=0, count5=0, count6=0, count7=0, count8=0, count9=0, count10=0, count11=0, count12=0, count13=0, count14=0;
	int f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	int s=0, c=0, d=0, h=0;
	int i, j, tmp;
	int firstPairValue, secondPairValue, thirdPairValue, highPairValue, highThreeValue;
	int pair = 0;
	int three = 0;
	while((p=fgetc(points)) != EOF){
		switch(p){
			case 'S': s ++; break;
			case 'C': c ++; break;
			case 'D': d ++; break;
			case 'H': h ++; break;
			case'2': f2=2; count2++; break;
			case'3': f3=3; count3++; break;
			case'4': f4=4; count4++; break;
			case'5': f5=5; count5++; break;
			case'6': f6=6; count6++; break;
			case'7': f7=7; count7++; break;
			case'8': f8=8; count8++; break;
			case'9': f9=9; count9++; break;
			case'T': f10=10; count10++; break;
			case'J': f11=11; count11++; break;
			case'Q': f12=12; count12++; break;
			case'K': f13=13; count13++; break;
			case'A': f14=14; count14++; break;
		}
	}
	
	int rank[RANK] = {f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};
	int count[RANK] = {count2,count3,count4,count5,count6,count7,count8,count9,count10,count11,count12,count13,count14};
	
	fclose(points);
	
	for(i=0; i<RANK; i++){
		
		if(count[i]==2){

			pair++;
			highPairValue = rank[i];
			for(j=0; j<3; j++){
				tmp = rank[i];
				rank[i] = rank[j];
				rank[j] = tmp;
			}
			
		}else if(count[i]==3){
			three++;
			highThreeValue = rank[i];
		}
		
	}
	
	firstPairValue = rank[0];
	secondPairValue = rank[1];
	thirdPairValue = rank[2];
	
	
	if		(pair>=2 && three==0){
		
		if		(firstPairValue > secondPairValue && firstPairValue > thirdPairValue){
			return 2*PAIR + firstPairValue + secondPairValue;
		}else if(secondPairValue > firstPairValue && secondPairValue > thirdPairValue){
			return 2*PAIR + firstPairValue + secondPairValue;
		}else if(thirdPairValue > firstPairValue && thirdPairValue > secondPairValue){
			return 2*PAIR + thirdPairValue + secondPairValue;
		}
	
				
	}else if(pair==1 && three == 0 && s < 6 && c < 6 && d < 6 && h < 6){
			
		return PAIR + highPairValue;
		
	}else if(pair == 0 && three == 1 && s < 6 && c < 6 && d < 6 && h < 6){
		
		return THREE + highThreeValue;
			
	}else if((pair >= 1 && three == 1) || (three == 2)){
		
		return FULLHOUSE + highThreeValue;
		
	}else{
		return 0;
	}
		
}

int checkPairAndThreeComputer(){
	
	FILE *points;
	points = fopen("points2.txt", "r");
	char p;
	
	int count2=0, count3=0, count4=0, count5=0, count6=0, count7=0, count8=0, count9=0, count10=0, count11=0, count12=0, count13=0, count14=0;
	int f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	int s=0, c=0, d=0, h=0;
	int i, j, tmp;
	int firstPairValue, secondPairValue, thirdPairValue, highPairValue, highThreeValue;
	int pair = 0;
	int three = 0;
	while((p=fgetc(points)) != EOF){
		switch(p){			
			case 'S': s ++; break;
			case 'C': c ++; break;
			case 'D': d ++; break;
			case 'H': h ++; break;
			case'2': f2=2; count2++; break;
			case'3': f3=3; count3++; break;
			case'4': f4=4; count4++; break;
			case'5': f5=5; count5++; break;
			case'6': f6=6; count6++; break;
			case'7': f7=7; count7++; break;
			case'8': f8=8; count8++; break;
			case'9': f9=9; count9++; break;
			case'T': f10=10; count10++; break;
			case'J': f11=11; count11++; break;
			case'Q': f12=12; count12++; break;
			case'K': f13=13; count13++; break;
			case'A': f14=14; count14++; break;
		}
	}
	
	int rank[RANK] = {f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};
	int count[RANK] = {count2,count3,count4,count5,count6,count7,count8,count9,count10,count11,count12,count13,count14};
	
	fclose(points);
	
	for(i=0; i<RANK; i++){
		
		if(count[i]==2){

			pair++;
			highPairValue = rank[i];
			for(j=0; j<3; j++){
				tmp = rank[i];
				rank[i] = rank[j];
				rank[j] = tmp;
			}
			
		}else if(count[i]==3){
			three++;
			highThreeValue = rank[i];
		}
		
	}
	
	firstPairValue = rank[0];
	secondPairValue = rank[1];
	thirdPairValue = rank[2];
	
	
	if		(pair>=2 && three==0){
		
		if		(firstPairValue > secondPairValue && firstPairValue > thirdPairValue){
			return 2*PAIR + firstPairValue + secondPairValue;
		}else if(secondPairValue > firstPairValue && secondPairValue > thirdPairValue){
			return 2*PAIR + firstPairValue + secondPairValue;
		}else if(thirdPairValue > firstPairValue && thirdPairValue > secondPairValue){
			return 2*PAIR + thirdPairValue + secondPairValue;
		}
	
				
	}else if(pair==1 && three == 0 && s < 6 && c < 6 && d < 6 && h < 6){
			
		return PAIR + highPairValue;
		
	}else if(pair == 0 && three == 1 && s < 6 && c < 6 && d < 6 && h < 6){
		
		return THREE + highThreeValue;
			
	}else if((pair >= 1 && three == 1) || (three == 2)){
		
		return FULLHOUSE + highThreeValue;
		
	}else{
		return 0;
	}
	
}

int checkHighCardPlayer(){
	FILE *points;
	points = fopen("points1.txt", "r");
	char p;
	int f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	int count2=0, count3=0, count4=0, count5=0, count6=0, count7=0, count8=0, count9=0, count10=0, count11=0, count12=0, count13=0, count14=0;
	int s=0, c=0, d=0, h=0;
	int i, j;
	int pair=0, three=0, four=0;
	int first, second, third, fourth, fifth;
	while((p=fgetc(points)) != EOF){
		switch(p){
			case'S': s++; break;
			case'C': c++; break;
			case'D': d++; break;
			case'H': h++; break;
			case'2': f2=2; count2++; break;
			case'3': f3=3; count3++; break;
			case'4': f4=4; count4++; break;
			case'5': f5=5; count5++; break;
			case'6': f6=6; count6++; break;
			case'7': f7=7; count7++; break;
			case'8': f8=8; count8++; break;
			case'9': f9=9; count9++; break;
			case'T': f10=10; count10++; break;
			case'J': f11=11; count11++; break;
			case'Q': f12=12; count12++; break;
			case'K': f13=13; count13++; break;
			case'A': f14=14; count14++; break;
		}
	}
	int count[RANK] = {count2,count3,count4,count5,count6,count7,count8,count9,count10,count11,count12,count13,count14};
	int rank[RANK] = {f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};
	
	fclose(points);
	
	for(i=0; i<RANK; i++){
		for(j=0; j<RANK; j++){
			if(rank[j]<rank[i]){
				int tmp=rank[i];
				rank[i]=rank[j];
				rank[j]=tmp;
			}
		}
	}
	
	first = rank[0];
	second = rank[1];
	third = rank[2];
	fourth = rank[3];
	fifth = rank[4];
	
	for(i=0; i<RANK; i++){
		if(count[i]==4){
			four++;
		}else if(count[i]==3){
			three++;
		}else if(count[i]==2){
			pair++;
		}
	}
	
	if(s == 5 || c == 5 || d == 5 || h == 5){
			return 0;
	}else if(four==1){
		for(i=0; i<RANK; i++){
			if(count[i]==4 && i == first-2){
				return second;
			}else{
				return first;
			}
		}
	}else if(three >= 1 && four == 0 && pair == 0){
		for(i=0; i<RANK; i++){
			if(count[i]==3 && i == first-2){
				return second+third;
			}else if(count[i]==3 && i == second - 2){
				return first+third;
			}else{
				return first+second;
			}
		}
	}else if(pair >= 1 && four == 0 && three == 0){
		for(i=0; i<RANK; i++){
			if(count[i]==2 && i == first-2){
				return second+third+fourth+fifth;
			}else if(count[i]==2 && i == second-2){
				return first+third+fourth+fifth;
			}else if(count[i]==2 && i == third-2){
				return first+second+fourth+fifth;
			}else if(count[i]==2 && i == fourth-2){
				return first+second+third+fifth;
			}else{
				return first+second+third+fourth;
			}
		}
	}else if(pair == 0 && three == 0 && four == 0){
		return first+second+third+fourth+fifth;
	}else{
		return 0;
	}
	
}

int checkHighCardComputer(){
	FILE *points;
	points = fopen("points2.txt", "r");
	char p;
	int f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	int count2=0, count3=0, count4=0, count5=0, count6=0, count7=0, count8=0, count9=0, count10=0, count11=0, count12=0, count13=0, count14=0;
	int s=0, c=0, d=0, h=0;
	int i, j;
	int pair=0, three=0, four=0;
	int first, second, third, fourth, fifth;
	while((p=fgetc(points)) != EOF){
		switch(p){
			case'S': s++; break;
			case'C': c++; break;
			case'D': d++; break;
			case'H': h++; break;
			case'2': f2=2; count2++; break;
			case'3': f3=3; count3++; break;
			case'4': f4=4; count4++; break;
			case'5': f5=5; count5++; break;
			case'6': f6=6; count6++; break;
			case'7': f7=7; count7++; break;
			case'8': f8=8; count8++; break;
			case'9': f9=9; count9++; break;
			case'T': f10=10; count10++; break;
			case'J': f11=11; count11++; break;
			case'Q': f12=12; count12++; break;
			case'K': f13=13; count13++; break;
			case'A': f14=14; count14++; break;
		}
	}
	int count[RANK] = {count2,count3,count4,count5,count6,count7,count8,count9,count10,count11,count12,count13,count14};
	int rank[RANK] = {f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};
	
	fclose(points);
	
	for(i=0; i<RANK; i++){
		for(j=0; j<RANK; j++){
			if(rank[j]<rank[i]){
				int tmp=rank[i];
				rank[i]=rank[j];
				rank[j]=tmp;
			}
		}
	}
	
	first = rank[0];
	second = rank[1];
	third = rank[2];
	fourth = rank[3];
	fifth = rank[4];
	
	for(i=0; i<RANK; i++){
		if(count[i]==4){
			four++;
		}else if(count[i]==3){
			three++;
		}else if(count[i]==2){
			pair++;
		}
	}
	
	if(s == 5 || c == 5 || d == 5 || h == 5){
			return 0;
	}else if(four==1){
		for(i=0; i<RANK; i++){
			if(count[i]==4 && i == first-2){
				return second;
			}else{
				return first;
			}
		}
	}else if(three >= 1 && four == 0 && pair == 0){
		for(i=0; i<RANK; i++){
			if(count[i]==3 && i == first-2){
				return second+third;
			}else if(count[i]==3 && i == second - 2){
				return first+third;
			}else{
				return first+second;
			}
		}
	}else if(pair >= 1 && four == 0 && three == 0){
		for(i=0; i<RANK; i++){
			if(count[i]==2 && i == first-2){
				return second+third+fourth+fifth;
			}else if(count[i]==2 && i == second-2){
				return first+third+fourth+fifth;
			}else if(count[i]==2 && i == third-2){
				return first+second+fourth+fifth;
			}else if(count[i]==2 && i == fourth-2){
				return first+second+third+fifth;
			}else{
				return first+second+third+fourth;
			}
		}
	}else if(pair == 0 && three == 0 && four == 0){
		return first+second+third+fourth+fifth;
	}else{
		return 0;
	}
	
}

