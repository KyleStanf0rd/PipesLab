#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>
#include "getRandInt.h"

#define MaxLen 80
#define PipeStdIn 0
#define PipeStdOut 1
//#define FIFO_FILE "MYFIFO"

int main(){

    time_t s = 1;
    struct tm* current_time;
    
    //FIFO
    int pipeFiles;
    int pipeFiles2;
    char *sharedPipe = "/tmp/myfifo";
    char *sharedPipe2 = "/tmp/myfifo2";
    int entrytimeL;
    int currentTimeL;
    char ret[MaxLen + 1];
    char buff[MaxLen + 1];
    const char* lifeSupport = "LIFESUPPORT: Adjusted the breathing gas levels inside the space ship!\n";
    const char* environment = "ENVIRONMENT: Adjusted the lighting and temperature levels!\n";


//I Made it go through 3 iterations for the sake of my time. 
//I understand It should go through an infinite amount of loops to make it repeat every 30 seconds



for(int i = 0; i <= 2; i++){
    seedRandGenerator();
    entrytimeL = time(NULL);
    //CHILD 1 PROCESS
    mkfifo(sharedPipe, 0777);
    pid_t pid = fork();
    if(pid < 0){
        perror("ERROR: FORK FAILED!");
        exit(1);
    }
    else if(pid == 0){
        pipeFiles = open(sharedPipe, O_CREAT|O_WRONLY, 0777);
        if(fcntl(pipeFiles, F_GETFD) == -1){
        perror("Open Failed!");
        exit(1);
        }
        write(pipeFiles, lifeSupport, strlen(lifeSupport));
        close(pipeFiles);
        unlink(sharedPipe);
        sleep((float)getRandExponential() * 5.0);
        wait(NULL);
        exit(0);

    }

    //CHILD TWO PROCESS
    mkfifo(sharedPipe2, 0777);
    pid_t pid2 = fork();
    if(pid2 < 0){
        perror("ERROR: FORK FAILED!");
        exit(1);
    }
    else if(pid2 == 0){
        pipeFiles2 = open(sharedPipe2, O_CREAT|O_WRONLY, 0777);
        if(fcntl(pipeFiles2, F_GETFD) == -1){
            perror("FAILED OPENING PIPE 2!");
            exit(1);
        }
        write(pipeFiles2, environment, strlen(environment));
        close(pipeFiles2);
        unlink(sharedPipe2);
        sleep((float)getRandExponential() * 4.0);
        wait(NULL);
        exit(0);
    }



    //PARENT PROCESS
    int entryTime = time(NULL);
    pipeFiles = open(sharedPipe, O_CREAT|O_RDONLY, 0777);
    if(fcntl(pipeFiles, F_GETFD) == -1){
        perror("OPENING FOR CHILD 1 FAILED!");
        exit(1);
    }
    wait(NULL);
    //READING FROM CHILD 1
    read(pipeFiles, buff, strlen(lifeSupport)+1);
    printf("Read: %s \n", buff);
    int currentTime = time(NULL);
    int t = currentTime - entryTime;
    printf("Time took to communicate: %d\n", t);
    close(pipeFiles); 
    s = time(NULL);
    current_time = localtime(&s);
    printf("%02d:%02d:%02d\n\n",
           current_time->tm_hour,
           current_time->tm_min,
           current_time->tm_sec);
    entryTime = time(NULL);
    pipeFiles2 = open(sharedPipe2, O_CREAT|O_RDONLY, 0777);
    if(fcntl(pipeFiles2, F_GETFD) == -1){
        perror("OPENING FOR CHILD 2 FAILED!");
        exit(1);
    }
    wait(NULL);
    //READING FROM CHILD 2
    read(pipeFiles2, buff, strlen(environment)+1);
    printf("Read: %s \n", buff);
    currentTime = time(NULL);
    t = currentTime - entryTime;
    printf("Time took to communicate: %d\n", t);
    close(pipeFiles2); 
    s = time(NULL);
    current_time = localtime(&s);
    printf("%02d:%02d:%02d\n\n",
           current_time->tm_hour,
           current_time->tm_min,
           current_time->tm_sec);
           
    currentTimeL = time(NULL);
    t = currentTimeL - entrytimeL;
    sleep(30-t);
    pid = 0;
    pid2 = 0;
    pipeFiles = 0;
    pipeFiles2 = 0;
    unlink(sharedPipe);
    unlink(sharedPipe2);
           
}
           
    return 0;

}

