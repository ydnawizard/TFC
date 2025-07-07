
void generate_title(char ** title,game_settings * game_settings_pointer)
{
	char* temp_title = "󰬀󰫲󰫹󰫲󰫰󰬁󰫲󰫱 󰫱󰫲󰫰󰫸󰬀 󰘸:";
	(*title) = realloc((*title),65*sizeof(char));
	for(int i=0;i<65;i++)
	{
		if(i == 64)
		{
			(*title)[i]='\0';
		}
		else
		{
			(*title)[i]=temp_title[i];
		}
	}
	if((*game_settings_pointer).deck_count > 0)
	{
		for(int i=0;i<(*game_settings_pointer).deck_count;i++)
		{
			(*title)=realloc((*title),(strlen((*title))+strlen((*game_settings_pointer).selected_decks[i].name))+2*sizeof(char));
			strcat((*title),(*game_settings_pointer).selected_decks[i].name);
			strcat((*title),",");
		}
	}
}

void deck_selection_menu(int * state,game_settings * game_settings_pointer)
{
	clear();
	int highlight = 0,
	    path_count = 0,
	    local_sub_tick,
	    local_file_tick,
	    key;
	char * title;
	title = malloc(sizeof(char));
	title[0] = '\0';
	char deck_path[128];
	char * deck_path_history[10];
	strcpy(deck_path,"decks/");
	deck_path_history[path_count]=malloc(strlen(deck_path)*sizeof(char));
	strcpy(deck_path_history[path_count],deck_path);
	directory_contents directory_contents_pointer;
	read_directory_contents(&directory_contents_pointer,deck_path);
	WINDOW * menu_win = newwin(menu_depth,menu_width,menu_y,menu_x);
	while( (*state) == 111)
	{
		local_sub_tick=0;
		wclear(menu_win);
		generate_title(&title,&(*game_settings_pointer));
		attron(COLOR_PAIR(2));
		mvprintw(title_y,title_x,"%s\n",title);
		attroff(COLOR_PAIR(2));
		refresh();
		while(local_sub_tick < directory_contents_pointer.sub_directory_count)
		{
			if(local_sub_tick == highlight)
			{
				wattron(menu_win,A_REVERSE);
			}
			mvwprintw(menu_win,local_sub_tick,1,"%s%s\n",directory_contents_pointer.sub_directory_names[local_sub_tick]," 󰉋");
			wattroff(menu_win,A_REVERSE);
			local_sub_tick += 1;
		}
		for(local_file_tick=0;local_file_tick<directory_contents_pointer.file_count;local_file_tick++)
		{
			if(local_file_tick == highlight - local_sub_tick)
			{
				wattron(menu_win,A_REVERSE);
			}
			mvwprintw(menu_win,local_sub_tick+local_file_tick,1,"%s%s\n",directory_contents_pointer.file_names[local_file_tick]," 󰘸");
			wattroff(menu_win,A_REVERSE);
		}
		wrefresh(menu_win);
		key = wgetch(menu_win);
		switch(key)
		{
			case 'k':
				if(highlight != 0)
				{
					highlight --;
					break;
				}
				else
				{
					break;
				}
			case 'j':
				if(highlight != (directory_contents_pointer.sub_directory_count + directory_contents_pointer.file_count)-1)
				{
					highlight ++;
					break;
				}
				else
				{
					break;
				}
			case 'l':
				if(highlight < directory_contents_pointer.sub_directory_count)
				{
					strcat(deck_path,directory_contents_pointer.sub_directory_names[highlight]);
					strcat(deck_path,"/");
					path_count += 1;
					deck_path_history[path_count]=malloc(64*sizeof(char));
					strcpy(deck_path_history[path_count],deck_path);
					read_directory_contents(&directory_contents_pointer,deck_path);
					highlight = 0;
					local_sub_tick = 0;
					break;
				}
				else if(game_settings_pointer->deck_count > 0)
				{
					for(int i=0;i<game_settings_pointer->deck_count;i++)
						if(strcmp(directory_contents_pointer.file_names[highlight-directory_contents_pointer.sub_directory_count],
									game_settings_pointer->selected_decks[i].name)==0)
						{
							for(int j=i;j<game_settings_pointer->deck_count;j++)
							{
								memcpy(&(*game_settings_pointer).selected_decks[j],&(*game_settings_pointer).selected_decks[j+1],sizeof(deck));
							}
							game_settings_pointer->deck_count-=1;
							break;
						}
						else if(i == game_settings_pointer->deck_count - 1)
						{
							deck temp_deck;
							char temp_path[128];
							strcpy(temp_path,deck_path);
							strcat(temp_path,directory_contents_pointer.file_names[highlight-directory_contents_pointer.sub_directory_count]);
							read_deck_file(&(*game_settings_pointer).selected_decks[game_settings_pointer->deck_count],temp_path);
							game_settings_pointer->deck_count+=1;
							break;
						}
					break;
				}
				else
				{
					deck temp_deck;
					char temp_path[128];
					strcpy(temp_path,deck_path);
					strcat(temp_path,directory_contents_pointer.file_names[highlight-directory_contents_pointer.sub_directory_count]);
					read_deck_file(&(*game_settings_pointer).selected_decks[game_settings_pointer->deck_count],temp_path);
					game_settings_pointer->deck_count+=1;
					break;
				}
			case 'h':
				if(path_count > 0)
				{
					memset(deck_path_history[path_count],'\0',strlen(deck_path_history[path_count]));
					path_count -= 1;
					memset(deck_path,'\0',strlen(deck_path));
					strcpy(deck_path,deck_path_history[path_count]);
					printf("%s\n",deck_path_history[0]);
					read_directory_contents(&directory_contents_pointer,deck_path);
					highlight=0;
					break;
				}
				else
				{
					(*state) = 11;
					return;
				}
			default:
				break;
		}
	}

}
