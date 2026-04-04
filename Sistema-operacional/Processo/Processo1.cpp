//
// Created by Robert L Resende on 22/05/25.
//
#include "sys/wait.h"
#include "cstdio"
#include "unistd.h"

int main(){

    pid_t pid;

    pid = fork();

    if(pid < 0){
        fprintf(stderr,"Erro na chamada do fork.");
        return 10;
    } else if(pid == 0){
        printf("[Filho] chamando comando execlp...\n");
        execlp("/bin/ps","ps","all",NULL);
        printf("[Filho] execlp finalizado!\n");
    } else{
        wait(NULL);
        printf("Filho completo!\n");
    }
    return 0;
}