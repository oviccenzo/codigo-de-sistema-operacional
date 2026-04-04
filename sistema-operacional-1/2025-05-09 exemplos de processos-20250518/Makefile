# Arquivos de código-fonte e binário
SRC = tarefa_1.c
BIN = tarefa_1.exe

# Diretivas do Makefile
all: compilar executar

compilar: limpar
	gcc $(SRC) -o $(BIN)

executar:
	./$(BIN)

limpar:
	rm -f $(BIN) *.o *.exe
