#include "descriptor.h" 
#include "descriptor.pb.h" 

// method 
void PODFileDescriptorSet::clear()
{
	file.clear(); 
}

int PODFileDescriptorSet::pb2pod(const FileDescriptorSet & pb)
{
		file.pb2pod(pb.file()); 
	return 0;
}

int PODFileDescriptorSet::pod2pb(FileDescriptorSet * pb)
{
	file.pod2pb(pb->mutable_file()); 
	return 0;
}


// method 
void PODFileDescriptorProto::clear()
{
	name = 0; 
	package = 0; 
	dependency = 0; 
	public_dependency = 0; 
	weak_dependency = 0; 
	message_type.clear(); 
	enum_type.clear(); 
	service.clear(); 
	extension.clear(); 
	options.clear(); 
	source_code_info.clear(); 
	syntax = 0; 
}

int PODFileDescriptorProto::pb2pod(const FileDescriptorProto & pb)
{
		name = pb.name(); 
		package = pb.package(); 
		dependency = pb.dependency(); 
		public_dependency = pb.public_dependency(); 
		weak_dependency = pb.weak_dependency(); 
		message_type.pb2pod(pb.message_type()); 
		enum_type.pb2pod(pb.enum_type()); 
		service.pb2pod(pb.service()); 
		extension.pb2pod(pb.extension()); 
		options.pb2pod(pb.options()); 
		source_code_info.pb2pod(pb.source_code_info()); 
		syntax = pb.syntax(); 
	return 0;
}

int PODFileDescriptorProto::pod2pb(FileDescriptorProto * pb)
{
	pb->set_name(name); 
	pb->set_package(package); 
	pb->set_dependency(dependency); 
	pb->set_public_dependency(public_dependency); 
	pb->set_weak_dependency(weak_dependency); 
	message_type.pod2pb(pb->mutable_message_type()); 
	enum_type.pod2pb(pb->mutable_enum_type()); 
	service.pod2pb(pb->mutable_service()); 
	extension.pod2pb(pb->mutable_extension()); 
	options.pod2pb(pb->mutable_options()); 
	source_code_info.pod2pb(pb->mutable_source_code_info()); 
	pb->set_syntax(syntax); 
	return 0;
}


// method 
void PODDescriptorProto::clear()
{
	name = 0; 
	field.clear(); 
	extension.clear(); 
	nested_type.clear(); 
	enum_type.clear(); 
	extension_range.clear(); 
	oneof_decl.clear(); 
	options.clear(); 
	reserved_range.clear(); 
	reserved_name = 0; 
}

int PODDescriptorProto::pb2pod(const DescriptorProto & pb)
{
		name = pb.name(); 
		field.pb2pod(pb.field()); 
		extension.pb2pod(pb.extension()); 
		nested_type.pb2pod(pb.nested_type()); 
		enum_type.pb2pod(pb.enum_type()); 
		extension_range.pb2pod(pb.extension_range()); 
		oneof_decl.pb2pod(pb.oneof_decl()); 
		options.pb2pod(pb.options()); 
		reserved_range.pb2pod(pb.reserved_range()); 
		reserved_name = pb.reserved_name(); 
	return 0;
}

int PODDescriptorProto::pod2pb(DescriptorProto * pb)
{
	pb->set_name(name); 
	field.pod2pb(pb->mutable_field()); 
	extension.pod2pb(pb->mutable_extension()); 
	nested_type.pod2pb(pb->mutable_nested_type()); 
	enum_type.pod2pb(pb->mutable_enum_type()); 
	extension_range.pod2pb(pb->mutable_extension_range()); 
	oneof_decl.pod2pb(pb->mutable_oneof_decl()); 
	options.pod2pb(pb->mutable_options()); 
	reserved_range.pod2pb(pb->mutable_reserved_range()); 
	pb->set_reserved_name(reserved_name); 
	return 0;
}


// method 
void PODExtensionRangeOptions::clear()
{
	uninterpreted_option.clear(); 
}

