#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;
#define SHM_SIZE 1024

int main(int argc, char **argv){
  key_t key;
  int shmid;
  char *data;
  int mode;
 
  if (argc > 2) {
    cerr << " usage rnd_shrdmmry [data to write] " <<endl;
    exit(1);
  }

  if ((key = ftok("rnd_shrdmmry.cpp", 'R')) == -1) {
    perror("ftok");
    exit(1);
  }

  if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
    perror("shmget");
    exit(1);
  }

  data = static_cast<char *>(shmat(shmid, (void *)0, 0));
  if (data == (char *)(-1)){
    perror("shmat");
    exit(1);
  }

  if (argc == 2) {
    cout << " writing to segment " << argv[1] << endl;
    strncpy(data, argv[1], SHM_SIZE);
  } else
    cout << "segment contains " << data << endl;

  if (shmdt(data) == -1) {
    perror("shmdt");
    exit(1);
  }
  return(0); 
}
