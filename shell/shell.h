#include <stdlib.h>

struct rdr_t{
  int fd;
  int std_fd;
}

int main();

void print_prompt(); // Prints the prompt in the form user@host:cwd$
char* user(); // Returns the username.
void host(char *buf); // Fills buf with the hostname.
char *cwd();
/*
  Returns the current working directory in terms of ~.
  Must be manually deallocated with free.
*/

char* home(); // Returns the full path of ~.

void read_line(char *buffer);
// Reads a line from stdin into buffer, replacing '\n' with '\0'.

void separate_cmds(char* ln, char **list); 
// Fills list with commands in ln terminated with NULL.

void separate_args(char* cmd, char **list);
// Fills list with arguments in cmd terminated with NULL.

void clear_strlist(char **list);
/*
  Given a manually allocated array of strings,
  Frees the entries until the first NULL entry and sets them to NULL.
*/

void split(char* s, char* delim, char **list);
/*
  Extracts tokens separated by delim in s.
  Fills list with the tokens terminated with NULL.
*/

void exec_cmd(char** args);
/*
  Executes arguments from arg[0] to the argument before NULL.
  Redirects or pipes as necessary.
*/

void exec_file(char** args);
/*
  Forks to execute the file at args[0]
  with arguments from filename(args[0]) and args[1]
  to the argument before NULL.
*/

void cd(char* path); // Changes the working directory to the specified path.

struct rdr_t redirect_out(char* path);
/* 
   Redirects stdout to the file at path
   and returns a struct containing a duplicate of STDOUT_FILENO and the fd of the file.
*/

struct rdr_t rdro_append(char* path);
// Same as redirect_out, except it appends to the file instead of overwriting.

struct rdr_t redirect_in(char* path);
// Same as redirect_out, except for stdin, not stdout.

struct rdr_t redirect_err(char* path);
// Same as redirect_out, except for stderr, not stdout.

int pipe();
// Redirects stdin to stdout and returns a duplicate of STDOUT_FILENO.
