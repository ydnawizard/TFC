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
#include "card_struct.c"
#include "deck_struct.c"
#include "game_settings_struct.c"
#include "game_struct.c"

//Read
#include "read_file.c"
#include "read_directory.c"

//Menus
#include "main_menu.c"
#include "info_menu.c"
#include "settings_menu.c"
