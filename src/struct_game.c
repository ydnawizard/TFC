
typedef struct game
{
	int state;
	struct card current_card;
	card* drawn;
	int drawn_count;
	bool repeat;
}game;
