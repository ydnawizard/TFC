//Define Constants
int title_x = 10,
    title_y = 10,
    menu_x = 10,
    menu_y = 11,
    menu_width = 35,
    menu_depth = 20;

//Standard Library
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>

//Ncurses
#include <ncurses.h>

//Structs
#include "struct_card.c"
#include "struct_deck.c"
#include "struct_game_settings.c"

//Read
#include "read_file.c"
#include "read_directory.c"
#include "read_card.c"
#include "read_deck.c"
#include "read_profile.c"

//Menus
#include "menu_main.c"
#include "menu_info.c"
#include "menu_settings.c"
#include "menu_deck_selection.c"
#include "menu_profile_selection.c"

//Game
#include "game_play.c"
