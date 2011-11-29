#include "redirect.h"

void exec_cmd(char **args, char **cmds);
/*
  Executes arguments from args[0] to the argument before NULL.
  Redirects or pipes as necessary.
  Needs cmds to free if exiting.
*/

void bye(char **args, char **cmds, struct rdr_t *redirects, int status);
// Frees the elements of args and cmds, frees redirects, and exits with status.

void cd(char *path); // Changes the working directory to the specified path.

void exec_file(char **args, char **cmds, struct rdr_t *redirects);
/*
  Forks to execute the file at args[0]
  with arguments from filename(args[0]) and args[1]
  to the argument before NULL.
  Needs cmds and redirects to free if the child cannot execute the file.
*/

