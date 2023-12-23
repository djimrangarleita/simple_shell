#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <ctype.h>
#include <fcntl.h>

extern char **environ;

/**
 * struct pfunc_t - printing functions and their identifiers
 * @spec: format specifier
 * @func: print function
 */
typedef struct pfunc_t
{
	char *spec;
	int (*func)(va_list, char *);
} pfunc_t;

/**
 * struct btin_t - shell built-in functions
 * @name: name of the function
 * @func: pointer to the function
 */
typedef struct btin_t
{
	char *name;
	int (*func)(char **cmd);
} btin_t;
int _printf(const char *format, ...);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
int _strlen(char *str);
int print_str(char *str, int len);
int ppstr(va_list ap, char *spec);
int ppchar(va_list ap, char *spec);
int put_char(char c);
int print_num(int n);
int ppnum(va_list ap, char *spec);
int execcmd(char **cmd);
int _printenv(char **cmd);
int _cd(char **cmd);
int _exitsh(char **cmd);
int _setenv(char **cmd);
int _unsetenv(char **cmd);
char **_strtok(char *line, int size, char *delim);
void free_toks(char **tokens);
char *findxpath(char *input);
int (*is_btin(char *cmd))(char **cmd);
int shelln_int(char *pname, char *filename);
int shell_int(char *pname, char *filename);
int statxcmd(char **toks);
char *_getenv(char *envkey);
int gettoksnum(char *line, int size, char *delim);
char **get_inputs(int *status, int fd);
int runcmds(char **lines, char *pname, int *status);
char *makexpath(char *input, char *curpath);
int _printerr(int status, char **cmd, char *pname, char *input);
int _pxiterr(char **cmd, char *pname);
int _plserr(char **cmd, char *input);
int _pcderr(char **cmd, char *pname);
char *_realloc(char *ptr, int old_size, int newsize);
int _pfilerr(int status, char *pname, char *filename);
int _preaderr(char *buffer, char *tmp);
char **filter_toks(char **toks, int *prevstatus);
char **shift_toks(char **toks, int pos);
int _pcmdisfolder(char *pname, char **cmd);

#endif
