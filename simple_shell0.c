#include "shell.h"

/**
 * prompt_message - print the default message for user to make input
 *
 * Return: EXIT_SUCCESS
 */

void prompt_message(void)
{
	printf("$ ");
}

/**
 * execute_command - fork a process to execute the command entered by the user
 * @command: string command entered by user
 * Return: EXIT_SUCCESS
 */

void execute_command(char *command)
{
	pid_t mypid = fork();

	if (mypid < 0)
	{
		perror("Fork failed.\n");
		exit(1);
	}
	else if (mypid == 0)
	{
		if (execlp(command, command, NULL) == -1)
		{
			fprintf(stderr, "Command not found: %s\n", command);
			exit(1);
		}
	}
	else
	{
		wait(NULL);
	}

}

/**
 * run_shell - loop the shell to continue taking command from user
 * Return: EXIT_SUCCESS
 */

void run_shell(void)
{
	char command[BUFFER_SIZE];

	while (1)
	{
		prompt_message();

		if (fgets(command, BUFFER_SIZE, stdin) == NULL)
			break;

		command[strcspn(command, "\n")] = '\0';

		execute_command(command);
	}
}
