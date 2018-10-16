// all the defined values and function prototypes are in the header file
// all the computers functions are identical to the players (exept for the file they read)
// so the computer functions aren't commented
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Texas Hold'em.h"


int main(int argc, char** argv) {
	//used to save the points
	int pointsPlayer = 0;
	int pointsComputer = 0;
	
	//runs the function to deal the cards
	deal();
	
	//if the functions straight and flush returns a value there is no need to check the high card function nor the pairs, threes
	//fours and fullhouse
	if(checkStraightPlayer()==0 || checkFlushPlayer() == 0){
		//sums the values of the functions together
		pointsPlayer = checkPairAndThreePlayer() + checkFourPlayer() + checkHighCardPlayer();
	}else{
		pointsPlayer = checkStraightPlayer() + checkFlushPlayer();
	}
	
	//if the functions straight and flush returns a value there is no need to check the high card function nor the pairs, threes
	//fours and fullhouse
	if(checkStraightComputer()==0 || checkFlushComputer() == 0){
		//sums the values of the functions together
		pointsComputer = checkPairAndThreeComputer() + checkFourComputer() + checkHighCardComputer();
	}else{
		pointsComputer == checkStraightComputer() + checkFlushComputer();
	}
	
	//checks the points and determines the winner
	//prints out only the points aquired throughout the functions and the cards can be found in the text files
	//are coded to be stored to same file where the program is ran
	if(pointsPlayer > pointsComputer){
		printf("The player wins! %d, %d", pointsPlayer, pointsComputer); 	//straight flush gets value of over 900 by combining
	}else if(pointsComputer > pointsPlayer){								//so it will stay the absolute
		printf("The computer wins! %d, %d", pointsComputer, pointsPlayer);
	}else{
		printf("its a draw");
	}
	
	return 0;
}

//function takes random face character and suit and divides them to 3 files which are hands that will be delt and table cards which will be delt
void deal(){
	//hand1 used for saving players cards in hand, hand2 used saving for computers cards in hand, table used for saving cards in table
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
			
		//first for loop for first hand, randomises 2 face values and 2 suit values to a file for player
		for(h1=1;h1<=CARD; h1++){
			pullCard = rand() % FACE;
			pullSuit = rand() % SUIT;
			fprintf(hand1,"%c%c ", face[pullCard], suit[pullSuit]);
		}
		
		//second for loop for second hand, randomises 2 face values and 2 suit values to a file for computer
		for(h2=1;h2<=CARD; h2++){
			pullCard = rand() % FACE;
			pullSuit = rand() % SUIT;
			fprintf(hand2,"%c%c ", face[pullCard], suit[pullSuit]);
		}
		
		//third for loop for the cards in table, randomises 5 face values and 5 suit values to a file that are for both player and computer
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

	//for loops used for reading the files where cards are dealt
	for(i=0; i<TABLE; i++){
		fscanf(hand1, "%c", &hand[i]);
	}

	// copying values of the hand array to determine first 2 cards (players)
	strncpy(card1, hand, CARD);
	strncpy(card2, hand+3, CARD);
	card1[CARD] = '\0';	//not fighting the rules of an array
	card2[CARD] = '\0';
	
	for(i=0; i<TABLE; i++){
		fscanf(hand2, "%c", &hand[i]);
	}	
	
	// copying values of the hand array to determine next 2 cards (computers)
	strncpy(card3, hand, CARD);
	strncpy(card4, hand+3, CARD);
	card3[CARD] = '\0';
	card4[CARD] = '\0';
	
	for(i=0; i<TABLE2; i++){
		fscanf(table, "%c", &thand[i]);
	}
	
	// copying values of the table array to determine last 5 cards (table)
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
	
	//compares the cards, if any of them have the same values as the other, the cards are delt again
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
	
	//used for saving players cards in a point file
	char tmp;
	
	//open files where cards are saved
	hand = fopen("hand1.txt", "r");
	table = fopen("table.txt", "r");
	points = fopen("points1.txt", "w");
	
	//saving cards in hand one character at a time
	while((tmp = fgetc(hand)) != EOF)
		fputc(tmp, points);
	
	//saving cards in table one character at a time
	while((tmp = fgetc(table)) != EOF)
		fputc(tmp,points);
	
	fclose(hand);
	fclose(table);
	fclose(points);
}

//Fills computers hand and the cards in the table to a new file for checking points (same as for the player)
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

