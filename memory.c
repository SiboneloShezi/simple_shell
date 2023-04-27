
#include "shell.h"

/**
* bfree - frees a pointer and NULLs the address
* @inscription: address of the pointer to free
*
* Return: 1 if freed, otherwise 0.
*/
int bfree(void **inscription)
{
if (inscription && *inscription)
{
free(*inscription);
*inscription = NULL;
return (1);
}
return (0);
}
