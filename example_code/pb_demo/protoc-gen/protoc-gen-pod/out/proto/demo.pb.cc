// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: proto/demo.proto

#include "proto/demo.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
constexpr UserMsg::UserMsg(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : id_(0u)
  , age_(0u)
  , passwd_(0u){}
struct UserMsgDefaultTypeInternal {
  constexpr UserMsgDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~UserMsgDefaultTypeInternal() {}
  union {
    UserMsg _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT UserMsgDefaultTypeInternal _UserMsg_default_instance_;
constexpr FamilyMsg::FamilyMsg(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : familys_()
  , rid_arrs_()
  , _rid_arrs_cached_byte_size_(0){}
struct FamilyMsgDefaultTypeInternal {
  constexpr FamilyMsgDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~FamilyMsgDefaultTypeInternal() {}
  union {
    FamilyMsg _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT FamilyMsgDefaultTypeInternal _FamilyMsg_default_instance_;
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_proto_2fdemo_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_proto_2fdemo_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_proto_2fdemo_2eproto = nullptr;

const uint32_t TableStruct_proto_2fdemo_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::UserMsg, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::UserMsg, id_),
  PROTOBUF_FIELD_OFFSET(::UserMsg, age_),
  PROTOBUF_FIELD_OFFSET(::UserMsg, passwd_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::FamilyMsg, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::FamilyMsg, familys_),
  PROTOBUF_FIELD_OFFSET(::FamilyMsg, rid_arrs_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::UserMsg)},
  { 9, -1, -1, sizeof(::FamilyMsg)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_UserMsg_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_FamilyMsg_default_instance_),
};

const char descriptor_table_protodef_proto_2fdemo_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\020proto/demo.proto\032\026proto/custom_opt.pro"
  "to\"2\n\007UserMsg\022\n\n\002id\030\001 \001(\r\022\013\n\003age\030\002 \001(\r\022\016"
  "\n\006passwd\030\003 \001(\r\"D\n\tFamilyMsg\022\037\n\007familys\030\001"
  " \003(\0132\010.UserMsgB\004\200\265\030\n\022\026\n\010rid_arrs\030\002 \003(\rB\004"
  "\200\265\0302B\014Z\n.;protocolb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_proto_2fdemo_2eproto_deps[1] = {
  &::descriptor_table_proto_2fcustom_5fopt_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_proto_2fdemo_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_proto_2fdemo_2eproto = {
  false, false, 186, descriptor_table_protodef_proto_2fdemo_2eproto, "proto/demo.proto", 
  &descriptor_table_proto_2fdemo_2eproto_once, descriptor_table_proto_2fdemo_2eproto_deps, 1, 2,
  schemas, file_default_instances, TableStruct_proto_2fdemo_2eproto::offsets,
  file_level_metadata_proto_2fdemo_2eproto, file_level_enum_descriptors_proto_2fdemo_2eproto, file_level_service_descriptors_proto_2fdemo_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_proto_2fdemo_2eproto_getter() {
  return &descriptor_table_proto_2fdemo_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_proto_2fdemo_2eproto(&descriptor_table_proto_2fdemo_2eproto);

// ===================================================================

class UserMsg::_Internal {
 public:
};

UserMsg::UserMsg(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:UserMsg)
}
UserMsg::UserMsg(const UserMsg& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&id_, &from.id_,
    static_cast<size_t>(reinterpret_cast<char*>(&passwd_) -
    reinterpret_cast<char*>(&id_)) + sizeof(passwd_));
  // @@protoc_insertion_point(copy_constructor:UserMsg)
}

inline void UserMsg::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&id_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&passwd_) -
    reinterpret_cast<char*>(&id_)) + sizeof(passwd_));
}

UserMsg::~UserMsg() {
  // @@protoc_insertion_point(destructor:UserMsg)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void UserMsg::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void UserMsg::ArenaDtor(void* object) {
  UserMsg* _this = reinterpret_cast< UserMsg* >(object);
  (void)_this;
}
void UserMsg::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void UserMsg::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void UserMsg::Clear() {
// @@protoc_insertion_point(message_clear_start:UserMsg)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&passwd_) -
      reinterpret_cast<char*>(&id_)) + sizeof(passwd_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* UserMsg::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint32 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 age = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          age_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 passwd = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          passwd_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* UserMsg::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:UserMsg)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 id = 1;
  if (this->_internal_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(1, this->_internal_id(), target);
  }

  // uint32 age = 2;
  if (this->_internal_age() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(2, this->_internal_age(), target);
  }

  // uint32 passwd = 3;
  if (this->_internal_passwd() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(3, this->_internal_passwd(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:UserMsg)
  return target;
}

size_t UserMsg::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:UserMsg)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // uint32 id = 1;
  if (this->_internal_id() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32SizePlusOne(this->_internal_id());
  }

  // uint32 age = 2;
  if (this->_internal_age() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32SizePlusOne(this->_internal_age());
  }

  // uint32 passwd = 3;
  if (this->_internal_passwd() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32SizePlusOne(this->_internal_passwd());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData UserMsg::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    UserMsg::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*UserMsg::GetClassData() const { return &_class_data_; }

void UserMsg::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<UserMsg *>(to)->MergeFrom(
      static_cast<const UserMsg &>(from));
}


