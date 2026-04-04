#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// definição do tipo de dados que a thread vai receber
// -- "pacote de dados"
typedef struct {
    double a;
    double b;
    double c;
    double d;
} Parametros;

// Função da thread (tarefa a ser executada)
// -- observe o padrão da assinatura da função
// -- tipo de retorno deve ser "void *"
// -- tipo do parametro deve ser "void *"
void * tarefa(void * param);

int main() {

	// identificador da thread
    pthread_t tid;

	// "pacote" de dados que serão passados para a thread (tarefa)
    Parametros parametros = {2.5, 3.5, 4.0, 1.5};

	// resultado esperado da thread (tarefa)
    double* resultado;

    // Criando a thread e passando a estrutura de parâmetros (dados "empacotados")
    if (pthread_create(&tid, NULL, tarefa, &parametros) != 0) {
        perror("Erro ao criar a thread");
        return EXIT_FAILURE;
    }

    // Esperando a conclusão da thread e recebendo o resultado
	// - observe o segundo parametro: a variável de resultado esperado....
    if (pthread_join(tid, (void**) &resultado) != 0) {
        perror("Erro ao aguardar a thread");
        return EXIT_FAILURE;
    }

    printf("Resultado da computação na thread: %.2f\n", *resultado);

    // Liberando memória alocada na thread
    free(resultado);

    return EXIT_SUCCESS;
}

// Implementação da função da thread (tarefa a ser executada)
void * tarefa(void * param) {

	// pacote de dados da tarefa, sendo "abertos"
    Parametros* p = (Parametros*) param;

	// trabalhando os dados recebidos

    printf("Valores recebidos: a=%.2f, b=%.2f, c=%.2f, d=%.2f\n", p->a, p->b, p->c, p->d);

    // Realizando uma operação simples com os valores (soma de todos)
    double * resultado = malloc(sizeof(double));
    *resultado = p->a + p->b + p->c + p->d;

	// retornando o resultado da tarefa para o processo principal
	// - observe o casting (void *) para seguir o padrão da POSIX
    return (void*) resultado;
}
