#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
using namespace std;

int main(int argc, char** argv){

  int fd, offset;
  char *data;
  struct stat sbuf;
 
  if (argc != 2) {
    cerr << "usage rnd_mmap offset " << endl;
    exit(1);
  }
 
  if ((fd = open("rnd_mmap.cpp", O_RDONLY)) == -1) {
    perror("open");
    exit(1);  
  } 
  if (stat("rnd_mmap.cpp", &sbuf) == -1) {
    perror("stat");
    exit(1);
  }
  offset = atoi(argv[1]);
  if (offset < 0 || offset > sbuf.st_size -1) {
    cerr << "rnd_mmap: offset must be in range 0 - " << (sbuf.st_size - 1) << endl; 
    exit(1);
  }
  
  data = static_cast<char *>(mmap((caddr_t)0, sbuf.st_size ,PROT_READ, MAP_SHARED, fd, 0));
  if (data == (caddr_t)(-1)){
    perror("mmap");
    exit(1);
  }

  cout << "byte at offset " << offset << " is " << data[offset] << endl;
  return(0);
}
