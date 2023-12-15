#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

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
	int (*func)(char **cmd, char *errormsg);
} btin_t;
int _printf(const char *format, ...);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
int _strlen(char *str);
int print_str(char *str, int len);
int ppstr(va_list ap, char *spec);
void _perror(char *errormsg);
int ppchar(va_list ap, char *spec);
int put_char(char c);
int print_num(int n);
int ppnum(va_list ap, char *spec);
int execcmd(char **cmd, char *errormsg);
int _printenv(char **cmd, char *errormsg);
int _cd(char **cmd, char *errormsg);
int _exitsh(char **cmd, char *errormsg);
char **_strtok(char *line, int size, char *delim);
void free_toks(char **tokens);
char *findxpath(char *input);
int (*is_btin(char *cmd))(char **cmd, char *errormsg);
int shelln_int(char *pname);
int shell_int(char *pname);
int statxcmd(char **toks, char *pname, struct stat buf, pid_t *child_pid);
char *getdir(char *dirkey);
int gettoksnum(char *line, int size, char *delim);
char **get_inputs();
int runcmds(char **lines, char *pname, struct stat buf, pid_t *child_pid);
char *makexpath(char *input, char *curpath);

#endif
