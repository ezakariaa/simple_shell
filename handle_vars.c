#include "shell.h"

void args_free(char **last_cmd_status, char **start_of_args);
char *fetch_pid(void);
char *fetch_val_env(char *env_var, int length);
void rep_var(char **cmd_args, int *last_cmd_status);

/**
* args_free - Frees the memory.
* @last_cmd_status: The last cmd.
* @start_of_args: The start of the arg.
*/
void args_free(char **last_cmd_status, char **start_of_args)
{
	size_t index;

	for (index = 0; last_cmd_status[index] || last_cmd_status[index + 1]; index++)
		free(last_cmd_status[index]);

	free(start_of_args);
}

/**
* fetch_pid - Fetchs the id's process.
*
* Return: The pid or NULL.
*/
char *fetch_pid(void)
{
	char *line_buff;
	ssize_t fd;
	size_t index = 0;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	line_buff = malloc(120);
	if (!line_buff)
	{
		close(fd);
		return (NULL);
	}
	read(fd, line_buff, 120);
	while (line_buff[index] != ' ')
		index++;
	line_buff[index] = '\0';

	close(fd);
	return (line_buff);
}

/**
* fetch_val_env - Fetchs the variable env's value.
* @env_var: Rhe var env to look for.
* @length: The length of the env var.
*
* Return: env var's value or empty str.
*/
 char *fetch_val_env(char *env_var, int length)
{
	char *rep = NULL, *t, *new_var;
	char **ad_var;

	new_var = malloc(length + 1);
	if (!new_var)
		return (NULL);
	new_var[0] = '\0';
	_str_n_cat(new_var, env_var, length);

	ad_var = custom_getenv(new_var);
	free(new_var);
	if (ad_var)
	{
		t = *ad_var;
		while (*t != '=')
			t++;
		t++;
		rep = malloc(_str_length(t) + 1);
		if (rep)
			_str_cpy(rep, t);
	}

	return (rep);
}

/**
* rep_var - Replaces the env var.
* @cmd_args: the cmd args.
* @last_cmd_status: the last command.
*/
void rep_var(char **cmd_args, int *last_cmd_status)
{
	char *rep = NULL, *cmd_old = NULL, *cmd_new;
	int length;
	int j, k = 0;

	cmd_old = *cmd_args;
	for (j = 0; cmd_old[j]; j++)
	{
		if (cmd_old[j] == '$' && cmd_old[j + 1] &&
			cmd_old[j + 1] != ' ')
		{
			if (cmd_old[j + 1] == '$')
			{
				rep = fetch_pid();
				k = j + 2;
			}
			else if (cmd_old[j + 1] == '?')
			{
				rep = custom_itoa(*last_cmd_status);
				k = j + 2;
			}
			else if (cmd_old[j + 1])
			{
				for (k = j + 1; cmd_old[k] &&
								cmd_old[k] != '$' &&
								cmd_old[k] != ' ';
								k++)
								;
				length = k - (j + 1);
				rep = fetch_val_env(&cmd_old[j + 1], length);
			}
			cmd_new = malloc(j + _str_length(rep) + _str_length(&cmd_old[k]) + 1);
			if (!cmd_args)
				return;
			cmd_new[0] = '\0';
			_str_n_cat(cmd_new, cmd_old, j);
			if (rep)
			{
				_str_cat(cmd_new, rep);
				free(rep);
				rep = NULL;
			}
			_str_cat(cmd_new, &cmd_old[k]);
			free(cmd_old);
			*cmd_args = cmd_new;
			cmd_old = cmd_new;
			j = -1;
		}
	}
}
