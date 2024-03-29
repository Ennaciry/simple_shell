#include "shell.h"

char *alx_fill_path_dir(char *path);
list_t *alx_get_path_dir(char *path);

/**
 * alx_get_location - Locates a command in the PATH.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *alx_get_location(char *command)
{
	char **path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = alx_getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = alx_get_path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(alx_strlen(dirs->dir) + alx_strlen(command) + 2);
		if (!temp)
			return (NULL);

		alx_strcpy(temp, dirs->dir);
		alx_strcat(temp, "/");
		alx_strcat(temp, command);

		if (stat(temp, &st) == 0)
		{
			alx_free_list(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	alx_free_list(head);

	return (NULL);
}

/**
 * alx_fill_path_dir - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *alx_fill_path_dir(char *path)
{
	int i, length = 0;
	char *path_copy, *pwd;

	pwd = *(alx_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += alx_strlen(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				alx_strcat(path_copy, pwd);
				alx_strcat(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				alx_strcat(path_copy, ":");
				alx_strcat(path_copy, pwd);
			}
			else
				alx_strcat(path_copy, ":");
		}
		else
		{
			alx_strncat(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * alx_get_path_dir - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
list_t *alx_get_path_dir(char *path)
{
	int index;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = alx_fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = alx_strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (alx_add_node_end(&head, dirs[index]) == NULL)
		{
			alx_free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}

