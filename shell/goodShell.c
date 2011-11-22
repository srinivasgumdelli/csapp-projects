#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include <errno.h>

#include <fcntl.h>
#include <sys/stat.h>

#include <dirent.h>

#include <sys/wait.h>

#include <limits.h>

#include "shell.h"

int main(){
  // called at the start of shell, manages all other shell commands
  
  printf("\nWelcome to GoodShell!\nTotally not a ripoff of Bash.\n\n");

  chdir("~");

  char input[MAX_INPUT];
  char *cmds[256];
  size_t i;
  for (i = 0; i < 256; i++)
    args[i] = NULL;

  while(1){
    // new line with path for new command
    print_prompt();

    // gets the command line argument
    read_line(input);
  		
    // seperates commands
    separate_args(input, cmds);

    while (*cmds)
      
  
    exec_cmd(args);
  }

  return EXIT_FAILURE;
}

void read_line(char *buffer){
  fgets(buffer, MAX_INPUT, stdin);

  char *last = buffer;
  while (*last){
    if (*last == '\n'){
      *last = '\0';
      break;
    }
    else
      last++;
  }
}

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

void print_prompt(){
  char h[HOST_NAME_MAX];
  host(h);

  char *path = cwd();

  printf("%s@%s:%s$ ", user(), h, path);

  free(path);
}

char *cwd(){
  char *full_path = getcwd(NULL, 0);
  char *path;

  if (strstr(full_path, home() ) ){
    size_t home_len = strlen(home() );
    size_t len = strlen(full_path) - home_len + 1;

    path = (char*)malloc(len + 1);
    path[0] = '~';
    strcpy(path + 1, full_path + home_len);
  }
  else
    path = strdup(full_path);

  free(full_path);
  return path;
}

char *home(){
  return getenv("HOME");
}

void host(char *name){
  gethostname(name, HOST_NAME_MAX);
}

char *user(){
  return getenv("USERNAME");
}

void cd(char *newPath){
  // change the directory manually
  if (!newPath || !strlen(newPath) )
    newPath = home();
  int result = chdir(newPath);
  if (result == -1)
    fprintf(stderr, "cd: %s: %s\n", newPath, strerror(errno) );
}

void separate_args(char *s, char **list){
  split(s, " ", list);
}

void separate_cmds(char *s, char **list){
  split(s, " ; ", list);
}

void clear_strlist(char **list){
  while (*list){
    free(*list);
    *(list++) = NULL;
  }
}

void split(char *s, char *delim, char **list){
  clear_strlist(list);
  while (s)
    *(list++) = strdup(strsep(&s, delim) );
  
  *list = NULL;
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

struct rdr_t redirect_out(char *path){
  struct rdr_t ans;
  umask(0000);
  ans.fd = open(path, O_CREAT | O_TRUNC, 0644);
  ans.std_fd = dup(STDOUT_FILENO);
  dup2(STDOUT_FILENO, ans.fd);
  return ans;
}

struct rdr_t rdro_append(char *path){
  struct rdr_t ans;
  umask(0000);
  ans.fd = open(path, O_CREAT | O_APPEND, 0644);
  ans.std_fd = dup(STDOUT_FILENO);
  dup2(STDOUT_FILENO, ans.fd);
  return ans;
}

struct rdr_t redirect_in(char *path){
  struct rdr_t ans;
  umask(0000);
  ans.fd = open(path, O_CREAT, 0444);
  ans.std_fd = dup(STDIN_FILENO);
  dup2(STDIN_FILENO, ans.fd);
  return ans;
}

struct rdr_t redirect_err(char *path){
  struct rdr_t ans;
  umask(0000);
  ans.fd = open(path, O_CREAT | O_TRUNC, 0644);
  ans.std_fd = dup(STDERR_FILENO);
  dup2(STDERR_FILENO, ans.fd);
  return ans;
}

struct rdr_t rdre_append(char *path){
  struct rdr_t ans;
  umask(0000);
  ans.fd = open(path, O_CREAT | O_APPEND, 0644);
  ans.std_fd = dup(STDERR_FILENO);
  dup2(STDERR_FILENO, ans.fd);
  return ans;
}

int pipe(){
  int out_fd = dup(STDOUT_FILENO);
  dup2(STDOUT_FILENO, STDIN_FILENO);
  return out_fd;
}