int PODExtensionRangeOptions::pb2pod(const ExtensionRangeOptions & pb)
{
		uninterpreted_option.pb2pod(pb.uninterpreted_option()); 
	return 0;
}

int PODExtensionRangeOptions::pod2pb(ExtensionRangeOptions * pb)
{
	uninterpreted_option.pod2pb(pb->mutable_uninterpreted_option()); 
	return 0;
}


// method 
void PODFieldDescriptorProto::clear()
{
	name = 0; 
	number = 0; 
	label = FieldDescriptorProto::LABEL_OPTIONAL; 
	type = FieldDescriptorProto::TYPE_DOUBLE; 
	type_name = 0; 
	extendee = 0; 
	default_value = 0; 
	oneof_index = 0; 
	json_name = 0; 
	options.clear(); 
	proto3_optional = 0; 
}

int PODFieldDescriptorProto::pb2pod(const FieldDescriptorProto & pb)
{
		name = pb.name(); 
		number = pb.number(); 
		label = pb.label(); 
		type = pb.type(); 
		type_name = pb.type_name(); 
		extendee = pb.extendee(); 
		default_value = pb.default_value(); 
		oneof_index = pb.oneof_index(); 
		json_name = pb.json_name(); 
		options.pb2pod(pb.options()); 
		proto3_optional = pb.proto3_optional(); 
	return 0;
}

int PODFieldDescriptorProto::pod2pb(FieldDescriptorProto * pb)
{
	pb->set_name(name); 
	pb->set_number(number); 
	pb->set_label(label); 
	pb->set_type(type); 
	pb->set_type_name(type_name); 
	pb->set_extendee(extendee); 
	pb->set_default_value(default_value); 
	pb->set_oneof_index(oneof_index); 
	pb->set_json_name(json_name); 
	options.pod2pb(pb->mutable_options()); 
	pb->set_proto3_optional(proto3_optional); 
	return 0;
}


// method 
void PODOneofDescriptorProto::clear()
{
	name = 0; 
	options.clear(); 
}

int PODOneofDescriptorProto::pb2pod(const OneofDescriptorProto & pb)
{
		name = pb.name(); 
		options.pb2pod(pb.options()); 
	return 0;
}

int PODOneofDescriptorProto::pod2pb(OneofDescriptorProto * pb)
{
	pb->set_name(name); 
	options.pod2pb(pb->mutable_options()); 
	return 0;
}


// method 
void PODEnumDescriptorProto::clear()
{
	name = 0; 
	value.clear(); 
	options.clear(); 
	reserved_range.clear(); 
	reserved_name = 0; 
}

int PODEnumDescriptorProto::pb2pod(const EnumDescriptorProto & pb)
{
		name = pb.name(); 
		value.pb2pod(pb.value()); 
		options.pb2pod(pb.options()); 
		reserved_range.pb2pod(pb.reserved_range()); 
		reserved_name = pb.reserved_name(); 
	return 0;
}

int PODEnumDescriptorProto::pod2pb(EnumDescriptorProto * pb)
{
	pb->set_name(name); 
	value.pod2pb(pb->mutable_value()); 
	options.pod2pb(pb->mutable_options()); 
	reserved_range.pod2pb(pb->mutable_reserved_range()); 
	pb->set_reserved_name(reserved_name); 
	return 0;
}


// method 
void PODEnumValueDescriptorProto::clear()
{
	name = 0; 
	number = 0; 
	options.clear(); 
}

int PODEnumValueDescriptorProto::pb2pod(const EnumValueDescriptorProto & pb)
{
		name = pb.name(); 
		number = pb.number(); 
		options.pb2pod(pb.options()); 
	return 0;
}

int PODEnumValueDescriptorProto::pod2pb(EnumValueDescriptorProto * pb)
{
	pb->set_name(name); 
	pb->set_number(number); 
	options.pod2pb(pb->mutable_options()); 
	return 0;
}


// method 
void PODServiceDescriptorProto::clear()
{
	name = 0; 
	method.clear(); 
	options.clear(); 
}

int PODServiceDescriptorProto::pb2pod(const ServiceDescriptorProto & pb)
{
		name = pb.name(); 
		method.pb2pod(pb.method()); 
		options.pb2pod(pb.options()); 
	return 0;
}

