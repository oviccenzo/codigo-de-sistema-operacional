# SRC = Servidor.cpp
SRC = Exemplo.cpp   
BIN = Exemplo.exe

all: compilar executar

compilar: limpar
	@g++ $(SRC) -o $(BIN) -Wall pthread 

executar:
	@./$(BIN)

limpar:
	@rm -f $(BIN)