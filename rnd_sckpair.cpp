#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

int main() {
  int sv[2];
  char buf;
  
  if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
    perror("socketpair");
    exit(1);
  }
  
  if (!fork()) {
    read(sv[1], &buf, 1);
    cout << "child: read " << buf << endl;
    buf = toupper(buf);
    write(sv[1], &buf, 1);
    cout << "child: send " << buf << endl;
  }else{
    write(sv[0], "b", 1);
    cout << "parent : send 'b'"  << endl;
    read(sv[0], &buf, 1);
    cout << "parent: read " << buf << endl;
    wait(NULL);
  }
  return(0);
}
