// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: heartbeat.proto

#ifndef PROTOBUF_INCLUDED_heartbeat_2eproto
#define PROTOBUF_INCLUDED_heartbeat_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_heartbeat_2eproto 

namespace protobuf_heartbeat_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_heartbeat_2eproto
namespace heartbeat {
class HeartBeatMessage;
class HeartBeatMessageDefaultTypeInternal;
extern HeartBeatMessageDefaultTypeInternal _HeartBeatMessage_default_instance_;
}  // namespace heartbeat
namespace google {
namespace protobuf {
template<> ::heartbeat::HeartBeatMessage* Arena::CreateMaybeMessage<::heartbeat::HeartBeatMessage>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace heartbeat {

// ===================================================================

class HeartBeatMessage : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:heartbeat.HeartBeatMessage) */ {
 public:
  HeartBeatMessage();
  virtual ~HeartBeatMessage();

  HeartBeatMessage(const HeartBeatMessage& from);

  inline HeartBeatMessage& operator=(const HeartBeatMessage& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  HeartBeatMessage(HeartBeatMessage&& from) noexcept
    : HeartBeatMessage() {
    *this = ::std::move(from);
  }

  inline HeartBeatMessage& operator=(HeartBeatMessage&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const HeartBeatMessage& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const HeartBeatMessage* internal_default_instance() {
    return reinterpret_cast<const HeartBeatMessage*>(
               &_HeartBeatMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(HeartBeatMessage* other);
  friend void swap(HeartBeatMessage& a, HeartBeatMessage& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline HeartBeatMessage* New() const final {
    return CreateMaybeMessage<HeartBeatMessage>(NULL);
  }

  HeartBeatMessage* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<HeartBeatMessage>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const HeartBeatMessage& from);
  void MergeFrom(const HeartBeatMessage& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(HeartBeatMessage* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string hostName = 2;
  void clear_hostname();
  static const int kHostNameFieldNumber = 2;
  const ::std::string& hostname() const;
  void set_hostname(const ::std::string& value);
  #if LANG_CXX11
  void set_hostname(::std::string&& value);
  #endif
  void set_hostname(const char* value);
  void set_hostname(const char* value, size_t size);
  ::std::string* mutable_hostname();
  ::std::string* release_hostname();
  void set_allocated_hostname(::std::string* hostname);

  // string ip = 3;
  void clear_ip();
  static const int kIpFieldNumber = 3;
  const ::std::string& ip() const;
  void set_ip(const ::std::string& value);
  #if LANG_CXX11
  void set_ip(::std::string&& value);
  #endif
  void set_ip(const char* value);
  void set_ip(const char* value, size_t size);
  ::std::string* mutable_ip();
  ::std::string* release_ip();
  void set_allocated_ip(::std::string* ip);

  // string info = 4;
  void clear_info();
  static const int kInfoFieldNumber = 4;
  const ::std::string& info() const;
  void set_info(const ::std::string& value);
  #if LANG_CXX11
  void set_info(::std::string&& value);
  #endif
  void set_info(const char* value);
  void set_info(const char* value, size_t size);
  ::std::string* mutable_info();
  ::std::string* release_info();
  void set_allocated_info(::std::string* info);

  // string info2 = 5;
  void clear_info2();
  static const int kInfo2FieldNumber = 5;
  const ::std::string& info2() const;
  void set_info2(const ::std::string& value);
  #if LANG_CXX11
  void set_info2(::std::string&& value);
  #endif
  void set_info2(const char* value);
  void set_info2(const char* value, size_t size);
  ::std::string* mutable_info2();
  ::std::string* release_info2();
  void set_allocated_info2(::std::string* info2);

  // int64 dateTime = 1;
  void clear_datetime();
  static const int kDateTimeFieldNumber = 1;
  ::google::protobuf::int64 datetime() const;
  void set_datetime(::google::protobuf::int64 value);

  // int64 info3 = 6;
  void clear_info3();
  static const int kInfo3FieldNumber = 6;
  ::google::protobuf::int64 info3() const;
  void set_info3(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:heartbeat.HeartBeatMessage)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr hostname_;
  ::google::protobuf::internal::ArenaStringPtr ip_;
  ::google::protobuf::internal::ArenaStringPtr info_;
  ::google::protobuf::internal::ArenaStringPtr info2_;
  ::google::protobuf::int64 datetime_;
  ::google::protobuf::int64 info3_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_heartbeat_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// HeartBeatMessage

// int64 dateTime = 1;
inline void HeartBeatMessage::clear_datetime() {
  datetime_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 HeartBeatMessage::datetime() const {
  // @@protoc_insertion_point(field_get:heartbeat.HeartBeatMessage.dateTime)
  return datetime_;
}
inline void HeartBeatMessage::set_datetime(::google::protobuf::int64 value) {
  
  datetime_ = value;
  // @@protoc_insertion_point(field_set:heartbeat.HeartBeatMessage.dateTime)
}

// string hostName = 2;
inline void HeartBeatMessage::clear_hostname() {
  hostname_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& HeartBeatMessage::hostname() const {
  // @@protoc_insertion_point(field_get:heartbeat.HeartBeatMessage.hostName)
  return hostname_.GetNoArena();
}
inline void HeartBeatMessage::set_hostname(const ::std::string& value) {
  
  hostname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:heartbeat.HeartBeatMessage.hostName)
}
#if LANG_CXX11
inline void HeartBeatMessage::set_hostname(::std::string&& value) {
  
  hostname_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:heartbeat.HeartBeatMessage.hostName)
}
#endif
inline void HeartBeatMessage::set_hostname(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  hostname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:heartbeat.HeartBeatMessage.hostName)
}
inline void HeartBeatMessage::set_hostname(const char* value, size_t size) {
  
  hostname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:heartbeat.HeartBeatMessage.hostName)
}
inline ::std::string* HeartBeatMessage::mutable_hostname() {
  
  // @@protoc_insertion_point(field_mutable:heartbeat.HeartBeatMessage.hostName)
  return hostname_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* HeartBeatMessage::release_hostname() {
  // @@protoc_insertion_point(field_release:heartbeat.HeartBeatMessage.hostName)
  
  return hostname_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void HeartBeatMessage::set_allocated_hostname(::std::string* hostname) {
  if (hostname != NULL) {
    
  } else {
    
  }
  hostname_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), hostname);
  // @@protoc_insertion_point(field_set_allocated:heartbeat.HeartBeatMessage.hostName)
}

// string ip = 3;
inline void HeartBeatMessage::clear_ip() {
  ip_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& HeartBeatMessage::ip() const {
  // @@protoc_insertion_point(field_get:heartbeat.HeartBeatMessage.ip)
  return ip_.GetNoArena();
}
inline void HeartBeatMessage::set_ip(const ::std::string& value) {
  
  ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:heartbeat.HeartBeatMessage.ip)
}
#if LANG_CXX11
inline void HeartBeatMessage::set_ip(::std::string&& value) {
  
  ip_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:heartbeat.HeartBeatMessage.ip)
}
#endif
inline void HeartBeatMessage::set_ip(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:heartbeat.HeartBeatMessage.ip)
}
inline void HeartBeatMessage::set_ip(const char* value, size_t size) {
  
  ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:heartbeat.HeartBeatMessage.ip)
}
inline ::std::string* HeartBeatMessage::mutable_ip() {
  
  // @@protoc_insertion_point(field_mutable:heartbeat.HeartBeatMessage.ip)
  return ip_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* HeartBeatMessage::release_ip() {
  // @@protoc_insertion_point(field_release:heartbeat.HeartBeatMessage.ip)
  
  return ip_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void HeartBeatMessage::set_allocated_ip(::std::string* ip) {
  if (ip != NULL) {
    
  } else {
    
  }
  ip_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ip);
  // @@protoc_insertion_point(field_set_allocated:heartbeat.HeartBeatMessage.ip)
}

// string info = 4;
inline void HeartBeatMessage::clear_info() {
  info_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& HeartBeatMessage::info() const {
  // @@protoc_insertion_point(field_get:heartbeat.HeartBeatMessage.info)
  return info_.GetNoArena();
}
inline void HeartBeatMessage::set_info(const ::std::string& value) {
  
  info_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:heartbeat.HeartBeatMessage.info)
}
#if LANG_CXX11
inline void HeartBeatMessage::set_info(::std::string&& value) {
  
  info_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:heartbeat.HeartBeatMessage.info)
}
#endif
inline void HeartBeatMessage::set_info(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  info_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:heartbeat.HeartBeatMessage.info)
}
inline void HeartBeatMessage::set_info(const char* value, size_t size) {
  
  info_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:heartbeat.HeartBeatMessage.info)
}
inline ::std::string* HeartBeatMessage::mutable_info() {
  
  // @@protoc_insertion_point(field_mutable:heartbeat.HeartBeatMessage.info)
  return info_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* HeartBeatMessage::release_info() {
  // @@protoc_insertion_point(field_release:heartbeat.HeartBeatMessage.info)
  
  return info_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void HeartBeatMessage::set_allocated_info(::std::string* info) {
  if (info != NULL) {
    
  } else {
    
  }
  info_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), info);
  // @@protoc_insertion_point(field_set_allocated:heartbeat.HeartBeatMessage.info)
}

// string info2 = 5;
inline void HeartBeatMessage::clear_info2() {
  info2_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& HeartBeatMessage::info2() const {
  // @@protoc_insertion_point(field_get:heartbeat.HeartBeatMessage.info2)
  return info2_.GetNoArena();
}
inline void HeartBeatMessage::set_info2(const ::std::string& value) {
  
  info2_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:heartbeat.HeartBeatMessage.info2)
}
#if LANG_CXX11
inline void HeartBeatMessage::set_info2(::std::string&& value) {
  
  info2_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:heartbeat.HeartBeatMessage.info2)
}
#endif
inline void HeartBeatMessage::set_info2(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  info2_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:heartbeat.HeartBeatMessage.info2)
}
inline void HeartBeatMessage::set_info2(const char* value, size_t size) {
  
  info2_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:heartbeat.HeartBeatMessage.info2)
}
inline ::std::string* HeartBeatMessage::mutable_info2() {
  
  // @@protoc_insertion_point(field_mutable:heartbeat.HeartBeatMessage.info2)
  return info2_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* HeartBeatMessage::release_info2() {
  // @@protoc_insertion_point(field_release:heartbeat.HeartBeatMessage.info2)
  
  return info2_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void HeartBeatMessage::set_allocated_info2(::std::string* info2) {
  if (info2 != NULL) {
    
  } else {
    
  }
  info2_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), info2);
  // @@protoc_insertion_point(field_set_allocated:heartbeat.HeartBeatMessage.info2)
}

// int64 info3 = 6;
inline void HeartBeatMessage::clear_info3() {
  info3_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 HeartBeatMessage::info3() const {
  // @@protoc_insertion_point(field_get:heartbeat.HeartBeatMessage.info3)
  return info3_;
}
inline void HeartBeatMessage::set_info3(::google::protobuf::int64 value) {
  
  info3_ = value;
  // @@protoc_insertion_point(field_set:heartbeat.HeartBeatMessage.info3)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace heartbeat

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_heartbeat_2eproto