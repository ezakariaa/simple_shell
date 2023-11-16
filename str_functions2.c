#include "shell.h"

/**
 * _str_n_cat - Concantenates two strings.
 * @dest_str: Destination string.
 * @src_str: Source string.
 * @num: number of bytes to copy from src.
 *
 * Return: The destination string.
 */
char *_str_n_cat(char *dest_str, const char *src_str, size_t num)
{
	size_t dest_length = _str_length(dest_str);
	size_t index;

	for (index = 0; index < num && src_str[index] != '\0'; index++)
		dest_str[dest_length + index] = src_str[index];
	dest_str[dest_length + index] = '\0';

	return (dest_str);
}

/**
 * _str_cpy - Copies the string (src) to the destination (des).
 * @dest_str: The str destination.
 * @src_str: The str source/
 *
 * Return: Pointer to dest.
 */
char *_str_cpy(char *dest_str, const char *src_str)
{
	size_t index;

	for (index = 0; src_str[index] != '\0'; index++)
		dest_str[index] = src_str[index];
	dest_str[index] = '\0';
	return (dest_str);
}

/**
 * _str_n_cmp - Compares two strings.
 * @str1: The first a string.
 * @str2: The second string.
 * @num: The number of bytes.
 *
 * Return: 0 if str1 and str2 match.
 * Greater than 0 if str1 is longer than str2.
 * Less than 0 if str1 is shorter than str2.
 */
int _str_n_cmp(const char *str1, const char *str2, size_t num)
{
	size_t index;

	for (index = 0; str1[index] && str2[index] && index < num; index++)
	{
		if (str1[index] > str2[index])
			return (str1[index] - str2[index]);
		else if (str1[index] < str2[index])
			return (str1[index] - str2[index]);
	}
	if (index == num)
		return (0);
	else
		return (-15);
}

/**
 * _str_spn - Returns the length of a substring.
 * @str: The str to look for.
 * @pref: The prefix of substring
 *
 * Return: Num of bytes
 */
int _str_spn(char *str, char *pref)
{
	int i, num_bytes = 0;

	while (*str)
	{
		for (i = 0; pref[i]; i++)
		{
			if (*str == pref[i])
			{
				num_bytes++;
				break;
			}
		}
		str++;
	}
	return (num_bytes);
}
