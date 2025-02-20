//Terminal Flash Cards
//A Terminal based flash card game/utility utilizing the ncurses library
//Supports easy definition of new card decks via a text file format
//Written by Oscillator

//Librarys
#include <stdlib.h> //Standard Library
#include <stdio.h> //Standard input output
#include <string.h> //String utilities
#include <dirent.h> //Directory utilities
#include <unistd.h>
#include <time.h>
#include <curses.h> //Utilities for terminal based graphics

//###GLOBALS###\\\

//Functions
//Menu declarations to avoid implicits 
int mainMenu();
int settingsMenu();
int rulesMenu();
int decksMenu();
int playGame();
int postGame();
int readDeck();
int readDecks();

//Structs
//Define rules struct
//Stores menuState in which game is initialized
struct rules{
	char* deck;
	char* orientation;
	bool shuffle;
	bool repeat;
};
//Initialize rules struct called game rules
struct rules gameRules;

//Card struct that cards read from deck file are passed into
//Each card gets an id so card based player performance data can
//be utililized to provide a better learning experience
typedef struct{
	char* front;
	char* back;
	int id;
}card;

//Performance struct
typedef struct{
	int correct;
	int incorrect;
}results;

//Initialize an array of card structs
card *deck;

results performance;
//Menu state is a global int used to terminate 
//while loops that display each menu. Its
//value changes based on the menu displayed so that
//the while loop displaying the previous menu is temrinated
int menuState=1;

//Arrays for what is displayed in each menu
char* menuOptions[3]={"Play","Settings","Quit"};
char* settings[3]={"Rules","Decks","Back"};
char* rules[5]={"Orientation:Front","Shuffle:False","Repeat:False","Back"};

//Decks is an array of all decks in the deck directory
//Used for menu display and gameplay
char** decks;
int decksLength;
int deckLength;

//Opens directory and grab names of decks
//add deck names to a global array called decks
int readDecks(){
	int i=0;
	DIR* d;
	//Initialize dirent struct called directory
	struct dirent *directory;
	//Must realloc because readDecks is called frequently in deck menu
	//and decks is mutated each time
	decks=(char**)realloc(decks,sizeof(char*));
	d=opendir("./decks/");
	if(d){
		while((directory=readdir(d))!=NULL){
			if(strcmp(directory->d_name,".")!=0&&strcmp(directory->d_name,"..")!=0){
				//realloc each item in deck to erase "[x]" assigned in deck menu
				decks[i]=(char*)realloc(decks[i],strlen(directory->d_name)*sizeof(char));
				strcpy(decks[i],directory->d_name);
				i+=1;
				decks=(char**)realloc(decks,(i+1)*sizeof(char*));
			}
		}
		//Adds "back" to the end of decks list because
		//decks list is accessed in deck menu and a back nav option is needed
		decks[i]=(char*)malloc(4*sizeof(char));
		decks[i]="back";
		decks=(char**)realloc(decks,(i+1)*sizeof(char*));
		i+=1;
		closedir(d);
	}
	decksLength=i;
	return 0;
}

