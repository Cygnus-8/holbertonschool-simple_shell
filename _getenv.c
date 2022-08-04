#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *_getenv(const char *name)
{
	extern char **environ;
	char *tmp;
	int i = 0, j = 0, k;

	while(environ[i])
	{
		tmp = strdup(environ[i]);
		while (tmp[j] != '=')
		{
			if (tmp[j] == name[j])
				k = 0;
			else
				k = -1;
			if(k == 0)
			{
				j++;
				continue;
			}
			else
				break;
		}
		if(k == 0)
			return (tmp);
		j = 0;
		tmp = NULL;
		i++;

	}

	return (NULL);
}

int main(int ac, char **av)
{

	if (_getenv(av[1]) != NULL)
		printf("The environement variable for %s is %s\n", av[1], _getenv(av[1]));
	else
		printf("There is no environement variable for %s", av[1]);

	return (0);
}
