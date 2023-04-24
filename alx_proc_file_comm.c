#include "shell.h"

int alx_cant_open(char *file_path);
int alx_proc_file_commands(char *file_path, int *exe_ret);

/**
 * alx_cant_open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int alx_cant_open(char *file_path)
{
	char *error, *hist_str;
	int len;

	hist_str = alx_itoa(hist);
	if (!hist_str)
		return (127);

	len = alx_strlen(name) + alx_strlen(hist_str) + alx_strlen(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	alx_strcpy(error, name);
	alx_strcat(error, ": ");
	alx_strcat(error, hist_str);
	alx_strcat(error, ": Can't open ");
	alx_strcat(error, file_path);
	alx_strcat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * alx_proc_file_commands - Takes file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int alx_proc_file_commands(char *file_path, int *exe_ret)
{
	ssize_t file, b_read, i;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = alx_cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = alx_realloc(line, old_size, line_size);
		alx_strcat(line, buffer);
		old_size = line_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	alx_variable_replacement(&line, exe_ret);
	alx_handle_line(&line, line_size);
	args = alx_strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (alx_check_args(args) != 0)
	{
		*exe_ret = 2;
		alx_free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (alx_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = alx_call_args(args, front, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}

	ret = alx_call_args(args, front, exe_ret);

	free(front);
	return (ret);
}