//Opens the slected deck text file specified in gameRules
//Passes each card to a global deck array of card structs;
int readDeck(){
	int i=0;
	int j=0;
	//Count lines relative to position in deck file
	int lineCount=1;
	//Count cards relative to position in deck array
	int cardCount=0;
	//Create complete deck path with filename from deck att.
	//in gameRules struct
	char deckPath[100]="./decks/";
	strcat(deckPath,gameRules.deck);
	//Alllocate memory for dynamic card front and card back strings;
	char* front=malloc(sizeof(char));
	char* back=malloc(sizeof(char));
	//Allocate memory for dynamic global deck of card structs array
	deck=(card*)malloc(sizeof(card));
	//Initialize file pointer
	FILE* deckFile=fopen(deckPath,"read");
	//Initialize char buffer for read characters
	char ch;
	while((ch=fgetc(deckFile))!=EOF){
		//If lineCount is odd, the front of card #cardCount is being read
		if(ch!='\n'&&lineCount%2!=0){
			front[i]=ch;
			i+=1;
			//realloc to make space for next char
			front=realloc(front,(i+1)*sizeof(char));
		//If lineCount is even, the back of card #cardCount is being read
		}else if(ch!='\n'&&lineCount%2==0){
			back[i]=ch;
			i+=1;
			//realloc to make space for next char
			back=realloc(back,(i+1)*sizeof(char));
		//If character is newline and lineCount is odd, put string front into 
		//deck[cardCount].front
		}else if(ch=='\n'&&lineCount%2!=0){
			//the method this function builds strings with requires manual addition
			//of a null terminator character to the end of the string
			front[i]='\0';
			//make space in deck for string front in the card struct
			deck[cardCount].front=malloc(strlen(front)*sizeof(char));
			//strcpy because using = would assign it a pointer value whos
			//contents are always changing
			strcpy(deck[cardCount].front,front);
			//reset i so next string assignment starts at 0
			i=0;
			//move to next line
			lineCount+=1;
			//realloc front so it has space for only one char
			//this effectively erases its previous contents
			front=realloc(front,sizeof(char));
		//If character is newline and lineCount is even, put string front into 
		//deck[cardCount].back
		}else if(ch=='\n'&&lineCount%2==0){
			//works the same way as the previous else if, just for card.back
			back[i]='\0';
			deck[cardCount].back=malloc(strlen(back)*sizeof(char));
			strcpy(deck[cardCount].back,back);
			back=realloc(back,2*sizeof(char));
			i=0;
			lineCount+=1;
			//assign an id number to the card
			deck[cardCount].id=cardCount;
			//now that card is fully filled out, move to next card
			cardCount+=1;
			//realloc deck to make space for next card
			deck=realloc(deck,(cardCount+1)*sizeof(card));
		}
	}
	deckLength=cardCount;
	//close/free file pointer
	fclose(deckFile);
}

//Displays a mutable menu of decks
//Selected deck receives a [x] in the menu display
int decksMenu(){
	curs_set(0);
	clear();
	mvprintw(10,10,"%s \n","Decks:");
	//Creat output window
	WINDOW * decksWin = newwin(20, 35, 11, 10);
	//box(settingsWin,0,0);
	refresh();
	wrefresh(decksWin);
	keypad(decksWin, true);
	int choice;
	int highlight=0;
	int selected=2;
	while(menuState==3){
		for(int i=0;i<decksLength;i++){
			if(i==highlight){
				wattron(decksWin,A_REVERSE);
			}
			mvwprintw(decksWin,i+1,1,"%s\n",decks[i]);
			wattroff(decksWin,A_REVERSE);
		}
		choice=wgetch(decksWin);
		switch(choice){
			case KEY_UP:
				if(highlight==0){
					break;
				}else{
					highlight--;
					break;
				}
			case KEY_DOWN:
				if(highlight==decksLength-1){
					break;
				}else{
					highlight++;
					break;
				}
			case KEY_RIGHT:
				if(highlight==decksLength-1){
					menuState=2;
					settingsMenu();
					break;
				}else{
					//Running read decks again returns a unmutated deck menu
					//Graphically this erases the previous deck selection and
					//places a [x] next to the new selection
					readDecks();
					gameRules.deck=realloc(gameRules.deck,strlen(decks[highlight])*sizeof(char));
					strcpy(gameRules.deck,decks[highlight]);
					strcat(decks[highlight],"[x]");
					break;
				}
			case KEY_LEFT:
				menuState=2;
				break;
			default:
				break;
		}
		if(choice==10){
			break;
		}
	}
	return 0;
}

