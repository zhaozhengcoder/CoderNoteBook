.PHONY: gen gen_cpp gen_go is clean

gen_go:
	protoc --go_out=./out ./proto/*.proto

gen_cpp:
	protoc --cpp_out=./out ./proto/*.proto

is:
	go install .

gen:
	protoc --demo_out=./out ./proto/*.proto 

clean:
	rm out/custom/*.cpp out/custom/*.h

all:
	make gen_go
	make gen_protoc
	make gen_cpp
	make gen
