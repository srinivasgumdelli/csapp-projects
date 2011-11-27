#include "readline.h"

#include <stdio.h>
#include <limits.h>

void read_line(char *buffer){
  fgets(buffer, MAX_INPUT, stdin);

  char *char_p;
  for (char_p = buffer; *char_p; char_p++)
    if (*char_p == '\n'){
      *char_p = '\0';
      return;
    }
}
