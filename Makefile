# Makefile para Detective Quest
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = detective_quest
OBJS = algoritmos_avancados.o sala.o pista.o suspeito.o

# Compilação padrão
all: $(TARGET)

# Regra principal
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "✓ Compilação concluída! Execute com: ./$(TARGET)"

# Regras individuais
algoritmos_avancados.o: algoritmos_avancados.c sala.h pista.h suspeito.h models.h
	$(CC) $(CFLAGS) -c algoritmos_avancados.c

sala.o: sala.c sala.h models.h
	$(CC) $(CFLAGS) -c sala.c

pista.o: pista.c pista.h models.h
	$(CC) $(CFLAGS) -c pista.c

suspeito.o: suspeito.c suspeito.h models.h
	$(CC) $(CFLAGS) -c suspeito.c

# Limpar arquivos de compilação
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "✓ Arquivos de compilação removidos"

# Executar o programa
run: all
	./$(TARGET)

# Recompilar tudo
rebuild: clean all

.PHONY: all clean run rebuild
