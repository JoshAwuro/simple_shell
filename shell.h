#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include <limits.h>

extern char **environ;
char *_strcat(char *end, char *src);
void prompt(void);
char *_strcat(char *end, char *src);
char prints_inputs(void);
int _strlen(char *s);
void hold(char *h);
char *command_finder(char *cmd);
char *file_finder(char *cmd);
int compare(char *str1, char *str2);
int _strcmp(char *str1, char *str2);
char *concat_str(char *str1, char *str2);
int _putchar(char ch);
int slash(char *command);
int check_exit(char *str1, char *str2);
int env_check(char *str1, char *str2);
char **strput(char *arg);
void controlled(int signal);
void perform(char **command);

#endif
