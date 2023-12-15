#include "main.h"

/**
 * _printenv - print env variables
 * @cmd: ptr to the cmd, with its args
 * @errormsg: error msg to print in case of error
 * Return: 0 on success, -1 on failure
 */
int _printenv(char **cmd, char *errormsg)
{
	int i;

	i = 0;
	while (cmd && environ && environ[i])
	{
		_printf("%s\n", environ[i++]);
	}

	if (i < 0)
	{
		_perror(errormsg);
		return (-1);
	}
	return (0);
}

/**
 * _cd - change directory using chdir() func
 * @cmd: cd cmd with args
 * @errormsg: error msg in case cd fail
 * Return: 0 on success, -1 otherwise
 */
int _cd(char **cmd, char *errormsg)
{
	char buf[1024], *ptr;
	char oldpwd[500], *ptroldpwd;
	char *tmp = NULL;

	ptroldpwd = getcwd(oldpwd, 500);
	tmp = _strdup(cmd[1]);
	if (!tmp || _strcmp(tmp, "~") == 0)
	{
		free(tmp);
		tmp = getdir("HOME");
	}
	else if (_strcmp(tmp, "-") == 0)
	{
		free(tmp);
		tmp = getdir("OLDPWD");
	}

	if (chdir(tmp) != 0)
	{
		_perror(errormsg);
		free(tmp);
		return (-1);
	}
	else
	{
		ptr = getcwd(buf, 1024);
		setenv("PWD", ptr, 1);
		setenv("OLDPWD", ptroldpwd, 1);
	}
	free(tmp);

	return (0);
}

/**
 * _exitsh - exit the shell or any,
 * @cmd: the exit cmd with args, code
 * @errormsg: error message to print, in case exit fail
 * Return: -1 on failure
 */
int _exitsh(char **cmd, char *errormsg)
{
	int code = 0;

	if (cmd[1] && errormsg)
		code = atoi(cmd[1]);
	free_toks(cmd);

	return (code);
}

/**
 * is_btin - check if cmd is a builtin cmd
 * @cmd: string representing the cmd
 * Return: ptr to function, the builtin func
 */
int (*is_btin(char *cmd))(char **cmd, char *errormsg)
{
	int i;
	btin_t btincmd[] = {
		{"env", _printenv},
		{"cd", _cd},
		{"exit", _exitsh},
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
