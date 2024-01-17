/* cgi_hello.cpp
public domain
NB: tested code.
*/
#include <iostream>

#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;



int main(int ac ,char ** av){

    int pid;
    pid = fork();
    if(pid <0){
      perror("fork fail");
      exit(1);
    }
    int fd = open("out.txt",O_CREAT | O_WRONLY | O_TRUNC,0644);
    char * cmd;
    char **arg;
    cmd = av[1];
    arg = av + 1; 

    if (pid == 0)
    {
        dup2(fd, STDOUT_FILENO);
        execve(cmd,arg,NULL);
        perror("execve");
    }
    return 0;
}