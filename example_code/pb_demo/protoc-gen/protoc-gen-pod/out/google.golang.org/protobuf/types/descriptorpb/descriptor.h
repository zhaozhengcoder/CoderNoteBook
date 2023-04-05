#ifndef __DESCRIPTOR_H_
#define __DESCRIPTOR_H_

#include <cstdint>
#include "descriptor.pb.h" 
struct PODFileDescriptorSet // pb name FileDescriptorSet 
{
	PODgoogle.protobuf.FileDescriptorProto file;

	// method 
	void clear();
	int pb2pod(const FileDescriptorSet & pb);
	int pod2pb(FileDescriptorSet * pb);
};

struct PODFileDescriptorProto // pb name FileDescriptorProto 
{
	unkown_type name;  //  name = 1 
	unkown_type package;  //  package = 2 
	unkown_type dependency;  //  dependency = 3 
	unkown_type public_dependency;  //  public_dependency = 10 
	unkown_type weak_dependency;  //  weak_dependency = 11 
	PODgoogle.protobuf.DescriptorProto message_type;
	PODgoogle.protobuf.EnumDescriptorProto enum_type;
	PODgoogle.protobuf.ServiceDescriptorProto service;
	PODgoogle.protobuf.FieldDescriptorProto extension;
	PODgoogle.protobuf.FileOptions options;
	PODgoogle.protobuf.SourceCodeInfo source_code_info;
	unkown_type syntax;  //  syntax = 12 

	// method 
	void clear();
	int pb2pod(const FileDescriptorProto & pb);
	int pod2pb(FileDescriptorProto * pb);
};

struct PODDescriptorProto // pb name DescriptorProto 
{
	unkown_type name;  //  name = 1 
	PODgoogle.protobuf.FieldDescriptorProto field;
	PODgoogle.protobuf.FieldDescriptorProto extension;
	PODgoogle.protobuf.DescriptorProto nested_type;
	PODgoogle.protobuf.EnumDescriptorProto enum_type;
	PODgoogle.protobuf.DescriptorProto.ExtensionRange extension_range;
	PODgoogle.protobuf.OneofDescriptorProto oneof_decl;
	PODgoogle.protobuf.MessageOptions options;
	PODgoogle.protobuf.DescriptorProto.ReservedRange reserved_range;
	unkown_type reserved_name;  //  reserved_name = 10 

	// method 
	void clear();
	int pb2pod(const DescriptorProto & pb);
	int pod2pb(DescriptorProto * pb);
};

struct PODExtensionRangeOptions // pb name ExtensionRangeOptions 
{
	PODgoogle.protobuf.UninterpretedOption uninterpreted_option;

	// method 
	void clear();
	int pb2pod(const ExtensionRangeOptions & pb);
	int pod2pb(ExtensionRangeOptions * pb);
};

struct PODFieldDescriptorProto // pb name FieldDescriptorProto 
{
	unkown_type name;  //  name = 1 
	unkown_type number;  //  number = 3 
	FieldDescriptorProto::Label label;  // EnumValues{{Name: LABEL_OPTIONAL, Number: 1}, {Name: LABEL_REQUIRED, Number: 2}, {Name: LABEL_REPEATED, Number: 3}}  
	FieldDescriptorProto::Type type;  // EnumValues{{Name: TYPE_DOUBLE, Number: 1}, {Name: TYPE_FLOAT, Number: 2}, {Name: TYPE_INT64, Number: 3}, {Name: TYPE_UINT64, Number: 4}, {Name: TYPE_INT32, Number: 5}, {Name: TYPE_FIXED64, Number: 6}, {Name: TYPE_FIXED32, Number: 7}, {Name: TYPE_BOOL, Number: 8}, {Name: TYPE_STRING, Number: 9}, {Name: TYPE_GROUP, Number: 10}, {Name: TYPE_MESSAGE, Number: 11}, {Name: TYPE_BYTES, Number: 12}, {Name: TYPE_UINT32, Number: 13}, {Name: TYPE_ENUM, Number: 14}, {Name: TYPE_SFIXED32, Number: 15}, {Name: TYPE_SFIXED64, Number: 16}, {Name: TYPE_SINT32, Number: 17}, {Name: TYPE_SINT64, Number: 18}}  
	unkown_type type_name;  //  type_name = 6 
	unkown_type extendee;  //  extendee = 2 
	unkown_type default_value;  //  default_value = 7 
	unkown_type oneof_index;  //  oneof_index = 9 
	unkown_type json_name;  //  json_name = 10 
	PODgoogle.protobuf.FieldOptions options;
	bool proto3_optional;  //  proto3_optional = 17 

