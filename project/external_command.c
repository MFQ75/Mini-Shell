#include "main.h"

int pid,ext_status;

void get_command(char *input, char *cmd[])
{
	char *token = strtok(input," ");

	int i = 0;
	while(token)
	{
		cmd[i] = malloc(strlen(token) + 1);
		strcpy(cmd[i],token);
		i++;
		token = strtok(NULL," ");
	}
	cmd[i] = NULL;
}
int execute_external_command(char *input)
{
	pid = fork();
        int ret;
	if(pid == 0)     //child process
	{
		char *cmd[10] = {NULL};
		get_command(input,cmd);
		execvp(cmd[0],cmd);
		printf("%s : command not found",input);
		exit(errno);
	}
	else
	{
		ret = waitpid(pid, &ext_status, WUNTRACED);
		if(WIFEXITED(ext_status))
		{
			printf("The child %d terminated normally with code %d\n",ret,WEXITSTATUS(ext_status));
			return WEXITSTATUS(ext_status);
		}
		else if(WIFSIGNALED(ext_status))
		{
			printf("The child %d terminated by recieving signal %d\n",ret,WTERMSIG(ext_status));
		}
		else if(WIFSTOPPED(ext_status))
		{
			printf("The child %d stopped by %d\n",ret,WSTOPSIG(ext_status));
		}
	}
}
