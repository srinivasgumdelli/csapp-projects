#include "redirect.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>

struct rdr_t redirect_std(int file_fd, int std_fd){
  struct rdr_t fds;
  fds.dup_fd = dup(std_fd);
  fds.orig_fd = dup2(file_fd, std_fd);
  close(file_fd);
  return fds;
}

struct rdr_t redirect_out(char *path){
  umask(0000);
  int fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
  return redirect_std(fd, STDOUT_FILENO);
}

struct rdr_t rdro_append(char *path){
  umask(0000);
  int fd = open(path, O_CREAT | O_APPEND | O_WRONLY, 0644);
  return redirect_std(fd, STDOUT_FILENO);
}

struct rdr_t redirect_in(char *path){
  int fd = open(path, O_RDONLY);
  return redirect_std(fd, STDIN_FILENO);
}

struct rdr_t redirect_err(char *path){
  umask(0000);
  int fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
  return redirect_std(fd, STDERR_FILENO);
}

struct rdr_t rdre_append(char *path){
  umask(0000);
  int fd = open(path, O_CREAT | O_APPEND | O_WRONLY, 0644);
  return redirect_std(fd, STDERR_FILENO);
}

void restore(struct rdr_t fds){
  close(fds.orig_fd);
  dup2(fds.dup_fd, fds.orig_fd);
}
