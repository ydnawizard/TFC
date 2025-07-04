#include "src/main.h"


int main()
{
	setlocale(LC_ALL,"en_US.UTF-8");
	initscr();
	noecho();
	cbreak();
	start_color();
	init_pair(1,COLOR_RED,COLOR_BLACK);
	init_pair(2,COLOR_BLUE,COLOR_BLACK);
	curs_set(0);
	keypad(stdscr,TRUE);
	game_settings game_settings_pointer;
	game_settings_pointer.card_orientation = 1;
	game_settings_pointer.repeat = false;
	game_settings_pointer.shuffle = false;
	game_settings_pointer.deck_count = 0;
	int state = 1;
	//Menu loop in this manner prevents infinite nesting
	//Its just safer and more manageable
	while(state > 0)
	{
		switch(state)
		{
			case 1:
				main_menu(&state);
			case 11:
				settings_menu(&state,&game_settings_pointer);
			case 12:
				info_menu(&state);
			case 111:
				deck_selection_menu(&state,&game_settings_pointer);
		}

	}
	endwin();
}

