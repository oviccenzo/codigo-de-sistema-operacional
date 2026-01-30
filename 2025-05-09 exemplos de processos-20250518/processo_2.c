#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    printf("[PAI] Meu PID é %d\n", getpid());

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Erro na chamada do fork.\n");
        return 10;
    } else if (pid == 0) {
        // Processo filho
        printf("[FILHO] Meu PID é %d, o PID do meu pai é %d\n", getpid(), getppid());
        printf("[FILHO] Chamando comando execlp...\n");
        execlp("/bin/ls", "ls", "-la", NULL);
        // Se execlp falhar, este trecho será executado
        printf("[FILHO] execlp finalizado!\n");
    } else {
        // Processo pai
        printf("[PAI] Meu filho tem PID %d\n", pid);
        wait(NULL);  // Aguarda o filho terminar
        printf("[PAI] Filho concluído!\n");
    }

    return 0;
}
