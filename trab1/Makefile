CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = agenda
SOURCES = main.c util.c datetime.c appointment.c list.c sort.c parser.c buckets.c comparators.c writers.c resultado.c
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

distclean: clean
	rm -f relatconfirmados.txt relatadiados.txt relatcancelados.txt relatcompromissos.txt resultado.txt
	rm -rf resultados

.PHONY: clean distclean run