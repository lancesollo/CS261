#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child1 (pid:%d)\n", (int) getpid());
	    sleep(1);
        exit(1);
    } 
    
    int rc2 = fork();
    if (rc2 < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc2 == 0) {
        // child (new process)
        printf("hello, I am child2 (pid:%d)\n", (int) getpid());
	    sleep(1);
        exit(2);
    } 
    
    int wc = waitpid(rc, NULL, 0);
    printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
	       rc, wc, (int) getpid());

    int wc2 = waitpid(rc2, NULL, 0);
    printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
	       rc2, wc2, (int) getpid());

    return 0;
}
