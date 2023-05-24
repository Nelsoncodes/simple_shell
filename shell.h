#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shell_loop.c */
int hssh(info_t *, char **);
int finds_builtin(info_t *);
void finds_cmd(info_t *);
void forks_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *finds_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlens(char *);
int _strcmps(schar *, char *);
char *starts_with(const char *, const char *);
char *_strcats(char *, char *);

/* toem_string1.c */
char *_strcpys(char *, char *);
char *_strdups(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpys(char *, char *, int);
char *_strncats(char *, char *, int);
char *_strchrs(char *, char);

/* toem_tokenizer.c */
char **strstows(char *, char *);
char **strstows2(char *, char);

/* toem_realloc.c */
char *_memsets(char *, char, unsigned int);
void ffrees(char **);
void *_reallocs(void *, unsigned int, unsigned int);

/* toem_memory.c */
int cfree(void **);

/* toem_atoi.c */
int interactive(info_t *);
int is_delit(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratois(char *);
void print_errors(info_t *, char *);
int prints_d(int, int);
char *convert_numbers(long int, int, int);
void removes_comments(char *);

/* toem_builtin.c */
int _theexit(info_t *);
int _thecd(info_t *);
int _thehelp(info_t *);

/* toem_builtin1.c */
int _thehistory(info_t *);
int unsets_alias(info_t *info, char *str)
int sets_alias(info_t *info, char *str)
int prints_alias(list_t *node);
int _thealias(info_t *);

/*toem_getline.c */
ssize_t inputs_buf(info_t *info, char **buf, size_t *len)
ssize_t get_inputs(info_t *info);
ssize_t reads_buf(info_t *info, char *buf, size_t *i)
int _getlines(info_t *, char **, size_t *);
void sigintHandlers(int);

/* toem_getinfo.c */
void clears_info(info_t *);
void sets_info(info_t *, char **);
void frees_info(info_t *, int);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _theenv(info_t *);
int _thesetenv(info_t *);
int _theunsetenv(info_t *);
int populates_env_list(info_t *);

/* toem_getenv.c */
char **gets_environ(info_t *);
int _unsetenvs(info_t *, char *);
int _setenvs(info_t *, char *, char *);

/* toem_history.c */
char *gets_history_file(info_t *info);
int writes_history(info_t *info);
int reads_history(info_t *info);
int builds_history_list(info_t *info, char *buf, int linecount);
int renumbers_history(info_t *info);

/* toem_lists.c */
list_t *adds_node(list_t **, const char *, int);
list_t *adds_node_end(list_t **, const char *, int);
size_t prints_list_str(const list_t *);
int deletes_node_at_index(list_t **, unsigned int);
void free_lists(list_t **);

/* toem_lists1.c */
size_t lists_len(const list_t *);
char **lists_to_strings(list_t *);
size_t prints_list(const list_t *);
list_t *nodes_starts_with(list_t *, char *, char);
ssize_t gets_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chains(info_t *, char *, size_t *);
void checks_chain(info_t *, char *, size_t *, size_t, size_t);
int replaces_alias(info_t *);
int replaces_vars(info_t *);
int replaces_string(char **, char *);

#endif
