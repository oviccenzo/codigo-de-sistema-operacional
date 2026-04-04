//
// Created by Robert L Resende on 25/05/25.
//
#include "cstdio"
#include "cstdlib"
#include "unistd.h"
#include "sys/wait.h"
#include "sys/types.h"

//Função que será executando pelo processo filho
void TarefaFilho(){
    printf("[FILHO] Meu pid é %d, executando tarefa...\n",getpid());
    sleep(2); //simulando um processamento
    printf("[FILHO] Tarefa concluídas\n");
}

int main(){
    pid_t pid;
    printf("[PAI]Meu PID é %d\n", getpid());

    pid = fork();//criando o processo filho

    if(pid < 0){
        fprintf(stderr,"Erro ao criar processo filho\n");
        return 1;
    } else if(pid == 0){
        //processo filho executa a função tarefa_filho()
        TarefaFilho();
        exit(0);//Finalizando o processo filho
    } else {
        //Processo pai espera o filho concluir
        wait(NULL);
        printf("[PAI]Filho finalizado, encerrando execução.\n");
    }

    return 0;
}