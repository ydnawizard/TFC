#include <stdlib.h>
#include <stdio.h>
#include <curses.h>


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

	//Creat output window
	WINDOW * menuwin = newwin(20, 35, 11, 10);
	box(menuwin,0,0);
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
				break;
			case KEY_DOWN:
				highlight++;
				break;
			default:
				break;
		}
		if(choice==10){
			break;
		}
	}
	//Draw window and Print Menu
	box(menuwin, 0,0);
	wrefresh(menuwin);



	//Closes ncurses screen
	endwin();
	return 0;
}







/*unsigned char title[56] ={0x20, 0x20, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5F, 0x5F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x0A, 0x20, 0x2F, 0x5F, 0x20, 0x20, 0x5F, 0x5F, 0x2F, 0x5F, 0x5F, 0x20, 0x20, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x20, 0x5F, 5F 5F 20 20 28 5F 29 5F 5F 5F 20 20 5F 5F 5F 5F 20 5F 2F 20 2F 20 20 20 20 20 20 20 20 0A 20 20 2F 20 2F 20 2F 20 5F 20 5C 2F 20 5F 5F 5F 2F 20 5F 5F 20 60 5F 5F 20 5C 2F 20 2F 20 5F 5F 20 5C 2F 20 5F 5F 20 60 2F 20 2F 20 20 20 20 20 20 20 20 20 0A 20 2F 20 2F 20 2F 20 20 5F 5F 2F 20 2F 20 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 20 2F 5F 2F 20 2F 20 2F 20 20 20 20 20 20 20 20 20 20 0A 2F 5F 2F 20 20 5C 5F 5F 5F 2F 5F 2F 20 20 2F 5F 2F 5F 2F 5F 2F 5F 2F 5F 2F 5F 2F 5F 2F 20 2F 5F 2F 5C 5F 5F 2C 5F 2F 5F 2F 20 20 20 20 20 20 20 20 20 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 5F 5F 5F 5F 2F 20 2F 5F 5F 5F 20 5F 5F 5F 5F 5F 5F 2F 20 2F 5F 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 2F 5F 20 20 2F 20 2F 20 5F 5F 20 60 2F 20 5F 5F 5F 2F 20 5F 5F 20 5C 20 20 20 20 20 20 20 20 20 20 20 20 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 5F 5F 2F 20 2F 20 2F 20 2F 5F 2F 20 28 5F 5F 20 20 29 20 2F 20 2F 20 2F 20 20 20 20 20 20 20 20 20 20 20 20 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 2F 5F 2F 20 20 20 2F 5F 2F 5C 5F 5F 2C 5F 2F 5F 5F 5F 5F 2F 5F 2F 20 2F 5F 2F 20 20 20 20 20 20 20 20 20 5F 5F 20 20 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 5F 5F 5F 5F 2F 5F 5F 5F 20 5F 5F 5F 5F 5F 5F 5F 5F 5F 5F 2F 20 2F 5F 5F 5F 5F 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 2F 20 20 20 2F 20 5F 5F 20 60 2F 20 5F 5F 5F 2F 20 5F 5F 20 20 2F 20 5F 5F 5F 2F 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 2F 20 2F 5F 5F 5F 2F 20 2F 5F 2F 20 2F 20 2F 20 20 2F 20 2F 5F 2F 20 28 5F 5F 20 20 29 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 5C 5F 5F 5F 5F 2F 5C 5F 5F 2C 5F 2F 5F 2F 20 20 20 5C 5F 5F 2C 5F 2F 5F 5F 5F 5F 2F 20 20 0A 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20*/
