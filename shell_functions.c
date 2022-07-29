#include "main.h"
#define delim " \t\r\n\a"

char *read_line(void) 
{
	char *line = NULL;
	ssize_t buffsize = 0;

	if (getline(&line, &buffsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS); 
		}
		else 
		{
			perror("Can't Read your entry");
			exit(EXIT_FAILURE);
		}
	}

	return (line); 
}

char **parse_line(char *line)
{
	int bufsize = 32, position = 0;
	char **tokens = malloc(sizeof(char *) * bufsize);
	char *token; 

	if(!tokens)
	{
		fprintf(stderr, "Malloc error: can't allocate\n");
		exit(EXIT_FAILURE); 
	}

	token = strtok(line, delim);

	while(token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 32;
			tokens = realloc(tokens, sizeof(char *) * bufsize);
			if (!tokens)
			{
				fprintf(stderr, "Realloc error: can't allocate again");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, delim);
	}
	tokens[position] = NULL;

	return (tokens);
}

int shell_launch(char **tokens)
{
	pid_t child_pid, wpid;
	int status;

	child_pid = fork();

	if (child_pid == 0)
	{
		if (execve(tokens[0], tokens, NULL) == -1)
		{
			perror("Exec error: can't execute your command");
		}
		exit(EXIT_FAILURE);
	}
	else if (child_pid < 0)
		perror("Fork error: can't create the child process");
	else
	{
		do {
			wpid = waitpid(child_pid, &status, WUNTRACED); 

		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}
