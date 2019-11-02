#include <iostream>

#include <stdlib.h>
#include <unistd.h>

int main(void)
{

  int pfds[2];
  pipe(pfds);

  if (!fork()) { // considering ls to be invoked
    close(1); // dont want to write to stdout , so closing
    dup(pfds[1]); // want to redirect output of ls to pfds[1]
    close(0); // no need of stdin 
    execlp("ls", "ls", NULL);
  }
  else {
    close(0);  // need to read from pfds[0] , not stdin , so closing it
    dup(pfds[0]); // making pfds[0] as stdin
    close(pfds[1]);  // not required
    execlp("wc" , "wc", "-l", NULL);
  }
  return(0);
}
