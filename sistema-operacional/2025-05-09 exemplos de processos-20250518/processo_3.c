#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int i;

    printf("[PAI] Meu PID é %d\n", getpid());

    for (i = 0; i < 5; i++) {
        pid = fork();

        if (pid < 0) {
            fprintf(stderr, "Erro ao criar processo filho %d\n", i+1);
            return 1;
        } else if (pid == 0) {
            // Processo filho
            printf("[FILHO %d] Meu PID é %d, o PID do meu pai é %d\n", i+1, getpid(), getppid());
            sleep(2);  // Simula alguma execução do filho
            return 0;
        }
    }

    // Processo pai espera todos os filhos terminarem
    for (i = 0; i < 5; i++) {
        wait(NULL);
    }

    printf("[PAI] Todos os filhos concluídos!\n");
    return 0;
}