//Displays a mutable menu of game rules
//Changing the rules changes the menuState of rules struct gameRules
int rulesMenu(){
	curs_set(0);
	clear();
	mvprintw(10,10,"%s \n","Rules:");
	//Creat output window
	WINDOW * rulesWin = newwin(20, 35, 11, 10);
	refresh();
	wrefresh(rulesWin);
	keypad(rulesWin, true);
	int choice;
	int highlight=0;
	while(menuState==6){
		for(int i=0;i<4;i++){
			if(i==highlight){
				wattron(rulesWin,A_REVERSE);
			}
			mvwprintw(rulesWin,i+1,1,rules[i]);
			wattroff(rulesWin,A_REVERSE);
		}
		choice=wgetch(rulesWin);
		switch(choice){
			case KEY_UP:
				if(highlight==0){
					break;
				}else{
					highlight--;
					break;
				}
			case KEY_DOWN:
				if(highlight==3){
					break;
				}else{
					highlight++;
					break;
				}
			//Right arrow key mutates rules menu in a incrementing manner
			case KEY_RIGHT:
				if(highlight==0){
					if(strcmp(gameRules.orientation,"front")==0){
						gameRules.orientation="back";
						rules[0]="Orientation:Back ";
					}else{
						gameRules.orientation="front";
						rules[0]="Orientation:Front";
				}
					break;
				}else if(highlight==1){
					if(gameRules.shuffle==false){
						gameRules.shuffle=true;
						rules[1]="Shuffle:True ";
					}else{
						gameRules.shuffle=false;
						rules[1]="Shuffle:False";
					}
					break;
				}else if(highlight==2){
					if(gameRules.repeat==false){
						gameRules.repeat=true;
						rules[2]="Repeat:True ";
					}else{
						gameRules.repeat=false;
						rules[2]="Repeat:False";
					}
					break;
				}else if(highlight==3){
					menuState=2;
					settingsMenu();
				break;
				}
			//Left arrow key mutates rules menu in a decrementing manner
			case KEY_LEFT:
				if(highlight==0){
					if(strcmp(gameRules.orientation,"front")==0){
						gameRules.orientation="back";
						rules[0]="Orientation:Back ";
					}else{
						gameRules.orientation="front";
						rules[0]="Orientation:Front";
				}
					break;
				}else if(highlight==1){
					if(gameRules.shuffle==false){
						gameRules.shuffle=true;
						rules[1]="Shuffle:True ";
					}else{
						gameRules.shuffle=false;
						rules[1]="Shuffle:False";
					}
					break;
				}else if(highlight==2){
					if(gameRules.repeat==false){
						gameRules.repeat=true;
						rules[2]="Repeat:True ";
					}else{
						gameRules.repeat=false;
						rules[2]="Repeat:False";
					}
					break;
				}else if(highlight==3){
					menuState=2;
					settingsMenu();
				break;
				}
			default:
				break;
		}
		if(choice==10){
			break;
		}
	}
}

//Displays settings menu
//Selected options  open submenus
int settingsMenu(){
	curs_set(0);
	clear();
	mvprintw(10,10,"%s \n","Settings:");
	//Creat output window
	WINDOW * settingsWin = newwin(20, 35, 11, 10);
	//box(settingsWin,0,0);
	refresh();
	wrefresh(settingsWin);
	keypad(settingsWin, true);
	int choice;
	int highlight=0;
	while(menuState==2){
		for(int i=0;i<3;i++){
			if(i==highlight){
				wattron(settingsWin,A_REVERSE);
			}
			mvwprintw(settingsWin,i+1,1,settings[i]);
			wattroff(settingsWin,A_REVERSE);
		}
		choice=wgetch(settingsWin);
		switch(choice){
			case KEY_UP:
				if(highlight==0){
					break;
				}else{
					highlight--;
					break;
				}
			case KEY_DOWN:
				if(highlight==2){
					break;
				}else{
					highlight++;
					break;
				}
			case KEY_RIGHT:
				if(highlight==0){
					menuState=6;
					rulesMenu();
				}else if(highlight==1){
					menuState=3;
					decksMenu();
				}else{
					menuState=1;
					mainMenu();
				}
			default:
				break;
		}
		if(choice==10){
			break;
		}
	}
}

//Displays Main Menu
//Selected options open submenus
int mainMenu(){
	curs_set(0);
	clear();
	mvprintw(10,10,"%s %s","Terminal Flash Cards","\n");
	//Creat output window
	WINDOW * menuWin = newwin(20, 35, 11, 10);
	//box(menuWin,0,0);
	refresh();
	wrefresh(menuWin);
	keypad(menuWin, true);
	int choice;
	int highlight=0;
	while(menuState==1){
		for(int i=0;i<3;i++){
			if(i==highlight){
				wattron(menuWin,A_REVERSE);
			}
			mvwprintw(menuWin,i+1,1,menuOptions[i]);
			wattroff(menuWin,A_REVERSE);
		}
		choice=wgetch(menuWin);
		switch(choice){
			case KEY_UP:
				if(highlight==0){
					break;
				}else{
					highlight--;
					break;
				}
			case KEY_DOWN:
				if(highlight==2){
					break;
				}else{
					highlight++;
					break;
				}
			case KEY_RIGHT:
				if(highlight==0){
					menuState=4;
					playGame();
				}else if(highlight==1){
					menuState=2;
					settingsMenu();
				}else{
					exit(0);
				}
				break;
			default:
				break;
		}
	}
}

