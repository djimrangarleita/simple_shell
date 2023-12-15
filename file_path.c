#include "main.h"

/**
 * findxpath - find full path of an executable
 * @input: ptr to user's path
 * Return: full path of an exec or input
 */
char *findxpath(char *input)
{
	int i;
	char *key, *val, *pathexec, *tmpenv = NULL;

	if (*input == '/')
	{
		return (_strdup(input));
	}

	i = 0;
	while (environ && environ[i] != NULL)
	{
		tmpenv = _strdup(environ[i]);
		key = strtok(tmpenv, "=");
		val = strtok(NULL, "=");
		if (_strcmp(key, "PATH") == 0)
		{
			pathexec = makexpath(input, val);
			if (pathexec)
			{
				free(tmpenv);
				return (pathexec);
			}
		}
		free(tmpenv);
		i++;
	}

	return (_strdup(input));
}

/**
 * makexpath - make full path to an exec
 * @input: user input, cmd,
 * @curpath: current token
 * Return: pointer to the path
 */
char *makexpath(char *input, char *curpath)
{
	char *path, *tmp, *tmpcat, *pathexec;
	struct stat buf;

	path = strtok(curpath, ":");
	while (path != NULL)
	{
		tmp = malloc((_strlen(path) + _strlen(input) + 2) * sizeof(char));
		if (!tmp)
		{
			return (_strdup(input));
		}
		tmp = _strcpy(tmp, path);
		tmp = _strcat(tmp, "/");
		tmpcat = _strcat(tmp, input);
		if (stat(tmpcat, &buf) == 0)
		{
			pathexec = malloc((_strlen(tmpcat) + 1) * sizeof(char));
			pathexec = _strcpy(pathexec, tmpcat);
			free(tmp);
			return (pathexec);
		}
		path = strtok(NULL, ":");
		free(tmp);
	}

	return (NULL);
}
