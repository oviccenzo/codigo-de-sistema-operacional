# definição dos parametros de configuração para o make
       # nome comum para o arquivo-fonte e seu executavel
#FILE = race-condition-01-sync
FILE = race-condition-01

SRC = $(FILE).c
EXEC = $(FILE).exe

# Regra principal: compilar
all: compilar

# Regra para compilar o codigo-fonte
compilar: limpar
	@gcc $(SRC) -o $(EXEC) -Wall -pthread

exec:
	@./$(EXEC) $(ARG)    # passando parametro como uma variavel do make

# Regra para executar o programa
run: compilar
	@./$(EXEC) $(ARG)    # passando parametro como uma variavel do make

runconstante: compilar
	@./$(EXEC) 10            # passando parametro como uma constante do make

# Regra para limpar arquivos gerados
limpar:
	@rm -f $(EXEC) *.exe
