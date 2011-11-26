#include "parser.h"

#include <string.h>
#include <stdlib.h>

void separate_cmds(char *s, char **list){
  split(s, ';', list);
}

void separate_args(char *s, char **list){
  split(s, ' ', list);
}

void split(char *s, char delim, char **list){
  clear_strlist(list);
  char *token;
  char delim_str[] = {delim, '\0'};
  while (s){
    token = strsep(&s, delim_str);
    if (strlen(token) )
      *(list++) = strdup(token);
  }
  
  *list = NULL;

}

void clear_strlist(char **list){
  while (*list){
    free(*list);
    *(list++) = NULL;
  }
}
