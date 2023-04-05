package main

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"os"

	"google.golang.org/protobuf/compiler/protogen"
	"google.golang.org/protobuf/proto"
	"google.golang.org/protobuf/types/pluginpb"
)

func main() {
	// 1. 读取标准输入，接收proto 解析的文件内容，并解析成结构体
	input, _ := ioutil.ReadAll(os.Stdin)
	var req pluginpb.CodeGeneratorRequest
	proto.Unmarshal(input, &req)

	// 2. 生成插件
	opts := protogen.Options{}
	plugin, err := opts.New(&req)
	if err != nil {
		panic(err)
	}

	// 3. 写入内容
	var buf bytes.Buffer
	pkg := fmt.Sprintf("hello world")
	buf.Write([]byte(pkg))

	// 指定输入文件名
	filename := "hello.txt"
	file := plugin.NewGeneratedFile(filename, ".")
	// 将内容写入插件文件内容
	file.Write(buf.Bytes())

	// 4. 生成响应
	stdout := plugin.Response()
	out, err := proto.Marshal(stdout)
	if err != nil {
		panic(err)
	}

	// 5. 将响应写回标准输入, protoc会读取这个内容
	fmt.Fprintf(os.Stdout, string(out))
}
