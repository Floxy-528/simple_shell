#include "shell.h"

/**
 * _myenv - Prints information about the current environment.
 * @info: A structure that may contain additional arguments for customization.
 *        This is used to maintain a consistent function prototype.
 * 
 * This function is designed to output details regarding the current execution
 * environment, such as system information. The @info parameter allows for
 * potential customization of the function's behavior. The function always
 * returns 0.
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Retrieves the value of an environment variable.
 * @info: Structure containing potential arguments, maintaining
 *        constant function prototype.
 * @name: Name of the environment variable.
 *
 * Return: The value of the specified environment variable.
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initializes a new environment variable or modifies an existing one.
 * @info: Structure containing potential arguments, ensuring a constant function prototype.
 *
 * Return: Always 0.
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - Populates an environment linked list.
 * @info: Structure containing potential arguments, ensuring a
 *        consistent function prototype.
 *
 * Return: Always 0.
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
