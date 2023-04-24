#include "shell.h"

int alx_shellby_alias(char **args, char __attribute__((__unused__)) **front);
void alx_set_alias(char *var_name, char *value);
void alx_print_alias(alias_t *alias);

/**
 * alx_shellby_alias - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int alx_shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int i, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			alx_print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		value = alx_strchr(args[i], '=');
		if (!value)
		{
			while (temp)
			{
				if (alx_strcmp(args[i], temp->name) == 0)
				{
					alx_print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = alx_create_error(args + i, 1);
		}
		else
			alx_set_alias(args[i], value);
	}
	return (ret);
}

/**
 * alx_set_alias - Will either set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'.
 * @var_name: Name of the alias.
 * @value: Value of the alias. First character is a '='.
 */
void alx_set_alias(char *var_name, char *value)
{
	alias_t *temp = aliases;
	int len, j, k;
	char *new_value;

	*value = '\0';
	value++;
	len = alx_strlen(value) - alx_strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (temp)
	{
		if (alx_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		alx_add_alias_end(&aliases, var_name, new_value);
}

/**
 * alx_print_alias - Prints the alias in the format name='value'.
 * @alias: Pointer to an alias.
 */
void alx_print_alias(alias_t *alias)
{
	char *alias_string;
	int len = alx_strlen(alias->name) + alx_strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	alx_strcpy(alias_string, alias->name);
	alx_strcat(alias_string, "='");
	alx_strcat(alias_string, alias->value);
	alx_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
/**
 * alx_replace_aliases - Goes through the arguments and replace matching alias
 * with their value.
 * @args: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **alx_replace_aliases(char **args)
{
	alias_t *temp;
	int i;
	char *new_value;

	if (alx_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (alx_strcmp(args[i], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (alx_strlen(temp->value) + 1));
				if (!new_value)
				{
					alx_free_args(args, args);
					return (NULL);
				}
				alx_strcpy(new_value, temp->value);
				free(args[i]);
				args[i] = new_value;
				i--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}

