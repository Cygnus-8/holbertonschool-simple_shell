#include "main.h"

int main(int ac, char **av, char **env)
{
	char *line;
	char **args;
	int status;
	(void)ac;
	(void)av;

	if (!isatty(stdin))
		do{
			args = parse_line(line);
			status = shell_launch(args, env);
			free(line);
			if (status != 2)
				free(args);
			line = read_line;
		}while (line != NULL);
	exit(EXIT_SUCCESS);

	do {
		line = read_line();
		args = parse_line(line);
		status = shell_launch(args, env);

		free(line);
		if (status != 2)
			free(args);
	} while	(status);

	return (0);
}

