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
 * Return: Pointer to the path
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

/**
 * getdir - get full path to a given directory
 * @dirkey: env var key
 * Return: char ptr to the path or NULL
 */
char *getdir(char *dirkey)
{
	int i = 0;
	char *key, *val, *tmpenv, *dir;

	while (environ && environ[i])
	{
		tmpenv = _strdup(environ[i]);
		key = strtok(tmpenv, "=");
		val = strtok(NULL, "=");
		if (_strcmp(key, dirkey) == 0)
		{
			dir = _strdup(val);
			free(tmpenv);
			return (dir);
		}
		free(tmpenv);
		i++;
	}

	return (NULL);
}

/**
 * is_btin - check if cmd is a builtin cmd
 * @cmd: string representing the cmd
 * Return: ptr to function, the builtin func
 */
int (*is_btin(char *cmd))(char **toks)
{
	int i;
	btin_t btincmd[] = {
		{"env", _printenv},
		{"cd", _cd},
		{"exit", _exitsh},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{NULL, NULL}
	};

	i = 0;
	while (cmd && btincmd[i].name != NULL)
	{
		if (_strcmp(cmd, btincmd[i].name) == 0)
			return (btincmd[i].func);
		i++;
	}

	return (NULL);
}
