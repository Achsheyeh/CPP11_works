#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;
struct mq_msg_buf{
  long mtype;
  char mtext[200];
};

int main(void){

   struct mq_msg_buf buf;
   int mqid;
   key_t key;
   
   if ((key = ftok("rnd_mqput.cpp", 'B')) == -1) {
     perror("ftok"); 
     exit(1);
   }

   if ((mqid = msgget(key, 0644)) == -1) {
     perror("msgget");; 
     exit(1);
   }

   cout << " mqget: ready to receive messages " << endl;
   for(;;) {
     if (msgrcv(mqid, &buf, sizeof(buf.mtext), 0, 0) == -1){
       perror("msgrcv");
       exit(1);
     }
     cout << "mqget : " << buf.mtext << endl;
   }
   return (0);
}
