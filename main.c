#include "src/main.h"

//Define Constants
int title_x = 10,
    title_y = 10,
    menu_x = 10,
    menu_y = 11,
    menu_width = 35,
    menu_length = 20;

int main()
{
	setlocale(LC_ALL,"en_US.UTF-8");
	initscr();
	noecho();
	cbreak();
	start_color();
	curs_set(0);
	keypad(stdscr,TRUE);
	game_settings game_settings_pointer;
	int state = 1;
	while(state > 0)
	{
		switch(state)
		{
			case 1:
				main_menu();
		}
	}
	endwin();
}

