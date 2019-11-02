#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main()
{

  pid_t ppid= getpid(), cpid;
  int wstatus;
  cout << "I m parent, i m going to launch child processes " << ppid << endl;
 
  cpid=fork();
  if (cpid != 0) {
     cout << "I m child , so i m going become defunct " << cpid << endl;
     sleep(100);
  }
  else {
     cout << "I m parent " << getpid() << endl;
     //waitpid(cpid, &wstatus, 0);
    // cout << "wstatus is " << wstatus << endl;
     
  }
     
}

