package main

import (
	"context"
	"fmt"
	"io"
	"strconv"

	"time"

	pb "./hellostream"
	"google.golang.org/grpc"
)

func main() {
	conn, e := grpc.Dial("localhost:6001", grpc.WithInsecure())
	if e != nil {
		fmt.Println(e.Error())
		return
	}
	defer conn.Close()
	c := pb.NewHelloServiceClient(conn)

	// // say hello
	// r, e := c.SayHello(context.Background(), &pb.HelloRequest{Username: "ft"})
	// if e != nil {
	//     fmt.Println(e.Error())
	//     return
	// }
	// fmt.Println(r.Message)

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// chat
	chatClilent, e := c.Chat(context.Background())
	if e != nil {
		fmt.Println(e.Error())
		return
	}
	go func() {
		for {
			time.Sleep(3 * time.Second)
			stream, e := chatClilent.Recv()
			if e == io.EOF {
				fmt.Println("EOF")
				return
			}
			if e != nil {
				fmt.Println("-----err:", e)
				return
			}
			fmt.Println("client recv:", string(stream.Stream))
		}
	}()

	go func() {
		i := 0
		for {
			time.Sleep(3 * time.Second)
			chatClilent.Send(&pb.ClientStream{Stream: []byte("client send i:" + strconv.Itoa(i))})
			i++
		}
	}()
	select {
	case <-time.After(20 * time.Second):
	}
}
