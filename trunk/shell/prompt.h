void print_prompt(); // Prints the prompt in the form user@host:cwd$
char* user(); // Returns the username.
void host(char *buf); // Fills buf with the hostname.
char *cwd();
/*
  Returns the current working directory in terms of ~.
  Must be manually deallocated with free.
*/

char* home(); // Returns the full path of ~.
