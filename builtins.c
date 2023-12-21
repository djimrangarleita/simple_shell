#include "main.h"

/**
 * _printenv - print env variables
 * @cmd: ptr to the cmd, with its args
 * Return: 0 on success, -1 on failure
 */
int _printenv(char **cmd)
{
	int i;

	i = 0;
	while (cmd && environ && environ[i])
	{
		_printf("%s\n", environ[i++]);
	}

	return (0);
}

/**
 * _cd - change directory using chdir() func
 * @cmd: cd cmd with args
 * Return: 0 on success, -1 otherwise
 */
int _cd(char **cmd)
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
	if (!tmp)
		tmp = _strdup(ptroldpwd);
	if (chdir(tmp) != 0)
	{
		free(tmp);
		return (-1);
	}
	else
	{
		ptr = getcwd(buf, 1024);
		setenv("PWD", ptr, 1);
		setenv("OLDPWD", ptroldpwd, 1);
		if (_strcmp(cmd[1], "-") == 0)
			_printf("%s\n", tmp);
	}
	free(tmp);

	return (0);
}

/**
 * _exitsh - exit the shell or any,
 * @cmd: the exit cmd with args, code
 * Return: -1 on failure
 */
int _exitsh(char **cmd)
{
	int code = 0;

	if (cmd[1])
	{
		if (isdigit(cmd[1][0]) != 0 || atoi(cmd[1]) > 0)
			code = atoi(cmd[1]);
		else
			return (-1);
	}

	return (code);
}

/**
 * _setenv - set an env var
 * @cmd: toks with cmd typed
 * Return: -1 on failure, 0 on success
 */
int _setenv(char **cmd)
{
	if (cmd[1] && !cmd[2])
		return (139);
	return (setenv(cmd[1], cmd[2], 1));
}

/**
 * _unsetenv - unset an env var
 * @cmd: toks with cmd typed
 * Return: -1 on failure, 0 on success
 */
int _unsetenv(char **cmd)
{
	return (unsetenv(cmd[1]));
}