//checks if player has 4 cards of the same value and returns a value for checking points
int checkFourPlayer(){
		
	FILE *points;
	points = fopen("points1.txt", "r");
	char p;
	
	//integers for saving the amount of same face value cards from file (set to 0 so values won't vary)
	int f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	
	//integer used to run for loop to check the face value integers
	int i;
	
	//used save if there are 4 of the face value cards
	int four = 0;
	
	//reads the point file and saves the amount of face values
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
	
	//saves the values in an array
	int rank[RANK] = {f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};
	
	fclose(points);
	
	//runs through the array and checks if there are 4 of any kind
	for(i=0; i<RANK; i++){
		if(rank[i]==4){
			four++;
			
			if(four==1){
				//returns defined value and the place (face value) in array
				return FOUR + i + 2;
				
			}else{
				//if there isn't 4 of the same kind, value will be 0
				return 0;
			}
		}
	}

}

//checks if computer has 4 cards of the same value and returns an integer for checking points(same as for player)
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
			
				return FOUR + i + 2;
				
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
	
	// p is used for reading file, tmp to temporarily save the char of suits
	char p, tmp;

	// cards from file are saved there
	char cards[CARDS]; 
	
	// char value of face of the card corresponding suit is saved here
	char spades[SUITSUM], clubs[SUITSUM], diamonds[SUITSUM], hearts[SUITSUM];	
	
	// used to convert face char to int value
	int f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	
	int s=0, c=0, d=0, h=0;		// amount of a suit is saved here
	int i = 0, j, value;		// i,j used in for loops, value to add up the values of flush face values
	int count;					// addresses the suit which makes a flush
	
	while((p = fgetc(points)) != EOF){ 		//cards are saved to an char array
		cards[i] = p;
		i++;
	}
	
	fclose(points);					// file is closed

	for(i=0; i<CARDS; i++){			// face char values are run throught the for loop
		
		if(cards[i]== 'S'){			// fills the face values which correspond to s (spades)
			tmp = cards[i-1];		//temporarily saves the value (one before the character 'S')
			cards[i-1] = spades[s];	//replaces the value
			spades[s] = tmp;		//stores the value to array
			s++;					//adds the amount of spades
			
		}else if(cards[i]=='C'){	// fills the face values which correspond to c (clubs)
			tmp = cards[i-1];
			cards[i-1] = clubs[c];
			clubs[c] = tmp;
			c++;
			
		}else if(cards[i]=='D'){	// fills the face values which correspond to d (diamonds)
			tmp = cards[i-1];
			cards[i-1] = diamonds[d];
			diamonds[d] = tmp;
			d++;
		}else if(cards[i]=='H'){	// fills the face values which correspond to h (hearts)
			tmp = cards[i-1];
			cards[i-1] = hearts[h];
			hearts[h] = tmp;
			h++;
		}
			
	}


	for(i=0; i<SUITSUM; i++){		//char values are stored through this loop
	
		if(s>=5){					//checks which of the suits can combine a flush
			count = spades[i];		//and stores it count to check through switch - case loop
		}else if(c>=5){
			count = clubs[i];
		}else if(d>=5){
			count = diamonds[i];
		}else if(h>=5){
			count = hearts[i];
		}
		
		switch(count){				//fills the integer values of the suit which creates a flush
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
			case'A': f14=14; break;
		}
	}
	
	int rank[RANK] = {f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};	//fills the values to an array
			
	for(i=0; i<RANK+1; i++){		//loop to create an ascending order
		for(j=0; j<RANK+1; j++){	//loop to compare values to each other
			if(rank[i]>rank[j]){	//compares the values
				tmp=rank[i];		//temporarily saves the value
				rank[i]=rank[j];	//replaces the value
				rank[j]=tmp;		//stores the value in array
			}
		}
	}
	
	for(i=0; i<5; i++){				//adds the values up
		value += rank[i];			//and stores them to a single integer
	}
	
	
	if(s>=5){						//checks what values to return (spades lowest, hearts highest)
		return FLUSH + SPADE + value;	//return value corresponding suit and face values
	}
	else if(c>=5){
		return FLUSH + CLUBS + value;
	}
	else if(d>=5){
		return FLUSH + DIAMONDS + value;
	}
	else if(h>=5){
		return FLUSH + HEARTS + value;
	}else{
		return 0;					//if theres no flush, 0 is returned
	}
	
}

