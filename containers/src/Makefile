CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -pedantic -fsanitize=address
LIBS = -L/usr/local/lib -lgtest -lgtest_main -pthread


# Файл с тестами
TESTS = tests/test_list.cc

# Создание объектов из исходников
OBJECTS = $(SOURCE:.cc=.o)

# Цели, которые должны выполняться всегда
.PHONY: all clean test rebuild

# Цель по умолчанию
all: clean test


# Сборка и запуск тестов
test: $(OBJECTS) $(TESTS:.cc=.o) 
	$(CC) $(CFLAGS) $(TESTS)  $(LIBS) -o test
	./test

# Очистка временных файлов
clean:
	-rm -rf *.o *.a test

# Пересборка проекта
rebuild: clean all
