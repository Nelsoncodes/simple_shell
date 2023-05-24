#include "shell.h"

/**
 * _strncpy - Copies a string
 * @dest: The destination string to be copied to
 * @src: The source string
 * @n: The number of characters to be copied
 *
 * Return: The concatenated string
 */
char *_strncpy(char *dest, const char *src, int n)
{
int i;

for (i = 0; i < n && src[i] != '\0'; i++)
dest[i] = src[i];

for (; i < n; i++)
dest[i] = '\0';

(return dest);
}

/**
 * _strncat - Concatenates two strings
 * @dest: The first string
 * @src: The second string
 * @n: The maximum number of bytes to be used
 *
 * Return: The concatenated string
 */
char *_strncat(char *dest, const char *src, int n)
{
int dest_len = 0;
int i;

while (dest[dest_len] != '\0')
dest_len++;

for (i = 0; i < n && src[i] != '\0'; i++)
dest[dest_len++] = src[i];

dest[dest_len] = '\0';

(return dest);
}

/**
 * _strchr - Locates a character in a string
 * @s: The string to be parsed
 * @c: The character to look for
 *
 * Return: A pointer to the first occurrence of the character in the string
 *         or NULL if the character is not found
 */
char *_strchr(const char *s, char c)
{
while (*s != '\0')
{
if (*s == c)
(return (char *)s);
s++;
}

if (*s == c)
(return (char *)s);

(return NULL);
}
