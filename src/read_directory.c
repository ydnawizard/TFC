typedef struct directory_contents
{
	int file_count;
	int sub_directory_count;
	char** file_names;
	char** sub_directory_names;
}directory_contents;

void read_directory_contents(
		directory_contents* directory_contents_pointer,
		char* directory_path)
{
	DIR* directory_raw_pointer
		=opendir(directory_path);
	struct dirent* 
		directory_clean_pointer;
	int file_count=0,
	    sub_directory_count=0;
	while((directory_clean_pointer = readdir(directory_raw_pointer))
			!= NULL)
	{
		if(strcmp(directory_clean_pointer->d_name,".") == 0
				|| strcmp(directory_clean_pointer->d_name,"..") == 0)
		{
			continue;
		}
		//if file
		else if(directory_clean_pointer->d_type == DT_REG)
		{
			if(file_count == 0)
			{
				directory_contents_pointer->file_names
					=malloc(sizeof(char*));
				directory_contents_pointer->file_names
					[file_count]
					=malloc(strlen(directory_clean_pointer->d_name)
							*sizeof(char));
				for(int i=0;i<strlen(directory_clean_pointer->d_name);i++)
				{
					directory_contents_pointer->file_names
						[file_count][i]
						=directory_clean_pointer->d_name
							[i];
				}
				file_count+=1;
			}
			else
			{
				void* tmp
					=realloc(directory_contents_pointer->file_names,
							(file_count+1)*sizeof(char*));
				if(tmp != NULL)
				{
					directory_contents_pointer->file_names
						=tmp;
					directory_contents_pointer->file_names
						[file_count]
						=malloc(strlen(directory_clean_pointer->d_name)
								*sizeof(char));
					for(int i=0;i<strlen(directory_clean_pointer->d_name);i++)
					{
						directory_contents_pointer->file_names
							[file_count][i]
							=directory_clean_pointer->d_name
								[i];
					}
					file_count+=1;
				}
			}
		}
		//if directory
		else if(directory_clean_pointer->d_type == DT_DIR)
		{
			if(sub_directory_count == 0)
			{
				directory_contents_pointer->sub_directory_names
					=malloc(sizeof(char*));
				directory_contents_pointer->sub_directory_names
					[sub_directory_count]
					=malloc(strlen(directory_clean_pointer->d_name)
							*sizeof(char));
				strcpy(directory_contents_pointer->sub_directory_names
						[sub_directory_count],
						directory_clean_pointer->d_name);
				sub_directory_count+=1;
			}
			else
			{
				char** tmp
					=realloc(directory_contents_pointer->sub_directory_names,
							(sub_directory_count+1)*sizeof(char*));
				if(tmp != NULL)
				{
					directory_contents_pointer->sub_directory_names
						=tmp;
					directory_contents_pointer->sub_directory_names
						[sub_directory_count]
						=malloc(strlen(directory_clean_pointer->d_name)
								*sizeof(char));
					strcpy(directory_contents_pointer->sub_directory_names
							[sub_directory_count],
							directory_clean_pointer->d_name);
					sub_directory_count+=1;
				}
			}
		}
	}
	directory_contents_pointer->sub_directory_count = sub_directory_count;
	directory_contents_pointer->file_count = file_count;
	closedir(directory_raw_pointer);
	free(directory_clean_pointer);
}
