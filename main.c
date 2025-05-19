#include "src/main.h"


int main()
{
	setlocale(LC_ALL,"en_US.UTF-8");
	initscr();
	noecho();
	cbreak();
	start_color();
	init_pair(1,COLOR_RED,COLOR_BLACK);
	init_pair(2,COLOR_CYAN,COLOR_BLACK);
	curs_set(0);
	keypad(stdscr,TRUE);
	game_settings game_settings_pointer;
	int state = 1;
	while(state > 0)
	{
		switch(state)
		{
			case 1:
				main_menu(&state);
			case 12:
				info_menu(&state);

		}
	}
	endwin();
}

