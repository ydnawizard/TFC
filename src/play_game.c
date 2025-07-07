void generate_hud(char*** hud,game_settings * game_settings_pointer)
{
	if(game_settings_pointer->repeat == false)
	{
		(*hud)[1]="󰫿󰫲󰫽󰫲󰫮󰬁 ";
	}
	else
	{
		(*hud)[1]="󰫿󰫲󰫽󰫲󰫮󰬁 ";
	}
	if(game_settings_pointer->shuffle == false)
	{
		(*hud)[2]="󰬀󰫵󰬂󰫳󰫳󰫹󰫲 ";
	}
	else
	{
		(*hud)[2]="󰬀󰫵󰬂󰫳󰫳󰫹󰫲 ";
	}
	if(game_settings_pointer->card_orientation == 1)
	{
		(*hud)[3]="󰫼󰫿󰫶󰫲󰫻󰬁󰫮󰬁󰫶󰫼󰫻 ";
	}
	else
	{
		(*hud)[3]="󰫼󰫿󰫶󰫲󰫻󰬁󰫮󰬁󰫶󰫼󰫻 ";
	}
	(*hud)[0]="    󰬀󰫲󰬁󰬁󰫶󰫻󰫴󰬀 ";
	(*hud)[4]="󰫱󰫲󰫰󰫸󰬀:";
	for(int i=5;i < 5+game_settings_pointer->deck_count; i++)
	{
		strcpy((*hud)[i],game_settings_pointer->selected_decks[i-5].name);
	}
}

void generate_master_deck(deck * master, game_settings * game_settings_pointer)
{
	master->card_count = 0;
	for(int i=0;i < game_settings_pointer->deck_count; i++)
	{
		for(int j=0;j < game_settings_pointer->selected_decks[i].card_count; j++)
		{
			strcpy(master->cards[master->card_count].front,game_settings_pointer->selected_decks[i].cards[j].front);
			strcpy(master->cards[master->card_count].back,game_settings_pointer->selected_decks[i].cards[j].back);
			master->card_count += 1;
		}
	}
}

void shuffle_and_repeat_handler(int * card_index,int ** drawn_cards,deck * master,game_settings * game_settings_pointer)
{
	srand(time(NULL));
	if(game_settings_pointer->shuffle == true && game_settings_pointer->repeat == false)
	{
		int sum = 0;
		for(int i = 0;i < master->card_count - 1;i++)
		{
			sum += (*drawn_cards)[i];
		}
		if(sum != master->card_count)
		{
			(*card_index) = rand() % master->card_count;
			(*drawn_cards)[(*card_index)] = (*card_index);
		}
		else
		{
			exit(0);
		}
	}
	if(game_settings_pointer->shuffle == true && game_settings_pointer->repeat == true)
	{
			(*card_index) = rand() % master->card_count;
			(*drawn_cards)[(*card_index)] = (*card_index);
	}
}

void answer_handler(int * key,char ** answer,int * answer_index,int * card_index,deck * master,bool * next_card)
{
	if((*key) == '\n')
	{
		if(strcmp((*answer),master->cards[(*card_index)].back) == 0)
		{
			(*next_card) = true;
			memset((*answer),' ',72);
			(*answer_index) = 0;
			return;
		}
		else
		{
			memset((*answer),' ',72);
			(*answer_index) = 0;
			return;
		}
	}
	else if((*key) == 127)
	{
		if((*answer_index) > 0)
		{
			(*answer)[(*answer_index)]='\0';
			(*answer_index) -= 1;
			(*answer)[(*answer_index)]=' ';
		}
	}
	else
	{
		(*answer)[(*answer_index)] = (*key);
		(*answer)[(*answer_index)+1] = '\0';
		(*answer_index) += 1;
	}
}


void play_game(int * state,game_settings * game_settings_pointer)
{
	//Ncurses housekeeping and new wins
	clear();
	refresh();
	WINDOW* profile_win = newwin(3,75,2,2);
	WINDOW* question_win = newwin(10,75,5,5);
	WINDOW* answer_win = newwin(3,75,15,5);
	WINDOW* hud_win = newwin(13,20,5,80);
	wborder(question_win,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
	wborder(answer_win,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
	wborder(hud_win,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
	wrefresh(question_win);
	wrefresh(answer_win);
	wrefresh(hud_win);
	wattron(profile_win,COLOR_PAIR(2));
	mvwprintw(profile_win,2,3,"󰫽󰫿󰫼󰫳󰫶󰫹󰫲:");
	wattroff(profile_win,COLOR_PAIR(2));
	wrefresh(profile_win);
	//Master deck gets cards from all selected decks
	deck master;
	generate_master_deck(&master,&(*game_settings_pointer));
	//Inits
	bool next_card = false;
	int highlight = 0,
	    card_index = 0,
	    answer_index = 0,
	    key;
	//Card history in case repeat is not on
	int * drawn_cards;
	drawn_cards = malloc(master.card_count*sizeof(int));
	for(int i = 0;i < master.card_count;i++)
	{
		drawn_cards[i] = 0;
	}
	//Hud 
	char ** hud;
	hud = malloc((5+game_settings_pointer->deck_count)*sizeof(char*));
	for(int i=0;i<(5+game_settings_pointer->deck_count);i++)
	{
		hud[i]=malloc(32*sizeof(char));
		for(int j=0;j<32;j++)
		{
			hud[i][j]='\0';
		}
	}
	generate_hud(&hud,&(*game_settings_pointer));
	//Answer
	char* answer;
	answer = malloc(256*sizeof(char));
	memset(answer,'\0',256);
	//main loop
	shuffle_and_repeat_handler(&card_index,&drawn_cards,&master,&(*game_settings_pointer));
	while((*state) == 114)
	{
		for(int i=0;i<(5+game_settings_pointer->deck_count);i++)
		{
			if(i>0)
			{
				wattron(hud_win,COLOR_PAIR(3));
				mvwprintw(hud_win,i+1,1,"%s",hud[i]);
				wattroff(hud_win,COLOR_PAIR(3));
				wrefresh(hud_win);
			}
			else
			{
				wattron(hud_win,COLOR_PAIR(2));
				mvwprintw(hud_win,i+1,1,"%s",hud[i]);
				wattroff(hud_win,COLOR_PAIR(2));
				wrefresh(hud_win);
			}
		}
		mvwprintw(question_win,2,2,"%s",master.cards[card_index].front);
		wrefresh(question_win);
		key = wgetch(question_win);
		answer_handler(&key,&answer,&answer_index,&card_index,&master,&next_card);
		mvwprintw(answer_win,1,2,"%s",answer);
		wrefresh(answer_win);
		if(next_card == true)
		{
			shuffle_and_repeat_handler(&card_index,&drawn_cards,&master,&(*game_settings_pointer));
			next_card = false;
		}
	
	}

}



