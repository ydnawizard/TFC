
void grab_deck_title(char ** title_pointer,char * deck_file_path)
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
				(*title_pointer)[k]=tmp_title[j-1];
				k+=1;
				j-=1;
			}
			(*title_pointer)[strlen(tmp_title)]='\0';
			return;
		}
	}
}

void read_deck_file(deck* deck_pointer,char* deck_file_path_suffix)
{
	char deck_file_path[128];
	getcwd(deck_file_path,sizeof(deck_file_path));
	strcat(deck_file_path,"/");
	strcat(deck_file_path,deck_file_path_suffix);
	//printf("%s\n",deck_file_path);
	txt file_contents;
	read_text_file_contents(&file_contents,deck_file_path);
	char* title_pointer;
	title_pointer = malloc(64*sizeof(char));
	grab_deck_title(&title_pointer,deck_file_path);
	printf("%s\n",title_pointer);
	exit(0);
	deck_pointer->name = malloc(strlen(title_pointer)*sizeof(char));
	strcpy((*deck_pointer).name,title_pointer);
}

