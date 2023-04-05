# golang 使用 protobuff hello world 教程

## 为什么要protobuff ？

    protobuff的序列化和反序列化编码实现：
    https://www.jianshu.com/p/131f0bf218ef

## hello world

目录结构：
```
.
├── person.pb.go
├── person.proto
└── server.go
```

person.proto
```
syntax = "proto3";

package main;

message Person {
    string name = 1;
    int32 age = 2;
}
```

server.go 
```
package main

import (
	"fmt"
	"log"

	proto "github.com/golang/protobuf/proto"
)

func main() {
	fmt.Println("hello proto")

	elliot := &Person{
		Name: "elliot",
		Age:  24,
	}

	data, err := proto.Marshal(elliot)
	if err != nil {
		log.Fatal("Marshal error : ", err)
	}
	fmt.Println(data)

	newElliot := &Person{}
	err = proto.Unmarshal(data, newElliot)
	if err != nil {
		log.Fatal("unmarshal error : ", err)
	}

	fmt.Println(newElliot.GetAge())
	fmt.Println(newElliot.GetName())
}
```

构建：
```
# 根据proto，导出.go 文件
protoc --go_out=./ *.proto

# run
go run server.go person.pb.go
```