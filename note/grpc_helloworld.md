# grpc 

## 目录

* [grpc helloworld例子](#helloworld)

* [几种rpc的类型](#demo)

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

参考一个不错的例子： https://zhuanlan.zhihu.com/p/30624616 

### 1. gRPC 中的三种类型的 RPC 方法。

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

    双边流的rpcdemo ： 


流式rpc和普通rcp的区别：


举个例子：

比如一对多的请求，比较适合用流式的rcp。比如，请求是一个点的坐标，响应是这个点最近的100个点。那么比较好的方式是，响应使用流式的rpc。 因为这是一个典型的一对多的例子。

那么，为什么不能改成1对1的响应，返回的响应是一个数组。为什么不能是这样的设计？ 

不这样做的原因是：
1. 这样的相应包可能会很大，如果网络环境不是很好的话，容易超时。
2. 就算不超时，这样的设计也并不是很优雅。因为，这样意味要，要不是等不到回包，要不然就是收到一个巨大的回包，然后开始“疯狂”的处理。 使用流式的rpc，尽量可能的用流的方式去一点点的平滑处理。

对应的demo ： > [demo](../example_code/grpc_demo/stream_rpc/server.go)

### 2. proto的声明

对应的demo ： > [demo](../example_code/grpc_demo/demo/main.go)

2.1 proto 如果有多个服务的话，可以在proto文件中，声明在一起：
```
// The Customer sercie definition
service Customer {
    rpc GetCustomers(GetCustomersRequest) returns (GetCustomersResponse) {}

    rpc CreateCustomer (CustomerRequest) returns (CustomerResponse) {}
}
```

2.2 proto 声明为数组：
```
message GetCustomersResponse {
    int32 ret = 1;
    message keyword {
        string word = 1;
    }

    // 声明为数组
    repeated keyword wordarray = 3;
}
```

在代码里面可以这样写入rsp：
```
func (s *server) GetCustomers(ctx context.Context, in *pb.GetCustomersRequest) (*pb.GetCustomersResponse, error) {
	log.Printf("GetCustomers")

	return &pb.GetCustomersResponse{
		Ret: 1,
		Wordarray: []*pb.GetCustomersResponseKeyword{
			&pb.GetCustomersResponseKeyword{
				Word: "hello",
			},

			&pb.GetCustomersResponseKeyword{
				Word: "golang",
			},

			&pb.GetCustomersResponseKeyword{
				Word: "grpc",
			},
		},
	}, nil
}
```

### 

----
## 参考

* rpc中文文档：

    http://doc.oschina.net/grpc?t=58009

* grpc github 提供的example ： 
    
    https://github.com/grpc/grpc-go/tree/master/examples/route_guide 