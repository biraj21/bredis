#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../shared/error_handling.h"

int main(void) {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    die("socket()");
  }

  // bind IPv4 addresses to the socket
  struct sockaddr_in addr = {
      .sin_family = AF_INET,
      .sin_port = ntohs(2111),
      .sin_addr.s_addr = ntohl(INADDR_LOOPBACK), // 127.0.0.1
  };
  if (connect(fd, (const struct sockaddr *)&addr, sizeof(addr))) {
    die("connect");
  }

  char msg[] = "hello";
  write(fd, msg, strlen(msg));

  char rbuf[64];
  ssize_t n = read(fd, rbuf, sizeof(rbuf) - 1);
  if (n < 0) {
    die("read");
  }
  printf("server says: %s\n", rbuf);
  close(fd);

  return EXIT_SUCCESS;
}