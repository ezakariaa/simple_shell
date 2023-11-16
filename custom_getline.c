#include "shell.h"

void *custom_realloc(void *buff, unsigned int first_s, unsigned int second_s);
void set_buff(char **buff_ptr, size_t *buff_size, char *str_buff, size_t bytes_buff);
ssize_t custom_getline(char **buff_ptr, size_t *buff_size, FILE *stream);

/**
* custom_realloc - Reallocates the mem.
* @buff: mem allocated.
* @first_s: Alocated spaces's size.
* @second_s: Mem blocked's size.
*
* Return: A pointer to the buff.
*/
void *custom_realloc(void *buff, unsigned int first_s, unsigned int second_s)
{
	unsigned int i;
	void *all_mem;
	char *new_p, *f;

	if (second_s == first_s)
		return (buff);

	if (buff == NULL)
	{
		all_mem = malloc(second_s);
		if (all_mem == NULL)
			return (NULL);
		return (all_mem);
	}

	if (second_s == 0 && buff != NULL)
	{
		free(buff);
			return (NULL);
	}

	new_p = buff;
	all_mem = malloc(sizeof(*new_p) * second_s);
	if (all_mem == NULL)
	{
		free(buff);
		return (NULL);
	}

	f = all_mem;

	for (i = 0; i < first_s && i < second_s; i++)
		f[i] = *new_p++;

	free(buff);
	return (all_mem);
}

/**
* set_buff - Sets the line to the buffer.
* @buff_ptr: Pointer the buffer.
* @buff_size: Buffer's size.
* @str_buff: The buffer string.
* @bytes_buff: The number of bytes in the buffer.
*/
void set_buff(char **buff_ptr, size_t *buff_size, char *str_buff, size_t bytes_buff)
{
	if (*buff_ptr == NULL)
	{
		if (bytes_buff > 120)
			*buff_size = bytes_buff;
		else
			*buff_size = 120;
		*buff_ptr = str_buff;
		}
		else if (*buff_size < bytes_buff)
		{
			if (bytes_buff > 120)
				*buff_size = bytes_buff;
			else
				*buff_size = 120;
			*buff_ptr = str_buff;
		}
		else
		{
			_str_cpy(*buff_ptr, str_buff);
			free(str_buff);
		}
}

/**
* custom_getline - Gets the line from the uses's input.
* @buff_ptr: A pointer to the buff.
* @buff_size: buff_str size.
* @stream: Stream to read from.
*
* Return: The bytes have been read.
*/
ssize_t custom_getline(char **buff_ptr, size_t *buff_size, FILE *stream)
{
	static ssize_t input;
	int fr;
	char l = 'x', *str_buff;
	ssize_t bytes_r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	str_buff = malloc(sizeof(char) * 120);
	if (!str_buff)
		return (-1);

	while (l != '\n')
	{
		fr = read(STDIN_FILENO, &l, 1);
		if (fr == -1 || (fr == 0 && input == 0))
		{
			free(str_buff);
			return (-1);
		}
		if (fr == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			str_buff = custom_realloc(str_buff, input, input + 1);

		str_buff[input] = l;
		input++;
	}

	str_buff[input] = '\0';

	set_buff(buff_ptr, buff_size, str_buff, input);

	bytes_r = input;
	if (fr != 0)
		input = 0;
	return (bytes_r);
}
