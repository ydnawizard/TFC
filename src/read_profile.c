void read_profile_file(game_settings * profile_pointer,char * profile_file_path_suffix)
{
	char profile_file_path[128];
	getcwd(profile_file_path,sizeof(profile_file_path));
	strcat(profile_file_path,"/profiles/");
	strcat(profile_file_path,profile_file_path_suffix);
	printf("%s\n",profile_file_path);
	txt file_contents;
	read_text_file_contents(&file_contents,profile_file_path);
	strcpy(profile_pointer->profile_name,file_contents.lines[0]);
	if(file_contents.lines[1] == 0)
	{
		profile_pointer->card_orientation = 0;
	}
	else
	{
		profile_pointer->card_orientation = 1;
	}
	if(strcmp(file_contents.lines[2],"true") == 0)
	{
		profile_pointer->repeat = true;
	}
	else
	{
		profile_pointer->repeat = false;
	}
	if(strcmp(file_contents.lines[3],"true") == 0)
	{
		profile_pointer->shuffle = true;
	}
	else
	{
		profile_pointer->shuffle = false;
	}
	profile_pointer->deck_count = atoi(file_contents.lines[4]);
	for(int i = 5; i < 5 + profile_pointer->deck_count; i++)
	{
		char deck_path[64];
		strcpy(deck_path,"decks/");
		strcat(deck_path,file_contents.lines[i]);
		read_deck_file(&(*profile_pointer).selected_decks[i-5],deck_path);
	}
}
