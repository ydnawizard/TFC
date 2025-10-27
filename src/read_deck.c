
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

void get_substring(char * target,char ** dest,int start,int stop)
{
	memset((*dest), '\0',32);
	int output_index = 0;
	for(int i = start; i <= stop;i++)
	{
		(*dest)[output_index] = target[i];
		output_index+=1;
	}
}

void resolve_location(char * deck_file_path,deck * deck_pointer)
{
	char * substring = malloc(32 * sizeof(char));
	for(int i = 0; i < strlen(deck_file_path)-9;i++)
	{
		get_substring(deck_file_path,&substring,i,i+9);
		if(strcmp(substring,"TFC/decks/")== 0)
		{
			get_substring(deck_file_path,&substring,i+10,
					strlen(deck_file_path));
			strcpy(deck_pointer->location,substring);
		}
	}
}


void read_deck_file(deck * deck_pointer,char * deck_file_path_suffix)
{
	char deck_file_path[128];
	getcwd(deck_file_path,sizeof(deck_file_path));
	strcat(deck_file_path,"/");
	strcat(deck_file_path,deck_file_path_suffix);
	printf("%s\n",deck_file_path);
	txt file_contents;
	read_text_file_contents(&file_contents,deck_file_path);
	char* name_pointer;
	name_pointer = malloc(64*sizeof(char));
	read_deck_name(&name_pointer,deck_file_path);
	strcpy(deck_pointer->name,name_pointer);
	resolve_location(deck_file_path,deck_pointer);
	deck_pointer->card_count = 0;
	read_deck_cards(&(*deck_pointer),deck_file_path);
}

