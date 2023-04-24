#ifndef _SHELL_H_
#define _SHELL_H_
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;
/* Global program name */
static char *name;
/* Global history counter */
static int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Main Helpers */
ssize_t alx_getline(char **lineptr, size_t *n, FILE *stream);
void *alx_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **alx_strtok(char *line, char *delim);
char *alx_get_location(char *command);
list_t *alx_get_path_dir(char *path);
int alx_execute(char **args, char **front);
void alx_free_list(list_t *head);
char *alx_itoa(int num);

/* Input Helpers */
void alx_handle_line(char **line, ssize_t read);
void alx_variable_replacement(char **args, int *exe_ret);
char *alx_get_args(char *line, int *exe_ret);
int alx_call_args(char **args, char **front, int *exe_ret);
int alx_run_args(char **args, char **front, int *exe_ret);
int alx_handle_args(int *exe_ret);
int alx_check_args(char **args);
void alx_free_args(char **args, char **front);
char **alx_replace_aliases(char **args);

/* String functions */
int alx_strlen(const char *s);
char *alx_strcat(char *dest, const char *src);
char *alx_strncat(char *dest, const char *src, size_t n);
char *alx_strcpy(char *dest, const char *src);
char *alx_strchr(char *s, char c);
int alx_strspn(char *s, char *accept);
int alx_strcmp(char *s1, char *s2);
int alx_strncmp(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*alx_get_builtin(char *command))(char **args, char **front);
int alx_shellby_exit(char **args, char **front);
int alx_shellby_env(char **args, char __attribute__((__unused__)) **front);
int alx_shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int alx_shellby_unsetenv(char **args,
						 char __attribute__((__unused__)) **front);
int alx_shellby_cd(char **args, char __attribute__((__unused__)) **front);
int alx_shellby_alias(char **args, char __attribute__((__unused__)) **front);
int alx_shellby_help(char **args, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **alx_copyenv(void);
void alx_free_env(void);
char **alx_getenv(const char *var);

/* Error Handling */
int alx_create_error(char **args, int err);
char *alx_error_env(char **args);
char *alx_error_1(char **args);
char *alx_error_2_exit(char **args);
char *alx_error_2_cd(char **args);
char *alx_error_2_syntax(char **args);
char *alx_error_126(char **args);
char *alx_error_127(char **args);

/* Linkedlist Helpers */
alias_t *alx_add_alias_end(alias_t **head, char *name, char *value);
void alx_free_alias_list(alias_t *head);
list_t *alx_add_node_end(list_t **head, char *dir);
void alx_free_list(list_t *head);

void alx_help_all(void);
void alx_help_alias(void);
void alx_help_cd(void);
void alx_help_exit(void);
void alx_help_help(void);
void alx_help_env(void);
void alx_help_setenv(void);
void alx_help_unsetenv(void);
void alx_help_history(void);

int alx_proc_file_commands(char *file_path, int *exe_ret);
#endif /* _SHELL_H_ */

