// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: proto/demo.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_proto_2fdemo_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_proto_2fdemo_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3019000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3019001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "proto/custom_opt.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_proto_2fdemo_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_proto_2fdemo_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_proto_2fdemo_2eproto;
class FamilyMsg;
struct FamilyMsgDefaultTypeInternal;
extern FamilyMsgDefaultTypeInternal _FamilyMsg_default_instance_;
class UserMsg;
struct UserMsgDefaultTypeInternal;
extern UserMsgDefaultTypeInternal _UserMsg_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::FamilyMsg* Arena::CreateMaybeMessage<::FamilyMsg>(Arena*);
template<> ::UserMsg* Arena::CreateMaybeMessage<::UserMsg>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class UserMsg final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:UserMsg) */ {
 public:
  inline UserMsg() : UserMsg(nullptr) {}
  ~UserMsg() override;
  explicit constexpr UserMsg(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  UserMsg(const UserMsg& from);
  UserMsg(UserMsg&& from) noexcept
    : UserMsg() {
    *this = ::std::move(from);
  }

  inline UserMsg& operator=(const UserMsg& from) {
    CopyFrom(from);
    return *this;
  }
  inline UserMsg& operator=(UserMsg&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const UserMsg& default_instance() {
    return *internal_default_instance();
  }
  static inline const UserMsg* internal_default_instance() {
    return reinterpret_cast<const UserMsg*>(
               &_UserMsg_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(UserMsg& a, UserMsg& b) {
    a.Swap(&b);
  }
  inline void Swap(UserMsg* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(UserMsg* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  UserMsg* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<UserMsg>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const UserMsg& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const UserMsg& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(UserMsg* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "UserMsg";
  }
  protected:
  explicit UserMsg(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIdFieldNumber = 1,
    kAgeFieldNumber = 2,
    kPasswdFieldNumber = 3,
  };
  // uint32 id = 1;
  void clear_id();
  uint32_t id() const;
  void set_id(uint32_t value);
  private:
  uint32_t _internal_id() const;
  void _internal_set_id(uint32_t value);
  public:

  // uint32 age = 2;
  void clear_age();
  uint32_t age() const;
  void set_age(uint32_t value);
  private:
  uint32_t _internal_age() const;
  void _internal_set_age(uint32_t value);
  public:

  // uint32 passwd = 3;
  void clear_passwd();
  uint32_t passwd() const;
  void set_passwd(uint32_t value);
  private:
  uint32_t _internal_passwd() const;
  void _internal_set_passwd(uint32_t value);
  public:

  // @@protoc_insertion_point(class_scope:UserMsg)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  uint32_t id_;
  uint32_t age_;
  uint32_t passwd_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_proto_2fdemo_2eproto;
};
// -------------------------------------------------------------------

class FamilyMsg final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:FamilyMsg) */ {
 public:
  inline FamilyMsg() : FamilyMsg(nullptr) {}
  ~FamilyMsg() override;
  explicit constexpr FamilyMsg(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  FamilyMsg(const FamilyMsg& from);
  FamilyMsg(FamilyMsg&& from) noexcept
    : FamilyMsg() {
    *this = ::std::move(from);
  }

  inline FamilyMsg& operator=(const FamilyMsg& from) {
    CopyFrom(from);
    return *this;
  }
  inline FamilyMsg& operator=(FamilyMsg&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const FamilyMsg& default_instance() {
    return *internal_default_instance();
  }
  static inline const FamilyMsg* internal_default_instance() {
    return reinterpret_cast<const FamilyMsg*>(
               &_FamilyMsg_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(FamilyMsg& a, FamilyMsg& b) {
    a.Swap(&b);
  }
  inline void Swap(FamilyMsg* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(FamilyMsg* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  FamilyMsg* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<FamilyMsg>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const FamilyMsg& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const FamilyMsg& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(FamilyMsg* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "FamilyMsg";
  }
  protected:
  explicit FamilyMsg(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kFamilysFieldNumber = 1,
    kRidArrsFieldNumber = 2,
  };
  // repeated .UserMsg familys = 1 [(.custom.opt_count) = 10];
  int familys_size() const;
  private:
  int _internal_familys_size() const;
  public:
  void clear_familys();
  ::UserMsg* mutable_familys(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::UserMsg >*
      mutable_familys();
  private:
  const ::UserMsg& _internal_familys(int index) const;
  ::UserMsg* _internal_add_familys();
  public:
  const ::UserMsg& familys(int index) const;
  ::UserMsg* add_familys();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::UserMsg >&
      familys() const;

  // repeated uint32 rid_arrs = 2 [(.custom.opt_count) = 50];
  int rid_arrs_size() const;
  private:
  int _internal_rid_arrs_size() const;
  public:
  void clear_rid_arrs();
  private:
  uint32_t _internal_rid_arrs(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
      _internal_rid_arrs() const;
  void _internal_add_rid_arrs(uint32_t value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
      _internal_mutable_rid_arrs();
  public:
  uint32_t rid_arrs(int index) const;
  void set_rid_arrs(int index, uint32_t value);
  void add_rid_arrs(uint32_t value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
      rid_arrs() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
      mutable_rid_arrs();

  // @@protoc_insertion_point(class_scope:FamilyMsg)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::UserMsg > familys_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t > rid_arrs_;
  mutable std::atomic<int> _rid_arrs_cached_byte_size_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_proto_2fdemo_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// UserMsg

// uint32 id = 1;
inline void UserMsg::clear_id() {
  id_ = 0u;
}
inline uint32_t UserMsg::_internal_id() const {
  return id_;
}
inline uint32_t UserMsg::id() const {
  // @@protoc_insertion_point(field_get:UserMsg.id)
  return _internal_id();
}
inline void UserMsg::_internal_set_id(uint32_t value) {
  
  id_ = value;
}
inline void UserMsg::set_id(uint32_t value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:UserMsg.id)
}

// uint32 age = 2;
inline void UserMsg::clear_age() {
  age_ = 0u;
}
inline uint32_t UserMsg::_internal_age() const {
  return age_;
}
inline uint32_t UserMsg::age() const {
  // @@protoc_insertion_point(field_get:UserMsg.age)
  return _internal_age();
}
inline void UserMsg::_internal_set_age(uint32_t value) {
  
  age_ = value;
}
inline void UserMsg::set_age(uint32_t value) {
  _internal_set_age(value);
  // @@protoc_insertion_point(field_set:UserMsg.age)
}

// uint32 passwd = 3;
inline void UserMsg::clear_passwd() {
  passwd_ = 0u;
}
inline uint32_t UserMsg::_internal_passwd() const {
  return passwd_;
}
inline uint32_t UserMsg::passwd() const {
  // @@protoc_insertion_point(field_get:UserMsg.passwd)
  return _internal_passwd();
}
inline void UserMsg::_internal_set_passwd(uint32_t value) {
  
  passwd_ = value;
}
inline void UserMsg::set_passwd(uint32_t value) {
  _internal_set_passwd(value);
  // @@protoc_insertion_point(field_set:UserMsg.passwd)
}

// -------------------------------------------------------------------

// FamilyMsg

// repeated .UserMsg familys = 1 [(.custom.opt_count) = 10];
inline int FamilyMsg::_internal_familys_size() const {
  return familys_.size();
}
inline int FamilyMsg::familys_size() const {
  return _internal_familys_size();
}
inline void FamilyMsg::clear_familys() {
  familys_.Clear();
}
inline ::UserMsg* FamilyMsg::mutable_familys(int index) {
  // @@protoc_insertion_point(field_mutable:FamilyMsg.familys)
  return familys_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::UserMsg >*
FamilyMsg::mutable_familys() {
  // @@protoc_insertion_point(field_mutable_list:FamilyMsg.familys)
  return &familys_;
}
inline const ::UserMsg& FamilyMsg::_internal_familys(int index) const {
  return familys_.Get(index);
}
inline const ::UserMsg& FamilyMsg::familys(int index) const {
  // @@protoc_insertion_point(field_get:FamilyMsg.familys)
  return _internal_familys(index);
}
inline ::UserMsg* FamilyMsg::_internal_add_familys() {
  return familys_.Add();
}
inline ::UserMsg* FamilyMsg::add_familys() {
  ::UserMsg* _add = _internal_add_familys();
  // @@protoc_insertion_point(field_add:FamilyMsg.familys)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::UserMsg >&
FamilyMsg::familys() const {
  // @@protoc_insertion_point(field_list:FamilyMsg.familys)
  return familys_;
}

// repeated uint32 rid_arrs = 2 [(.custom.opt_count) = 50];
inline int FamilyMsg::_internal_rid_arrs_size() const {
  return rid_arrs_.size();
}
inline int FamilyMsg::rid_arrs_size() const {
  return _internal_rid_arrs_size();
}
inline void FamilyMsg::clear_rid_arrs() {
  rid_arrs_.Clear();
}
inline uint32_t FamilyMsg::_internal_rid_arrs(int index) const {
  return rid_arrs_.Get(index);
}
inline uint32_t FamilyMsg::rid_arrs(int index) const {
  // @@protoc_insertion_point(field_get:FamilyMsg.rid_arrs)
  return _internal_rid_arrs(index);
}
inline void FamilyMsg::set_rid_arrs(int index, uint32_t value) {
  rid_arrs_.Set(index, value);
  // @@protoc_insertion_point(field_set:FamilyMsg.rid_arrs)
}
inline void FamilyMsg::_internal_add_rid_arrs(uint32_t value) {
  rid_arrs_.Add(value);
}
inline void FamilyMsg::add_rid_arrs(uint32_t value) {
  _internal_add_rid_arrs(value);
  // @@protoc_insertion_point(field_add:FamilyMsg.rid_arrs)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
FamilyMsg::_internal_rid_arrs() const {
  return rid_arrs_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
FamilyMsg::rid_arrs() const {
  // @@protoc_insertion_point(field_list:FamilyMsg.rid_arrs)
  return _internal_rid_arrs();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
FamilyMsg::_internal_mutable_rid_arrs() {
  return &rid_arrs_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
FamilyMsg::mutable_rid_arrs() {
  // @@protoc_insertion_point(field_mutable_list:FamilyMsg.rid_arrs)
  return _internal_mutable_rid_arrs();
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_proto_2fdemo_2eproto
