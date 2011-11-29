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

void exec_cmd(char **args, char **cmds){
  size_t size = 0;
  struct rdr_t *redirects = NULL;

  char *operators[] = {">", ">>", "<", "2>", "2>>"};
  struct rdr_t (*function[])(char *)
    = {&redirect_out, &rdro_append, &redirect_in,
       &redirect_err, &rdre_append};

  char **p;
  size_t i;
  for (p = args; *p; p++){
    for (i = 0; i < 5; i++)
      if (!strcmp(*p, operators[i]) ){
	free(*p);
	*p = NULL;

	redirects = realloc(redirects, (size+1) * sizeof(*redirects) );
	redirects[size++] = (*function[i])(*(p+1) );

	free(*(p+1) );
	*(++p) = NULL;
	break;
      }
  }

  // exits if argument is exit
  if (!strcmp(args[0], "exit") )
    bye(args, cmds, redirects, EXIT_SUCCESS);
  // executes cd
  else if (!strcmp(args[0], "cd") )
    cd(args[1]);
  else
    exec_file(args, cmds, redirects);

  for (i = 0; i < size; i++)
    restore(redirects[i]);

  free(redirects);
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

void exec_file(char **args, char **cmds, struct rdr_t *redirects){
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
