#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_MAX 256

int main(){
  umask(0000);

  int r, g, b, i, j;

  int xres = 255;
  int yres = 255;
  int maxc = 255;

  int fd = open("MAGIC.ppm", O_CREAT | O_EXCL | O_WRONLY, 0644);

  char line[BUFFER_MAX];
  sprintf(line, "P3\n%d %d %d\n", xres, yres, maxc);

  write(fd, line, sizeof(line));

  for (i = 0; i < xres; i++){
    for (j = 0; j < yres; j++){
      r = 0;
      g = 0;
      b = 255;
      sprintf(line, "%d %d %d\n", r, g, b);
      write(fd, line, sizeof(line));
    }
  }

  close(fd);
}
