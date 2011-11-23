#include "prompt.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void print_prompt(){
  char h[HOST_NAME_MAX];
  host(h);

  char *path = cwd();

  printf("GS:%s@%s:%s$ ", user(), h, path);

  free(path);
}

char *user(){
  return getenv("USERNAME");
}

void host(char *name){
  gethostname(name, HOST_NAME_MAX);
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
