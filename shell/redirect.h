struct rdr_t{
  int dup_fd;
  int orig_fd;
};

struct rdr_t redirect_std(int file_fd, int std_fd);
/*
  Redirects std_fd, a file descriptor of a standard stream,
  to file_fd and closes file_fd.
  Returns a pointer to a struct rdr_t containing std_fd and its duplicate.
*/

struct rdr_t redirect_out(char* path);
/* 
   Redirects stdout to the file at path
   and returns a struct rdr_t containing STDOUT_FILENO and its duplicate.
*/

struct rdr_t rdro_append(char* path);
// Same as redirect_out, except it appends to the file instead of overwriting.

struct rdr_t redirect_in(char* path);
// Same as redirect_out, except for stdin, not stdout.

struct rdr_t redirect_err(char* path);
// Same as redirect_out, except for stderr, not stdout.

struct rdr_t rdre_append(char* path);
// Same as redirect_err, except it appends to the file instead of overwriting.

void restore(struct rdr_t fds);
// Redirects fds.orig_fd to fds.dup_fd and closes fds.dup_fd.

void pipe_io(int fds[2]);
// Creates a pipe between stdin and stdout.
