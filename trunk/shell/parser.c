#include "parser.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char **separate_cmds(char *s){
  return split(s, ';');
}

char **separate_args(char *s){
  return split(s, ' ');
}

char **split(char *s, char delim){
  char **list = NULL;
  char *token;
  char delim_str[] = {delim, '\0'};
  size_t i = 0;

  while (s){
    token = strsep(&s, delim_str);
    if (strlen(token) ){
      list = realloc(list, (i+2) * sizeof(*list) );
      list[i++] = strdup(token);
    }
  }
  
  if (list)
    list[i] = NULL;
  
  return list;
}

void free_strlist(char **list){
  if (list){
    char **str_p;
    for (str_p = list; *str_p; str_p++)
      free(*str_p);
    free(list);
  }
}
