# init go mod
go mod init protoc-gen-helloworld

# 查看结果
# ls $GOPATH/bin

# build 
# go install . 

# run
protoc --helloworld_out=./out demo.proto