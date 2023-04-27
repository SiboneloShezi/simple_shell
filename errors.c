#include "shell.h"

/**
* _eputs - prints an input string
* @str: the string to be printed
*
* Return: Nothing
*/
void _eputs(char *str)
{
int a = 0;

if (!str)
return;
while (str[a] != '\0')
{
_eputchar(str[a]);
a++;
}
}

/**
* _eputchar - writes the character c to stderr
* @c: The character to print
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _eputchar(char c)
{
static int a;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
{
write(2, buf, a);
a = 0;
}
if (c != BUF_FLUSH)
buf[a++] = c;
return (1);
}

/**
* _putab - writes the character c to given ab
* @c: The character to print
* @ab: The filedescriptor to write to
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _putab(char c, int ab)
{
static int a;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
{
write(ab, buf, a);
a = 0;
}
if (c != BUF_FLUSH)
buf[a++] = c;
return (1);
}

/**
* _putsab - prints an input string
* @str: the string to be printed
* @ab: the filedescriptor to write to
*
* Return: the number of chars put
*/
int _putsab(char *str, int ab)
{
int a = 0;

if (!str)
return (0);
while (*str)
{
a += _putab(*str++, ab);
}
return (a);
}
