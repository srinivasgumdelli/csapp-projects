#include "parser.h"

#include <string.h>
#include <stdlib.h>

void separate_cmds(char *s, char **list){
  clear_strlist(list);
  char *token, *delim;
  while (s){
    token = s;
    delim = strstr(s, " ; ");
    if (delim){
      *delim = '\0';
      s = delim + 3;
    }
    else
      s = NULL;
    *(list++) = strdup(token);
  }

  *list = NULL;
}

void separate_args(char *s, char **list){
  clear_strlist(list);
  while (s)
    *(list++) = strdup(strsep(&s, " ") );
  
  *list = NULL;

}

void clear_strlist(char **list){
  while (*list){
    free(*list);
    *(list++) = NULL;
  }
}
