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

void exec_cmd(char **args){
  // exits if argument is exit
  if(!strcmp(args[0], "exit") ){
    clear_strlist(args);
    exit(EXIT_SUCCESS);
  }
  // executes cd
  else if(!strcmp(args[0], "cd") )
    cd(args[1]);
  else if (strlen(args[0]) )
    exec_file(args);
}

void cd(char *newPath){
  // change the directory manually
  if (!newPath || !strlen(newPath) )
    newPath = home();
  int result = chdir(newPath);
  if (result == -1)
    fprintf(stderr, "cd: %s: %s\n", newPath, strerror(errno) );
}

void exec_file(char **args){
  pid_t child_pid = fork();

  if(child_pid){
    int status;
    waitpid(child_pid, &status, 0);
  }
  else{
    char *full_path = args[0];
    args[0] = basename(args[0]);
    if (execvp(full_path, args) ){
      fprintf(stderr, "%s: %s\n", args[0], strerror(errno) );
      free(full_path);
      clear_strlist(args + 1);
      exit(EXIT_FAILURE);
    }
  }
}
