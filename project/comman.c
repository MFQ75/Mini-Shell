#include "main.h"

extern int pid,ext_status;

int check_command_type(char *input)
{
	FILE *fptr = fopen("external_command.txt" ,"r");
	char ch[50],arr[strlen(input) + 1];
	strcpy(arr,input);
	char *cmd = strtok(arr," ");
	while (fscanf(fptr,"%s",ch) != EOF)
	{
		if(strcmp(ch,arr) == 0)
			return EXT_CMD;
	}
	return INT_CMD;
}

void signal_handler(int signum)
{
	//check is there any forground process running
	//if present, then send SIGINT signal to the child process
	//ELSE, ignore the signal
	if(pid > 0)
	{
		switch(signum)
		{
			case SIGINT :
				kill(pid,SIGINT);
				ext_status = 128 + SIGINT;
				pid = 0;
				break;
			case SIGTSTP :
				//call function to add the stopped process PID into the list.
				printf("%d stopped\n",pid);
				kill(pid,SIGTSTP);
				pid = 0;
		}
	}
	printf("\n");
}
