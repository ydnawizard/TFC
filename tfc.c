//Terminal Flash Cards
//A Terminal based flash card game/utility utilizing the ncurses library
//Supports easy definition of new card decks via a text file format
//Written by Oscillator

//Librarys
#include <stdlib.h> //Standard Library
#include <stdio.h> //Standard input output
#include <string.h> //String utilities
#include <dirent.h> //Directory utilities
#include <curses.h> //Utilities for terminal based graphics


//Menu declarations to avoid implicits 
int mainMenu();
int settingsMenu();
int rulesMenu();
int decksMenu();
int playGame();
int readDeck();
int readDecks();

//Define rules struct
//Stores state in which game is initialized
struct rules{
	char* deck;
	char* orientation;
	int timer;
	bool shuffle;
	bool repeat;
};

//Initialize rules struct called game rules
struct rules gameRules;

//Globals
//Decks is an array of all decks in the deck directory
char** decks;
int decksLength;

//deckFront is an array of the front of each card in the selected deck (specified in gameRules);
char** deckFront;
//deckBack is an array of the back of each card in the selected deck (specified in gameRules);
char** deckBack;

//Arrays for what is displayed in each menu
char* menuOptions[3]={"Play","Settings","Quit"};
char* settings[3]={"Rules","Decks","Back"};
char* rules[5]={"Orientation:Front","Timer:None","Shuffle:False","Repeat:False","Back"};

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
		//decks list is acces in deck menu and a back nav option is needed
		decks[i]=(char*)malloc(4*sizeof(char));
		decks[i]="back";
		decks=(char**)realloc(decks,(i+1)*sizeof(char*));
		i+=1;
		closedir(d);
	}
	decksLength=i;
	return 0;
}

//Opens the slected deck specified in gameRules
//Passes each card to a global deckFront and deckBack arrays;
//int readDeck(){