//checks if computer has a Flush
int checkFlushComputer(){
	FILE *points;
	points = fopen("points2.txt", "r");
	
	char p, tmp; 	
	char cards[CARDS]; 		
	char spades[SUITSUM], clubs[SUITSUM], diamonds[SUITSUM], hearts[SUITSUM];
	
	int f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	int s=0, c=0, d=0, h=0;	
	int i = 0, j, value;		
	int count;					
	
	while((p = fgetc(points)) != EOF){ 		
		cards[i] = p;
		i++;
	}
	
	fclose(points);				

	for(i=0; i<CARDS; i++){		
		
		if(cards[i]== 'S'){			
			tmp = cards[i-1];		
			cards[i-1] = spades[s];	
			spades[s] = tmp;		
			s++;					
			
		}else if(cards[i]=='C'){
			tmp = cards[i-1];
			cards[i-1] = clubs[c];
			clubs[c] = tmp;
			c++;
			
		}else if(cards[i]=='D'){	
			tmp = cards[i-1];
			cards[i-1] = diamonds[d];
			diamonds[d] = tmp;
			d++;
		}else if(cards[i]=='H'){	
			tmp = cards[i-1];
			cards[i-1] = hearts[h];
			hearts[h] = tmp;
			h++;
		}
			
	}


	for(i=0; i<SUITSUM; i++){		
	
		if(s>=5){					
			count = spades[i];		
		}else if(c>=5){
			count = clubs[i];
		}else if(d>=5){
			count = diamonds[i];
		}else if(h>=5){
			count = hearts[i];
		}
		
		switch(count){				
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
			case'A': f14=14; break;
		}
	}
	
	int rank[RANK] = {f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};	
			
	for(i=0; i<RANK; i++){			
		for(j=0; j<RANK; j++){
			if(rank[j]<rank[i]){
				int tmp=rank[i];
				rank[i]=rank[j];
				rank[j]=tmp;
			}
		}
	}
	
	for(i=0; i<5; i++){				
		value += rank[i];			
	}
	
	
	if(s>=5){						
		return FLUSH + SPADE + value;	
	}
	else if(c>=5){
		return FLUSH + CLUBS + value;
	}
	else if(d>=5){
		return FLUSH + DIAMONDS + value;
	}
	else if(h>=5){
		return FLUSH + HEARTS + value;
	}else{
		return 0;					
	}
}

int checkStraightPlayer(){
	FILE *points;
	points = fopen("points1.txt", "r");
	char p;
	
	//used save the face values of the cards
	int f1=0, f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	
	//used in for loop to arrange the cards in descending order
	int i, j, tmp;
	
	//gets all the different values of cards
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
			case'A': f1=1; f14=14; break;	// A (Ace) as a 1 in straight is the only place the value is needed for comparison
		}
	}
	
	//saves the values in an array
	int rank[RANK+1] = {f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};
	
	fclose(points);
	
	for(i=0; i<RANK+1; i++){		//loop to create an ascending order
		for(j=0; j<RANK+1; j++){	//loop to compare values to each other
			if(rank[i]>rank[j]){	//compares the values
				tmp=rank[i];		//temporarily saves the value
				rank[i]=rank[j];	//replaces the value
				rank[j]=tmp;		//stores the value
			}
		}
	}

	//now that the values are in descending (7 cards) there are only 4 ways for them to be consecutive numbers (5 consecutive)
	if		(rank[0]-1 == rank[1] && rank[1]-1 == rank[2] && rank[2]-1 == rank[3] && rank[3]-1 == rank[4] && rank[4] != 0){
		return STRAIGHT + rank[0]; 	//returns value for comparing and the highest value in the straight
	}else if(rank[1]-1 == rank[2] && rank[2]-1 == rank[3] && rank[3]-1 == rank[4] && rank[4]-1 == rank[5] && rank[5] != 0){
		return STRAIGHT + rank[1];	//returns value for comparing and the highest value in the straight
	}else if(rank[2]-1 == rank[3] && rank[3]-1 == rank[4] && rank[4]-1 == rank[5] && rank[5]-1 == rank[6] && rank[6] != 0){
		return STRAIGHT + rank[2];	//returns value for comparing and the highest value in the straight
	}else if(rank[3]-1 == rank[4] && rank[4]-1 == rank[5] && rank[5]-1 == rank[6] && rank[6]-1 == rank[7] && rank[7] != 0){
		return STRAIGHT + rank[3];	//returns value for comparing and the highest value in the straight
	}else{
		return 0;	//and if there is no straight return value is 0
	}


}

