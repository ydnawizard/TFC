
void read_deck_name(char ** name_pointer,char * deck_file_path)
{
	char tmp_title[128];
	int j=0;
	for(int i=strlen(deck_file_path)-1;i>0;i--)
	{
		if(deck_file_path[i] != '/')
		{
			tmp_title[j]=deck_file_path[i];
			j+=1;
		}
		else
		{
			tmp_title[j]='\0';
			int k=0;
			while(j>0)
			{
				(*name_pointer)[k]=tmp_title[j-1];
				k+=1;
				j-=1;
			}
			(*name_pointer)[strlen(tmp_title)]='\0';
			return;
		}
	}
}

void read_deck_cards(deck * deck_pointer,char * deck_file_path)
{
	txt deck_contents;
	read_text_file_contents(&deck_contents,deck_file_path);
	while(deck_pointer->card_count < deck_contents.line_count/2)
	{
		read_card(deck_contents,&(*deck_pointer));
		deck_pointer->card_count += 1;
	}
}

void read_deck_file(deck * deck_pointer,char * deck_file_path_suffix)
{
	char deck_file_path[128];
	getcwd(deck_file_path,sizeof(deck_file_path));
	strcat(deck_file_path,"/");
	strcat(deck_file_path,deck_file_path_suffix);
	txt file_contents;
	read_text_file_contents(&file_contents,deck_file_path);
	char* name_pointer;
	name_pointer = malloc(64*sizeof(char));
	read_deck_name(&name_pointer,deck_file_path);
	strcpy(deck_pointer->name,name_pointer);
	deck_pointer->card_count = 0;
	read_deck_cards(&(*deck_pointer),deck_file_path);
}

