#include "execute.h"
#include "parser.h"
#include "prompt.h"
#include "redirect.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <libgen.h>

void exec_cmd(char **args, char **cmds){
  // exits if argument is exit
  if (!strcmp(args[0], "exit") )
    bye(args, cmds, EXIT_SUCCESS);
  // executes cd
  else if (!strcmp(args[0], "cd") )
    cd(args[1]);
  else
    exec_file(args, cmds);
}

void bye(char **args, char **cmds, int status){
  free_strlist(args);
  free_strlist(cmds);
  exit(status);
}

void cd(char *newPath){
  // change the directory manually
  if (!newPath)
    newPath = home();
  if (chdir(newPath) )
    fprintf(stderr, "cd: %s: %s\n", newPath, strerror(errno) );
}

void exec_file(char **args, char **cmds){
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
      bye(args, cmds, EXIT_FAILURE);
    }
  }
}
