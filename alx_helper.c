#include "shell.h"

void alx_free_args(char **args, char **front);
char *alx_get_pid(void);
char *alx_get_env_value(char *beginning, int len);
void alx_variable_replacement(char **args, int *exe_ret);

/**
 * alx_free_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */
void alx_free_args(char **args, char **front)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(front);
}

/**
 * alx_get_pid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *alx_get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * alx_get_env_value - Gets an environmental variable.
 * @beginning: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *alx_get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	alx_strncat(var, beginning, len);

	var_addr = alx_getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(alx_strlen(temp) + 1);
		if (replacement)
			alx_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * alx_variable_replacement - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void alx_variable_replacement(char **line, int *exe_ret)
{
	int j, k = 0, len;
	char *replacement = NULL, *o_line = NULL, *n_line;

	o_line = *line;
	for (j = 0; o_line[j]; j++)
	{
		if (o_line[j] == '$' && o_line[j + 1] &&
			o_line[j + 1] != ' ')
		{
			if (o_line[j + 1] == '$')
			{
				replacement = alx_get_pid();
				k = j + 2;
			}
			else if (o_line[j + 1] == '?')
			{
				replacement = alx_itoa(*exe_ret);
				k = j + 2;
			}
			else if (o_line[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; o_line[k] &&
								o_line[k] != '$' &&
								o_line[k] != ' ';
					 k++)
					;
				len = k - (j + 1);
				replacement = alx_get_env_value(&o_line[j + 1], len);
			}
			n_line = malloc(j + alx_strlen(replacement) + alx_strlen(&o_line[k]) + 1);
			if (!line)
				return;
			n_line[0] = '\0';
			alx_strncat(n_line, o_line, j);
			if (replacement)
			{
				alx_strcat(n_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			alx_strcat(n_line, &o_line[k]);
			free(o_line);
			*line = n_line;
			o_line = n_line;
			j = -1;
		}
	}
}

