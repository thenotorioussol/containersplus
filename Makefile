CC = gcc
CFLAGS = -std=c++17 -lstdc++ -pedantic -Wall -Werror -Wextra

TEST_FILES = $(wildcard tests/*.cc)

test:
	$(MAKE) clean
	$(CC) $(CFLAGS) -lgtest $(TEST_FILES) -o test_containers
	./test_containers

clean:
	rm -rf test_containers

style:
	clang-format -style=Google -n tests/* *.h