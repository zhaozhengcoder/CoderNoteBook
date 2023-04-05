package main

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"os"
	"strings"

	"protoc-gen-demo/out/custom"

	"google.golang.org/protobuf/compiler/protogen"
	"google.golang.org/protobuf/proto"
	"google.golang.org/protobuf/reflect/protoreflect"
	"google.golang.org/protobuf/types/descriptorpb"
	"google.golang.org/protobuf/types/pluginpb"
)

// https://godocs.io/google.golang.org/protobuf/compiler/protogen
func main() {
	//1.读取标准输入，接收proto 解析的文件内容，并解析成结构体
	input, _ := ioutil.ReadAll(os.Stdin)
	var req pluginpb.CodeGeneratorRequest
	proto.Unmarshal(input, &req)

	//2.生成插件
	opts := protogen.Options{}
	plugin, err := opts.New(&req)
	if err != nil {
		panic(err)
	}

	pb_gen(plugin)

	// 生成响应
	stdout := plugin.Response()
	out, err := proto.Marshal(stdout)
	if err != nil {
		panic(err)
	}
	// 将响应写回标准输入, protoc会读取这个内容
	fmt.Fprintf(os.Stdout, string(out))
}

func pb_gen(plugin *protogen.Plugin) {
	pb_gen_hpp(plugin)
	pb_gen_cpp(plugin)
}

func pb_gen_hpp(plugin *protogen.Plugin) {
	// 3.在插件plugin.Files就是demo.proto 的内容了,是一个切片，每个切片元素代表一个文件内容
	// 我们只需要遍历这个文件就能获取到文件的信息了
	// 生成hpp文件
	for _, file := range plugin.Files {
		//创建一个buf 写入生成的文件内容

		var buf bytes.Buffer
		// 写入go 文件的package名
		content := ""
		content += pb_gen_hpp_header(file)

		//遍历消息,这个内容就是protobuf的每个消息
		for _, msg := range file.Messages {
			content += fmt.Sprintf("struct POD%s // pb name %s \n", msg.GoIdent.GoName, msg.GoIdent.GoName)
			content += fmt.Sprintf("{\n")
			//遍历消息的每个字段
			for _, field := range msg.Fields {
				custom_opt := ""
				if field_has_optcount(field) {
					value := field_get_optcount(field)
					if value != "" {
						custom_opt += fmt.Sprintf("[%s]", value)
					}
				}

				// https://godocs.io/google.golang.org/protobuf/reflect/protoreflect#Kind
				// https://pkg.go.dev/github.com/golang/protobuf/v2/reflect/protoreflect#Descriptor
				if field.Desc.Kind() == protoreflect.EnumKind {
					content += fmt.Sprintf("	%s::%s %s;  // %s  \n", msg.GoIdent.GoName, field.Desc.Enum().Name(), field.Desc.TextName(), field.Desc.Enum().Values())
				} else if field.Desc.Kind() == protoreflect.MessageKind {
					content += fmt.Sprintf("	POD%s %s%s;\n", field.Desc.Message().FullName(), field.Desc.TextName(), custom_opt)
				} else {
					content += fmt.Sprintf("	%s %s%s;  //  %s = %d \n", pb_to_cpp_type(field.Desc.Kind()), field.Desc.TextName(), custom_opt, field.Desc.TextName(), field.Desc.Number())
				}
			}

			// method
			content += fmt.Sprintf("\n	// method \n")
			content += fmt.Sprintf("	void clear();\n")
			content += fmt.Sprintf("	int pb2pod(const %s & pb);\n", msg.GoIdent.GoName)
			content += fmt.Sprintf("	int pod2pb(%s * pb);\n", msg.GoIdent.GoName)
			content += fmt.Sprintf("};\n\n")
		}

		content += fmt.Sprintf("#endif\n")
		buf.Write([]byte(content))
		//指定输入文件名,输出文件名为demo.foo.go
		filename := file.GeneratedFilenamePrefix + ".h"
		file := plugin.NewGeneratedFile(filename, ".")
		// 将内容写入插件文件内容
		file.Write(buf.Bytes())
	}
}

