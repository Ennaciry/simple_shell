#include "shell.h"
int (*alx_get_builtin(char *command))(char **args, char **front);
int alx_shellby_exit(char **args, char **front);
int alx_shellby_cd(char **args, char __attribute__((__unused__)) **front);
int alx_shellby_help(char **args, char __attribute__((__unused__)) **front);

/**
 * alx_get_builtin - Matches a command with a corresponding
 *               shellby builtin function.
 * @command: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*alx_get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{"exit", alx_shellby_exit},
		{"env", alx_shellby_env},
		{"setenv", alx_shellby_setenv},
		{"unsetenv", alx_shellby_unsetenv},
		{"cd", alx_shellby_cd},
		{"alias", alx_shellby_alias},
		{"help", alx_shellby_help},
		{NULL, NULL}};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (alx_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * alx_shellby_exit - Causes normal process termination
 *                for the shellby shell.
 * @args: An array of arguments containing the exit value.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */
int alx_shellby_exit(char **args, char **front)
{
	int i, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (alx_create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (alx_create_error(--args, 2));
	args -= 1;
	alx_free_args(args, front);
	alx_free_env();
	alx_free_alias_list(aliases);
	exit(num);
}

/**
 * alx_shellby_cd - Changes the current directory of the shellby process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int alx_shellby_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || alx_strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
				args[0][1] == '\0')
			{
				if (alx_getenv("OLDPWD") != NULL)
					(chdir(*alx_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (alx_create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode) 
			&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (alx_create_error(args, 2));
			}
		}
	}
	else
	{
		if (alx_getenv("HOME") != NULL)
			chdir(*(alx_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (alx_shellby_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (alx_shellby_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, alx_strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * alx_shellby_help - Displays information about shellby builtin commands.
 * @args: An array of arguments.
 * @front: A pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int alx_shellby_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		alx_help_all();
	else if (alx_strcmp(args[0], "alias") == 0)
		alx_help_alias();
	else if (alx_strcmp(args[0], "cd") == 0)
		alx_help_cd();
	else if (alx_strcmp(args[0], "exit") == 0)
		alx_help_exit();
	else if (alx_strcmp(args[0], "env") == 0)
		alx_help_env();
	else if (alx_strcmp(args[0], "setenv") == 0)
		alx_help_setenv();
	else if (alx_strcmp(args[0], "unsetenv") == 0)
		alx_help_unsetenv();
	else if (alx_strcmp(args[0], "help") == 0)
		alx_help_help();
	else
		write(STDERR_FILENO, name, alx_strlen(name));

	return (0);
}

