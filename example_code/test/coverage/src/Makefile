APP_EXE=../bin/main 

all: $(APP_EXE)

CFLAGS += -Wsign-conversion -Wpedantic -Wall -DNDEBUG -O3
CFLAGS += -g --coverage

$(APP_EXE):main.c module_a.c module_b.c Makefile
	g++ -std=c++11 $(CFLAGS) main.c module_a.c module_b.c -o $(APP_EXE) 

clean:
	rm $(APP_EXE) 
	rm *.gcno

start:
	./$(APP_EXE)

coverage:
	gcov module_a.c
	gcov module_b.c
	gcov main.c