	// method 
	void clear();
	int pb2pod(const FieldDescriptorProto & pb);
	int pod2pb(FieldDescriptorProto * pb);
};

struct PODOneofDescriptorProto // pb name OneofDescriptorProto 
{
	unkown_type name;  //  name = 1 
	PODgoogle.protobuf.OneofOptions options;

	// method 
	void clear();
	int pb2pod(const OneofDescriptorProto & pb);
	int pod2pb(OneofDescriptorProto * pb);
};

struct PODEnumDescriptorProto // pb name EnumDescriptorProto 
{
	unkown_type name;  //  name = 1 
	PODgoogle.protobuf.EnumValueDescriptorProto value;
	PODgoogle.protobuf.EnumOptions options;
	PODgoogle.protobuf.EnumDescriptorProto.EnumReservedRange reserved_range;
	unkown_type reserved_name;  //  reserved_name = 5 

	// method 
	void clear();
	int pb2pod(const EnumDescriptorProto & pb);
	int pod2pb(EnumDescriptorProto * pb);
};

struct PODEnumValueDescriptorProto // pb name EnumValueDescriptorProto 
{
	unkown_type name;  //  name = 1 
	unkown_type number;  //  number = 2 
	PODgoogle.protobuf.EnumValueOptions options;

	// method 
	void clear();
	int pb2pod(const EnumValueDescriptorProto & pb);
	int pod2pb(EnumValueDescriptorProto * pb);
};

struct PODServiceDescriptorProto // pb name ServiceDescriptorProto 
{
	unkown_type name;  //  name = 1 
	PODgoogle.protobuf.MethodDescriptorProto method;
	PODgoogle.protobuf.ServiceOptions options;

	// method 
	void clear();
	int pb2pod(const ServiceDescriptorProto & pb);
	int pod2pb(ServiceDescriptorProto * pb);
};

struct PODMethodDescriptorProto // pb name MethodDescriptorProto 
{
	unkown_type name;  //  name = 1 
	unkown_type input_type;  //  input_type = 2 
	unkown_type output_type;  //  output_type = 3 
	PODgoogle.protobuf.MethodOptions options;
	bool client_streaming;  //  client_streaming = 5 
	bool server_streaming;  //  server_streaming = 6 

	// method 
	void clear();
	int pb2pod(const MethodDescriptorProto & pb);
	int pod2pb(MethodDescriptorProto * pb);
};

struct PODFileOptions // pb name FileOptions 
{
	unkown_type java_package;  //  java_package = 1 
	unkown_type java_outer_classname;  //  java_outer_classname = 8 
	bool java_multiple_files;  //  java_multiple_files = 10 
	bool java_generate_equals_and_hash[0];  //  java_generate_equals_and_hash = 20 
	bool java_string_check_utf8;  //  java_string_check_utf8 = 27 
	FileOptions::OptimizeMode optimize_for;  // EnumValues{{Name: SPEED, Number: 1}, {Name: CODE_SIZE, Number: 2}, {Name: LITE_RUNTIME, Number: 3}}  
	unkown_type go_package;  //  go_package = 11 
	bool cc_generic_services;  //  cc_generic_services = 16 
	bool java_generic_services;  //  java_generic_services = 17 
	bool py_generic_services;  //  py_generic_services = 18 
	bool php_generic_services;  //  php_generic_services = 42 
	bool deprecated;  //  deprecated = 23 
	bool cc_enable_arenas;  //  cc_enable_arenas = 31 
	unkown_type objc_class_prefix;  //  objc_class_prefix = 36 
	unkown_type csharp_namespace;  //  csharp_namespace = 37 
	unkown_type swift_prefix;  //  swift_prefix = 39 
	unkown_type php_class_prefix;  //  php_class_prefix = 40 
	unkown_type php_namespace;  //  php_namespace = 41 
	unkown_type php_metadata_namespace;  //  php_metadata_namespace = 44 
	unkown_type ruby_package;  //  ruby_package = 45 
	PODgoogle.protobuf.UninterpretedOption uninterpreted_option;

	// method 
	void clear();
	int pb2pod(const FileOptions & pb);
	int pod2pb(FileOptions * pb);
};

