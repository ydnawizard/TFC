
void read_profile_name(char ** name_pointer,char * profile_file_path)
{
	char tmp_title[64];
	int j=0;
	for(int i=strlen(profile_file_path)-1;i>0;i--)
	{
		if(profile_file_path[i] != '/')
		{
			tmp_title[j]=profile_file_path[i];
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


void read_profile_file(game_settings * profile_pointer,char * profile_file_path_suffix)
{
	char profile_file_path[128];
	getcwd(deck_file_path,sizeof(profile_file_path));
	strcat(deck_file_path,"/");
	strcat(deck_file_path,profile_file_path_suffix);
	printf("%s\n",profile_file_path);
	exit(0);
}
