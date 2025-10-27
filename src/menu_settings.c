

void generate_settings_menu_options(char*** settings_menu_options,game_settings * game_settings_pointer)
{
	(*settings_menu_options)[0]="󰬺. Decks ";
	(*settings_menu_options)[4]="   󰫽󰫹󰫮󰬆";
	if(game_settings_pointer->repeat == false)
	{
		(*settings_menu_options)[1]="󰬻. Repeat ";
	}
	else
	{
		(*settings_menu_options)[1]="󰬻. Repeat ";
	}
	if(game_settings_pointer->shuffle == false)
	{
		(*settings_menu_options)[2]="󰬼. Shuffle ";
	}
	else
	{
		(*settings_menu_options)[2]="󰬼. Shuffle ";
	}
	if(game_settings_pointer->card_orientation == 1)
	{
		(*settings_menu_options)[3]="󰬽. Orientation ";
	}
	else
	{
		(*settings_menu_options)[3]="󰬽. Orientation ";
	}
}

void profile_name_handler(int * key,int * name_index,char ** name,game_settings * game_settings_pointer)
{
	if((*key) == '\n')
	{
		char * file_name = malloc(strlen((*name)) + 9 * sizeof(char));
		strcpy(file_name,"profiles/");
		strcat(file_name,(*name));
		FILE * profile = fopen(file_name,"w");
		fputs((*name),profile);
		fputs("\n",profile);
		fprintf(profile,"%d\n",game_settings_pointer->card_orientation);
		if(game_settings_pointer->repeat == true)
		{
			fprintf(profile,"%s\n","true");
		}
		else
		{
			fprintf(profile,"%s\n","false");
		}
		if(game_settings_pointer->shuffle == true)
		{
			fprintf(profile,"%s\n","true");
		}
		else
		{
			fprintf(profile,"%s\n","false");
		}
		fprintf(profile,"%d\n",game_settings_pointer->deck_count);
		for(int i = 0; i < game_settings_pointer->deck_count; i++)
		{
			fprintf(profile,"%s\n",game_settings_pointer->selected_decks[i].location);
		}
		fclose(profile);
		memset((*name),' ',72);
		(*name_index) = 0;
		return;
	}
	else
	{
		(*name)[(*name_index)] = (*key);
		(*name)[(*name_index)+1] = '\0';
		(*name_index) += 1;
	}
}

void settings_menu(int * state,game_settings * game_settings_pointer)
{
	int highlight = 0,
	    key,
	    profile_key = 1,
	    profile_name_index = 0;
	clear();
	attron(COLOR_PAIR(2));
	mvprintw(title_y,title_x,"%s\n","󰬀󰫲󰬁󰬁󰫶󰫻󰫴󰬀 ");
	attroff(COLOR_PAIR(2));
	attron(COLOR_PAIR(4));
	mvprintw(title_y,19,"%s\n","");
	attroff(COLOR_PAIR(4));
	refresh();
	WINDOW * menu_win = newwin(menu_depth,menu_width,menu_y,menu_x);
	WINDOW * profile_win = newwin(3,20,13,5);
	WINDOW * profile_title_win = newwin(3,20,10,5);
	char** settings_menu_options=malloc(5*sizeof(char*));
	char * profile_name = malloc(32 * sizeof(char));
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
			case 'w':
				clear();
				refresh();
				wborder(profile_win,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
				profile_key = 1;
				while(profile_key>0)
				{
					wrefresh(profile_win);	
					mvwprintw(profile_title_win,1,2,"%s","󰫽󰫿󰫼󰫳󰫶󰫹󰫲 󰬁󰫶󰬁󰫹󰫲");
					wrefresh(profile_title_win);
					profile_key = wgetch(profile_win);
					profile_name_handler(&profile_key,&profile_name_index,&profile_name,game_settings_pointer);
					mvwprintw(profile_win,1,2,"%s",profile_name);
					wrefresh(profile_win);
					if(profile_key == '\n')
					{
						profile_key = 0;
						wclear(profile_win);
						wclear(profile_title_win);
						wrefresh(profile_win);
						wrefresh(profile_title_win);	
						attron(COLOR_PAIR(2));
						mvprintw(title_y,title_x,"%s\n","󰬀󰫲󰬁󰬁󰫶󰫻󰫴󰬀 ");
						attroff(COLOR_PAIR(2));
						attron(COLOR_PAIR(4));
						mvprintw(title_y,19,"%s\n","");
						attroff(COLOR_PAIR(4));
						refresh();
					}
				}
		}
	}
}