int playGame(){
	curs_set(0);
	int i=0;
	int j=0;
	int* dealt=malloc(deckLength+1*sizeof(char));
	dealt[0]=0;
	performance.correct=0;
	performance.incorrect=0;
	readDeck();
	clear();
	mvprintw(10,10,"%s \n","Terminal Flash Cards");
	WINDOW * gameWin=newwin(4,60,11,10);
	WINDOW * answerWin=newwin(3,40,16,9);
	//nodelay(stdscr,true);
	nodelay(gameWin,true);
	//nodelay(answerWin,true);
	wrefresh(answerWin);
	keypad(gameWin,true);
	refresh();
	wrefresh(gameWin);
	int answerChar;
	char* answer=malloc(2*sizeof(char));
	answer[1]='\0';
	answer[0]=' ';
	while(menuState==4){
		if(strcmp(gameRules.orientation,"front")==0){
			mvwprintw(gameWin,1,0,"%s \n",deck[i].front);
			mvwprintw(gameWin,1,40,"%s%s \n","Deck:",gameRules.deck);
			mvwprintw(gameWin,2,40,"%s%d \n","Card:",deck[i].id);
			wborder(answerWin,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
			mvwprintw(answerWin,1,1,"%s",answer);
			answer=realloc(answer,j+2*sizeof(char));
			wrefresh(gameWin);
			wrefresh(answerWin);
		}
		else if(strcmp(gameRules.orientation,"back")==0){
			mvwprintw(gameWin,1,0,"%s \n",deck[i].back);
			mvwprintw(gameWin,1,40,"%s%s \n","Deck:",gameRules.deck);
			mvwprintw(gameWin,2,40,"%s%d \n","Card:",deck[i].id);
			wborder(answerWin,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
			mvwprintw(answerWin,1,1,"%s",answer);
			answer=realloc(answer,j+2*sizeof(char));
			wrefresh(gameWin);
			wrefresh(answerWin);
		}
		answer[j]=mvwgetch(answerWin,1,1);
		answer[j+1]='\0';
		if(answer[j]=='\n'){
			answer[j]='\0';
			answer=realloc(answer,j*sizeof(char));
			if(strcmp(answer,deck[i].back)==0&&strcmp(gameRules.orientation,"front")==0){
				performance.correct+=1;
				answer=realloc(answer,2*sizeof(char));
				answer[0]=' ';
				answer[1]='\0';
				wclear(answerWin);
				j=0;
				if(gameRules.shuffle==true&&gameRules.repeat==true){
					i=rand()%(deckLength+1-0)+0;
				}if(gameRules.shuffle==false&&i==deckLength){
					exit(0);
				}else{
					i+=1;
				}
			}else if(strcmp(answer,deck[i].front)==0&&strcmp(gameRules.orientation,"back")==0){
				performance.correct+=1;
				answer=realloc(answer,2*sizeof(char));
				answer[0]=' ';
				answer[1]='\0';
				wclear(answerWin);
				j=0;
				if(gameRules.shuffle==true&&gameRules.repeat==true){
					i=rand()%(deckLength+1-0)+0;
				}else if(gameRules.shuffle==false&&gameRules.repeat==true){
					if(i==deckLength-1){
						i=0;
					}else{
						i+=1;
					}
				}else if(gameRules.shuffle==true&&gameRules.repeat==false){
					while(i==dealt[i]){
						i=rand()%(deckLength+1-0)+0;
					}
					dealt[i]=i;
					for(int k=0;k<=deckLength;k++){
						if(k!=dealt[k]){
							break;
						}else if(k==deckLength){
							menuState=5;
							postGame();
						}
					}
				}else if(gameRules.repeat==false&&i==deckLength-1){
					menuState=5;
					postGame();
				}else{
					i+=1;
				}
			}else{
				performance.incorrect+=1;
				answer=realloc(answer,2*sizeof(char));
				answer[0]=' ';
				answer[1]='\0';
				wclear(answerWin);
				j=0;
			}
		}else if(answer[j]==127){
			if(j>1){
				answer[j]='\0';
				j-=1;
				answer[j]=' ';
				answer=realloc(answer,j*sizeof(char));
			}else{
				answer[0]=' ';
				answer[1]='\0';
				j=0;
				answer=realloc(answer,2*sizeof(char));
			}
		}else if(answer[j]==27){
			menuState=5;
			postGame();
		}else{
			j+=1;
		}
	}
}
	

int postGame(){
	clear();
	mvprintw(10,10,"%s \n","Performance");
	WINDOW * postWin=newwin(4,60,11,10);
	refresh();
	wrefresh(postWin);
	keypad(postWin,true);
	while(menuState==5){
		mvwprintw(postWin,1,0,"%s %d \n","Correct:",performance.correct);
		mvwprintw(postWin,2,0,"%s %d \n","Incorrect:",performance.incorrect);
		wrefresh(postWin);
	}
}



int main(){
	//Read decks directory and pass into global array
	readDecks();

	//Define default game rules
	gameRules.orientation="front";
	gameRules.shuffle=false;
	gameRules.repeat=false;

	//Initialize ncurses screen
	initscr();
	noecho();
	cbreak();

	//Get Screen Size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	//Print Menu Title

	mainMenu();
	//Draw window and Print Menu



	//Closes ncurses screen
	endwin();
	return 0;
}







/*unsigned char title[56] ={0x20, 0x20, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5F, 0x5F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x0A, 0x20, 0x2F, 0x5F, 0x20, 0x20, 0x5F, 0x5F, 0x2F, 0x5F, 0x5F, 0x20, 0x20, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x20, 0x5F, 5F 5F 20 20 28 5F 29 5F 5F 5F 20 20 5F 5F 5F 5F 20 5F 2F 20 2F 20 20 20 20 20 20 20 20 0A 20 20 2F 20 2F 20 2F 20 5F 20 5C 2F 20 5F 5F 5F 2F 20 5F 5F 20 60 5F 5F 20 5C 2F 20 2F 20 5F 5F 20 5C 2F 20 5F 5F 20 60 2F 20 2F 20 20 20 20 20 20 20 20 20 0A 20 2F 20 2F 20 2F 20 20 5F 5F 2F 20 2F 20 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 5F 2F 20 2F 20 2F 20 20 20 20 20 20 20 20 20 20 0A 2F 5F 2F 20 20 5C 5F 5F 5F 2F 5F 2F 20 20 2F 5F 2F 5F 2F 5F 2F 5F 2F 5F 2F 5F 2F 5F 2F 20 2F 5F 2F 5C 5F 5F 2C 5F 2F 5F 2F 20 20 20 20 20 20 20 20 20 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 5F 5F 5F 5F 2F 20 2F 5F 5F 5F 20 5F 5F 5F 5F 5F 5F 2F 20 2F 5F 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 2F 5F 20 20 2F 20 2F 20 5F 5F 20 60 2F 20 5F 5F 5F 2F 20 5F 5F 20 5C 20 20 20 20 20 20 20 20 20 20 20 20 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 5F 5F 2F 20 2F 20 2F 20 2F 5F 2F 20 28 5F 5F 20 20 29 20 2F 20 2F 20 2F 20 20 20 20 20 20 20 20 20 20 20 20 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 2F 5F 2F 20 20 20 2F 5F 2F 5C 5F 5F 2C 5F 2F 5F 5F 5F 5F 2F 5F 2F 20 2F 5F 2F 20 20 20 20 20 20 20 20 20 5F 5F 20 20 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 5F 5F 5F 5F 2F 5F 5F 5F 20 5F 5F 5F 5F 5F 5F 5F 5F 5F 5F 2F 20 2F 5F 5F 5F 5F 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 2F 20 20 20 2F 20 5F 5F 20 60 2F 20 5F 5F 5F 2F 20 5F 5F 20 20 2F 20 5F 5F 5F 2F 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 2F 5F 5F 5F 2F 20 2F 5F 2F 20 2F 20 2F 20 20 2F 20 2F 5F 2F 20 28 5F 5F 20 20 29 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 5C 5F 5F 5F 5F 2F 5C 5F 5F 2C 5F 2F 5F 2F 20 20 20 5C 5F 5F 2C 5F 2F 5F 5F 5F 5F 2F 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20*/
