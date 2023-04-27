#include "shell.h"

/**
* reciprocal - returns true if shell is reciprocal mode
* @info: struct address
*
* Return: 1 if reciprocal mode, 0 otherwise
*/
int reciprocal(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* is_sep - checks if character is a separator
* @c: the char to check
* @sep: the separator string
* Return: 1 if true, 0 if false
*/
int is_sep(char c, char *sep)
{
while (*sep)
if (*sep++ == c)
return (1);
return (0);
}

/**
* _isalpha - checks for alphabetic character
* @d: The character to input
* Return: 1 if c is alphabetic, 0 otherwise
*/

int _isalpha(int d)
{
if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z'))
return (1);
else
return (0);
}

/**
* _atoi - converts a string to an integer
* @b: the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
*/

int _atoi(char *b)
{
int e, indication = 1, banner = 0, yield;
unsigned int result = 0;

for (e = 0; b[e] != '\0' && banner != 2; e++)
{
if (b[e] == '-')
indication *= -1;

if (b[e] >= '0' && b[e] <= '9')
{
banner = 1;
result *= 10;
result += (b[e] - '0');
}
else if (banner == 1)
banner  = 2;
}

if (indication == -1)
yield = -result;
else
yield = result;

return (yield);
}
