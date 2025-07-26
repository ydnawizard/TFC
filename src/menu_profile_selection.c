


void profile_menu(int * state)
{
	clear();
	attron(COLOR_PAIR(2));
	WINDOW * menu_win = newwin(menu_depth,menu_width,menu_y,menu_x);
	mvprintw(title_y,title_x,"%s\n","󰫽󰫿󰫼󰫳󰫶󰫹󰫲󰬀 ");
	refresh();
	attroff(COLOR_PAIR(2));
	attron(COLOR_PAIR(3));
	mvprintw(title_y,25,"%s\n","");
	attroff(COLOR_PAIR(3));
	wrefresh(menu_win);
	int highlight = 0,
	    key;
	while( (*state) == 13)
	{
	}
}

