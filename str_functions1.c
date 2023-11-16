#include "shell.h"

/**
 * _str_length - Gets the length of a string.
 * @str: Pointer to the string.
 *
 * Return: The length of the string.
 */
int _str_length(const char *str)
{
	int len = 0;

	if (!str)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

/**
 * _str_cat - Concantenates two strings.
 * @dest_str: Pointer to destination str.
 * @src_str: Pointer to source str.
 *
 * Return: Pointer to the dest string.
 */
char *_str_cat(char *dest_str, const char *src_str)
{
	const char *temp_src;
	char *temp_dest;

	temp_dest = dest_str;
	temp_src = src_str;
	while (*temp_dest != '\0')
		temp_dest++;
	while (*temp_src != '\0')
		*temp_dest++ = *temp_src++;

	*temp_dest = '\0';
	return (dest_str);
}

/**
 * _str_cmp - Compares two strings.
 * @str1: The first str.
 * @str2: The second str.
 *
 * Return: Zero if str1 = str2,
 * positive int if str1 > str2,
 * negative int if str1 < str2.
 */
int _str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (*str1 != *str2)
		return (*str1 - *str2);
	return (0);
}

/**
 * _str_chr - Looks for a character in a string.
 * @str: the string to look for.
 * @character: the character to look for.
 *
 * Return: A pointer to the first occurence - if character is found.
 * NULL - f character is not found.
 */
char *_str_chr(char *str, char character)
{
	do {
		if (*str == character)
			return (str);
	} while (*str++ != '\0');
	return (NULL);
}
