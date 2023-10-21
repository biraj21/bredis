
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_handling.h"

void die(const char *msg) {
  if (errno) {
    perror(msg);
  } else {
    fprintf(stderr, "%s\n", msg == NULL ? "something went wrong" : msg);
  }

  exit(EXIT_FAILURE);
}
