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

void generate_master_deck(deck * master, game_settings * game_settings_pointer)
{
	master->card_count = 0;
	for(int i=0;i < game_settings_pointer->deck_count; i++)
	{
		int card_count = game_settings_pointer->selected_decks[i].card_count;
		for(int j=0;j < card_count; j++)
		{
			//master->cards[master->card_count].front = malloc(strlen(game_settings_pointer->selected_decks[i].cards[j].front)*sizeof(char));
			strcpy((*master).cards[master->card_count].front,game_settings_pointer->selected_decks[i].cards[j].front);
			//master->cards[master->card_count].back = malloc(strlen(game_settings_pointer->selected_decks[i].cards[j].back)*sizeof(char));
			strcpy((*master).cards[master->card_count].back,game_settings_pointer->selected_decks[i].cards[j].back);
			master->card_count += 1;
		}
	}
}

int grab_total_card_count(game_settings * game_settings_pointer)
{
	int card_count = 0;
	for(int i=0;i < game_settings_pointer->deck_count; i++)
	{
		card_count += game_settings_pointer->selected_decks[i].card_count;
	}
	return card_count;
}

void play_game(int * state,game_settings * game_settings_pointer)
{
	clear();
	refresh();
	int highlight = 0,
	    card_index = 0,
	    deck_index = 0,
	    card_count = grab_total_card_count(&(*game_settings_pointer)),
	    key;
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
	deck master;
	generate_master_deck(&master,&(*game_settings_pointer));
	for(int i=0;i<(4+game_settings_pointer->deck_count);i++)
	{
		hud[i]=malloc(32*sizeof(char));
		for(int j=0;j<32;j++)
		{
			hud[i][j]='\0';
		}
	}
	generate_hud(&hud,&(*game_settings_pointer));
	//For some reason the state is lost after generate master is called, so redefine it here
	(*state) = 114;
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
		if(game_settings_pointer->shuffle == true)
		{
			deck_index = rand() % game_settings_pointer->deck_count + 1;
			card_index = rand() % card_count + 1;
			printf("%d\n",card_index);
			exit(0);
		}
		if(game_settings_pointer->repeat == false)
		{
		}
		mvwprintw(question_win,2,2,"%s",master.cards[0].back);
		wrefresh(question_win);
		key = wgetch(question_win);
		switch(key)
		{
		}
	}
}



