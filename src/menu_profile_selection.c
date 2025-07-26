


void profile_menu(int * state,game_settings * game_settings_pointer)
{
	//ncurses housekeeping
	clear();
	attron(COLOR_PAIR(2));
	WINDOW * menu_win = newwin(menu_depth,menu_width,menu_y,menu_x);
	mvprintw(title_y,title_x,"%s\n","󰫽󰫿󰫼󰫳󰫶󰫹󰫲󰬀 ");
	refresh();
	//Title
	attroff(COLOR_PAIR(2));
	wrefresh(menu_win);
	//INITS
	//Ints
	int highlight = 0,
	    key;
	directory_contents profiles;
	char directory_path[64];
	strcpy(directory_path,"profiles/");
	read_directory_contents(&profiles,directory_path);
	while( (*state) == 13)
	{
		for(int i = 0; i < profiles.file_count; i++)
		{
			if(i == highlight)
			{
				wattron(menu_win,A_REVERSE);
			}
			mvwprintw(menu_win,i,1,"%s\n",profiles.file_names[i]);
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
				if(highlight != profiles.file_count-1)
				{
					highlight+=1;
					break;
				}
				else
				{
					break;
				}
			case 'l':
				read_profile_file(&(*game_settings_pointer),profiles.file_names[highlight]);
				(*state) = 114;
				return;
			case 'h':
				(*state) = 1;
				return;
		}
	}
}

