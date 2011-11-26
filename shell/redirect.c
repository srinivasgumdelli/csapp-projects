#include "redirect.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct rdr_t redirect_out(char *path){
  struct rdr_t ans;
  umask(0000);
  ans.fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
  ans.std_fd = dup(STDOUT_FILENO);
  dup2(STDOUT_FILENO, ans.fd);
  return ans;
}

struct rdr_t rdro_append(char *path){
  struct rdr_t ans;
  umask(0000);
  ans.fd = open(path, O_CREAT | O_APPEND | O_WRONLY, 0644);
  ans.std_fd = dup(STDOUT_FILENO);
  dup2(STDOUT_FILENO, ans.fd);
  return ans;
}

struct rdr_t redirect_in(char *path){
  struct rdr_t ans;
  ans.fd = open(path, O_RDONLY);
  ans.std_fd = dup(STDIN_FILENO);
  dup2(STDIN_FILENO, ans.fd);
  return ans;
}

struct rdr_t redirect_err(char *path){
  struct rdr_t ans;
  umask(0000);
  ans.fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
  ans.std_fd = dup(STDERR_FILENO);
  dup2(STDERR_FILENO, ans.fd);
  return ans;
}

struct rdr_t rdre_append(char *path){
  struct rdr_t ans;
  umask(0000);
  ans.fd = open(path, O_CREAT | O_APPEND | O_WRONLY, 0644);
  ans.std_fd = dup(STDERR_FILENO);
  dup2(STDERR_FILENO, ans.fd);
  return ans;
}

int pipe_io(){
  int out_fd = dup(STDOUT_FILENO);
  dup2(STDOUT_FILENO, STDIN_FILENO);
  return out_fd;
}
