APP_EXE=unittest 

all: $(APP_EXE)

CFLAGS += -Wsign-conversion -Wpedantic -Wall -DNDEBUG -O3
CFLAGS += -g

ifeq ($(_LOCK), 1)
CFLAGS += -D USE_LOCK
endif

#默认无锁版本
$(APP_EXE):unittest.cpp ../ringbuff.h Makefile
	g++ -std=c++11  $(CFLAGS) unittest.cpp ../ringbuff.h -o $(APP_EXE) -lpthread 

#构建有锁版本
lock_version:
	make $(APP_EXE) _LOCK=1

clean:
	rm $(APP_EXE)