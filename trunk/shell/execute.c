#include "execute.h"
#include "parser.h"
#include "prompt.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <libgen.h>

char * const OPERATORS[] = {">", ">>", "<", "2>", "2>>"};
struct rdr_t (* const FUNC_PTRS[])(char *) = {&redirect_out, &rdro_append, &redirect_in, &redirect_err, &rdre_append};

void exec_cmd(char **args, char **cmds){
  exec_helper(args, args, cmds);
}

void exec_helper(char **current_p, char **args, char **cmds){
  if (!*current_p)
    return;

  size_t size = 0;
  struct rdr_t *redirects = NULL;

  char **p;
  size_t i;
  for (p = current_p; *p; p++){
    for (i = 0; i < 5; i++){
      if (!strcmp(*p, OPERATORS[i]) ){
	free(*p);
	*p = NULL;

	redirects = realloc(redirects, (size+1) * sizeof(*redirects) );
	redirects[size++] = (*FUNC_PTRS[i])(*(p+1) );

	free(*(p+1) );
	*(++p) = NULL;
	break;
      }
      else if (!strcmp(*p, "|") ){
	free(*p);
	*p = NULL;

	int fds[2];
	pipe_io(fds);

	p++;
	break;
      }
    }
  }

  // exits if argument is exit
  if (!strcmp(*current_p, "exit") )
    bye(args, cmds, redirects, EXIT_SUCCESS);
  // executes cd
  else if (!strcmp(*current_p, "cd") )
    cd(current_p[1]);
  else
    exec_file(current_p, args, cmds, redirects);

  for (i = 0; i < size; i++)
    restore(redirects[i]);

  free(redirects);

  exec_helper(p, args, cmds);
}

void bye(char **args, char **cmds, struct rdr_t *redirects, int status){
  free_strlist(args);
  free_strlist(cmds);
  free(redirects);
  exit(status);
}

void cd(char *newPath){
  // change the directory manually
  if (!newPath)
    newPath = home();
  if (chdir(newPath) )
    fprintf(stderr, "cd: %s: %s\n", newPath, strerror(errno) );
}

void exec_file(char **current_p, char **args, char **cmds, struct rdr_t *redirects){
  pid_t child_pid = fork();

  if (child_pid == -1)
    fprintf(stderr, "%s: %s\n", args[0], strerror(errno) );

  else if (child_pid > 0){
    int status;
    waitpid(child_pid, &status, 0);
  }

  else{
    char *full_path = args[0];
    args[0] = basename(full_path);

    if (execvp(full_path, args) ){
      fprintf(stderr, "%s: %s\n", full_path, strerror(errno) );
      args[0] = full_path;
      bye(args, cmds, redirects, EXIT_FAILURE);
    }
  }
}
