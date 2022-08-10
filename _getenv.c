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
