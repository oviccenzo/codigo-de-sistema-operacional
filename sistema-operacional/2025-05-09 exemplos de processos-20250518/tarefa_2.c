#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// Função executada pelo processo filho, recebendo dois parâmetros
void tarefa_filho(int a, int b) {
    printf("[FILHO] Meu PID é %d, o PID do meu pai é %d\n", getpid(), getppid());

    // Criando uma nova sessão para tornar o filho independente
    if (setsid() < 0) {
        fprintf(stderr, "[FILHO] Erro ao criar nova sessão\n");
        exit(1);
    }

    // Gerando tempo aleatório de 1 a 5 segundos
    srand(getpid());
    int tempo_filho = (rand() % 5) + 1;

    printf("[FILHO] Temporizador de %d segundos iniciado...\n", tempo_filho);
    sleep(tempo_filho);
    
    printf("[FILHO] Executando soma: %d + %d = %d\n", a, b, a + b);
    printf("[FILHO] Tarefa concluída após %d segundos.\n", tempo_filho);
}

int main() {
    pid_t pid;
    int num1 = 5, num2 = 3;  // Parâmetros para a função

    printf("[PAI] Meu PID é %d\n", getpid());

    pid = fork();  // Criando o processo filho

    if (pid < 0) {
        fprintf(stderr, "Erro ao criar processo filho\n");
        return 1;
    } else if (pid == 0) {
        // Processo filho executa a função com os parâmetros
        tarefa_filho(num1, num2);
        exit(0);  // Finaliza o filho
    } else {
        // Processo pai continua sua execução independentemente
        srand(getpid());
        int tempo_pai = (rand() % 5) + 1;

        printf("[PAI] Temporizador de %d segundos iniciado...\n", tempo_pai);
        sleep(tempo_pai);

        printf("[PAI] Processo pai concluindo após %d segundos.\n", tempo_pai);
    }

    return 0;
}
