#include "main.h"

int main(int ac, char **av, char **env)
{
	char *line;
	char **args;
	int status;
	(void)ac;
	(void)av;

	do {
		line = read_line();
		args = parse_line(line);
		status = shell_launch(args, env);

		free(line);
		free(args);
	} while	(status);

	return (0);
}
