#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Função que será executada pelo processo filho
void tarefa_filho() {
    printf("[FILHO] Meu PID é %d, executando tarefa...\n", getpid());
    sleep(2);  // Simulando um processamento
    printf("[FILHO] Tarefa concluída!\n");
}

int main() {
    
    pid_t pid;

    printf("[PAI] Meu PID é %d\n", getpid());

    pid = fork();  // Criando o processo filho

    if (pid < 0) {
        fprintf(stderr, "Erro ao criar processo filho\n");
        return 1;
    } else if (pid == 0) {
        // Processo filho executa a função tarefa_filho()
        tarefa_filho();
        exit(0);  // Finalizando o processo filho
    } else {
        // Processo pai espera o filho concluir
        wait(NULL);
        printf("[PAI] Filho finalizado, encerrando execução.\n");
    }

    return 0;
}
