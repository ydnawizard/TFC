void generate_hud(char*** hud,game_settings * game_settings_pointer)
{
	if(game_settings_pointer->repeat == false)
	{
		(*hud)[0]="󰫿󰫲󰫽󰫲󰫮󰬁 ";
	}
	else
	{
		(*hud)[0]="󰫿󰫲󰫽󰫲󰫮󰬁 ";
	}
	if(game_settings_pointer->shuffle == false)
	{
		(*hud)[1]="󰬀󰫵󰬂󰫳󰫳󰫹󰫲 ";
	}
	else
	{
		(*hud)[1]="󰬀󰫵󰬂󰫳󰫳󰫹󰫲 ";
	}
	if(game_settings_pointer->card_orientation == 1)
	{
		(*hud)[2]="󰫼󰫿󰫶󰫲󰫻󰬁󰫮󰬁󰫶󰫼󰫻 ";
	}
	else
	{
		(*hud)[2]="󰫼󰫿󰫶󰫲󰫻󰬁󰫮󰬁󰫶󰫼󰫻 ";
	}
	(*hud)[3]="󰫱󰫲󰫰󰫸󰬀:";
	for(int i=4;i < 4+game_settings_pointer->deck_count; i++)
	{
		strcpy((*hud)[i],game_settings_pointer->selected_decks[i-4].name);
	}
}

/*void generate_master_deck(deck* master_deck,game_settings * game_settings_pointer)
{
	for(int i=0;i<game_settings_pointer->deck_count;i++)
	{
		//printf("%d\n",game_settings_pointer->deck_count);
		for(int j=0;j<game_settings_pointer->selected_decks[i].card_count;j++)
		{
			//printf("%d\n",game_settings_pointer->selected_decks[i].card_count);
			strcpy(master_deck->cards[j].front,game_settings_pointer->selected_decks->cards[j].front);
			printf("%d\n",j);
			master_deck->card_count += 1;
		}
	}
}*/


void play_game(int * state,game_settings * game_settings_pointer)
{
	clear();
	refresh();
	int highlight = 0,
	    key;
	srand(time(NULL));
	WINDOW* profile_win = newwin(3,75,2,2);
	WINDOW* question_win = newwin(10,75,5,5);
	WINDOW* answer_win = newwin(4,75,15,5);
	WINDOW* hud_win = newwin(14,20,5,80);
	wborder(question_win,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
	wborder(answer_win,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
	wborder(hud_win,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
	wrefresh(question_win);
	wrefresh(answer_win);
	wrefresh(hud_win);
	char** hud = malloc((4+game_settings_pointer->deck_count)*sizeof(char*));
	for(int i=0;i<(4+game_settings_pointer->deck_count);i++)
	{
		hud[i]=malloc(32*sizeof(char));
		for(int j=0;j<32;j++)
		{
			hud[i][j]='\0';
		}
	}
	generate_hud(&hud,&(*game_settings_pointer));
	while((*state) == 114)
	{
		for(int i=0;i<(4+game_settings_pointer->deck_count);i++)
		{
			wattron(hud_win,COLOR_PAIR(1));
			mvwprintw(hud_win,i+1,1,hud[i]);
			wattroff(hud_win,COLOR_PAIR(1));
			wrefresh(hud_win);
		}
		wattron(profile_win,COLOR_PAIR(2));
		mvwprintw(profile_win,2,3,"󰫽󰫿󰫼󰫳󰫶󰫹󰫲:");
		wattroff(profile_win,COLOR_PAIR(2));
		wrefresh(profile_win);
		key = wgetch(question_win);
		switch(key)
		{
		}
	}
}