//same as for the player in the earlier function
int checkStraightComputer(){
	FILE *points;
	points = fopen("points2.txt", "r");
	char p;
	
	int f1=0, f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	int i,j,tmp;
	
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
				tmp=rank[i];
				rank[i]=rank[j];
				rank[j]=tmp;
			}
		}
	}

	if		(rank[0]-1 == rank[1] && rank[1]-1 == rank[2] && rank[2]-1 == rank[3] && rank[3]-1 == rank[4] && rank[4] != 0){
		return STRAIGHT + rank[0];
	}else if(rank[1]-1 == rank[2] && rank[2]-1 == rank[3] && rank[3]-1 == rank[4] && rank[4]-1 == rank[5] && rank[5] != 0){
		return STRAIGHT + rank[1];
	}else if(rank[2]-1 == rank[3] && rank[3]-1 == rank[4] && rank[4]-1 == rank[5] && rank[5]-1 == rank[6] && rank[6] != 0){
		return STRAIGHT + rank[2];
	}else if(rank[3]-1 == rank[4] && rank[4]-1 == rank[5] && rank[5]-1 == rank[6] && rank[6]-1 == rank[7] && rank[7] != 0){
		return STRAIGHT + rank[3];
	}else{
		return 0;
	}

}

//checks pairs, threes and fullhouse for player
int checkPairAndThreePlayer(){
	FILE *points;
	points = fopen("points1.txt", "r");
	char p;
	//count save the amount of the same face values
	int count2=0, count3=0, count4=0, count5=0, count6=0, count7=0, count8=0, count9=0, count10=0, count11=0, count12=0, count13=0, count14=0;
	//and f (face) save the value of face of the cards
	int f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;

	int i, j, tmp;	//used in for loop to put pair values in descending order
	int firstPairValue, secondPairValue, thirdPairValue, highThreeValue; // used for return values
	int pair = 0; //used to check amount of pairs
	int three = 0;	// used to check amount of threes
	while((p=fgetc(points)) != EOF){
		switch(p){
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
	
	//save the face values to array
	int rank[RANK] = {f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};	
	
	// save the amount to array
	int count[RANK] = {count2,count3,count4,count5,count6,count7,count8,count9,count10,count11,count12,count13,count14}; 
	
	fclose(points);
	
	for(i=0; i<RANK; i++){	//loop for amount of values
		
		if(count[i]==2){	//checks if there are pairs

			pair++;		//saves the amount of pairs
			for(j=0; j<3; j++){		// loops the values of pairs in descending order (max 3)
				if(rank[i]>rank[j]){ //compares the values
					tmp = rank[i];	//stores temporary
					rank[i] = rank[j];	//switches
					rank[j] = tmp;		//stores in array
				}
			}
			
		}else if(count[i]==3){	
			three++;	// saves the amount of threes
			highThreeValue = rank[i];	// saves the higher value of threes (max 2)
		}
		
	}
	
	firstPairValue = rank[0];	//saves the highest value of pair to lowest
	secondPairValue = rank[1];
	
	if	(pair>=2 && three==0){	// if there are 2 or 3 pairs
		
		return 2*PAIR + firstPairValue + secondPairValue;	//2 times the PAIR values and the face values regarding pairs
	
	}else if(pair==1 && three == 0){	// here is a possibility for a flush to overlap (1 pair)
			
		return PAIR + firstPairValue;
		
	}else if(pair == 0 && three == 1){	// here is a possibility for a flush to overlap (1 three)
		
		return THREE + highThreeValue;
			
	}else if(pair >= 1 && three == 1){ 		//pair and three (fullhouse)
		
		return FULLHOUSE + highThreeValue + firstPairValue;
		
	}else if(three == 2){	//two times three (fullhouse) returns the higher value
		
		return FULLHOUSE + highThreeValue;
		
	}else{
		return 0;	//and if conditions aren't met value of function will be 0
	}
		
}

//same as for the player to check pairs and such
int checkPairAndThreeComputer(){
	
	FILE *points;
	points = fopen("points2.txt", "r");
	char p;
	
	int count2=0, count3=0, count4=0, count5=0, count6=0, count7=0, count8=0, count9=0, count10=0, count11=0, count12=0, count13=0, count14=0;
	int f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	int i, j, tmp;
	int firstPairValue, secondPairValue, thirdPairValue, highThreeValue;
	int pair = 0;
	int three = 0;
	while((p=fgetc(points)) != EOF){
		switch(p){			
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
			for(j=0; j<3; j++){
				if(rank[i]>rank[j]){
					tmp = rank[i];
					rank[i] = rank[j];
					rank[j] = tmp;
				}
			}
			
		}else if(count[i]==3){
			three++;
			highThreeValue = rank[i];
		}
		
	}
	
	firstPairValue = rank[0];
	secondPairValue = rank[1];
	
	if	(pair>=2 && three==0){
		
		return 2 * PAIR + firstPairValue + secondPairValue;
		
	}else if(pair==1 && three == 0){
			
		return PAIR + firstPairValue;
		
	}else if(pair == 0 && three == 1){
		
		return THREE + highThreeValue;
			
	}else if((pair >= 1 && three == 1) || (three == 2)){
		
		return FULLHOUSE + highThreeValue + firstPairValue;
		
	}else if(three == 2){
		return FULLHOUSE + highThreeValue;
	}else{
		return 0;
	}
	
}

//used to check the high card to some extent
int checkHighCardPlayer(){
	FILE *points;
	points = fopen("points1.txt", "r");
	char p;
	
		// fills face values
	int f2=0, f3=0, f4=0, f5=0, f6=0, f7=0, f8=0, f9=0, f10=0, f11=0, f12=0, f13=0, f14=0;
	
		// fills the amount of values
	int count2=0, count3=0, count4=0, count5=0, count6=0, count7=0, count8=0, count9=0, count10=0, count11=0, count12=0, count13=0, count14=0; 
	
		// i mainly used in for loops, j when need to get consecutive numbers and tmp when to temporarily save a card
	int i, j, tmp;
	
		// counts the amount of pairs, threes and fours
	int pair=0, three=0, four=0;
	
		// 5 highest cards are saved here
	int first, second, third, fourth, fifth;
	
		//used get a value if there are three pairs
	int amount[TABLE];
	
		//stores the face values and the amount of values
	while((p=fgetc(points)) != EOF){
		switch(p){
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
	
	//stores the amount values and face values in an array
	int count[RANK] = {count2,count3,count4,count5,count6,count7,count8,count9,count10,count11,count12,count13,count14};
	int rank[RANK] = {f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14};
	
	for(i=0; i<RANK; i++){	// if there exists a larger quantity of a single number, it's ignored
		if(count[i]>1){
			rank[i]=0;
		}
	}
	
	fclose(points);
	
	for(i=0; i<RANK; i++){	// numbers are arranged in an ascending order
		for(j=0; j<RANK; j++){
			if(rank[j]<rank[i]){
				tmp=rank[i];
				rank[i]=rank[j];
				rank[j]=tmp;
			}
		}
	}
	
	first = rank[0];	//five of the largest remaining numbers are stored
	second = rank[1];
	third = rank[2];
	fourth = rank[3];
	fifth = rank[4];
	
	for(i=0; i<RANK; i++){	//counting the amount of fours threes and pairs
		if(count[i]==4){
			four++;
		}else if(count[i]==3){
			three++;
		}else if(count[i]==2){
			amount[pair] = i+2;	//calculates the smallest value of pairs (if there's 3 pairs)
			pair++;
		}
	}
	
	if(four==1){	// if theres 4 of the same value, room only for 1 number
		return first;
	}else if(four==0 && three==1 && pair==0){	// if threes apprear only once, room for sum of 2 numbers
		return first + second;
		
	}else if(pair == 3){						//3 pair exeption, the smallest value of the pairs is returned
		return amount[0];
		
	}else if(four==0 && three==0 && pair==2){	//2 pairs, room for 1
		return first;
		
	}else if(four==0 && three==0 && pair==1){	// 1 pair room for sum of 3
		return first + second + third;
		
	}else if(four==0 && three==0 && pair==0){	//nothing but the highest cards return sum of five
		return first + second + third + fourth + fifth;
		
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
	int i, j, tmp;
	int pair=0, three=0, four=0;
	int first, second, third, fourth, fifth;
	int amount[TABLE];
	
	
	while((p=fgetc(points)) != EOF){
		switch(p){
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
	
	for(i=0; i<RANK; i++){
		if(count[i]>1){
			rank[i]=0;
		}
	}
	
	fclose(points);
	
	for(i=0; i<RANK; i++){
		for(j=0; j<RANK; j++){
			if(rank[j]<rank[i]){
				tmp=rank[i];
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
			amount[pair] = i+2;
			pair++;
		}
	}
	
	if(four==1){
		return first;
	}else if(four==0 && three==1 && pair==0){
		return first + second;
	}else if(pair == 3){
		return amount[0];
	}else if(four==0 && three==0 && pair==2){
		return first;
	}else if(four==0 && three==0 && pair==1){
		return first + second + third;
	}else if(four==0 && three==0 && pair==0){
		return first + second + third + fourth + fifth;
	}else{
		return 0;
	}
	
}

