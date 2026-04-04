//
// Created by Robert L Resende on 23/05/25.
//
#include "sys/wait.h"
#include "cstdio"
#include "unistd.h"

int main(){

    pid_t pid;

    pid = fork();

    if(pid < 0){
        fprintf(stderr, "Erro na chamado do fork");
    } else if(pid == 0){
        printf("[FILHO] execpl finalizado!\n");
    } else {
        wait(NULL);
        printf("Filho completo\n");
    }
    return 0;
}
//
// Criado por Robert L Resende em 23/05/25.
//
//#include <sys/wait.h>
//#include <stdio.h>
//#include <unistd.h>
//
//int main() {
//    pid_t pid;
//    int a = 7, b = 9, soma;
//
//    pid = fork();
//
//    if (pid < 0) {
//        fprintf(stderr, "Erro na chamada do fork\n");
//        return 1;
//    } else if (pid == 0) {
//        soma = a + b;
//        printf("[FILHO] A soma de %d + %d é: %d\n", a, b, soma);
//    } else {
//        wait(NULL);  // Espera o processo filho terminar
//        printf("[PAI] Processo filho finalizado.\n");
//    }
//
//    return 0;
//}
