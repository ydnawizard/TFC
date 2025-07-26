
typedef struct game_settings
{
	char profile_name[64];
	int card_orientation;
	bool repeat;
	bool shuffle;
	int deck_count;
	deck selected_decks[10];
}game_settings;
