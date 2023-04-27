#include "shell.h"

/**
* get_history_file - gets the history file
* @info: parameter struct
*
* Return: allocated string containg history file
*/

char *get_history_file(info_t *info)
{
char *cushion, *folder;

folder = _getenv(info, "HOME=");
if (!folder)
return (NULL);
cushion = malloc(sizeof(char) * (_strlen(folder) + _strlen(HIST_FILE) + 2));
if (!cushion)
return (NULL);
cushion[0] = 0;
_strcpy(cushion, folder);
_strcat(cushion, "/");
_strcat(cushion, HIST_FILE);
return (cushion);
}

/**
* write_history - creates a file, or appends to an existing file
* @info: the parameter struct
*
* Return: 1 on success, else -1
*/
int write_history(info_t *info)
{
ssize_t ab;
char *filename = get_history_file(info);
list_t *node = NULL;

if (!filename)
return (-1);

ab = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (ab == -1)
return (-1);
for (node = info->history; node; node = node->next)
{
_putsfd(node->str, ab);
_putab('\n', ab);
}
_putab(BUF_FLUSH, ab);
close(ab);
return (1);
}

/**
* read_history - reads history from file
* @info: the parameter struct
*
* Return: histcount on success, 0 otherwise
*/
int read_history(info_t *info)
{
int a, last = 0, linecount = 0;
ssize_t ab, rdlen, fsize = 0;
struct stat st;
char *cushion = NULL, *filename = get_history_file(info);

if (!filename)
return (0);

ab = open(filename, O_RDONLY);
free(filename);
if (ab == -1)
return (0);
if (!fstat(ab, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
cushion = malloc(sizeof(char) * (fsize + 1));
if (!cushion)
return (0);
rdlen = read(ab, cushion, fsize);
cushion[fsize] = 0;
if (rdlen <= 0)
return (free(cushion), 0);
close(ab);
for (a = 0; a < fsize; a++)
if (cushion[a] == '\n')
{
cushion[a] = 0;
build_history_list(info, cushion + last, linecount++);
last = a + 1;
}
if (last != a)
build_history_list(info, cushion + last, linecount++);
free(cushion);
info->histcount = linecount;
while (info->histcount-- >= HIST_MAX)
delete_node_at_index(&(info->history), 0);
renumber_history(info);
return (info->histcount);
}

/**
* build_history_list - adds entry to a history linked list
* @info: Structure containing potential arguments. Used to maintain
* @cushion: buffer
* @linecount: the history linecount, histcount
*
* Return: Always 0
*/
int build_history_list(info_t *info, char *cushion, int linecount)
{
list_t *node = NULL;

if (info->history)
node = info->history;
add_node_end(&node, cushion, linecount);

if (!info->history)
info->history = node;
return (0);
}

/**
* renumber_history - renumbers the history linked list after changes
* @info: Structure containing potential arguments. Used to maintain
*
* Return: the new histcount
*/
int renumber_history(info_t *info)
{
list_t *node = info->history;
int a = 0;

while (node)
{
node->num = a++;
node = node->next;
}
return (info->histcount = a);
}
