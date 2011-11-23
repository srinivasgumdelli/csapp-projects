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
  if(!strcmp(args[0], "exit") )
    bye(args, cmds, EXIT_SUCCESS);
  // executes cd
  else if(!strcmp(args[0], "cd") )
    cd(args[1]);
  else if (strlen(args[0]) )
    exec_file(args, cmds);
}

void bye(char **args, char **cmds, int status){
  clear_strlist(args);
  clear_strlist(cmds);
  exit(status);
}

void cd(char *newPath){
  // change the directory manually
  if (!newPath || !strlen(newPath) )
    newPath = home();
  if (chdir(newPath) )
    fprintf(stderr, "cd: %s: %s\n", newPath, strerror(errno) );
}

void exec_file(char **args, char **cmds){
  pid_t child_pid = fork();

  if(child_pid){
    int status;
    waitpid(child_pid, &status, 0);
  }
  else{
    char *full_path = args[0];
    args[0] = basename(full_path);
    if (execvp(full_path, args) ){
      fprintf(stderr, "%s: %s\n", full_path, strerror(errno) );
      free(full_path);
      bye(args + 1, cmds, EXIT_FAILURE);
    }
  }
}
