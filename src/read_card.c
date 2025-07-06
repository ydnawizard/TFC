void read_card(txt deck_contents,deck * deck_pointer)
{
	if(deck_contents.line_count>0)
	{
		if(deck_pointer->card_count == 0)
		{
		/*deck_pointer->cards[deck_pointer->card_count].front=malloc(
				strlen(deck_contents.lines[0])*sizeof(char));
		/deck_pointer->cards[deck_pointer->card_count].back=malloc(
				strlen(deck_contents.lines[1])*sizeof(char));*/
		strcpy(deck_pointer->cards[deck_pointer->card_count].front,deck_contents.lines[0]);
		strcpy(deck_pointer->cards[deck_pointer->card_count].back,deck_contents.lines[1]);
		return;
		}
		else
		{
		/*deck_pointer->cards[deck_pointer->card_count].front=malloc(
				strlen(deck_contents.lines[deck_pointer->card_count*2])*sizeof(char));
		deck_pointer->cards[deck_pointer->card_count].back=malloc(
				strlen(deck_contents.lines[deck_pointer->card_count*2+1])*sizeof(char));*/
		strcpy(deck_pointer->cards[deck_pointer->card_count].front,deck_contents.lines[deck_pointer->card_count*2]);
		strcpy(deck_pointer->cards[deck_pointer->card_count].back,deck_contents.lines[deck_pointer->card_count*2+1]);
		return;
		}
	}
}
