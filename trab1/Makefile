CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -Iinclude
LDFLAGS = 
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .

SRCS = $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(SRC_DIR)/classes/*.c) \
       $(wildcard $(SRC_DIR)/data/*.c) \
       $(wildcard $(SRC_DIR)/lista/*.c) \
       $(wildcard $(SRC_DIR)/io/*.c) \
       $(wildcard $(SRC_DIR)/relatorios/*.c) \
       $(wildcard $(SRC_DIR)/filtro/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/trabalho_poo
all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "✅ Executável criado: $(TARGET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "🧹 Arquivos de compilação removidos"

debug: CFLAGS += -DDEBUG -O0
debug: $(TARGET)

release: CFLAGS += -O2
release: $(TARGET)
help:
	@echo "Comandos disponíveis:"
	@echo "  make all     - Compila o projeto"
	@echo "  make run     - Compila e executa"
	@echo "  make clean   - Remove arquivos compilados"
	@echo "  make debug   - Compila com flags de debug"
	@echo "  make release - Compila com otimização"

.PHONY: all run clean debug release help