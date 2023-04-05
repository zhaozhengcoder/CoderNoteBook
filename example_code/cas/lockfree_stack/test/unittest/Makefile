APP_EXE=unittest 

all: $(APP_EXE)

CFLAGS += -Wsign-conversion -Wpedantic -Wall -DNDEBUG -O3
CFLAGS += -g

$(APP_EXE):unittest.cpp ../../lockfree_stack.h ../../lockfree_stack.cpp Makefile
	g++ -std=c++11  $(CFLAGS) unittest.cpp ../../lockfree_stack.cpp -o $(APP_EXE) -lpthread 

clean:
	rm $(APP_EXE)