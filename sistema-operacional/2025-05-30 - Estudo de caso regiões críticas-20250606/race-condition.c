#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define randnum(min, max) ((rand() % (int)(((max) + 1) - (min))) + (min))

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex para sincronização

int contador = 0;  // Variável compartilhada

// Função que tenta incrementar o contador 100 vezes
void* incrementar(void* arg) {
	
	srand(time(NULL));

    for (int i = 0; i < 100; i++) {
		
		//pthread_mutex_lock(&mutex);  // Bloqueia o mutex antes de acessar o contador
        int temp = contador;  // Lê o valor atual do contador
        temp = temp + 1;       // Incrementa
        contador = temp;       // Atribui de volta o novo valor ao contador
		//pthread_mutex_unlock(&mutex);  // Desbloqueia o mutex depois de atualizar o contador

        // Imprime o valor do contador a cada incremento
        printf("Contador: %d\n", contador);
        //usleep( randnum(5, 5) * 100 );  // Delay de 10 microsegundos para aumentar a chance de race condition
		sleep( randnum(1, 3) * 1 );
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Cria duas threads
	printf("Criando as threads....\n");
    pthread_create(&thread1, NULL, incrementar, NULL);
    pthread_create(&thread2, NULL, incrementar, NULL);

    // Espera as threads terminarem
	printf("Aguardando as threads terminarem....\n");
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Valor final do contador: %d\n", contador);
    return 0;
}
