//
// Created by Robert L Resende on 22/05/25.
//
#include "cstdio"
#include "unistd.h"
#include "sys/wait.h"

int main(){

    pid_t pid;
    int i;
    printf("[Pai]Meu pi e %d\n",getpid());

    for(i = 0; i < 5; i++){
        pid = fork();

        if(pid < 0){
            fprintf(stderr, "Erro ao criar processo filho %d\n",i+1);
            return 1;
        } else if(pid == 0){
            //processo filho
            printf("[Filho %d] Meu PID e %d, o PID do meu pai e %d\n", i + 1, getpid(), getppid());
            sleep(2);
            return 0;
        }
    }
    for (i = 0; i < 5; ++i) {
        wait(NULL);
    }
    printf("[Pai] todos os filhos concluidos!\n");
}