#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// variável global que guarda o resultado do somatório
int sum;

/* Tarefa para ser executada via thread */
void * runner(void * param);

/* função principal do programa */
int main(int argc, char const *argv[]) {

	pthread_t tid;       // identificação da thread
	pthread_attr_t attr; // atributos da thread

	// tratamento dos argumentos obrigatórios
	if ( argc != 2) {
		fprintf(stderr, "Uso: %s <valor inteiro>\n", argv[0]);
		return -1;
	}

	// tratamento do tipo de dado do argumento obrigatório
	if (atoi(argv[1]) < 0) {
		fprintf(stderr, "%d deve ser >= 0\n", atoi(argv[1]));
		return -2;
	}

	// preparação da thread: configuração dos atributos
	pthread_attr_init(&attr);

	// criação da thread
	pthread_create(&tid, &attr, runner, (void *) argv[1]);

	// Esperando a conclusão da thread e recebendo o resultado
	pthread_join(tid, NULL);

	// resultado da thread
	printf("Soma = %d\n", sum);

	return 0;
}

/* Implementação da tarefa para ser executada via thread */
void * runner(void * param) {

	int upper = atoi(param);

	sum = 0;
	for (int i = 0; i < upper; i++) {
		sum += i;
	}

	// finalização da thread
	pthread_exit(0); // código 0 = fim bem sucedido
}