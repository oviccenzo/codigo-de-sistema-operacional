#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("[PAI] Meu PID é %d\n", getpid());

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Erro ao criar processo filho\n");
        return 1;
    } else if (pid == 0) {
        // Processo filho
        printf("[FILHO] Meu PID é %d, o PID do meu pai é %d\n", getpid(), getppid());

        // Criando uma nova sessão para tornar o filho independente
        if (setsid() < 0) {
            fprintf(stderr, "[FILHO] Erro ao criar nova sessão\n");
            return 1;
        }

        // Gerando um tempo aleatório entre 1 e 4 segundos
        srand(getpid());
        int tempo = (rand() % 4) + 1;

        printf("[FILHO] Temporizador de %d segundos iniciado...\n", tempo);
        sleep(tempo);
        printf("[FILHO] Finalizando execução após %d segundos.\n", tempo);
        
        return 0;
    } else {
        // Processo pai
        printf("[PAI] Meu filho tem PID %d, mas não vou esperar ele finalizar!\n", pid);
        printf("[PAI] Continuando minha execução normalmente...\n");
    }

    return 0;
}
