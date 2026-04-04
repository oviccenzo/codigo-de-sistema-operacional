#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Função da thread
void * tarefa(void * param);

int main() {

	// identificador da thread
    pthread_t tid;
    double parametro = 5.5;
    double * resultado;
    
    // Criando a thread e passando o parâmetro
    if (pthread_create(&tid, NULL, tarefa, &parametro) != 0) {
        perror("Erro ao criar a thread");
        return EXIT_FAILURE;
    }

    // Esperando a conclusão da thread e recebendo o resultado
    if (pthread_join(tid, (void**) &resultado) != 0) {
        perror("Erro ao aguardar a thread");
        return EXIT_FAILURE;
    }

    printf("Resultado da computação na thread: %.2f\n", *resultado);
    
    // Liberando memória alocada na thread
    free(resultado);
    
    return EXIT_SUCCESS;
}

// Implementação da função da thread
void* tarefa(void* param) {

    // Convertendo o argumento para double
    double valor = * ((double*) param);
    
    printf("Valor recebido na thread: %.2f\n", valor);
    
    // Retornando um novo valor como resultado da computação
    double * resultado = malloc(sizeof(double));
    *resultado = valor * 2;
    
    return (void*) resultado;
}