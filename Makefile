CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -g -02 -Iincludes

TARGET = a.exe
SRC_DIRS = command_files d_linked_list file_functions tree_functions
INCLUDE_DIR = includes

FUNCTIONS = main.c \ $(wildcard command_files/*.c)
					\ $(wildcard d_linked_list/*.c)
					 \ $(wildcard file_functions/*.c)
					  \ $(wildcard tree_functions/*.c)

OBJECTS = $(FUNCTIONS:.c = .o)


.PHONY: clean rebuild run info


$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)
	@echo "Сборка $(TARGET) завершена"

main.o main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

command_files/%.o: command_files/%.c includes/%.h
	$(CC) $(CFLAGS) -c $< -o $@

d_linked_list/%.o: d_linked_list/%.c includes/%.h
	$(CC) $(CFLAGS) -c $< -o $@

file_functions/%.o: file_functions/%.c includes/%.h
	$(CC) $(CFLAGS) -c $< -o $@

tree_functions/%.o: tree_functions/%.c includes/%.h
	$(CC) $(CFLAGS) -c $< -o $@


run: $(TARGET)
	./$(TARGET)

clean: 
	rm -f $(OBJECTS) &(TARGET) a.exe main.o
	@echo "Очистка завершена"

rebuild:
	clean $(TARGET)

info:
	@echo "::::::::::::::::::::Информация::::::::::::::::::::"
	@echo "Файл запуска ------- $(TARGET)"
	@echo "Функции:"
	@echo "$(FUNCTIONS)" | tr ' ' '\n'
	@echo "Объектники:"
	@echo "$(FUNCTIONS)" | tr ' ' '\n'