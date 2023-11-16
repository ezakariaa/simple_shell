#include "shell.h"

char **_cpy_environement(void);
void envir_free(void);
char **custom_getenv(const char *var);

/**
* _cpy_environement - Generates a copy of env vars.
*
* Return: A pointer to the copy.
*/
char **_cpy_environement(void)
{
	int i;
	size_t s;
	char **env_next;

	for (s = 0; environ[s]; s++)
		;

	env_next = malloc(sizeof(char *) * (s + 1));
	if (!env_next)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		env_next[i] = malloc(_str_length(environ[i]) + 1);

		if (!env_next[i])
		{
			for (i--; i >= 0; i--)
				free(env_next[i]);
			free(env_next);
			return (NULL);
		}
		_str_cpy(env_next[i], environ[i]);
	}
	env_next[i] = NULL;

	return (env_next);
}
/**
* envir_free - free the env copy.
*/
void envir_free(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}

/**
* custom_getenv - Fetch env vars.
* @var: Var's name.
*
* Return: env vars or NULL.
*/
char **custom_getenv(const char *var)
{
	int length;
	int i;

	length = _str_length(var);
	for (i = 0; environ[i]; i++)
	{
		if (_str_n_cmp(var, environ[i], length) == 0)
			return (&environ[i]);
	}

	return (NULL);
}
