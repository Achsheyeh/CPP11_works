#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

using namespace std;
volatile sig_atomic_t got_usr1;

void sigusr1_handler(int sig)
{
   got_usr1 = 1;
}

int main(void) {
   struct sigaction sa;
   got_usr1 = 0;
   sa.sa_handler = sigusr1_handler;
   sa.sa_flags = 0;
   if (sigaction(SIGUSR1, &sa, NULL) == -1) {
      perror("sigaction");
      exit(1);
   }
   
   while(!got_usr1) {
       cout << "PID " <<  getpid() << ": working hard ...." << endl;
       sleep(1);
   }

   cout << "Done in by SIGUSR1 " << endl;
   return(0);
}
