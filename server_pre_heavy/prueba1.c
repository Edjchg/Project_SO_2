
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include "fd_shared.h"

int main(int argc, char **argv)
{
  const char *filename = "hola.txt";
  if (argc > 1){
    filename = argv[1];
  }
  if (configure_socket_pair() == -1) return -1;
  int pid = fork();
  if (pid > 0)  // in parent
  {
    printf("Parent at work\n");
    int fd = open(filename, O_RDONLY);
    if (fd < 0){
      printf("Failed to open file %s for reading\n", filename);
      return -1;
    }
    user_send(fd);
  }
  else  // in child
  {
    printf("Child at play\n");
    int fd = user_receive();
    char buffer[256];
    ssize_t nbytes;
    while ((nbytes = read(fd, buffer, sizeof(buffer))) > 0)
        write(1, buffer, nbytes);
    close(fd);
  }
}