struct PODMessageOptions // pb name MessageOptions 
{
	bool message_set_wire_format;  //  message_set_wire_format = 1 
	bool no_standard_descriptor_accessor;  //  no_standard_descriptor_accessor = 2 
	bool deprecated;  //  deprecated = 3 
	bool map_entry;  //  map_entry = 7 
	PODgoogle.protobuf.UninterpretedOption uninterpreted_option;

	// method 
	void clear();
	int pb2pod(const MessageOptions & pb);
	int pod2pb(MessageOptions * pb);
};

struct PODFieldOptions // pb name FieldOptions 
{
	FieldOptions::CType ctype;  // EnumValues{{Name: STRING}, {Name: CORD, Number: 1}, {Name: STRING_PIECE, Number: 2}}  
	bool packed;  //  packed = 2 
	FieldOptions::JSType jstype;  // EnumValues{{Name: JS_NORMAL}, {Name: JS_STRING, Number: 1}, {Name: JS_NUMBER, Number: 2}}  
	bool lazy;  //  lazy = 5 
	bool deprecated;  //  deprecated = 3 
	bool weak;  //  weak = 10 
	PODgoogle.protobuf.UninterpretedOption uninterpreted_option;

	// method 
	void clear();
	int pb2pod(const FieldOptions & pb);
	int pod2pb(FieldOptions * pb);
};

struct PODOneofOptions // pb name OneofOptions 
{
	PODgoogle.protobuf.UninterpretedOption uninterpreted_option;

	// method 
	void clear();
	int pb2pod(const OneofOptions & pb);
	int pod2pb(OneofOptions * pb);
};

struct PODEnumOptions // pb name EnumOptions 
{
	bool allow_alias;  //  allow_alias = 2 
	bool deprecated;  //  deprecated = 3 
	PODgoogle.protobuf.UninterpretedOption uninterpreted_option;

	// method 
	void clear();
	int pb2pod(const EnumOptions & pb);
	int pod2pb(EnumOptions * pb);
};

struct PODEnumValueOptions // pb name EnumValueOptions 
{
	bool deprecated;  //  deprecated = 1 
	PODgoogle.protobuf.UninterpretedOption uninterpreted_option;

	// method 
	void clear();
	int pb2pod(const EnumValueOptions & pb);
	int pod2pb(EnumValueOptions * pb);
};

struct PODServiceOptions // pb name ServiceOptions 
{
	bool deprecated;  //  deprecated = 33 
	PODgoogle.protobuf.UninterpretedOption uninterpreted_option;

	// method 
	void clear();
	int pb2pod(const ServiceOptions & pb);
	int pod2pb(ServiceOptions * pb);
};

struct PODMethodOptions // pb name MethodOptions 
{
	bool deprecated;  //  deprecated = 33 
	MethodOptions::IdempotencyLevel idempotency_level;  // EnumValues{{Name: IDEMPOTENCY_UNKNOWN}, {Name: NO_SIDE_EFFECTS, Number: 1}, {Name: IDEMPOTENT, Number: 2}}  
	PODgoogle.protobuf.UninterpretedOption uninterpreted_option;

	// method 
	void clear();
	int pb2pod(const MethodOptions & pb);
	int pod2pb(MethodOptions * pb);
};

struct PODUninterpretedOption // pb name UninterpretedOption 
{
	PODgoogle.protobuf.UninterpretedOption.NamePart name;
	unkown_type identifier_value;  //  identifier_value = 3 
	uint64_t positive_int_value;  //  positive_int_value = 4 
	int64_t negative_int_value;  //  negative_int_value = 5 
	unkown_type double_value;  //  double_value = 6 
	unkown_type string_value;  //  string_value = 7 
	unkown_type aggregate_value;  //  aggregate_value = 8 

	// method 
	void clear();
	int pb2pod(const UninterpretedOption & pb);
	int pod2pb(UninterpretedOption * pb);
};

struct PODSourceCodeInfo // pb name SourceCodeInfo 
{
	PODgoogle.protobuf.SourceCodeInfo.Location location;

	// method 
	void clear();
	int pb2pod(const SourceCodeInfo & pb);
	int pod2pb(SourceCodeInfo * pb);
};

struct PODGeneratedCodeInfo // pb name GeneratedCodeInfo 
{
	PODgoogle.protobuf.GeneratedCodeInfo.Annotation annotation;

	// method 
	void clear();
	int pb2pod(const GeneratedCodeInfo & pb);
	int pod2pb(GeneratedCodeInfo * pb);
};

#endif
