/*  
*   Title: Process Timer
*   Author: Aleksandar Damnjanovic
*   Date: 12.12.2021
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char** argv){

    if(argc<2){
        printf("You must provide command to start process\n");
        exit(-1);
    }

    __pid_t id;
    long dif=0;

    struct timespec start, stop;    
    timespec_get(&start, TIME_UTC);

    int pid= fork();
    if(pid==0){
        execvp(argv[1],NULL);

    }else{
        int rs;
        waitpid(-1, &rs, WUNTRACED | WCONTINUED);

        struct stat sts;
        char cmd[256];
        char* id= malloc(8);
        sprintf(id,"%d", pid);
        strcpy(cmd, "/proc/");
        strcat(cmd, id);

            timespec_get(&stop, TIME_UTC);
            dif= stop.tv_sec - start.tv_sec;
            long dd= stop.tv_nsec - start.tv_nsec;
            long full=(dif*1000000000)+dd;

            printf("seconds: %ld\n",dif);
            printf("miliseconds: %ld\n", full / 1000000);
            printf("microseconds: %ld\n", full / 1000);
            printf("nanoseconds: %ld\n",full);
        
    }

    return 0;
}