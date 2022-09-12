// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: proto/machine.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_proto_2fmachine_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_proto_2fmachine_2eproto

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
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_proto_2fmachine_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_proto_2fmachine_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_proto_2fmachine_2eproto;
class InfoMessage;
struct InfoMessageDefaultTypeInternal;
extern InfoMessageDefaultTypeInternal _InfoMessage_default_instance_;
class MachineInfoMessage;
struct MachineInfoMessageDefaultTypeInternal;
extern MachineInfoMessageDefaultTypeInternal _MachineInfoMessage_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::InfoMessage* Arena::CreateMaybeMessage<::InfoMessage>(Arena*);
template<> ::MachineInfoMessage* Arena::CreateMaybeMessage<::MachineInfoMessage>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class InfoMessage final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:InfoMessage) */ {
 public:
  inline InfoMessage() : InfoMessage(nullptr) {}
  ~InfoMessage() override;
  explicit constexpr InfoMessage(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  InfoMessage(const InfoMessage& from);
  InfoMessage(InfoMessage&& from) noexcept
    : InfoMessage() {
    *this = ::std::move(from);
  }

  inline InfoMessage& operator=(const InfoMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline InfoMessage& operator=(InfoMessage&& from) noexcept {
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
  static const InfoMessage& default_instance() {
    return *internal_default_instance();
  }
  static inline const InfoMessage* internal_default_instance() {
    return reinterpret_cast<const InfoMessage*>(
               &_InfoMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(InfoMessage& a, InfoMessage& b) {
    a.Swap(&b);
  }
  inline void Swap(InfoMessage* other) {
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
  void UnsafeArenaSwap(InfoMessage* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  InfoMessage* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<InfoMessage>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const InfoMessage& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const InfoMessage& from);
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
  void InternalSwap(InfoMessage* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "InfoMessage";
  }
  protected:
  explicit InfoMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena,
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
    kIpFieldNumber = 1,
    kTimeFieldNumber = 2,
  };
  // uint32 ip = 1;
  void clear_ip();
  uint32_t ip() const;
  void set_ip(uint32_t value);
  private:
  uint32_t _internal_ip() const;
  void _internal_set_ip(uint32_t value);
  public:

  // uint32 time = 2;
  void clear_time();
  uint32_t time() const;
  void set_time(uint32_t value);
  private:
  uint32_t _internal_time() const;
  void _internal_set_time(uint32_t value);
  public:

  // @@protoc_insertion_point(class_scope:InfoMessage)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  uint32_t ip_;
  uint32_t time_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_proto_2fmachine_2eproto;
};
// -------------------------------------------------------------------

class MachineInfoMessage final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:MachineInfoMessage) */ {
 public:
  inline MachineInfoMessage() : MachineInfoMessage(nullptr) {}
  ~MachineInfoMessage() override;
  explicit constexpr MachineInfoMessage(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  MachineInfoMessage(const MachineInfoMessage& from);
  MachineInfoMessage(MachineInfoMessage&& from) noexcept
    : MachineInfoMessage() {
    *this = ::std::move(from);
  }

  inline MachineInfoMessage& operator=(const MachineInfoMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline MachineInfoMessage& operator=(MachineInfoMessage&& from) noexcept {
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
  static const MachineInfoMessage& default_instance() {
    return *internal_default_instance();
  }
  static inline const MachineInfoMessage* internal_default_instance() {
    return reinterpret_cast<const MachineInfoMessage*>(
               &_MachineInfoMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(MachineInfoMessage& a, MachineInfoMessage& b) {
    a.Swap(&b);
  }
  inline void Swap(MachineInfoMessage* other) {
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
  void UnsafeArenaSwap(MachineInfoMessage* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  MachineInfoMessage* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<MachineInfoMessage>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const MachineInfoMessage& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const MachineInfoMessage& from);
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
  void InternalSwap(MachineInfoMessage* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "MachineInfoMessage";
  }
  protected:
  explicit MachineInfoMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena,
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
    kInfoFieldNumber = 2,
    kTraceIdFieldNumber = 1,
    kTypeFieldNumber = 3,
  };
  // .InfoMessage info = 2;
  bool has_info() const;
  private:
  bool _internal_has_info() const;
  public:
  void clear_info();
  const ::InfoMessage& info() const;
  PROTOBUF_NODISCARD ::InfoMessage* release_info();
  ::InfoMessage* mutable_info();
  void set_allocated_info(::InfoMessage* info);
  private:
  const ::InfoMessage& _internal_info() const;
  ::InfoMessage* _internal_mutable_info();
  public:
  void unsafe_arena_set_allocated_info(
      ::InfoMessage* info);
  ::InfoMessage* unsafe_arena_release_info();

  // uint32 trace_id = 1;
  void clear_trace_id();
  uint32_t trace_id() const;
  void set_trace_id(uint32_t value);
  private:
  uint32_t _internal_trace_id() const;
  void _internal_set_trace_id(uint32_t value);
  public:

  // uint32 type = 3;
  void clear_type();
  uint32_t type() const;
  void set_type(uint32_t value);
  private:
  uint32_t _internal_type() const;
  void _internal_set_type(uint32_t value);
  public:

  // @@protoc_insertion_point(class_scope:MachineInfoMessage)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::InfoMessage* info_;
  uint32_t trace_id_;
  uint32_t type_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_proto_2fmachine_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// InfoMessage

// uint32 ip = 1;
inline void InfoMessage::clear_ip() {
  ip_ = 0u;
}
inline uint32_t InfoMessage::_internal_ip() const {
  return ip_;
}
inline uint32_t InfoMessage::ip() const {
  // @@protoc_insertion_point(field_get:InfoMessage.ip)
  return _internal_ip();
}
inline void InfoMessage::_internal_set_ip(uint32_t value) {
  
  ip_ = value;
}
inline void InfoMessage::set_ip(uint32_t value) {
  _internal_set_ip(value);
  // @@protoc_insertion_point(field_set:InfoMessage.ip)
}

// uint32 time = 2;
inline void InfoMessage::clear_time() {
  time_ = 0u;
}
inline uint32_t InfoMessage::_internal_time() const {
  return time_;
}
inline uint32_t InfoMessage::time() const {
  // @@protoc_insertion_point(field_get:InfoMessage.time)
  return _internal_time();
}
inline void InfoMessage::_internal_set_time(uint32_t value) {
  
  time_ = value;
}
inline void InfoMessage::set_time(uint32_t value) {
  _internal_set_time(value);
  // @@protoc_insertion_point(field_set:InfoMessage.time)
}

// -------------------------------------------------------------------

// MachineInfoMessage

// uint32 trace_id = 1;
inline void MachineInfoMessage::clear_trace_id() {
  trace_id_ = 0u;
}
inline uint32_t MachineInfoMessage::_internal_trace_id() const {
  return trace_id_;
}
inline uint32_t MachineInfoMessage::trace_id() const {
  // @@protoc_insertion_point(field_get:MachineInfoMessage.trace_id)
  return _internal_trace_id();
}
inline void MachineInfoMessage::_internal_set_trace_id(uint32_t value) {
  
  trace_id_ = value;
}
inline void MachineInfoMessage::set_trace_id(uint32_t value) {
  _internal_set_trace_id(value);
  // @@protoc_insertion_point(field_set:MachineInfoMessage.trace_id)
}

// .InfoMessage info = 2;
inline bool MachineInfoMessage::_internal_has_info() const {
  return this != internal_default_instance() && info_ != nullptr;
}
inline bool MachineInfoMessage::has_info() const {
  return _internal_has_info();
}
inline void MachineInfoMessage::clear_info() {
  if (GetArenaForAllocation() == nullptr && info_ != nullptr) {
    delete info_;
  }
  info_ = nullptr;
}
inline const ::InfoMessage& MachineInfoMessage::_internal_info() const {
  const ::InfoMessage* p = info_;
  return p != nullptr ? *p : reinterpret_cast<const ::InfoMessage&>(
      ::_InfoMessage_default_instance_);
}
inline const ::InfoMessage& MachineInfoMessage::info() const {
  // @@protoc_insertion_point(field_get:MachineInfoMessage.info)
  return _internal_info();
}
inline void MachineInfoMessage::unsafe_arena_set_allocated_info(
    ::InfoMessage* info) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(info_);
  }
  info_ = info;
  if (info) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:MachineInfoMessage.info)
}
inline ::InfoMessage* MachineInfoMessage::release_info() {
  
  ::InfoMessage* temp = info_;
  info_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::InfoMessage* MachineInfoMessage::unsafe_arena_release_info() {
  // @@protoc_insertion_point(field_release:MachineInfoMessage.info)
  
  ::InfoMessage* temp = info_;
  info_ = nullptr;
  return temp;
}
inline ::InfoMessage* MachineInfoMessage::_internal_mutable_info() {
  
  if (info_ == nullptr) {
    auto* p = CreateMaybeMessage<::InfoMessage>(GetArenaForAllocation());
    info_ = p;
  }
  return info_;
}
inline ::InfoMessage* MachineInfoMessage::mutable_info() {
  ::InfoMessage* _msg = _internal_mutable_info();
  // @@protoc_insertion_point(field_mutable:MachineInfoMessage.info)
  return _msg;
}
inline void MachineInfoMessage::set_allocated_info(::InfoMessage* info) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete info_;
  }
  if (info) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<::InfoMessage>::GetOwningArena(info);
    if (message_arena != submessage_arena) {
      info = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, info, submessage_arena);
    }
    
  } else {
    
  }
  info_ = info;
  // @@protoc_insertion_point(field_set_allocated:MachineInfoMessage.info)
}

// uint32 type = 3;
inline void MachineInfoMessage::clear_type() {
  type_ = 0u;
}
inline uint32_t MachineInfoMessage::_internal_type() const {
  return type_;
}
inline uint32_t MachineInfoMessage::type() const {
  // @@protoc_insertion_point(field_get:MachineInfoMessage.type)
  return _internal_type();
}
inline void MachineInfoMessage::_internal_set_type(uint32_t value) {
  
  type_ = value;
}
inline void MachineInfoMessage::set_type(uint32_t value) {
  _internal_set_type(value);
  // @@protoc_insertion_point(field_set:MachineInfoMessage.type)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_proto_2fmachine_2eproto