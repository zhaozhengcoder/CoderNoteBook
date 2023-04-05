package main

import (
	"context"
	"fmt"
	"io"
	"net"
	"strconv"
	"time"

	pb "./hellostream"
	"google.golang.org/grpc"
)

type HelloService struct {
}

func (hs *HelloService) SayHello(ctx context.Context, req *pb.HelloRequest) (*pb.HelloResponse, error) {
	return &pb.HelloResponse{Message: fmt.Sprintf("hello ，%s", req.Username)}, nil
}

func (hs *HelloService) Chat(conn pb.HelloService_ChatServer) error {
	go func() {
		var i int = 100
		for {
			time.Sleep(2 * time.Second)
			conn.Send(&pb.ServerStream{Stream: []byte("server send i:" + strconv.Itoa(i))})
			i++
		}
	}()

	for {
		time.Sleep(2 * time.Second)
		stream, err := conn.Recv()
		if err == io.EOF {
			return nil
		}
		if err != nil {
			return err
		}
		fmt.Println("server recv:", string(stream.Stream))
		// fmt.Println("receive from client:", stream.Stream)

	}

	return nil
}

// ++++++++++++++++++++

func main() {
	lis, err := net.Listen("tcp", ":6001")
	if err != nil {
		fmt.Println(err.Error())
		return
	}
	s := grpc.NewServer()
	pb.RegisterHelloServiceServer(s, &HelloService{})
	go func() {
		s.Serve(lis)
	}()

	fmt.Println("fmt info : ", s.GetServiceInfo())
	select {}
}

// func newBytes(a ...byte) []byte {
// 	return a
// }