func pb_gen_cpp(plugin *protogen.Plugin) {
	// 生成cpp文件
	for _, file := range plugin.Files {
		//创建一个buf 写入生成的文件内容
		var buf bytes.Buffer
		content := ""
		content += pb_gen_cpp_header(file)

		//遍历消息,这个内容就是protobuf的每个消息
		for _, msg := range file.Messages {
			// method
			content += fmt.Sprintf("\n// method \n")

			// clear()
			content += fmt.Sprintf("void POD%s::clear()\n", msg.GoIdent.GoName)
			content += fmt.Sprintf("{\n")
			for _, field := range msg.Fields {
				opt_str := ""
				opt_noindex_str := ""
				if field_has_optcount(field) {
					field_cnt := field_get_optcount(field)
					content += fmt.Sprintf("	for (int i = 0; i < %s; i++) {\n", field_cnt)
					opt_str += "[i]"
					opt_noindex_str += "i"
				}

				if field.Desc.Kind() == protoreflect.EnumKind {
					if field.Desc.Enum().Values().Len() > 0 {
						content += fmt.Sprintf("	%s = %s::%s; \n", field.Desc.TextName(), msg.GoIdent.GoName, field.Desc.Enum().Values().Get(0).Name())
					}
				} else if field.Desc.Kind() == protoreflect.MessageKind {
					content += fmt.Sprintf("	%s%s.clear(); \n", field.Desc.TextName(), opt_str)
				} else {
					content += fmt.Sprintf("	%s%s = 0; \n", field.Desc.TextName(), opt_str)
				}

				if opt_str != "" {
					content += fmt.Sprintf("	}\n")
				}
			}
			content += fmt.Sprintf("}\n")
			content += fmt.Sprintf("\n")

			// pb2pod
			content += fmt.Sprintf("int POD%s::pb2pod(const %s & pb)\n", msg.GoIdent.GoName, msg.GoIdent.GoName)
			content += fmt.Sprintf("{\n")

			for _, field := range msg.Fields {
				opt_str := ""
				opt_noindex_str := ""
				if field_has_optcount(field) {
					field_cnt := field_get_optcount(field)
					content += fmt.Sprintf("	for (int i = 0; i < %s; i++) {\n", field_cnt)
					opt_str += "[i]"
					opt_noindex_str += "i"
				}

				if field.Desc.Kind() == protoreflect.MessageKind {
					content += fmt.Sprintf("		%s%s.pb2pod(pb.%s(%s)); \n", field.Desc.TextName(), opt_str, field.Desc.TextName(), opt_noindex_str)
				} else {
					content += fmt.Sprintf("		%s%s = pb.%s(%s); \n", field.Desc.TextName(), opt_str, field.Desc.TextName(), opt_noindex_str)
				}

				if opt_str != "" {
					content += fmt.Sprintf("	}\n")
				}
			}
			content += fmt.Sprintf("	return 0;\n")
			content += fmt.Sprintf("}\n")
			content += fmt.Sprintf("\n")

			// pod2pb
			content += fmt.Sprintf("int POD%s::pod2pb(%s * pb)\n", msg.GoIdent.GoName, msg.GoIdent.GoName)
			content += fmt.Sprintf("{\n")
			for _, field := range msg.Fields {

				opt_str := ""
				if field_has_optcount(field) {
					field_cnt := field_get_optcount(field)
					content += fmt.Sprintf("	for (int i = 0; i < %s; i++) {\n", field_cnt)
					opt_str += "[i]"
				}

				if field.Desc.Kind() == protoreflect.MessageKind {
					if opt_str != "" {
						content += fmt.Sprintf("	%s%s.pod2pb(pb->add_%s()); \n", field.Desc.TextName(), opt_str, field.Desc.TextName())
					} else {
						content += fmt.Sprintf("	%s.pod2pb(pb->mutable_%s()); \n", field.Desc.TextName(), field.Desc.TextName())
					}
				} else {
					if opt_str != "" {
						content += fmt.Sprintf("	pb->add_%s(%s%s); \n", field.Desc.TextName(), field.Desc.TextName(), opt_str)
					} else {
						content += fmt.Sprintf("	pb->set_%s(%s); \n", field.Desc.TextName(), field.Desc.TextName())
					}
				}

				if opt_str != "" {
					content += fmt.Sprintf("	}\n")
				}
			}
			content += fmt.Sprintf("	return 0;\n")
			content += fmt.Sprintf("}\n")
			content += fmt.Sprintf("\n")
		}
		buf.Write([]byte(content))
		//指定输入文件名,输出文件名为demo.foo.go
		filename := file.GeneratedFilenamePrefix + ".cpp"
		file := plugin.NewGeneratedFile(filename, ".")
		// 将内容写入插件文件内容
		file.Write(buf.Bytes())
	}
}