int PODServiceDescriptorProto::pod2pb(ServiceDescriptorProto * pb)
{
	pb->set_name(name); 
	method.pod2pb(pb->mutable_method()); 
	options.pod2pb(pb->mutable_options()); 
	return 0;
}


// method 
void PODMethodDescriptorProto::clear()
{
	name = 0; 
	input_type = 0; 
	output_type = 0; 
	options.clear(); 
	client_streaming = 0; 
	server_streaming = 0; 
}

int PODMethodDescriptorProto::pb2pod(const MethodDescriptorProto & pb)
{
		name = pb.name(); 
		input_type = pb.input_type(); 
		output_type = pb.output_type(); 
		options.pb2pod(pb.options()); 
		client_streaming = pb.client_streaming(); 
		server_streaming = pb.server_streaming(); 
	return 0;
}

int PODMethodDescriptorProto::pod2pb(MethodDescriptorProto * pb)
{
	pb->set_name(name); 
	pb->set_input_type(input_type); 
	pb->set_output_type(output_type); 
	options.pod2pb(pb->mutable_options()); 
	pb->set_client_streaming(client_streaming); 
	pb->set_server_streaming(server_streaming); 
	return 0;
}


// method 
void PODFileOptions::clear()
{
	java_package = 0; 
	java_outer_classname = 0; 
	java_multiple_files = 0; 
	for (int i = 0; i < 0; i++) {
	java_generate_equals_and_hash[i] = 0; 
	}
	java_string_check_utf8 = 0; 
	optimize_for = FileOptions::SPEED; 
	go_package = 0; 
	cc_generic_services = 0; 
	java_generic_services = 0; 
	py_generic_services = 0; 
	php_generic_services = 0; 
	deprecated = 0; 
	cc_enable_arenas = 0; 
	objc_class_prefix = 0; 
	csharp_namespace = 0; 
	swift_prefix = 0; 
	php_class_prefix = 0; 
	php_namespace = 0; 
	php_metadata_namespace = 0; 
	ruby_package = 0; 
	uninterpreted_option.clear(); 
}

int PODFileOptions::pb2pod(const FileOptions & pb)
{
		java_package = pb.java_package(); 
		java_outer_classname = pb.java_outer_classname(); 
		java_multiple_files = pb.java_multiple_files(); 
	for (int i = 0; i < 0; i++) {
		java_generate_equals_and_hash[i] = pb.java_generate_equals_and_hash(i); 
	}
		java_string_check_utf8 = pb.java_string_check_utf8(); 
		optimize_for = pb.optimize_for(); 
		go_package = pb.go_package(); 
		cc_generic_services = pb.cc_generic_services(); 
		java_generic_services = pb.java_generic_services(); 
		py_generic_services = pb.py_generic_services(); 
		php_generic_services = pb.php_generic_services(); 
		deprecated = pb.deprecated(); 
		cc_enable_arenas = pb.cc_enable_arenas(); 
		objc_class_prefix = pb.objc_class_prefix(); 
		csharp_namespace = pb.csharp_namespace(); 
		swift_prefix = pb.swift_prefix(); 
		php_class_prefix = pb.php_class_prefix(); 
		php_namespace = pb.php_namespace(); 
		php_metadata_namespace = pb.php_metadata_namespace(); 
		ruby_package = pb.ruby_package(); 
		uninterpreted_option.pb2pod(pb.uninterpreted_option()); 
	return 0;
}

