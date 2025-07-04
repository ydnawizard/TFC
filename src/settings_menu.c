

void generate_settings_menu_options(char*** settings_menu_options,game_settings * game_settings_pointer)
{
	(*settings_menu_options)[0]="Decks ";
	(*settings_menu_options)[4]="󰫽󰫹󰫮󰬆";
	if(game_settings_pointer->repeat == false)
	{
		(*settings_menu_options)[1]="Repeat ";
	}
	else
	{
		(*settings_menu_options)[1]="Repeat ";
	}
	if(game_settings_pointer->shuffle == false)
	{
		(*settings_menu_options)[2]="Shuffle ";
	}
	else
	{
		(*settings_menu_options)[2]="Shuffle ";
	}
	if(game_settings_pointer->card_orientation == 1)
	{
		(*settings_menu_options)[3]="Orientation ";
	}
	else
	{
		(*settings_menu_options)[3]="Orientation ";
	}
}

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
	char** settings_menu_options=malloc(5*sizeof(char*));
	for(int i=0;i<5;i++)
	{
		settings_menu_options[i]=malloc(32*sizeof(char));
		for(int j=0;j<32;j++)
		{
			settings_menu_options[i][j]='\0';
		}
	}
	while( (*state) == 11)
	{
		generate_settings_menu_options(&settings_menu_options,game_settings_pointer);
		for(int i=0;i<5;i++)
		{
			if(i == highlight)
			{
				if(highlight == 4)
				{
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
						if( (*game_settings_pointer).repeat == false)
						{
							(*game_settings_pointer).repeat = true;
						}
						else
						{
							(*game_settings_pointer).repeat = false;
						}
						break;
					case 2:
						if( (*game_settings_pointer).shuffle == false)
						{
							(*game_settings_pointer).shuffle = true;
						}
						else
						{
							(*game_settings_pointer).shuffle = false;
						}
						break;
					case 3:
						if( (*game_settings_pointer).card_orientation == 1)
						{
							(*game_settings_pointer).card_orientation = 0;
						}
						else
						{
							(*game_settings_pointer).card_orientation = 1;
						}
						break;
					case 4:
						(*state) = 114;
						return;
					default:
						break;
				}
				break;
			case KEY_LEFT:
			case 'h':
				(*state) = 1;
				return;
		}
	}
}

