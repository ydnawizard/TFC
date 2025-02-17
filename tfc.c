#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <curses.h>


//Menu declarations to avoid implicits
int mainMenu();
int settingsMenu();
int rulesMenu();
int decksMenu();
int playGame();

struct rules{
	char deck[20];
	char* orientation;
	int timer;
};

struct rules gameRules;

//Puts names of all valid decks into an array
//Displays array in new menu/window
int decksMenu(){
	int i=0;
	DIR* decks;
	char** options=(char**)malloc(sizeof(char*));
	struct dirent *directory;
	decks=opendir("./decks/");
	if(decks){
		while((directory=readdir(decks))!=NULL){
			if(i<=1){
				i+=1;
			}else{
				options[i]=(char*)malloc(strlen(directory->d_name)*sizeof(char));
				strncpy(options[i],directory->d_name,strlen(directory->d_name));
				i+=1;
				options=(char**)realloc(options,(i+1)*sizeof(char*));
			}
		}
		closedir(decks);
	}
	//Creat output window
	WINDOW * decksWin = newwin(20, 35, 11, 10);
	//box(settingsWin,0,0);
	refresh();
	wrefresh(decksWin);
	keypad(decksWin, true);
	int choice;
	int highlight=2;
	while(1){
		for(int i=2;i<5;i++){
			if(i==highlight){
				wattron(decksWin,A_REVERSE);
			}
			mvwprintw(decksWin,i-1,1,"%s\n",options[i]);
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
				strcpy(options[highlight],strcat(options[highlight],"[x]"));
				strcpy(gameRules.deck,options[highlight]);
				//printf("%s\n",gameRules.deck);
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
int rulesMenu(){
}
int playGame(){
}

int settingsMenu(){
	//Creat output window
	WINDOW * settingsWin = newwin(20, 35, 11, 10);
	//box(settingsWin,0,0);
	refresh();
	wrefresh(settingsWin);

	keypad(settingsWin, true);
	char* options[3]={"Rules","Decks","Back"};
	int choice;
	int highlight=0;
	while(1){
		for(int i=0;i<3;i++){
			if(i==highlight){
				wattron(settingsWin,A_REVERSE);
			}
			mvwprintw(settingsWin,i+1,1,options[i]);
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

int mainMenu(){
	//Creat output window
	WINDOW * menuwin = newwin(20, 35, 11, 10);
	//box(menuwin,0,0);
	refresh();
	wrefresh(menuwin);

	keypad(menuwin, true);
	char* options[3]={"Play","Settings","Quit"};
	int choice;
	int highlight=0;
	while(1){
		for(int i=0;i<3;i++){
			if(i==highlight){
				wattron(menuwin,A_REVERSE);
			}
			mvwprintw(menuwin,i+1,1,options[i]);
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