func pb_gen_hpp_header(file *protogen.File) string {
	content := ""
	file_name_str := strings.Split(file.GeneratedFilenamePrefix, "/")
	content += fmt.Sprintf("#ifndef __%s_H_\n", strings.ToUpper(file_name_str[len(file_name_str)-1]))
	content += fmt.Sprintf("#define __%s_H_\n\n", strings.ToUpper(file_name_str[len(file_name_str)-1]))

	content += fmt.Sprintf("#include <cstdint>\n")
	content += fmt.Sprintf("#include \"%s.pb.h\" \n", file_name_str[len(file_name_str)-1])
	return content
}

func pb_gen_cpp_header(file *protogen.File) string {
	content := ""
	file_name_str := strings.Split(file.GeneratedFilenamePrefix, "/")
	content += fmt.Sprintf("#include \"%s.h\" \n", file_name_str[len(file_name_str)-1])
	content += fmt.Sprintf("#include \"%s.pb.h\" \n", file_name_str[len(file_name_str)-1])
	return content
}

func pb_to_cpp_type(pb_type protoreflect.Kind) string {
	switch pb_type {
	case protoreflect.BoolKind:
		return "bool"
	case protoreflect.Int32Kind:
	case protoreflect.Sint32Kind:
		return "int32_t"

	case protoreflect.Uint32Kind:
		return "uint32_t"

	case protoreflect.Sint64Kind:
	case protoreflect.Int64Kind:
		return "int64_t"
	case protoreflect.Uint64Kind:
		return "uint64_t"
	case protoreflect.MessageKind:
		return "Message"
	default:
		return "unkown_type"
	}
	return "unkown_type"
}

// https://pkg.go.dev/google.golang.org/protobuf/compiler/protogen#Plugin
// https://stackoverflow.com/questions/69311708/how-to-retrieve-fieldoption-value
// https://pkg.go.dev/google.golang.org/protobuf/proto#GetExtension
func GetOptionMaxCount(field *descriptorpb.FieldOptions) string {
	if field == nil {
		return ""
	}
	v := proto.GetExtension(field, custom.E_OptCount)
	str := fmt.Sprintf("%v", v)
	return str
}

func field_has_optcount(field *protogen.Field) bool {
	op, ok := field.Desc.Options().(*descriptorpb.FieldOptions)
	if ok == false {
		return false
	}

	if op == nil {
		return false
	}

	v := proto.GetExtension(op, custom.E_OptCount)
	str := fmt.Sprintf("%v", v)
	if str == "" {
		return false
	}
	return true
}

func field_get_optcount(field *protogen.Field) string {
	op, ok := field.Desc.Options().(*descriptorpb.FieldOptions)
	if ok == false {
		return ""
	}

	if op == nil {
		return ""
	}
	v := proto.GetExtension(op, custom.E_OptCount)
	str := fmt.Sprintf("%v", v)
	return str
}
