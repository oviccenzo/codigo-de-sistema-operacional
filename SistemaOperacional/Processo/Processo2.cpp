//
// Created by Robert L Resende on 22/05/25.
//
#include "sys/wait.h"
#include "cstdio"
#include "unistd.h"

int main(){

    pid_t pid;

    printf("[Pai] Meu pid: e %d \n",getpid());

    pid = fork();
    
    if(pid < 0){
        fprintf(stderr, "Eroo na chamada do fork.\n");
        return 10;
    } else if(pid == 0){
        //Processo filho
        printf("[Filho] Meu pid e %d, o pid do meu pai e: %d\n",getpid(),getppid());
        printf("[Filho] Chamando comando execpl...\n");
        execlp("/bin/ls", "ls", "-la", NULL);
        //Se execpl falha, este trecho sera executado
        printf("[Filho] execpl finalizado!\n");
    } else{
        //processo pai
        printf("[Pai] Meu filho tem pid %d\n",pid);
        wait(NULL);
        printf("[Pai] filho concluido!\n");
    }

}