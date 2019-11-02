#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main()
{

  pid_t ppid= getpid(), cpid;
  int wstatus, i = 0;
  cout << "I m parent, i m going to launch child processes " << ppid << endl;
 
  for(;i< 5; i++) { 
    if (ppid == getpid())  
      cpid = fork();
  }
  if (ppid == getpid()) {
     cout << "I m parent, exiting " << ppid << endl;
  }
  else {
     cout << "I m child , sleeping for 30 secs " <<  getpid() << endl;
     sleep(30);
     cout << "I m child , exiting " <<  getpid() << endl;
     //waitpid(cpid, &wstatus, 0);
    //cout << "wstatus is " << wstatus << endl;
  }
     
}
