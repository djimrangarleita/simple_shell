#include "main.h"

/**
 * _strlen - Returns the lenght of the string 
 * @str: char pointer to string
 * Return: int representing the length of @str
 */
int _strlen(char *str)
{
	int len = 0;

	while (str && str[len])
		len++;

	return (len);
}

/**
 * _strcat - Concatenate 2 strings
 * @dest: Destination string
 * @src: Source string
 * Return: Pointer to concatenated string
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0, destlen = 0, srclen = 0;

	destlen = _strlen(dest);
	srclen = _strlen(src);
	while (dest[i] != '\0')
		i++;

	for (; i < destlen + srclen; i++)
	{
		dest[i] = src[j];
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - Compare string src and string dest
 * @s1: Left side string
 * @s2: Right side string
 * Return: Left - Right
 */
int _strcmp(char *s1, char *s2)
{
	int i, s1len = 0;

	s1len = _strlen(s1);
	for (i = 0; i <= s1len; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}

	return (0);
}

/**
 * _strcpy - Copy string src to string dest
 * @dest: Where to copy src
 * @src: The string to paste to dest
 * Return: Pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i, srclen = 0;

	srclen = _strlen(src);
	for (i = 0; i < srclen; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * _strdup - Copy a string to a newly allocated space in the mem
 * @str: The string to copy
 * Return: Pointer to the newly allocated space or NULL
 */
char *_strdup(char *str)
{
	int i, size;
	char *ptr;

	if (str == NULL)
		return (NULL);

	i = 0;
	size = _strlen(str);
	ptr = malloc((size + 1) * sizeof(char));

	if (ptr == NULL)
		return (NULL);

	while (i < size)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';

	return (ptr);
}
