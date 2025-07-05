
char * main_menu_options[3] = {"Play","Info","Quit"};

void main_menu(int* state)
{
	int highlight = 0,
	    key;
	clear();
	attron(COLOR_PAIR(2));
	mvprintw(title_y,title_x,"%s\n","󰫳󰫹󰫮󰬀󰫵 󰫰󰫮󰫿󰫱󰬀 ");
	attroff(COLOR_PAIR(2));
	attron(COLOR_PAIR(3));
	mvprintw(title_y,22,"%s\n","");
	attroff(COLOR_PAIR(3));
	refresh();
	WINDOW * menu_win = newwin(menu_depth,menu_width,menu_y,menu_x);
	while( (*state) == 1 )
	{
		for(int i=0;i<3;i++)
		{
			if(i == highlight)
			{
				wattron(menu_win,A_REVERSE);
			}
			mvwprintw(menu_win,i,1,main_menu_options[i]);
			wattroff(menu_win,A_REVERSE);
		}
		wrefresh(menu_win);
		key = wgetch(menu_win);
		switch(key)
		{
			case 'k':
			case KEY_UP:
				if(highlight != 0)
				{
					highlight-=1;
					break;
				}
				else
				{
					break;
				}
			case 'j':
			case KEY_DOWN:
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
