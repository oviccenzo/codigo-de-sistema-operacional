//
// Created by Robert L Resende on 22/05/25.
//
#include "cstdio"
#include "cstdlib"
#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"

int main(){
    pid_t pid;

    printf("[Pai] Meu PID e %d\n",getpid());
    
    pid = fork();
    
    if(pid < 0){
        fprintf(stderr, "Erro ao criar processos filho\n");
        return 1;
    } else if(pid == 0){
        //processo filho
        printf("[Filho]Meu PID e %d, o PID do meu pai e %d\n", getpid(),getppid());
        
        //criando uma nova sessao para tornar o filho independete
        if(setsid() < 0){
            fprintf(stderr,"[filho] Erro ao criar nova sessao\n");
            return 1;
        }
        //gerrando um tempo aleatorios entre 1 e 4 segundos
        srand(getpid());
        int tempo = (rand() % 4) + 1;

        printf("[FILHO] Temporaizador de %d segundos iniciados...\n", tempo);
        sleep(tempo);
        printf("[FILHO] Finalizando execucao apos %d segundos.\n", tempo);

        return 0;
    } else {
        //Processo pai
        printf("[PAI]Meu filho tem PID %d, mas nao vou esperar ele finalizadr!\n", pid);
        printf("[PAI]Continuando minha execucao normalmente\n");
    }

    return 0;
}