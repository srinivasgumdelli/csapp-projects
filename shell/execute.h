#include "redirect.h"

void exec_cmd(char **args, char **cmds);
/*
  Executes arguments from args[0] to the argument before NULL.
  Redirects of peipes as necessary.
  Needs cmds to free if exiting.
*/

void exec_helper(char **current_p, char **args, char **cmds);
/*
  Executes arguments from current_p[0] to the argument before "|" or NULL.
  Redirects or pipes as necessary.
  Needs args and cmds to free if exiting.
*/

void bye(char **args, char **cmds, struct rdr_t *redirects, int status);
// Frees the elements of args and cmds, frees redirects, and exits with status.

void cd(char *path); // Changes the working directory to the specified path.

void exec_file(char **current_p, char **args, char **cmds, struct rdr_t *redirects);
/*
  Forks to execute the file at current_p[0]
  with arguments from filename(current_p[0]) and current_p[1]
  to the argument before NULL.
  Needs args, cmds, and redirects to free if the child cannot execute the file.
*/

