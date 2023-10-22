#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../shared/config.h"
#include "../shared/error_handling.h"

static void do_something(int connfd);

int main(void) {
  // create a new socket & get fd
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    die("socket()");
  }

  // configure options for the socket
  int optval = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
    die("setsockopt()");
  }

  // bind IPv4 addresses to the socket
  struct sockaddr_in addr = {
      .sin_family = AF_INET,
      .sin_port = ntohs(PORT),
      .sin_addr.s_addr = ntohl(0), // wildcard address 0.0.0.0
  };
  if (bind(fd, (const struct sockaddr *)&addr, sizeof(addr))) {
    die("bind()");
  }

  // listen for connections
  if (listen(fd, SOMAXCONN)) {
    die("listen()");
  }

  while (true) {
    // accept
    struct sockaddr_in client_addr;
    socklen_t socklen = sizeof(client_addr);
    int connfd = accept(fd, (struct sockaddr *)&client_addr, &socklen);
    if (connfd < 0) {
      continue; // error
    }

    do_something(connfd);
    close(connfd);
  }

  return EXIT_SUCCESS;
}

static void do_something(int connfd) {
  char rbuf[64];
  ssize_t n = read(connfd, rbuf, sizeof(rbuf) - 1);
  if (n < 0) {
    puts("read() error");
    return;
  }
  printf("client says: %s\n", rbuf);

  char wbuf[] = "world";
  write(connfd, wbuf, strlen(wbuf));
}