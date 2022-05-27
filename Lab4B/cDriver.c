#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "getRandInt.h"

#define MaxLen 80
const char* lifeSupport = "LIFESUPPORT: Adjusted the breathing gas levels inside the space ship!";
const char* environment = "ENVIRONMENT: Adjusted the lighting and temperature levels!";


int main(){

    time_t s = 1;
    struct tm* current_time;
    seedRandGenerator();
    char ret[MaxLen + 1];
    int C1Out[2] = {0};
    int C2Out[2] = {0};
    char buff[MaxLen + 1];
    int id, id2 = 0;
    //const char* lifeSupport = "LIFESUPPORT: Adjusted the breathing gas levels inside the space ship!\n Time Took to Adjust : 5 seconds";
    //const char* environment = "ENVIRONMENT: Adjusted the lighting and temperature levels!\n Time Took to Adjust : 4 seconds";
    if(pipe(C1Out) == -1){
    printf("An error occured with opening Pipe 1!\n");
    exit(1);
    }
    id = fork();
    if(id == 0){
    //FIRST CHILD PROCESS
    write (C1Out[1], lifeSupport,strlen(lifeSupport)+1);
    close (C1Out[0]);
    close (C1Out[1]);
    sleep((float)getRandExponential() * 5.0);
    wait(NULL);
    exit(0);

    }

    if(pipe(C2Out) == -1){
    printf("An error occured with opening Pipe 2!\n");
    exit(1);
    }

    id2 = fork();
    if(id2 == 0){
    //SECOND CHILD PROCESS
    write(C2Out[1], environment,  strlen(environment)+1);
    close(C2Out[0]);
    close (C2Out[1]);
    sleep((float)getRandExponential() * 4.0);
    wait(NULL);
    exit(0);
    }

    //PARENT PROCESS
    int entryTime = time(NULL);
    wait(NULL);
    read(C1Out[0], buff, strlen(lifeSupport)+1);
    printf("Read: %s\n", buff);
    int currentTime = time(NULL);
    int t = currentTime - entryTime;
    printf("Time took to communicate: %d\n", t);
    close(C1Out[0]);
    close(C1Out[1]);
    s = time(NULL);
    current_time = localtime(&s);
    printf("%02d:%02d:%02d\n\n",
           current_time->tm_hour,
           current_time->tm_min,
           current_time->tm_sec);
    entryTime = time(NULL);
    wait(NULL);
    read(C2Out[0], buff, strlen(environment)+1);
    printf("Read: %s\n", buff);
    currentTime = time(NULL);
    t = currentTime - entryTime;
    printf("Time took to communicate: %d\n", t);
    close(C2Out[0]);
    close(C2Out[1]);
    s = time(NULL);
    current_time = localtime(&s);
    printf("%02d:%02d:%02d\n\n",
           current_time->tm_hour,
           current_time->tm_min,
           current_time->tm_sec);

    return 0;



}
