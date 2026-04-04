//
// Created by Robert L Resende on 23/05/25.
//
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>

int main(){

    pid_t pid;

    printf("[Pai] Meu pid é %d\n",getpid());

    for (int i = 0; i < 5; ++i) {
        pid = fork();

        if(pid < 0){
            fprintf(stderr,"Erro ao criar processo filho %d\n",i+1);
            return 1;
        } else if(pid == 0){
            //processo filho
            printf("[FILHO %d]Meu pid é %d, o PID do meu pai é %d\n",i+1,getpid(), getppid());

            //Criando uma nova sessão para tornar o filho independente
            if(setsid() < 0){
                fprintf(stderr,"[FILHO %d] Erro ao criar nova sessão\n",i + 1);
                return 1;
            }

            //gerando um tempo aleatorio entre 1 e 4 segundos
            srand(getpid());
            int tempo = (rand() % 4) + 1;

            printf("[FILHO %d]Temporizador de %d segundos iniciados...\n", i + 1,tempo);
            sleep(tempo);
            printf("[FILHO %d]Finalizando execução após %d segundos.\n", i + 1, tempo);

            return 0;
        }
    }

    //processo pai não espera os filhos terminarem e segue sua execução
    printf("[PAI]Todos os filhos foram criados e estão executando independentemente!\n");
    return 0;
}