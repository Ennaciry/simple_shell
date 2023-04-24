#include "shell.h"

void alx_sig_handler(int sig);
int alx_execute(char **args, char **front);
int hist;
char *name;
/**
 * alx_sig_handler - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void alx_sig_handler(int sig)
{
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, alx_sig_handler);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * alx_execute - alx_Executes a command in a child process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last alx_executed command.
 */
int alx_execute(char **args, char **front)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = alx_get_location(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (alx_create_error(args, 126));
		else
			ret = (alx_create_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
				ret = (alx_create_error(args, 126));
			alx_free_env();
			alx_free_args(args, front);
			alx_free_alias_list(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (ret);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last alx_executed command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exe_ret = &retn;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, alx_sig_handler);

	*exe_ret = 0;
	environ = alx_copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = alx_proc_file_commands(argv[1], exe_ret);
		alx_free_env();
		alx_free_alias_list(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = alx_handle_args(exe_ret);
		alx_free_env();
		alx_free_alias_list(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = alx_handle_args(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			alx_free_env();
			alx_free_alias_list(aliases);
			exit(*exe_ret);
		}
	}

	alx_free_env();
	alx_free_alias_list(aliases);
	return (*exe_ret);
}

