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

  chdir(home() );

  char input[MAX_INPUT];
  char **cmds, **cmd_p, **args;

  while(1){
    // new line with path for new command
    print_prompt();

    // gets the command line argument
    read_line(input);

    // seperates commands
    cmds = separate_cmds(input);
    if (cmds){
      for (cmd_p = cmds; *cmd_p; cmd_p++){
    		args = separate_args(*cmd_p);
    		if (args){
      		exec_cmd(args, cmds);
      		free_strlist(args);
    		}
      }
      free_strlist(cmds);
    }
  }

  return EXIT_FAILURE;
}
