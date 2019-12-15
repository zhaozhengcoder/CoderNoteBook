# grpc 

## 目录

* [grpc helloworld例子](#helloworld)

* [另外一个例子](#demo)

---

## helloworld 

目录结构：
```
├── client.go
├── helloworld
│   ├── build.sh
│   ├── helloworld.pb.go
│   └── helloworld.proto
└── server.go
```

proto 定义
```
syntax = "proto3";

package helloworld;

service Greeter {
    rpc SayHello (Helloreq) returns (Hellorsp) {}
}

message Helloreq {
    string message = 1;
}

message Hellorsp {
    string message = 1;
}
```

构建
```
protoc -I . --go_out=plugins=grpc:. ./helloworld.proto
```

sever.go 
```
package main

import (
	"context"
	"log"
	"net"

	pb "./helloworld"
	"google.golang.org/grpc"
)

const (
	port = ":50051"
)

// server is used to implement helloworld.GreeterServer.
type server struct {
	pb.UnimplementedGreeterServer
}

// SayHello implements helloworld.GreeterServer
func (s *server) SayHello(ctx context.Context, in *pb.Helloreq) (*pb.Hellorsp, error) {
	log.Printf("Received: %v", in.GetMessage())
	return &pb.Hellorsp{Message: "Hello " + in.GetMessage()}, nil
}

func main() {
	lis, err := net.Listen("tcp", port)
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}
	s := grpc.NewServer()
	pb.RegisterGreeterServer(s, &server{})
	if err := s.Serve(lis); err != nil {
		log.Fatalf("failed to serve: %v", err)
	}
}

```

client.go 
```
package main

import (
	"context"
	"log"
	"os"
	"time"

	pb "./helloworld"
	"google.golang.org/grpc"
)

const (
	address     = "localhost:50051"
	defaultName = "world"
)

func main() {
	// Set up a connection to the server.
	conn, err := grpc.Dial(address, grpc.WithInsecure(), grpc.WithBlock())
	if err != nil {
		log.Fatalf("did not connect: %v", err)
	}
	defer conn.Close()
	c := pb.NewGreeterClient(conn)

	// Contact the server and print out its response.
	message := defaultName
	if len(os.Args) > 1 {
		message = os.Args[1]
	}
	ctx, cancel := context.WithTimeout(context.Background(), time.Second)
	defer cancel()
	r, err := c.SayHello(ctx, &pb.Helloreq{Message: message})
	if err != nil {
		log.Fatalf("could not greet: %v", err)
	}
	log.Printf("Greeting: %s", r.GetMessage())
}
```

```
go run server.go 
go run client.go 
```

## demo 

gRPC 中的三种类型的 RPC 方法。

* simple RPC
    
    应用于常见的典型的 Request/Response 模型。客户端通过 stub 请求 RPC 的服务端并等待服务端的响应。

* Server-side streaming RPC

    客户端给服务端发送一个请求并获取服务端返回的流，用以读取一连串的服务端响应。stream 关键字在响应类型的前面。// 例子

    rpc LotsOfReplies(HelloRequest) returns (stream HelloResponse){}


* Client-side streaming RPC
    
    客户端发送的请求 payload 有一连串的的信息，通过流给服务端发送请求。stream 关键字在请求类型前面。 /／ 例子

    rpc LotsOfGreetings(stream HelloRequest) returns (HelloResponse) {}

* Bidirectional streaming RPC

    服务端和客户端之间都使用 read-write stream 进行通信。stream 关键字在请求类型和响应类型前面。// 例子
    
    rpc BidiHello(stream HelloRequest) returns (stream HelloResponse){}

> [demo](../example_code/grpc_demo/main.go)