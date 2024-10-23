// Code by Lance

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    char buff[1024]; //char array size being 1024
    char *args[64]; //char array pointers that point to the tokens
    while(1){
        printf("shell> "); //Prints out the prompt shell
        if(fgets(buff, sizeof(buff), stdin) == NULL){ //reads and processes inputs from keyboard
            break; //Understands that the end of the file is reached.
        }

        buff[strcspn(buff, "\n")] = 0; //Removes newline

        char *token = strtok(buff, " ");
        int i = 0;
        while(token != NULL){
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if(args[0] == NULL){
            continue;
        }

        int pro = fork(); //creates a new process using fork()
        if(pro == 0){
            if(execvp(args[0], args) == -1){
                perror("failure of execvp");
                exit(EXIT_FAILURE);
            }
        } else if(pro > 0){
            wait(NULL);
        }else{
            perror("failure of fork");
        }
    }
    return 0;
}