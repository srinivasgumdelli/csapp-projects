#include "readline.h"

#include <stdio.h>
#include <limits.h>

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
