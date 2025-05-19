
char * settings_menu_options[5] = {"Decks 󰉋", "Repeat:", "Shuffle:", "Orientation:","█ 󰫱󰫲󰫮󰫹 █"};

void settings_menu(int * state,game_settings * game_settings_pointer)
{
	int highlight = 0,
	    key;
	clear();
	attron(COLOR_PAIR(2));
	mvprintw(title_y,title_x,"%s\n","󰬀ettings ");
	attroff(COLOR_PAIR(2));
	refresh();
	WINDOW * menu_win = newwin(menu_depth,menu_width,menu_y,menu_x);
	while( (*state) == 11)
	{
		for(int i=0;i<5;i++)
		{
			if(i == highlight)
			{
				if(highlight == 4)
				{
					wattron(menu_win,A_REVERSE);
					wattron(menu_win,COLOR_PAIR(1));
				}
				else
				{
					wattron(menu_win,A_REVERSE);
				}
			}
			mvwprintw(menu_win,i,1,settings_menu_options[i]);
			wattroff(menu_win,A_REVERSE);
			wattroff(menu_win,COLOR_PAIR(1));
		}
		wrefresh(menu_win);
		key = wgetch(menu_win);
		switch(key)
		{
			case KEY_UP:
			case 'k':
				if(highlight != 0)
				{
					highlight-=1;
					break;
				}
				else
				{
					break;
				}
			case KEY_DOWN:
			case 'j':
				if(highlight != 4)
				{
					highlight+=1;
					break;
				}
				else
				{
					break;
				}
			case KEY_RIGHT:
			case 'l':
				switch(highlight)
				{
					case 0:
						(*state) = 111;
						return;
					case 1:
						(*state) = 112;
						return;
					case 2:
						(*state) = 113;
						return;
					case 3:
						(*state) = 114;
						return;
					case 5:
						(*state) = 115;
						return;
				}
			case KEY_LEFT:
			case 'h':
				(*state) = 1;
				return;
		}
	}
}

