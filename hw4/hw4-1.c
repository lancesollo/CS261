#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int x = 50;
    printf("hello world (pid:%d)\n", (int) getpid());
    x = 100;
    printf("x val: %d\n", x);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        x = 25;
        printf("hello, I am the child (pid:%d), x val: %d\n", (int) getpid(), x);
	sleep(1);
    } else {
        int wc = wait(NULL);
        x = 125;
        printf("hello, I am parent of %d (wc:%d) (pid:%d), x val: %d\n",
	       rc, wc, (int) getpid(), x);
    }
    printf("final x: %d\n", x);
    
    return 0;
}

//First, you write a program that calls fork(). But before you call fork(), have the main process access a variable (like x) and set
//its value to something (like 100). What value is the variable in the child process? What happens to the
//variable when both the child and parent change the value of x? Submit this code as hw4-1.c and place your
//responses to the question in comments

//When the main process accesses x and sets it to 100, x is also 100 in the child process.
//When both the child proccess and the parent proccess change the value of x, the child proccess ends 
//with x being whatever the chidl sets it to, and the parent proccess ends with x being whatever the parent  sets it to.

//Question: Why the variants using the text input here. // waitpid() is a variant of wait() that allows you to wait on a particular pid.
//Answer: Because theres' many variants of the same call because of its flexibility towards arguments and environments being passed through
//        program. Some of the variants lets you pass arguments into the function call, and some take a function array. It's the same concept with
//        environments. 
