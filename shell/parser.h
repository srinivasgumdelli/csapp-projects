void separate_cmds(char* ln, char **list); 
// Fills list with commands in ln terminated with NULL.

void separate_args(char* cmd, char **list);
// Fills list with arguments in cmd terminated with NULL.

void clear_strlist(char **list);
/*
  Given a manually allocated array of strings,
  Frees the entries until the first NULL entry and sets them to NULL.
*/
