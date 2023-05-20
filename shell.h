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


/* Command Chaining. */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


/* Convert_Number(). */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


/* Read And Write Buffers. */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Using System getline(). */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - THE  Singly Linked List.
 * @num: A num Field.
 * @str: THE String.
 * @next:THE Points For A  Next Node.
 */
typedef struct liststr
{
	char *str;
	struct liststr *next;
	int num;
} list_t;


/**
 *struct passinfo - THE Contains Pseudo Arguements To Pass into function.
 *@err_num: AN Error Code.
 *@linecount_flag: IF On THE Count This Line Of THE input.
 *@fname: A Program Filename.
 *@env: THE Linked List Local Copy OF environ.
 *@environ: THE Custom Modified Copy OF environ.
 *@history: A History Node.
 *@arg: THE Str Generate From getline Containing arg.
 *@argv: THE arr Of Str Generate From arg.
 *@line_count: The Error Count.
 *@path: THE Str Path For Current Command.
 *@argc: AN arg Count.
 *@alias: AN alias Node.
 *@env_changed: That If environ Changed.
 *@cmd_buf_type:THE CMD_type ||, &&, ;.
 *@readfd: AN fd From Which TO Read Line.
 *@histcount: A History Line num Count.
 *@status: A Return Status OF Last Command.
 *@cmd_buf:AN Address Of Pointer TO cmd_buf.
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
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;

} info_t;


#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}



/**
 *struct builtin - They Contain THE Builtin Str AND  Related Functions.
 *@type: A Builtin Command Flag.
 *@func: A Function.
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_t;



/* a_toi.c */
int _atoi(char *);
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);


/* built_in.c */
int _mycd(info_t *);
int _myhelp(info_t *);
int _myexit(info_t *);

/* env_iron.c */
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);


/* built_in1.c */
int _myalias(info_t *);
int _myhistory(info_t *);


/* ex_its.c */
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);


/* get_env.c */
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);


/* error_s1.c */
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _erratoi(char *);
void print_error(info_t *, char *);


/* get_info.c */
void set_info(info_t *, char **);
void free_info(info_t *, int);
void clear_info(info_t *);


/* his_tory.c */
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
char *get_history_file(info_t *info);


/* error_s.c */
int _putfd(char c, int fd);
int _eputchar(char);
int _putsfd(char *str, int fd);
void _eputs(char *);


/* get_line.c */
void sigintHandler(int);
int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);


/* list_s.c */
void free_list(list_t **);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
list_t *add_node_end(list_t **, const char *, int);
list_t *add_node(list_t **, const char *, int);


/* mem_ory.c */
int bfree(void **);


/* list_s1.c */
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
list_t *node_starts_with(list_t *, char *, char);
size_t list_len(const list_t *);


/* var_s.c */
int replace_alias(info_t *);
int replace_vars(info_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_string(char **, char *);
int is_chain(info_t *, char *, size_t *);


/* shell_loo_p.c */
void fork_cmd(info_t *);
int find_builtin(info_t *);
void find_cmd(info_t *);
int hsh(info_t *, char **);


/* strin_g1.c */
void _puts(char *);
int _putchar(char);
char *_strdup(const char *);
char *_strcpy(char *, char *);


/* token_izer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);


/* strin_g.c */
char *starts_with(const char *, const char *);
int _strlen(char *);
char *_strcat(char *, char *);
int _strcmp(char *, char *);


/* pars_er.c */
char *find_path(info_t *, char *, char *);
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);


/* real_loc.c */
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);
void ffree(char **);


/* main.c */
int main(int ac, char **av);

#endif
