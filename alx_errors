#include "shell.h"

int alx_num_len(int num);
char *alx_itoa(int num);
int alx_create_error(char **args, int err);

/**
 * alx_num_len - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int alx_num_len(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}

	return (len);
}

/**
 * alx_itoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *alx_itoa(int num)
{
	char *buffer;
	int len = alx_num_len(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do
	{
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}

/**
 * alx_create_error - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int alx_create_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = alx_error_env(args);
		break;
	case 1:
		error = alx_error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = alx_error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = alx_error_2_syntax(args);
		else
			error = alx_error_2_cd(args);
		break;
	case 126:
		error = alx_error_126(args);
		break;
	case 127:
		error = alx_error_127(args);
		break;
	}
	write(STDERR_FILENO, error, alx_strlen(error));

	if (error)
		free(error);
	return (err);
}

