void read_card(txt deck_contents,deck * deck_pointer)
{
	if(deck_contents.line_count>0)
	{
		if(deck_pointer->card_count == 0)
		{
		strcpy(deck_pointer->cards[deck_pointer->card_count].front,deck_contents.lines[0]);
		printf("%s\n",(*deck_pointer).cards[deck_pointer->card_count].front);
		strcpy(deck_pointer->cards[deck_pointer->card_count].back,deck_contents.lines[1]);
		return;
		}
		else
		{
		strcpy(deck_pointer->cards[deck_pointer->card_count].front,deck_contents.lines[deck_pointer->card_count*2]);
		printf("%s\n",&deck_pointer->cards[deck_pointer->card_count*2].front);
		strcpy(deck_pointer->cards[deck_pointer->card_count].back,deck_contents.lines[deck_pointer->card_count*2+1]);
		return;
		}
	}
}
