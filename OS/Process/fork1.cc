#if 0
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    fork();
    //fork();
    //fork();
    printf("hello\n");
    return 0;
}
#else
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{

    // make two process which run same
    // program after this instruction
    printf("before fork. \n");
    pid_t p = fork();
    pid_t p1 = fork();
    printf("fork return val: %d, %d \n", p, p1);
    //if(p<0 || p1 < 0){
    if(p<0) {
      perror("fork fail");
      //exit(1);
      printf("Process fork failed.");
    }
    //else if(p==0 || p1==0) {
    else if(p==0){
      printf("Child - Process_id(pid) = %d, p=%d, p1=%d \n",getpid(),p,p1);
      sleep(2);
      printf("Child - Process FIN. \n");
    }
    else {
      printf("Parent - Process_id(pid) = %d, p=%d,p1=%d \n",getpid(),p,p1);
      wait(NULL); // Wait for child process to complete
      printf("Parent - Process FIN. \n");
    }
    //wait;
    return 0;
}
#endif
