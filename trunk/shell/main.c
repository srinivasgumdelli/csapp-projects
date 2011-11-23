#include "prompt.h"
#include "readline.h"
#include "parser.h"
#include "execute.h"

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

int main(){
  // called at the start of shell, manages all other shell commands
  
  printf("\nWelcome to GoodShell!\nTotally not a ripoff of Bash.\n\n");

  chdir("~");

  char input[MAX_INPUT];
  char *cmds[256], *args[256];
  size_t i;
  for (i = 0; i < 256; i++)
    cmds[i] = args[i] = NULL;

  while(1){
    // new line with path for new command
    print_prompt();

    // gets the command line argument
    read_line(input);
  		
    // seperates commands
    separate_cmds(input, cmds);

    char **cmd_p = cmds;
    while (*cmd_p){
      separate_args(*(cmd_p++), args);
      exec_cmd(args);
    }
  
  }

  return EXIT_FAILURE;
}
