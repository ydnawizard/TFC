
typedef struct game_settings
{
	int card_orientation;
	bool repeat;
	bool shuffle;
	int deck_count;
	deck selected_decks[1];
}game_settings;