int PODFileOptions::pod2pb(FileOptions * pb)
{
	pb->set_java_package(java_package); 
	pb->set_java_outer_classname(java_outer_classname); 
	pb->set_java_multiple_files(java_multiple_files); 
	for (int i = 0; i < 0; i++) {
	pb->add_java_generate_equals_and_hash(java_generate_equals_and_hash[i]); 
	}
	pb->set_java_string_check_utf8(java_string_check_utf8); 
	pb->set_optimize_for(optimize_for); 
	pb->set_go_package(go_package); 
	pb->set_cc_generic_services(cc_generic_services); 
	pb->set_java_generic_services(java_generic_services); 
	pb->set_py_generic_services(py_generic_services); 
	pb->set_php_generic_services(php_generic_services); 
	pb->set_deprecated(deprecated); 
	pb->set_cc_enable_arenas(cc_enable_arenas); 
	pb->set_objc_class_prefix(objc_class_prefix); 
	pb->set_csharp_namespace(csharp_namespace); 
	pb->set_swift_prefix(swift_prefix); 
	pb->set_php_class_prefix(php_class_prefix); 
	pb->set_php_namespace(php_namespace); 
	pb->set_php_metadata_namespace(php_metadata_namespace); 
	pb->set_ruby_package(ruby_package); 
	uninterpreted_option.pod2pb(pb->mutable_uninterpreted_option()); 
	return 0;
}


// method 
void PODMessageOptions::clear()
{
	message_set_wire_format = 0; 
	no_standard_descriptor_accessor = 0; 
	deprecated = 0; 
	map_entry = 0; 
	uninterpreted_option.clear(); 
}

int PODMessageOptions::pb2pod(const MessageOptions & pb)
{
		message_set_wire_format = pb.message_set_wire_format(); 
		no_standard_descriptor_accessor = pb.no_standard_descriptor_accessor(); 
		deprecated = pb.deprecated(); 
		map_entry = pb.map_entry(); 
		uninterpreted_option.pb2pod(pb.uninterpreted_option()); 
	return 0;
}

int PODMessageOptions::pod2pb(MessageOptions * pb)
{
	pb->set_message_set_wire_format(message_set_wire_format); 
	pb->set_no_standard_descriptor_accessor(no_standard_descriptor_accessor); 
	pb->set_deprecated(deprecated); 
	pb->set_map_entry(map_entry); 
	uninterpreted_option.pod2pb(pb->mutable_uninterpreted_option()); 
	return 0;
}


// method 
void PODFieldOptions::clear()
{
	ctype = FieldOptions::STRING; 
	packed = 0; 
	jstype = FieldOptions::JS_NORMAL; 
	lazy = 0; 
	deprecated = 0; 
	weak = 0; 
	uninterpreted_option.clear(); 
}

int PODFieldOptions::pb2pod(const FieldOptions & pb)
{
		ctype = pb.ctype(); 
		packed = pb.packed(); 
		jstype = pb.jstype(); 
		lazy = pb.lazy(); 
		deprecated = pb.deprecated(); 
		weak = pb.weak(); 
		uninterpreted_option.pb2pod(pb.uninterpreted_option()); 
	return 0;
}

int PODFieldOptions::pod2pb(FieldOptions * pb)
{
	pb->set_ctype(ctype); 
	pb->set_packed(packed); 
	pb->set_jstype(jstype); 
	pb->set_lazy(lazy); 
	pb->set_deprecated(deprecated); 
	pb->set_weak(weak); 
	uninterpreted_option.pod2pb(pb->mutable_uninterpreted_option()); 
	return 0;
}


// method 
void PODOneofOptions::clear()
{
	uninterpreted_option.clear(); 
}

int PODOneofOptions::pb2pod(const OneofOptions & pb)
{
		uninterpreted_option.pb2pod(pb.uninterpreted_option()); 
	return 0;
}

int PODOneofOptions::pod2pb(OneofOptions * pb)
{
	uninterpreted_option.pod2pb(pb->mutable_uninterpreted_option()); 
	return 0;
}


// method 
void PODEnumOptions::clear()
{
	allow_alias = 0; 
	deprecated = 0; 
	uninterpreted_option.clear(); 
}

int PODEnumOptions::pb2pod(const EnumOptions & pb)
{
		allow_alias = pb.allow_alias(); 
		deprecated = pb.deprecated(); 
		uninterpreted_option.pb2pod(pb.uninterpreted_option()); 
	return 0;
}

int PODEnumOptions::pod2pb(EnumOptions * pb)
{
	pb->set_allow_alias(allow_alias); 
	pb->set_deprecated(deprecated); 
	uninterpreted_option.pod2pb(pb->mutable_uninterpreted_option()); 
	return 0;
}


