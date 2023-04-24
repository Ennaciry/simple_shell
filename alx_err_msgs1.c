#include "shell.h"

char *alx_error_env(char **args);
char *alx_error_1(char **args);
char *alx_error_2_exit(char **args);
char *alx_error_2_cd(char **args);
char *alx_error_2_syntax(char **args);
/**
 * alx_error_env - Creates an error message for shellby_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *alx_error_env(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = alx_itoa(hist);
	if (!hist_str)
		return (NULL);

	args--;
	len = alx_strlen(name) + alx_strlen(hist_str) + alx_strlen(args[0]) + 45;
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
	alx_strcat(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * alx_error_1 - Creates an error message for shellby_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *alx_error_1(char **args)
{
	char *error;
	int len;

	len = alx_strlen(name) + alx_strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	alx_strcpy(error, "alias: ");
	alx_strcat(error, args[0]);
	alx_strcat(error, " not found\n");

	return (error);
}

/**
 * alx_error_2_exit - Creates an error message for shellby_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *alx_error_2_exit(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = alx_itoa(hist);
	if (!hist_str)
		return (NULL);

	len = alx_strlen(name) + alx_strlen(hist_str) + alx_strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	alx_strcpy(error, name);
	alx_strcat(error, ": ");
	alx_strcat(error, hist_str);
	alx_strcat(error, ": exit: Illegal number: ");
	alx_strcat(error, args[0]);
	alx_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * alx_error_2_cd - Creates an error message for shellby_cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *alx_error_2_cd(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = alx_itoa(hist);
	if (!hist_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
		alx_strcat(error, ": cd: Illegal option ");
	else
		alx_strcat(error, ": cd: can't cd to ");
	alx_strcat(error, args[0]);
	alx_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * alx_error_2_syntax - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *alx_error_2_syntax(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = alx_itoa(hist);
	if (!hist_str)
		return (NULL);

	len = alx_strlen(name) + alx_strlen(hist_str) + alx_strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	alx_strcpy(error, name);
	alx_strcat(error, ": ");
	alx_strcat(error, hist_str);
	alx_strcat(error, ": Syntax error: \"");
	alx_strcat(error, args[0]);
	alx_strcat(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}

