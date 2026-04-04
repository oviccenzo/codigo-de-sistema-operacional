//
// Created by Robert L Resende on 25/05/25.
//
#include "cstdio"
#include "cstdlib"
#include "unistd.h"
#include "sys/wait.h"
#include "sys/types.h"

//funcao executada pelo processo filho, recebendo dois parametros
void TarefaFilho(int a, int b){
    printf("[FILHO] Meu pid é %d, o pid do meu pai é %d\n",getpid(),getppid());

    if(setsid() < 0){
        fprintf(stderr,"[FILHO]Erro ao criar nova sessão\n");
        exit(1);
    }

    srand(getpid());
    int TempoFilho = (rand() % 5) + 1;

    printf("[FILHO]Temporizador de %d segundos iniciados...\n",TempoFilho);
    sleep(TempoFilho);

    printf("[FILHO]Executando soma: %d + %d = %d\n",a,b,a+b);
    printf("[FILHO]Tarefa concluida após %d segundos.\n",TempoFilho);
}

int main(){
    pid_t  pid;
    int num1 = 5, num2 = 3; //parametros para a função
    printf("[PAI] Meu pid é %d\n",getpid());
    pid = fork(); //criando o processo filho
    if(pid<0){
        fprintf(stderr,"Erro ao criar processo filho\n");
        return 1;
    } else if(pid == 0){
        //processo filho executa a funçao com os parametros
        TarefaFilho(num1,num2);
        exit(0);//finaliza o filho
    } else{
        //processo pai continua sua execucao independentemente
        srand(getpid());
        int TempoPai = (rand() % 5) + 1;

        printf("[PAI]Temporizador de %d segundos iniciados...\n",TempoPai);
        sleep(TempoPai);

        printf("[PAI]Processo pai concluindo após %d segundos.\n",TempoPai);
    }

    return 0;
}