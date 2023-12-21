#include "main.h"

/**
 * execcmd - execute cmd,
 * @cmd: The cmd to be executed
 * Return: exec code indicating error
 */
int execcmd(char **cmd)
{
	return (execve(cmd[0], cmd, environ));
}

/**
 * shell_int - interactive shell
 * @pname: program name, to print alongside error msg
 * Return: int indicating exec status
 */
int shell_int(char *pname)
{
	char **lines;
	int execres = 0;

	while (1)
	{
		_printf("($) ");
		lines = get_inputs(&execres);

		execres = runcmds(lines, pname, &execres);

		free_toks(lines);
	}

	return (execres);
}

/**
 * shelln_int - non interactive version of the shell
 * @pname: name of the program, print alongside error msg
 * Return: int, exec status
 */
int shelln_int(char *pname)
{
	int execres = 0;
	char **lines;

	lines = get_inputs(&execres);

	execres = runcmds(lines, pname, &execres);
	free_toks(lines);

	return (execres);
}

/**
 * runcmds - takes parsed cmd lines and run it
 * @lines: set of commands to be exec
 * @pname: name of the program
 * @status: last/prev execution status
 * Return: exec status
 */
int runcmds(char **lines, char *pname, int *status)
{
	int size, i, (*btin)(char **);
	char *tmp, **toks, *path;

	for (i = 0; lines && lines[i]; i++)
	{
		size = _strlen(lines[i]);
		toks = _strtok(lines[i], size, " \t");
		if (toks && toks[0])
		{
			/* check if any tok == || or && */
			btin = is_btin(toks[0]);
			tmp = _strdup(toks[0]);
			if (btin)
			{
				if (_strcmp(toks[0], "exit") != 0 || toks[1])
					*status = btin(toks);
				if (_strcmp(toks[0], "exit") == 0 && *status >= 0)
				{
					free(tmp);
					free_toks(toks);
					free_toks(lines);
					exit(*status);
				}
			}
			else
			{
				path = findxpath(toks[0]);
				free(toks[0]);
				toks[0] = path;
				*status = statxcmd(toks);
			}
			if (*status != 0)
				*status = _printerr(*status, toks, pname, tmp);
			free(tmp);
		}
		free_toks(toks);
	}
	return (*status);
}

/**
 * statxcmd - read and execute program
 * @toks: tokenized cmd
 * Return: int, exec status
 */
int statxcmd(char **toks)
{
	int status, statusCode = 0;
	struct stat buf;
	pid_t child_pid;

	if (stat(toks[0], &buf) != 0)
	{
		return (127);
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			return (-1);
		}
		else if (child_pid == 0)
		{
			execcmd(toks);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
			{
				statusCode = WEXITSTATUS(status);
			}
		}
	}

	return (statusCode);
}
