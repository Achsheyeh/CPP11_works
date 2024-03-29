#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

using namespace std;

#define MAX_RETRIES 10
union semun {
  int val;
  struct semid_ds *buf;
  ushort *array;
};

int initsem(key_t key, int nsems) {
  int i;
  union semun arg;
  struct semid_ds buf;
  struct sembuf sb;
  int semid;

  semid = semget(key, nsems, IPC_CREAT | IPC_EXCL | 0666);
  if (semid >= 0) {
    sb.sem_op = 1; sb.sem_flg = 0;
    arg.val = 1;
   
    cout << " press enter " << endl;
    getchar();

    for (sb.sem_num = 0; sb.sem_num < nsems; sb.sem_num++) {
      if (semop(semid , &sb, 1) == -1) {
        int e = errno;
        semctl(semid , 0, IPC_RMID);
        errno = e;
        return (-1);
      }
    }
  } else if (errno = EEXIST) {
    int ready = 0;
   
    semid = semget(key, nsems, 0);
    if (semid < 0) return semid;
  
    arg.buf = &buf;
    for (i = 0; i < MAX_RETRIES && !ready; i++) {
      semctl(semid, nsems-1 , IPC_STAT, arg);
      if(arg.buf->sem_otime != 0) {
        ready = 1;
      } else {
        sleep(1);
      }
    } 
    if (!ready){
      errno = ETIME;
      return -1;
    }
  }else
     return semid;
  return semid;


}

int main(void){
  key_t key;
  int semid;
  struct sembuf sb;
  
  sb.sem_num = 0;
  sb.sem_op = -1;
  sb.sem_flg = SEM_UNDO;
  
  if ((key = ftok("rnd_smphcreate.cpp", 'J')) == -1) {
    perror("ftok");
    exit(1);
  }

  if ((semid = initsem(key, 1)) -1) {
    perror("initsem");
    exit(1);
  }

  cout << " press enter to lock " << endl;
  getchar();
  cout << "trying to lock \n " << endl;
  
  if (semop(semid, &sb, 1) == -1) {
    perror("semop");
    exit(1);
  }

  cout << "locked " << endl;
  cout << "Press enter to lock " << endl;
  getchar();
  
  sb.sem_op = 1;
  if (semop(semid, &sb, 1) == -1) {
    perror("semop");
    exit(1);
  }

   cout << "unlocked " << endl;
   return(0);
}
