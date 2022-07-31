.PHONY: all proto clean run

all:
	g++ main.cpp ./out/person.pb.cc -o main -I./out -lprotobuf -lpthread -L/usr/local/lib -g

proto:
	protoc --cpp_out=./out *.proto

run:
	./main

clean:
	rm main