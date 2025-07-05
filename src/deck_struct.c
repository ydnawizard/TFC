
typedef struct deck
{
	int card_count;
	float average_score;
	float average_time;
	char name[128];
	card cards[1];
}deck;
