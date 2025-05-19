void info_menu(int* state)
{
	int highlight = 0,
	    key;
	clear();
	attron(COLOR_PAIR(2));
	attroff(COLOR_PAIR(2));
	refresh();
	WINDOW * menu_win = newwin(menu_depth+10,menu_width,menu_y,menu_x);
	while( (*state) == 12)
	{
		mvwprintw(menu_win,0,1,"%s\n","Terminal Flashcards is an extremely minimal and lightweight flash card utility written in c. Besides basic functionality, it boasts some minor minor enhancements that you will find greatly improve your experience. First, there are basic vim key-binds for navigation. The program can load multiple deck files for use in the session. Deck file selections and other settings can be saved as a profile by hitting CTRL+s+{profile_name} where profile name is a single key. Saving to a profile name that is already written to will overwrite it. Profiles can then be loaded from anywhere in the menu using CTRL+l+{profile_name} Deck files are defined by making the first line the front of the card, the second line the back of the card, and any more cards follow suit. There is a deck file in the deck folder included as an example. All Deck files should go in the ~/.tfc/decks folder.");
		wrefresh(menu_win);
		key = wgetch(menu_win);
		switch(key)
		{
			case KEY_LEFT:
			case 'h':
			case 'q':
			case 27:
				(*state) = 1;
				return;
		}
	}
}

