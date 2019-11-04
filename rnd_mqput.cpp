#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;

struct mq_msg_buf{
  long mtype;
  char mtext[200];
};

int main(void) {
  struct mq_msg_buf buf;
  int mqid;
  key_t key;
  
  if ((key = ftok("rnd_mqput.cpp",'B')) == -1){
    perror("ftok");
    exit(1);
  }

  if ((mqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
    perror("msgget");
    exit(1);
  }

  cout << "Enter lines of text, ^D to quit: " << endl;  
  buf.mtype = 1;
  
  while(fgets(buf.mtext, sizeof(buf.mtext), stdin) != NULL) {
    int len = strlen(buf.mtext);
    if (buf.mtext[len - 1] = '\n')
      buf.mtext[len - 1] = '\0';
    if (msgsnd(mqid, &buf, len+1, 0) == -1)
      perror("msgsnd"); 
  }

  if (msgctl(mqid, IPC_RMID, NULL) == -1) {
    perror("msgctl");
    exit(1);
  }
  return(0);
}
