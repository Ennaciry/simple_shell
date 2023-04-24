#include "shell.h"

char *alx_error_126(char **args);
char *alx_error_127(char **args);

/**
 * alx_error_126 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *alx_error_126(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = alx_itoa(hist);
	if (!hist_str)
		return (NULL);

	len = alx_strlen(name) + alx_strlen(hist_str) + alx_strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	alx_strcpy(error, name);
	alx_strcat(error, ": ");
	alx_strcat(error, hist_str);
	alx_strcat(error, ": ");
	alx_strcat(error, args[0]);
	alx_strcat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * alx_error_127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *alx_error_127(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = alx_itoa(hist);
	if (!hist_str)
		return (NULL);

	len = alx_strlen(name) + alx_strlen(hist_str) + alx_strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	alx_strcpy(error, name);
	alx_strcat(error, ": ");
	alx_strcat(error, hist_str);
	alx_strcat(error, ": ");
	alx_strcat(error, args[0]);
	alx_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}

