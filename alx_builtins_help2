#include "shell.h"

void alx_help_env(void);
void alx_help_setenv(void);
void alx_help_unsetenv(void);
void alx_help_history(void);

/**
 * alx_help_env - Displays information on the shellby builtin command 'env'.
 */
void alx_help_env(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, alx_strlen(msg));
}

/**
 * alx_help_setenv - Displays information on the shellby builtin command 'setenv'.
 */
void alx_help_setenv(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, alx_strlen(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, alx_strlen(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, alx_strlen(msg));
}

/**
 * alx_help_unsetenv - Displays information on the shellby builtin command
 * 'unsetenv'.
 */
void alx_help_unsetenv(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, alx_strlen(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, alx_strlen(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, alx_strlen(msg));
}