// method 
void PODEnumValueOptions::clear()
{
	deprecated = 0; 
	uninterpreted_option.clear(); 
}

int PODEnumValueOptions::pb2pod(const EnumValueOptions & pb)
{
		deprecated = pb.deprecated(); 
		uninterpreted_option.pb2pod(pb.uninterpreted_option()); 
	return 0;
}

int PODEnumValueOptions::pod2pb(EnumValueOptions * pb)
{
	pb->set_deprecated(deprecated); 
	uninterpreted_option.pod2pb(pb->mutable_uninterpreted_option()); 
	return 0;
}


// method 
void PODServiceOptions::clear()
{
	deprecated = 0; 
	uninterpreted_option.clear(); 
}

int PODServiceOptions::pb2pod(const ServiceOptions & pb)
{
		deprecated = pb.deprecated(); 
		uninterpreted_option.pb2pod(pb.uninterpreted_option()); 
	return 0;
}

int PODServiceOptions::pod2pb(ServiceOptions * pb)
{
	pb->set_deprecated(deprecated); 
	uninterpreted_option.pod2pb(pb->mutable_uninterpreted_option()); 
	return 0;
}


// method 
void PODMethodOptions::clear()
{
	deprecated = 0; 
	idempotency_level = MethodOptions::IDEMPOTENCY_UNKNOWN; 
	uninterpreted_option.clear(); 
}

int PODMethodOptions::pb2pod(const MethodOptions & pb)
{
		deprecated = pb.deprecated(); 
		idempotency_level = pb.idempotency_level(); 
		uninterpreted_option.pb2pod(pb.uninterpreted_option()); 
	return 0;
}

int PODMethodOptions::pod2pb(MethodOptions * pb)
{
	pb->set_deprecated(deprecated); 
	pb->set_idempotency_level(idempotency_level); 
	uninterpreted_option.pod2pb(pb->mutable_uninterpreted_option()); 
	return 0;
}


// method 
void PODUninterpretedOption::clear()
{
	name.clear(); 
	identifier_value = 0; 
	positive_int_value = 0; 
	negative_int_value = 0; 
	double_value = 0; 
	string_value = 0; 
	aggregate_value = 0; 
}

int PODUninterpretedOption::pb2pod(const UninterpretedOption & pb)
{
		name.pb2pod(pb.name()); 
		identifier_value = pb.identifier_value(); 
		positive_int_value = pb.positive_int_value(); 
		negative_int_value = pb.negative_int_value(); 
		double_value = pb.double_value(); 
		string_value = pb.string_value(); 
		aggregate_value = pb.aggregate_value(); 
	return 0;
}

int PODUninterpretedOption::pod2pb(UninterpretedOption * pb)
{
	name.pod2pb(pb->mutable_name()); 
	pb->set_identifier_value(identifier_value); 
	pb->set_positive_int_value(positive_int_value); 
	pb->set_negative_int_value(negative_int_value); 
	pb->set_double_value(double_value); 
	pb->set_string_value(string_value); 
	pb->set_aggregate_value(aggregate_value); 
	return 0;
}


// method 
void PODSourceCodeInfo::clear()
{
	location.clear(); 
}

int PODSourceCodeInfo::pb2pod(const SourceCodeInfo & pb)
{
		location.pb2pod(pb.location()); 
	return 0;
}

int PODSourceCodeInfo::pod2pb(SourceCodeInfo * pb)
{
	location.pod2pb(pb->mutable_location()); 
	return 0;
}


// method 
void PODGeneratedCodeInfo::clear()
{
	annotation.clear(); 
}

int PODGeneratedCodeInfo::pb2pod(const GeneratedCodeInfo & pb)
{
		annotation.pb2pod(pb.annotation()); 
	return 0;
}

int PODGeneratedCodeInfo::pod2pb(GeneratedCodeInfo * pb)
{
	annotation.pod2pb(pb->mutable_annotation()); 
	return 0;
}

