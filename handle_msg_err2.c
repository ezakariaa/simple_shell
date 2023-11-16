#include "shell.h"

char *env_err(char **cmd_arg);
char *first_err(char **cmd_arg);
char *sec_ex_err(char **cmd_arg);
char *sec_cd_err(char **cmd_arg);
char *sec_syn_err(char **cmd_arg);
/**
* env_err - Generates msg errs.
* @cmd_arg: Args.
*
* Return: err msg.
*/
char *env_err(char **cmd_arg)
{
	int length;
	char *err, *str_his;

	str_his = custom_itoa(history_count);
	if (!str_his)
		return (NULL);

	cmd_arg--;
	length = _str_length(program_name) + _str_length(str_his) + _str_length(cmd_arg[0]) + 45;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(str_his);
		return (NULL);
	}

	_str_cpy(err, program_name);
	_str_cat(err, ": ");
	_str_cat(err, str_his);
	_str_cat(err, ": ");
	_str_cat(err, cmd_arg[0]);
	_str_cat(err, ": Unable to add/remove from environment\n");

	free(str_his);
	return (err);
}

/**
* first_err - Generates msg errs.
* @cmd_arg: Args.
*
* Return: err msg.
*/
char *first_err(char **cmd_arg)
{
	int length;
	char *err;

	length = _str_length(program_name) + _str_length(cmd_arg[0]) + 13;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
		return (NULL);

	_str_cpy(err, "alias: ");
	_str_cat(err, cmd_arg[0]);
	_str_cat(err, " not found\n");

	return (err);
}

/**
* sec_ex_err - Generates exit err.
* @cmd_arg: Args.
*
* Return: err msg.
*/
char *sec_ex_err(char **cmd_arg)
{
	int length;
	char *err, *str_his;

	str_his = custom_itoa(history_count);
	if (!str_his)
		return (NULL);

	length = _str_length(program_name) + _str_length(str_his) + _str_length(cmd_arg[0]) + 27;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(str_his);
		return (NULL);
	}

	_str_cpy(err, program_name);
	_str_cat(err, ": ");
	_str_cat(err, str_his);
	_str_cat(err, ": exit: Illegal number: ");
	_str_cat(err, cmd_arg[0]);
	_str_cat(err, "\n");

	free(str_his);
	return (err);
}

/**
* sec_cd_err - Generates exit err.
* @cmd_arg: Args.
*
* Return: err msg.
*/
char *sec_cd_err(char **cmd_arg)
{
	int length;
	char *err, *str_his;

	str_his = custom_itoa(history_count);
	if (!str_his)
		return (NULL);

	if (cmd_arg[0][0] == '-')
		cmd_arg[0][2] = '\0';
	length = _str_length(program_name) + _str_length(str_his) + _str_length(cmd_arg[0]) + 24;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(str_his);
		return (NULL);
	}

	_str_cpy(err, program_name);
	_str_cat(err, ": ");
	_str_cat(err, str_his);
	if (cmd_arg[0][0] == '-')
		_str_cat(err, ": cd: Illegal option ");
	else
		_str_cat(err, ": cd: can't cd to ");
	_str_cat(err, cmd_arg[0]);
	_str_cat(err, "\n");

	free(str_his);
	return (err);
}

/**
* sec_syn_err - Generates msg err.
* @cmd_arg: Args.
*
* Return: msg err.
*/
char *sec_syn_err(char **cmd_arg)
{
	int length;
	char *err, *str_his;

	str_his = custom_itoa(history_count);
	if (!str_his)
		return (NULL);

	length = _str_length(program_name) + _str_length(str_his) + _str_length(cmd_arg[0]) + 33;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(str_his);
		return (NULL);
	}

	_str_cpy(err, program_name);
	_str_cat(err, ": ");
	_str_cat(err, str_his);
	_str_cat(err, ": Syntax error: \"");
	_str_cat(err, cmd_arg[0]);
	_str_cat(err, "\" unexpected\n");

	free(str_his);
	return (err);
}
