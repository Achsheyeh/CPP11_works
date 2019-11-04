#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

/*** About advisory lock *********

There are two types of (advisory!) locks: read locks and write locks (also referred to as shared locks and exclusive locks, respectively.) The way read locks work is that they don't interfere with other read locks. For instance, multiple processes can have a file locked for reading at the same. However, when a process has an write lock on a file, no other process can activate either a read or write lock until it is relinquished. One easy way to think of this is that there can be multiple readers simultaneously, but there can only be one writer at a time

**********************/
using namespace std;

int main(int argc, char **argv){

   struct flock fl = {F_WRLCK, SEEK_SET, 0 , 0, 0};
   int fd;
   
   fl.l_pid = getpid();
   if (argc > 1)
     fl.l_type = F_RDLCK;
   
   if ((fd = open("rnd_filelock.cpp", O_RDWR)) == -1) {
     perror("open");
     exit(1);
   }
   
   cout << "Press enter to try to get lock " << endl;
   getchar();
   cout << "Trying to get lock " << endl;
   if (fcntl(fd, F_SETLKW, &fl) == -1) {
     perror("fcntl");
     exit(1);
   }
   
   cout << "Got lock " << endl;
   cout << "Press enter to try to release lock " << endl;
   getchar();
 
   fl.l_type = F_UNLCK;
   if (fcntl(fd, F_SETLK, &fl) == -1) {
     perror("fcntl");
     exit(1);
   }

   cout << "unlocked " << endl;
   close(fd);
   return(0);   
}