//Displays a mutable menu of decks
//Selected deck receives a [x] in the menu display
int decksMenu(){
	//Creat output window
	WINDOW * decksWin = newwin(20, 35, 11, 10);
	//box(settingsWin,0,0);
	refresh();
	wrefresh(decksWin);
	keypad(decksWin, true);
	int choice;
	int highlight=2;
	int selected=2;
	while(1){
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
				highlight--;
				break;
			case KEY_DOWN:
				highlight++;
				break;
			case KEY_RIGHT:
				if(highlight==decksLength-1){
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
				settingsMenu();
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
//Changing the rules changes the state of rules struct gameRules
int rulesMenu(){
	//Creat output window
	WINDOW * rulesWin = newwin(20, 35, 11, 10);
	refresh();
	wrefresh(rulesWin);
	keypad(rulesWin, true);
	int choice;
	int highlight=0;
	while(1){
		for(int i=0;i<5;i++){
			if(i==highlight){
				wattron(rulesWin,A_REVERSE);
			}
			mvwprintw(rulesWin,i+1,1,rules[i]);
			wattroff(rulesWin,A_REVERSE);
		}
		choice=wgetch(rulesWin);
		switch(choice){
			case KEY_UP:
				highlight--;
				break;
			case KEY_DOWN:
				highlight++;
				break;
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
					gameRules.timer+=10;
					if(gameRules.timer>60){
						rules[1]="Timer:None";
						gameRules.timer=0;
						break;
					}else{
						//Grabs timer value from game rules and converts to string
						//Appends timer value to end of "Timer:" string and
						//replaces the string in rules[3] with new timer string
						char timer[3];
						sprintf(timer,"%d",gameRules.timer);
						char timerRule[7]="Timer:";
						strcat(timerRule,timer);
						strcat(timerRule,"  ");
						rules[1]=timerRule;
						break;
					}
				}else if(highlight==2){
					if(gameRules.shuffle==false){
						gameRules.shuffle=true;
						rules[2]="Shuffle:True ";
					}else{
						gameRules.shuffle=false;
						rules[2]="Shuffle:False";
					}
					break;
				}else if(highlight==3){
					if(gameRules.repeat==false){
						gameRules.repeat=true;
						rules[3]="Repeat:True ";
					}else{
						gameRules.repeat=false;
						rules[3]="Repeat:False";
					}
					break;
				}else if(highlight==4){
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
					gameRules.timer-=10;
					if(gameRules.timer==0){
						rules[1]="Timer:None";
						gameRules.timer=0;
						break;
					}else if(gameRules.timer<0){
						gameRules.timer=60;
						rules[1]="Timer:60  ";
						break;
					}
					else{
						//Works the same way as right arrow key function
						//but the gameRule.timer decrementing at beginning of 
						//last else if makes it behave different
						char timer[3];
						sprintf(timer,"%d",gameRules.timer);
						char timerRule[7]="Timer:";
						strcat(timerRule,timer);
						strcat(timerRule,"  ");
						rules[1]=timerRule;
						break;
					}
				}else if(highlight==2){
					if(gameRules.shuffle==false){
						gameRules.shuffle=true;
						rules[2]="Shuffle:True ";
					}else{
						gameRules.shuffle=false;
						rules[2]="Shuffle:False";
					}
					break;
				}else if(highlight==3){
					if(gameRules.repeat==false){
						gameRules.repeat=true;
						rules[3]="Repeat:True ";
					}else{
						gameRules.repeat=false;
						rules[3]="Repeat:False";
					}
					break;
				}else if(highlight==4){
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
int playGame(){
}

//Displays settings menu
//Selected options  open submenus
int settingsMenu(){
	//Creat output window
	WINDOW * settingsWin = newwin(20, 35, 11, 10);
	//box(settingsWin,0,0);
	refresh();
	wrefresh(settingsWin);

	keypad(settingsWin, true);
	int choice;
	int highlight=0;
	while(1){
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
				highlight--;
				break;
			case KEY_DOWN:
				highlight++;
				break;
			case KEY_RIGHT:
				if(highlight==0){
					rulesMenu();
				}else if(highlight==1){
					decksMenu();
				}else{
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
	//Creat output window
	WINDOW * menuwin = newwin(20, 35, 11, 10);
	//box(menuwin,0,0);
	refresh();
	wrefresh(menuwin);
	keypad(menuwin, true);
	int choice;
	int highlight=0;
	while(1){
		for(int i=0;i<3;i++){
			if(i==highlight){
				wattron(menuwin,A_REVERSE);
			}
			mvwprintw(menuwin,i+1,1,menuOptions[i]);
			wattroff(menuwin,A_REVERSE);
		}
		choice=wgetch(menuwin);
		switch(choice){
			case KEY_UP:
				highlight--;
				if(highlight<=0){
					highlight=0;
				}
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight>=3){
					highlight=2;
				}
				break;
			case KEY_RIGHT:
				if(highlight==0){
					playGame();
				}else if(highlight==1){
					settingsMenu();
				}else{
					exit(0);
				}
				break;
			default:
				break;
		}
		if(choice==1){
			settingsMenu();
		}
	}
}


int main(){
	//Read decks directory and pass into global array
	readDecks();

	//Define default game rules
	gameRules.orientation="front";
	gameRules.timer=0;
	gameRules.shuffle=false;
	gameRules.repeat=false;

	//Initialize ncurses screen
	initscr();
	noecho();
	cbreak();

	//Get Screen Size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	//Initialize Colors
	start_color();
	init_pair(1,COLOR_BLUE,COLOR_BLACK);
	init_pair(2,COLOR_RED,COLOR_BLACK);

	//Print Menu Title
	attron(COLOR_PAIR(1));
	mvprintw(10,10,"%s %s","Terminal Flash Cards","\n");
	attroff(COLOR_PAIR(1));

	mainMenu();
	//Draw window and Print Menu



	//Closes ncurses screen
	endwin();
	return 0;
}







/*unsigned char title[56] ={0x20, 0x20, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5F, 0x5F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x0A, 0x20, 0x2F, 0x5F, 0x20, 0x20, 0x5F, 0x5F, 0x2F, 0x5F, 0x5F, 0x20, 0x20, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x20, 0x5F, 5F 5F 20 20 28 5F 29 5F 5F 5F 20 20 5F 5F 5F 5F 20 5F 2F 20 2F 20 20 20 20 20 20 20 20 0A 20 20 2F 20 2F 20 2F 20 5F 20 5C 2F 20 5F 5F 5F 2F 20 5F 5F 20 60 5F 5F 20 5C 2F 20 2F 20 5F 5F 20 5C 2F 20 5F 5F 20 60 2F 20 2F 20 20 20 20 20 20 20 20 20 0A 20 2F 20 2F 20 2F 20 20 5F 5F 2F 20 2F 20 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 5F 2F 20 2F 20 2F 20 20 20 20 20 20 20 20 20 20 0A 2F 5F 2F 20 20 5C 5F 5F 5F 2F 5F 2F 20 20 2F 5F 2F 5F 2F 5F 2F 5F 2F 5F 2F 5F 2F 5F 2F 20 2F 5F 2F 5C 5F 5F 2C 5F 2F 5F 2F 20 20 20 20 20 20 20 20 20 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 5F 5F 5F 5F 2F 20 2F 5F 5F 5F 20 5F 5F 5F 5F 5F 5F 2F 20 2F 5F 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 2F 5F 20 20 2F 20 2F 20 5F 5F 20 60 2F 20 5F 5F 5F 2F 20 5F 5F 20 5C 20 20 20 20 20 20 20 20 20 20 20 20 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 5F 5F 2F 20 2F 20 2F 20 2F 5F 2F 20 28 5F 5F 20 20 29 20 2F 20 2F 20 2F 20 20 20 20 20 20 20 20 20 20 20 20 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 2F 5F 2F 20 20 20 2F 5F 2F 5C 5F 5F 2C 5F 2F 5F 5F 5F 5F 2F 5F 2F 20 2F 5F 2F 20 20 20 20 20 20 20 20 20 5F 5F 20 20 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 5F 5F 5F 5F 2F 5F 5F 5F 20 5F 5F 5F 5F 5F 5F 5F 5F 5F 5F 2F 20 2F 5F 5F 5F 5F 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 2F 20 20 20 2F 20 5F 5F 20 60 2F 20 5F 5F 5F 2F 20 5F 5F 20 20 2F 20 5F 5F 5F 2F 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 2F 5F 5F 5F 2F 20 2F 5F 2F 20 2F 20 2F 20 20 2F 20 2F 5F 2F 20 28 5F 5F 20 20 29 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 5C 5F 5F 5F 5F 2F 5C 5F 5F 2C 5F 2F 5F 2F 20 20 20 5C 5F 5F 2C 5F 2F 5F 5F 5F 5F 2F 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20*/
