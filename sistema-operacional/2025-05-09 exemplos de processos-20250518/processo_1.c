#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main() {

    pid_t pid;

    pid = fork();

    if ( pid < 0 ) {
        fprintf(stderr, "Erro na chamada do fork.");
        return 10;
    } else if ( pid == 0 ) {
        printf("[FILHO] chamando comando execlp...\n");
        execlp("/bin/ps", "ps", "all", NULL);
        printf("[FILHO] execlp finalizado!\n");
    } else {
        wait(NULL);
        printf("Child complete!\n");
    }

    return 0;
}