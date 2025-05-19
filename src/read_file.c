
//Define file contents structure for organized storage
typedef struct text_file_contents
{
	int character_count;
	int string_count;
	int line_count;
	char* characters;
	char** strings;
	char** lines;
}txt;

//Single-character handling
void read_character_to_text_file_contents_pointer(
		txt* text_file_contents_pointer,
		char character,
		int character_index
		)
{
	if(character_index == 0)
	{
		if(character != '\n' && character != ' ')
		{
			text_file_contents_pointer->characters
				=malloc(sizeof(char));
			text_file_contents_pointer->characters
				[character_index]
				=character;
			text_file_contents_pointer->character_count
				=1;
		}
	}
	else
	{
		if(character != '\n' && character != ' ')
		{
			void* tmp=realloc(text_file_contents_pointer->characters,
						(character_index+1)*sizeof(char));
			if(tmp != NULL)
			{
				text_file_contents_pointer->characters=tmp;
				text_file_contents_pointer->characters
					[character_index]
					=character;
				text_file_contents_pointer->character_count+=1;
			}
		}
		else
		{
			void* tmp=realloc(text_file_contents_pointer->characters,
						(character_index+1)*sizeof(char));
			if(tmp != NULL)
			{
				text_file_contents_pointer->characters=tmp;
				text_file_contents_pointer->characters
					[character_index]
					='\0';
				text_file_contents_pointer->character_count+=1;
			}
		}

	}
}

//String handling
void read_strings_to_text_file_contents_pointer(
		txt* text_file_contents_pointer,
		int* string_index,
		int* string_character_index,
		char character
		)
{
	//first char first str
	if((*string_character_index) == 0 && (*string_index) == 0)
	{
		if(character != ' ' && character != '\n')
		{
			text_file_contents_pointer->strings
				=malloc(sizeof(char*));
			text_file_contents_pointer->strings
				[0]
				=malloc(sizeof(char));
			text_file_contents_pointer->strings
				[0][0]
				=character;
			text_file_contents_pointer->string_count=0;
			(*string_character_index)+=1;
		}
	}
	//first char n str
	else if((*string_character_index) == 0 && (*string_index) != 0)
	{
		if(character != ' ' && character != '\n')
		{
			void* tmp=realloc(text_file_contents_pointer->strings,
						((*string_index)+1)*sizeof(char*));
			if(tmp != NULL)
			{
				text_file_contents_pointer->strings=tmp;
				text_file_contents_pointer->strings
					[(*string_index)]
					=malloc(sizeof(char));
				text_file_contents_pointer->strings
					[(*string_index)][(*string_character_index)]
					=character;
				(*string_character_index)+=1;
			}
		}
	}
	else
	{
		if(character != ' ' && character != '\n')
		{
			void* tmp=realloc(text_file_contents_pointer->strings
						[(*string_index)],
						((*string_character_index)+1)*sizeof(char));
			if(tmp != NULL)
			{
				text_file_contents_pointer->strings
					[(*string_index)]
					=tmp;
				text_file_contents_pointer->strings
					[(*string_index)][(*string_character_index)]
					=character;
				(*string_character_index)+=1;
			}
		}
		else
		{
			void* tmp=realloc(text_file_contents_pointer->strings
						[(*string_index)],
						((*string_character_index)+1)*sizeof(char));
			if(tmp != NULL)
			{
				text_file_contents_pointer->strings
					[(*string_index)]
					=tmp;
				text_file_contents_pointer->strings
					[(*string_index)][(*string_character_index)]
					='\0';
				text_file_contents_pointer->string_count+=1;
				(*string_index)+=1;
				(*string_character_index)=0;
			}
		}
	}
}

//Line handler
void read_lines_to_text_file_contents_pointer(
		txt* text_file_contents_pointer,
		int* line_index,
		int* line_character_index,
		char character
		)
{
	//If first char first line
	if((*line_character_index) == 0 && (*line_index) == 0)
	{
		if(character != ' ' && character != '\n')
		{
			text_file_contents_pointer->lines
				=malloc(sizeof(char*));
			text_file_contents_pointer->lines
				[0]
				=malloc(sizeof(char));
			text_file_contents_pointer->lines
				[0][0]
				=character;
			text_file_contents_pointer->line_count=0;
			(*line_character_index)+=1;
		}
	}
	//first char n line
	else if((*line_character_index) == 0 && (*line_index) != 0)
	{
		if(character != '\n')
		{
			void* tmp=realloc(text_file_contents_pointer->lines,
						((*line_index)+1)*sizeof(char*));
			if(tmp != NULL)
			{
				text_file_contents_pointer->lines=tmp;
				text_file_contents_pointer->lines
					[(*line_index)]
					=malloc(sizeof(char));
				text_file_contents_pointer->lines
					[(*line_index)][(*line_character_index)]
					=character;
				(*line_character_index)+=1;
			}
		}
	}
	else
	{
		if(character != '\n')
		{
			void* tmp=realloc(text_file_contents_pointer->lines
						[(*line_index)],
						((*line_character_index)+1)*sizeof(char));
			if(tmp != NULL)
			{
				text_file_contents_pointer->lines
					[(*line_index)]
					=tmp;
				text_file_contents_pointer->lines
					[(*line_index)][(*line_character_index)]
					=character;
				(*line_character_index)+=1;
			}
		}
		else
		{
			void* tmp=realloc(text_file_contents_pointer->lines
						[(*line_index)],
						((*line_character_index)+1)*sizeof(char));
			if(tmp != NULL)
			{
				text_file_contents_pointer->lines
					[(*line_index)]
					=tmp;
				text_file_contents_pointer->lines
					[(*line_index)][(*line_character_index)]
					='\0';
				text_file_contents_pointer->line_count+=1;
				(*line_index)+=1;
				(*line_character_index)=0;
			}
		}
	}
}

//main function
void read_text_file_contents(txt* text_file_contents_pointer,char* file_path)
{
	char character;
	int character_index=0,
	    string_index=0,
	    string_character_index=0,
	    line_index=0,
	    line_character_index=0;
	FILE* file_pointer = fopen(file_path,"read");
	while((character = fgetc(file_pointer))!=EOF)
	{
		read_character_to_text_file_contents_pointer(
				&(*text_file_contents_pointer),
				character,
				character_index
				);
		read_strings_to_text_file_contents_pointer(
				&(*text_file_contents_pointer),
				&string_index,
				&string_character_index,
				character
				);
		read_lines_to_text_file_contents_pointer(
				&(*text_file_contents_pointer),
				&line_index,
				&line_character_index,
				character
				);
		character_index+=1;
	}
	fclose(file_pointer);
}


