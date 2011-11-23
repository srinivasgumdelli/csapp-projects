struct rdr_t{
  int fd;
  int std_fd;
};

struct rdr_t redirect_out(char* path);
/* 
   Redirects stdout to the file at path
   and returns a struct containing a duplicate of STDOUT_FILENO
   and the fd of the file.
*/

struct rdr_t rdro_append(char* path);
// Same as redirect_out, except it appends to the file instead of overwriting.

struct rdr_t redirect_in(char* path);
// Same as redirect_out, except for stdin, not stdout.

struct rdr_t redirect_err(char* path);
// Same as redirect_out, except for stderr, not stdout.

int pipe_io();
// Redirects stdin to stdout and returns a duplicate of STDOUT_FILENO.
