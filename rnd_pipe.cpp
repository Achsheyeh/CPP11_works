#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(void) {

  int pfds[2];
  char buf[30];
  pipe(pfds);

  if(!fork()) {
     cout << "child writing to pipe" << endl;
     write(pfds[1], "test", 5);
     cout << "child exiting" << endl;
     exit(0);
  } else {
     cout << "parent reading from pipe" << endl;
     read(pfds[0], buf, 5);
     cout << "parent got data from child as " << buf << endl;
     wait(NULL);
  }
     return(0);
}
