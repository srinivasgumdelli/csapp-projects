void exec_cmd(char** args);
/*
  Executes arguments from arg[0] to the argument before NULL.
  Redirects or pipes as necessary.
*/

void exec_file(char** args);
/*
  Forks to execute the file at args[0]
  with arguments from filename(args[0]) and args[1]
  to the argument before NULL.
*/

void cd(char* path); // Changes the working directory to the specified path.
