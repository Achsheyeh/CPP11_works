#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

using namespace std;
void sigint_handler(int sig) {
    write (0, "Ahhh! SIGINT!\n", 14); 
}


int main(void) {
    char s[200];
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
      perror("sigaction");
      exit(1);
    }
    cout << "Enter a string: " << endl;

    if (fgets(s, sizeof(s), stdin) == NULL)
      perror("fgets");
    else
      cout << "you entered " << s << endl;
    return (0);
}