void UserMsg::MergeFrom(const UserMsg& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:UserMsg)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_id() != 0) {
    _internal_set_id(from._internal_id());
  }
  if (from._internal_age() != 0) {
    _internal_set_age(from._internal_age());
  }
  if (from._internal_passwd() != 0) {
    _internal_set_passwd(from._internal_passwd());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void UserMsg::CopyFrom(const UserMsg& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:UserMsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool UserMsg::IsInitialized() const {
  return true;
}

void UserMsg::InternalSwap(UserMsg* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(UserMsg, passwd_)
      + sizeof(UserMsg::passwd_)
      - PROTOBUF_FIELD_OFFSET(UserMsg, id_)>(
          reinterpret_cast<char*>(&id_),
          reinterpret_cast<char*>(&other->id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata UserMsg::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_proto_2fdemo_2eproto_getter, &descriptor_table_proto_2fdemo_2eproto_once,
      file_level_metadata_proto_2fdemo_2eproto[0]);
}

// ===================================================================

class FamilyMsg::_Internal {
 public:
};

FamilyMsg::FamilyMsg(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned),
  familys_(arena),
  rid_arrs_(arena) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:FamilyMsg)
}
FamilyMsg::FamilyMsg(const FamilyMsg& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      familys_(from.familys_),
      rid_arrs_(from.rid_arrs_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:FamilyMsg)
}

inline void FamilyMsg::SharedCtor() {
}

FamilyMsg::~FamilyMsg() {
  // @@protoc_insertion_point(destructor:FamilyMsg)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void FamilyMsg::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void FamilyMsg::ArenaDtor(void* object) {
  FamilyMsg* _this = reinterpret_cast< FamilyMsg* >(object);
  (void)_this;
}
void FamilyMsg::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void FamilyMsg::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void FamilyMsg::Clear() {
// @@protoc_insertion_point(message_clear_start:FamilyMsg)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  familys_.Clear();
  rid_arrs_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* FamilyMsg::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // repeated .UserMsg familys = 1 [(.custom.opt_count) = 10];
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_familys(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
        } else
          goto handle_unusual;
        continue;
      // repeated uint32 rid_arrs = 2 [(.custom.opt_count) = 50];
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedUInt32Parser(_internal_mutable_rid_arrs(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<uint8_t>(tag) == 16) {
          _internal_add_rid_arrs(::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* FamilyMsg::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:FamilyMsg)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .UserMsg familys = 1 [(.custom.opt_count) = 10];
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_familys_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, this->_internal_familys(i), target, stream);
  }

  // repeated uint32 rid_arrs = 2 [(.custom.opt_count) = 50];
  {
    int byte_size = _rid_arrs_cached_byte_size_.load(std::memory_order_relaxed);
    if (byte_size > 0) {
      target = stream->WriteUInt32Packed(
          2, _internal_rid_arrs(), byte_size, target);
    }
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:FamilyMsg)
  return target;
}

size_t FamilyMsg::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:FamilyMsg)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .UserMsg familys = 1 [(.custom.opt_count) = 10];
  total_size += 1UL * this->_internal_familys_size();
  for (const auto& msg : this->familys_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // repeated uint32 rid_arrs = 2 [(.custom.opt_count) = 50];
  {
    size_t data_size = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      UInt32Size(this->rid_arrs_);
    if (data_size > 0) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
            static_cast<int32_t>(data_size));
    }
    int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(data_size);
    _rid_arrs_cached_byte_size_.store(cached_size,
                                    std::memory_order_relaxed);
    total_size += data_size;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData FamilyMsg::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    FamilyMsg::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*FamilyMsg::GetClassData() const { return &_class_data_; }

void FamilyMsg::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<FamilyMsg *>(to)->MergeFrom(
      static_cast<const FamilyMsg &>(from));
}


void FamilyMsg::MergeFrom(const FamilyMsg& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:FamilyMsg)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  familys_.MergeFrom(from.familys_);
  rid_arrs_.MergeFrom(from.rid_arrs_);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void FamilyMsg::CopyFrom(const FamilyMsg& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:FamilyMsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FamilyMsg::IsInitialized() const {
  return true;
}

void FamilyMsg::InternalSwap(FamilyMsg* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  familys_.InternalSwap(&other->familys_);
  rid_arrs_.InternalSwap(&other->rid_arrs_);
}

::PROTOBUF_NAMESPACE_ID::Metadata FamilyMsg::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_proto_2fdemo_2eproto_getter, &descriptor_table_proto_2fdemo_2eproto_once,
      file_level_metadata_proto_2fdemo_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::UserMsg* Arena::CreateMaybeMessage< ::UserMsg >(Arena* arena) {
  return Arena::CreateMessageInternal< ::UserMsg >(arena);
}
template<> PROTOBUF_NOINLINE ::FamilyMsg* Arena::CreateMaybeMessage< ::FamilyMsg >(Arena* arena) {
  return Arena::CreateMessageInternal< ::FamilyMsg >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>