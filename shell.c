#include "main.h"

int main(void)
{
	char *line;
	char **args;
	int status;

	do {
		//printf("#cisfun$ ");
		line = read_line();
		args = parse_line(line);
		status = shell_launch(args);

		free(line);
		free(args);
	} while	(status);

	return (0);
}
