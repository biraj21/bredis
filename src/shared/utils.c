#include <stdlib.h>

/**
 * this function is meant to be used with
 * `#include <signal.h>`
 * `signal(SIGINT, handle_sigint);`
 *
 *
 * it just calls`exit()` manually so that any cleanup function registerd using
 * `atexit()` can be executed.
 */
void handle_sigint(__attribute__((unused)) int sig) {
  // call exit manually because atexit() registered the cleanup function
  exit(EXIT_SUCCESS);
}
