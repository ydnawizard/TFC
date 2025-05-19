
char * main_menu_options[3] = {"Play","Info","Quit"};

void main_menu(int* state)
{
	int loop_state = 1,
	    highlight = 0,
	    key;

	clear();
	attron(COLOR_PAIR(2));
	mvprintw(title_y,title_x,"%s\n","󰬁erminal 󰫳lash 󰫰ards 󰘸");
	attroff(COLOR_PAIR(2));
	refresh();
	WINDOW * menu_win = newwin(menu_depth,menu_width,menu_y,menu_x);
	while( loop_state > 0 )
	{
		for(int i=0;i<3;i++)
		{
			if(i == highlight)
			{
				wattron(menu_win,A_REVERSE);
			}
			mvwprintw(menu_win,i,0,main_menu_options[i]);
			wattroff(menu_win,A_REVERSE);
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
				if(highlight != 2)
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
						(*state) = 11;
						return;
					case 1:
						(*state) = 12;
						return;
					case 2:
						(*state) = 0;
						return;
				}
			case 'q':
				(*state) = 0;
				return;
		}
	}
}
