#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * _getenv - cfr description
 * @name: const char variable
 * Description: It's return a env variable
 * Return: NULL if it's found
 */

char *_getenv(const char *name)
{
	char *tmp;
	int i = 0, j = 0, k;

	while (environ[i])
	{
		tmp = strdup(environ[i]);
		while (tmp[j] != '=')
		{
			if (tmp[j] == name[j])
				k = 0;
			else
				k = -1;
			if (k == 0)
			{
				j++;
				continue;
			}
			else
				break;
		}
		if (k == 0)
			return (tmp);
		j = 0;
		tmp = NULL;
		i++;

	}

	return (NULL);
}
