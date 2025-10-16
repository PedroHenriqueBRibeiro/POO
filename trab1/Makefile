# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -Iinclude
LDFLAGS = 

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .

# Arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(SRC_DIR)/classes/*.c) \
       $(wildcard $(SRC_DIR)/data/*.c) \
       $(wildcard $(SRC_DIR)/lista/*.c) \
       $(wildcard $(SRC_DIR)/io/*.c) \
       $(wildcard $(SRC_DIR)/relatorios/*.c) \
       $(wildcard $(SRC_DIR)/filtro/*.c)

# Arquivos objeto
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Nome do executável
TARGET = $(BIN_DIR)/trabalho_poo

# Regra principal
all: $(TARGET)

# Link do executável
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "✅ Executável criado: $(TARGET)"

# Compilação dos objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para executar
run: $(TARGET)
	./$(TARGET)

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "🧹 Arquivos de compilação removidos"

# Debug
debug: CFLAGS += -DDEBUG -O0
debug: $(TARGET)

# Release
release: CFLAGS += -O2
release: $(TARGET)

# Ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make all     - Compila o projeto"
	@echo "  make run     - Compila e executa"
	@echo "  make clean   - Remove arquivos compilados"
	@echo "  make debug   - Compila com flags de debug"
	@echo "  make release - Compila com otimização"

.PHONY: all run clean debug release help