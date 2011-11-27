char **separate_cmds(char *ln);
/*
  Returns a list with commands in ln terminated with NULL,
  or returns NULL if no commands were found.
  Must be freed.
*/

char **separate_args(char *cmd);
/*
  Returns a list with arguments in cmd terminated with NULL,
  or returns NULL if no arguments were found.
  Must be freed.
*/

char **split(char *s, char delim);
/*
  Splits s by delim, ignoring empty tokens.
  Returns a list of tokens terminated by NULL,
  or returns NULL if no tokens were found.
  Must be freed.
*/

void free_strlist(char **list);
/*
  Given a manually allocated list of manually allocated strings,
  Frees the entries until the first NULL entry,
  then frees the list itself.
  Does nothing if the list is NULL.
*/
