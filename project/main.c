#include "main.h"

int main()
{
	char input[50],prompt[50] = "minishell$";
	int cmmd;
	char *ptr;

	struct sigaction act;
        act.sa_handler = signal_handler;

	//registring the signal
	sigaction(SIGINT,&act,NULL);
	//sigaction(SIGTSTP,&act,NULL);
	while(1)
	{
		printf("%s ",prompt);

		//reading the user input
		fgets(input,50,stdin);

		//removing the new line
		ptr = strchr(input,'\n');
		if(ptr)
			*ptr = '\0';

		if(*input == '\0')
		{
			continue;
		}
		else if(strncmp(input,"PS1=",4) == 0)
		{
			strcpy(prompt,input+4);
		}
		else if(strcmp(input,"echo $$") == 0)
		{
			printf("%d\n",getpid());
		}
		else if(strcmp(input,"echo $SHELL")==0)
		{
			printf("%s/minishell\n",get_current_dir_name());
		}
		else if(strcmp(input,"echo $?") == 0)
		{
			printf("%d\n",0);
		}
		else if((cmmd = check_command_type(input)) == EXT_CMD)
		{
			execute_external_command(input);
		}
		else if(cmmd == INT_CMD)
		{
			execute_internal_command(input);
		}
		else
		{
			printf("%s : command not found\n",input);
		}
	}
}
