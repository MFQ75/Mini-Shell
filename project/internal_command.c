#include "main.h"

int execute_internal_command(char *input)
{
	if(strcmp(input,"exit") == 0)
	{
		exit(0);
	}
	else if(strcmp(input,"pwd") == 0)
	{
		printf("%s\n",get_current_dir_name());
	}
	else if(strcmp(input,"cd") == 0)
	{
		chdir(input);
	}
	
}
