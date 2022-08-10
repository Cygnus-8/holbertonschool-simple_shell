#include "main.h"
#define delim " \t\r\n\a"
/**
 * read_line - cfr description
 * Description: Read user's line
 * Return: User's line
 */
char *read_line(void)
{
	char *line = NULL;
	size_t buffsize = 0;

	if (getline(&line, &buffsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("Can't Read your entry");
			free(line);
			exit(EXIT_FAILURE);
		}
	}
	if (line == NULL)
	{
		free(line);
		return (NULL);
	}

	return (line);
}
/**
 * parse_line - cfr description
 * @line: pointer to user's line
 * description: divide line for read
 * Return: token
 */
char **parse_line(char *line)
{
	int bufsize = 32, position = 0;
	char **tokens;
	char *token;

	if (line == NULL)
		return (NULL);

	tokens = malloc(sizeof(char *) * bufsize);

	if (!tokens)
	{
		fprintf(stderr, "Malloc error: can't allocate\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, delim);

	while (token != NULL)
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
				for (; position != 0; position--)
					free(tokens[position]);
				free(tokens);
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, delim);
	}
	tokens[position] = NULL;

	return (tokens);
}
/**
 * shell_launch - cfr description
 * @tokens: pointer on char pointer that contains all tokens
 * @env: environemnt variable pointer
 * Return: 1 or 2 depends on situation
 */
int shell_launch(char **tokens, char **env)
{
	pid_t child_pid, wpid;
	int status;

	child_pid = fork();

	if (child_pid == 0)
	{
		if (tokens[0] == NULL)
		{
			free(tokens);
			return (2);
		}
		if (execve(tokens[0], tokens, env) == -1)
		{
			perror("Exec error: can't execute your command");
		}
		free(tokens);
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
	(void)wpid;

	return (1);
}
