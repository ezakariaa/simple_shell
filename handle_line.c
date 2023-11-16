#include "shell.h"

/**
 * check_oper - Checks the logical operator for the cmd
 * @cmd: The command to be checked
 * @fresh_length: The length
 */
void check_oper(char *cmd, ssize_t *fresh_length)
{
	char cur;
	char next;
	char pre;

	cur = *cmd;
	next = *(cmd + 1);
	pre = *(cmd - 1);
	if (cur == '&')
	{
		if (next == '&' && pre != ' ')
			(*fresh_length)++;
		else if (pre == '&' && next != ' ')
			(*fresh_length)++;
	}
	else if (cur == '|')
	{
		if (next == '|' && pre != ' ')
			(*fresh_length)++;
		else if (pre == '|' && next != ' ')
			(*fresh_length)++;
	}
}

/**
 * fetch_length - Fetchs new length of a cmd.
 * @cmd: the command.
 * Return: Length of the command.
 */
ssize_t fetch_length(char *cmd)
{
	char cur, next;
	size_t index;
	ssize_t fresh_length = 0;

	for (index = 0; cmd[index]; index++)
	{
		cur = cmd[index];
		next = cmd[index + 1];
		if (cur == '#')
		{
			if (index == 0 || cmd[index - 1] == ' ')
			{
				cmd[index] = '\0';
				break;
			}
		}
		else if (index != 0)
		{
			if (cur == ';')
			{
				if (next == ';' && cmd[index - 1] != ' ' && cmd[index - 1] != ';')
				{
					fresh_length += 2;
					continue;
				}
				else if (cmd[index - 1] == ';' && next != ' ')
				{
					fresh_length += 2;
					continue;
				}
				if (cmd[index - 1] != ' ')
					fresh_length++;
				if (next != ' ')
					fresh_length++;
			}
			else
				check_oper(&cmd[index], &fresh_length);
		}
		else if (cur == ';')
		{
			if (index != 0 && cmd[index - 1] != ' ')
				fresh_length++;
			if (next != ' ' && next != ';')
				fresh_length++;
		}
		fresh_length++;
	}
	return (fresh_length);
}
/**
 * read_line - Splits the line.
 * @cmd: The line
 * @mode: The line's length.
 */
void read_line(char **cmd, ssize_t mode)
{
	char pre, cur, next;
	char *pre_cmd, *nex_cmd;
	ssize_t fresh_length;
	size_t index, j;

	fresh_length = fetch_length(*cmd);
	if (fresh_length == mode - 1)
		return;
	nex_cmd = malloc(fresh_length + 1);
	if (!nex_cmd)
		return;
	j = 0;
	pre_cmd = *cmd;
	for (index = 0; pre_cmd[index]; index++)
	{
		cur = pre_cmd[index];
		next = pre_cmd[index + 1];
		if (index != 0)
		{
			pre = pre_cmd[index - 1];
			if (cur == ';')
			{
				if (next == ';' && pre != ' ' && pre != ';')
				{
					nex_cmd[j++] = ' ';
					nex_cmd[j++] = ';';
					continue;
				}
				else if (pre == ';' && next != ' ')
				{
					nex_cmd[j++] = ';';
					nex_cmd[j++] = ' ';
					continue;
				}
				if (pre != ' ')
					nex_cmd[j++] = ' ';
				nex_cmd[j++] = ';';
				if (next != ' ')
					nex_cmd[j++] = ' ';
				continue;
			}
			else if (cur == '&')
			{
				if (next == '&' && pre != ' ')
					nex_cmd[j++] = ' ';
				else if (pre == '&' && next != ' ')
				{
					nex_cmd[j++] = '&';
					nex_cmd[j++] = ' ';
					continue;
				}
			}
			else if (cur == '|')
			{
				if (next == '|' && pre != ' ')
					nex_cmd[j++]  = ' ';
				else if (pre == '|' && next != ' ')
				{
					nex_cmd[j++] = '|';
					nex_cmd[j++] = ' ';
					continue;
				}
			}
		}
		else if (cur == ';')
		{
			if (index != 0 && pre_cmd[index - 1] != ' ')
				nex_cmd[j++] = ' ';
			nex_cmd[j++] = ';';
			if (next != ' ' && next != ';')
				nex_cmd[j++] = ' ';
			continue;
		}
		nex_cmd[j++] = pre_cmd[index];
	}
	nex_cmd[j] = '\0';
	free(*cmd);
	*cmd = nex_cmd;
}
