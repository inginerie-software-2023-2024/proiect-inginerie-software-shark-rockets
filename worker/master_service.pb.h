// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: master_service.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_master_5fservice_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_master_5fservice_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION < 4024000
#error "This file was generated by a newer version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please update"
#error "your headers."
#endif  // PROTOBUF_VERSION

#if 4024003 < PROTOBUF_MIN_PROTOC_VERSION
#error "This file was generated by an older version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please"
#error "regenerate this file with a newer version of protoc."
#endif  // PROTOBUF_MIN_PROTOC_VERSION
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_master_5fservice_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_master_5fservice_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_master_5fservice_2eproto;
class RegisterJobReply;
struct RegisterJobReplyDefaultTypeInternal;
extern RegisterJobReplyDefaultTypeInternal _RegisterJobReply_default_instance_;
class RegisterJobRequest;
struct RegisterJobRequestDefaultTypeInternal;
extern RegisterJobRequestDefaultTypeInternal _RegisterJobRequest_default_instance_;
class RegisterWorkerReply;
struct RegisterWorkerReplyDefaultTypeInternal;
extern RegisterWorkerReplyDefaultTypeInternal _RegisterWorkerReply_default_instance_;
class RegisterWorkerRequest;
struct RegisterWorkerRequestDefaultTypeInternal;
extern RegisterWorkerRequestDefaultTypeInternal _RegisterWorkerRequest_default_instance_;
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google


// ===================================================================


// -------------------------------------------------------------------

class RegisterWorkerRequest final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:RegisterWorkerRequest) */ {
 public:
  inline RegisterWorkerRequest() : RegisterWorkerRequest(nullptr) {}
  ~RegisterWorkerRequest() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR RegisterWorkerRequest(::google::protobuf::internal::ConstantInitialized);

  RegisterWorkerRequest(const RegisterWorkerRequest& from);
  RegisterWorkerRequest(RegisterWorkerRequest&& from) noexcept
    : RegisterWorkerRequest() {
    *this = ::std::move(from);
  }

  inline RegisterWorkerRequest& operator=(const RegisterWorkerRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline RegisterWorkerRequest& operator=(RegisterWorkerRequest&& from) noexcept {
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

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const RegisterWorkerRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const RegisterWorkerRequest* internal_default_instance() {
    return reinterpret_cast<const RegisterWorkerRequest*>(
               &_RegisterWorkerRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(RegisterWorkerRequest& a, RegisterWorkerRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(RegisterWorkerRequest* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(RegisterWorkerRequest* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  RegisterWorkerRequest* New(::google::protobuf::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<RegisterWorkerRequest>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const RegisterWorkerRequest& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom( const RegisterWorkerRequest& from) {
    RegisterWorkerRequest::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(RegisterWorkerRequest* other);

  private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "RegisterWorkerRequest";
  }
  protected:
  explicit RegisterWorkerRequest(::google::protobuf::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::google::protobuf::Message::ClassData*GetClassData() const final;

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIpFieldNumber = 1,
    kPortFieldNumber = 2,
  };
  // string ip = 1;
  void clear_ip() ;
  const std::string& ip() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_ip(Arg_&& arg, Args_... args);
  std::string* mutable_ip();
  PROTOBUF_NODISCARD std::string* release_ip();
  void set_allocated_ip(std::string* ptr);

  private:
  const std::string& _internal_ip() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_ip(
      const std::string& value);
  std::string* _internal_mutable_ip();

  public:
  // int32 port = 2;
  void clear_port() ;
  ::int32_t port() const;
  void set_port(::int32_t value);

  private:
  ::int32_t _internal_port() const;
  void _internal_set_port(::int32_t value);

  public:
  // @@protoc_insertion_point(class_scope:RegisterWorkerRequest)
 private:
  class _Internal;

  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<1, 2, 0, 32, 2> _table_;
  template <typename T> friend class ::google::protobuf::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::google::protobuf::internal::ArenaStringPtr ip_;
    ::int32_t port_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_master_5fservice_2eproto;
};// -------------------------------------------------------------------

class RegisterWorkerReply final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:RegisterWorkerReply) */ {
 public:
  inline RegisterWorkerReply() : RegisterWorkerReply(nullptr) {}
  ~RegisterWorkerReply() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR RegisterWorkerReply(::google::protobuf::internal::ConstantInitialized);

  RegisterWorkerReply(const RegisterWorkerReply& from);
  RegisterWorkerReply(RegisterWorkerReply&& from) noexcept
    : RegisterWorkerReply() {
    *this = ::std::move(from);
  }

  inline RegisterWorkerReply& operator=(const RegisterWorkerReply& from) {
    CopyFrom(from);
    return *this;
  }
  inline RegisterWorkerReply& operator=(RegisterWorkerReply&& from) noexcept {
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

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const RegisterWorkerReply& default_instance() {
    return *internal_default_instance();
  }
  static inline const RegisterWorkerReply* internal_default_instance() {
    return reinterpret_cast<const RegisterWorkerReply*>(
               &_RegisterWorkerReply_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(RegisterWorkerReply& a, RegisterWorkerReply& b) {
    a.Swap(&b);
  }
  inline void Swap(RegisterWorkerReply* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(RegisterWorkerReply* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  RegisterWorkerReply* New(::google::protobuf::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<RegisterWorkerReply>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const RegisterWorkerReply& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom( const RegisterWorkerReply& from) {
    RegisterWorkerReply::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(RegisterWorkerReply* other);

  private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "RegisterWorkerReply";
  }
  protected:
  explicit RegisterWorkerReply(::google::protobuf::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::google::protobuf::Message::ClassData*GetClassData() const final;

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kOkFieldNumber = 1,
  };
  // bool ok = 1;
  void clear_ok() ;
  bool ok() const;
  void set_ok(bool value);

  private:
  bool _internal_ok() const;
  void _internal_set_ok(bool value);

  public:
  // @@protoc_insertion_point(class_scope:RegisterWorkerReply)
 private:
  class _Internal;

  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<0, 1, 0, 0, 2> _table_;
  template <typename T> friend class ::google::protobuf::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    bool ok_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_master_5fservice_2eproto;
};// -------------------------------------------------------------------

class RegisterJobRequest final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:RegisterJobRequest) */ {
 public:
  inline RegisterJobRequest() : RegisterJobRequest(nullptr) {}
  ~RegisterJobRequest() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR RegisterJobRequest(::google::protobuf::internal::ConstantInitialized);

  RegisterJobRequest(const RegisterJobRequest& from);
  RegisterJobRequest(RegisterJobRequest&& from) noexcept
    : RegisterJobRequest() {
    *this = ::std::move(from);
  }

  inline RegisterJobRequest& operator=(const RegisterJobRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline RegisterJobRequest& operator=(RegisterJobRequest&& from) noexcept {
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

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const RegisterJobRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const RegisterJobRequest* internal_default_instance() {
    return reinterpret_cast<const RegisterJobRequest*>(
               &_RegisterJobRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(RegisterJobRequest& a, RegisterJobRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(RegisterJobRequest* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(RegisterJobRequest* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  RegisterJobRequest* New(::google::protobuf::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<RegisterJobRequest>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const RegisterJobRequest& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom( const RegisterJobRequest& from) {
    RegisterJobRequest::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(RegisterJobRequest* other);

  private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "RegisterJobRequest";
  }
  protected:
  explicit RegisterJobRequest(::google::protobuf::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::google::protobuf::Message::ClassData*GetClassData() const final;

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kPathFieldNumber = 1,
    kMapperFieldNumber = 2,
    kReducerFieldNumber = 3,
  };
  // string path = 1;
  void clear_path() ;
  const std::string& path() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_path(Arg_&& arg, Args_... args);
  std::string* mutable_path();
  PROTOBUF_NODISCARD std::string* release_path();
  void set_allocated_path(std::string* ptr);

  private:
  const std::string& _internal_path() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_path(
      const std::string& value);
  std::string* _internal_mutable_path();

  public:
  // string mapper = 2;
  void clear_mapper() ;
  const std::string& mapper() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_mapper(Arg_&& arg, Args_... args);
  std::string* mutable_mapper();
  PROTOBUF_NODISCARD std::string* release_mapper();
  void set_allocated_mapper(std::string* ptr);

  private:
  const std::string& _internal_mapper() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_mapper(
      const std::string& value);
  std::string* _internal_mutable_mapper();

  public:
  // string reducer = 3;
  void clear_reducer() ;
  const std::string& reducer() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_reducer(Arg_&& arg, Args_... args);
  std::string* mutable_reducer();
  PROTOBUF_NODISCARD std::string* release_reducer();
  void set_allocated_reducer(std::string* ptr);

  private:
  const std::string& _internal_reducer() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_reducer(
      const std::string& value);
  std::string* _internal_mutable_reducer();

  public:
  // @@protoc_insertion_point(class_scope:RegisterJobRequest)
 private:
  class _Internal;

  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<2, 3, 0, 44, 2> _table_;
  template <typename T> friend class ::google::protobuf::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::google::protobuf::internal::ArenaStringPtr path_;
    ::google::protobuf::internal::ArenaStringPtr mapper_;
    ::google::protobuf::internal::ArenaStringPtr reducer_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_master_5fservice_2eproto;
};// -------------------------------------------------------------------

class RegisterJobReply final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:RegisterJobReply) */ {
 public:
  inline RegisterJobReply() : RegisterJobReply(nullptr) {}
  ~RegisterJobReply() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR RegisterJobReply(::google::protobuf::internal::ConstantInitialized);

  RegisterJobReply(const RegisterJobReply& from);
  RegisterJobReply(RegisterJobReply&& from) noexcept
    : RegisterJobReply() {
    *this = ::std::move(from);
  }

  inline RegisterJobReply& operator=(const RegisterJobReply& from) {
    CopyFrom(from);
    return *this;
  }
  inline RegisterJobReply& operator=(RegisterJobReply&& from) noexcept {
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

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const RegisterJobReply& default_instance() {
    return *internal_default_instance();
  }
  static inline const RegisterJobReply* internal_default_instance() {
    return reinterpret_cast<const RegisterJobReply*>(
               &_RegisterJobReply_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  friend void swap(RegisterJobReply& a, RegisterJobReply& b) {
    a.Swap(&b);
  }
  inline void Swap(RegisterJobReply* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(RegisterJobReply* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  RegisterJobReply* New(::google::protobuf::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<RegisterJobReply>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const RegisterJobReply& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom( const RegisterJobReply& from) {
    RegisterJobReply::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(RegisterJobReply* other);

  private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "RegisterJobReply";
  }
  protected:
  explicit RegisterJobReply(::google::protobuf::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::google::protobuf::Message::ClassData*GetClassData() const final;

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kOkFieldNumber = 1,
  };
  // bool ok = 1;
  void clear_ok() ;
  bool ok() const;
  void set_ok(bool value);

  private:
  bool _internal_ok() const;
  void _internal_set_ok(bool value);

  public:
  // @@protoc_insertion_point(class_scope:RegisterJobReply)
 private:
  class _Internal;

  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<0, 1, 0, 0, 2> _table_;
  template <typename T> friend class ::google::protobuf::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    bool ok_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_master_5fservice_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// RegisterWorkerRequest

// string ip = 1;
inline void RegisterWorkerRequest::clear_ip() {
  _impl_.ip_.ClearToEmpty();
}
inline const std::string& RegisterWorkerRequest::ip() const {
  // @@protoc_insertion_point(field_get:RegisterWorkerRequest.ip)
  return _internal_ip();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void RegisterWorkerRequest::set_ip(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.ip_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:RegisterWorkerRequest.ip)
}
inline std::string* RegisterWorkerRequest::mutable_ip() {
  std::string* _s = _internal_mutable_ip();
  // @@protoc_insertion_point(field_mutable:RegisterWorkerRequest.ip)
  return _s;
}
inline const std::string& RegisterWorkerRequest::_internal_ip() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.ip_.Get();
}
inline void RegisterWorkerRequest::_internal_set_ip(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.ip_.Set(value, GetArenaForAllocation());
}
inline std::string* RegisterWorkerRequest::_internal_mutable_ip() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  return _impl_.ip_.Mutable( GetArenaForAllocation());
}
inline std::string* RegisterWorkerRequest::release_ip() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:RegisterWorkerRequest.ip)
  return _impl_.ip_.Release();
}
inline void RegisterWorkerRequest::set_allocated_ip(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.ip_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.ip_.IsDefault()) {
          _impl_.ip_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:RegisterWorkerRequest.ip)
}

// int32 port = 2;
inline void RegisterWorkerRequest::clear_port() {
  _impl_.port_ = 0;
}
inline ::int32_t RegisterWorkerRequest::port() const {
  // @@protoc_insertion_point(field_get:RegisterWorkerRequest.port)
  return _internal_port();
}
inline void RegisterWorkerRequest::set_port(::int32_t value) {
  _internal_set_port(value);
  // @@protoc_insertion_point(field_set:RegisterWorkerRequest.port)
}
inline ::int32_t RegisterWorkerRequest::_internal_port() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.port_;
}
inline void RegisterWorkerRequest::_internal_set_port(::int32_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.port_ = value;
}

// -------------------------------------------------------------------

// RegisterWorkerReply

// bool ok = 1;
inline void RegisterWorkerReply::clear_ok() {
  _impl_.ok_ = false;
}
inline bool RegisterWorkerReply::ok() const {
  // @@protoc_insertion_point(field_get:RegisterWorkerReply.ok)
  return _internal_ok();
}
inline void RegisterWorkerReply::set_ok(bool value) {
  _internal_set_ok(value);
  // @@protoc_insertion_point(field_set:RegisterWorkerReply.ok)
}
inline bool RegisterWorkerReply::_internal_ok() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.ok_;
}
inline void RegisterWorkerReply::_internal_set_ok(bool value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.ok_ = value;
}

// -------------------------------------------------------------------

// RegisterJobRequest

// string path = 1;
inline void RegisterJobRequest::clear_path() {
  _impl_.path_.ClearToEmpty();
}
inline const std::string& RegisterJobRequest::path() const {
  // @@protoc_insertion_point(field_get:RegisterJobRequest.path)
  return _internal_path();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void RegisterJobRequest::set_path(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.path_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:RegisterJobRequest.path)
}
inline std::string* RegisterJobRequest::mutable_path() {
  std::string* _s = _internal_mutable_path();
  // @@protoc_insertion_point(field_mutable:RegisterJobRequest.path)
  return _s;
}
inline const std::string& RegisterJobRequest::_internal_path() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.path_.Get();
}
inline void RegisterJobRequest::_internal_set_path(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.path_.Set(value, GetArenaForAllocation());
}
inline std::string* RegisterJobRequest::_internal_mutable_path() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  return _impl_.path_.Mutable( GetArenaForAllocation());
}
inline std::string* RegisterJobRequest::release_path() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:RegisterJobRequest.path)
  return _impl_.path_.Release();
}
inline void RegisterJobRequest::set_allocated_path(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.path_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.path_.IsDefault()) {
          _impl_.path_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:RegisterJobRequest.path)
}

// string mapper = 2;
inline void RegisterJobRequest::clear_mapper() {
  _impl_.mapper_.ClearToEmpty();
}
inline const std::string& RegisterJobRequest::mapper() const {
  // @@protoc_insertion_point(field_get:RegisterJobRequest.mapper)
  return _internal_mapper();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void RegisterJobRequest::set_mapper(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.mapper_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:RegisterJobRequest.mapper)
}
inline std::string* RegisterJobRequest::mutable_mapper() {
  std::string* _s = _internal_mutable_mapper();
  // @@protoc_insertion_point(field_mutable:RegisterJobRequest.mapper)
  return _s;
}
inline const std::string& RegisterJobRequest::_internal_mapper() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.mapper_.Get();
}
inline void RegisterJobRequest::_internal_set_mapper(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.mapper_.Set(value, GetArenaForAllocation());
}
inline std::string* RegisterJobRequest::_internal_mutable_mapper() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  return _impl_.mapper_.Mutable( GetArenaForAllocation());
}
inline std::string* RegisterJobRequest::release_mapper() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:RegisterJobRequest.mapper)
  return _impl_.mapper_.Release();
}
inline void RegisterJobRequest::set_allocated_mapper(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.mapper_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.mapper_.IsDefault()) {
          _impl_.mapper_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:RegisterJobRequest.mapper)
}

// string reducer = 3;
inline void RegisterJobRequest::clear_reducer() {
  _impl_.reducer_.ClearToEmpty();
}
inline const std::string& RegisterJobRequest::reducer() const {
  // @@protoc_insertion_point(field_get:RegisterJobRequest.reducer)
  return _internal_reducer();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void RegisterJobRequest::set_reducer(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.reducer_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:RegisterJobRequest.reducer)
}
inline std::string* RegisterJobRequest::mutable_reducer() {
  std::string* _s = _internal_mutable_reducer();
  // @@protoc_insertion_point(field_mutable:RegisterJobRequest.reducer)
  return _s;
}
inline const std::string& RegisterJobRequest::_internal_reducer() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.reducer_.Get();
}
inline void RegisterJobRequest::_internal_set_reducer(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.reducer_.Set(value, GetArenaForAllocation());
}
inline std::string* RegisterJobRequest::_internal_mutable_reducer() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  return _impl_.reducer_.Mutable( GetArenaForAllocation());
}
inline std::string* RegisterJobRequest::release_reducer() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:RegisterJobRequest.reducer)
  return _impl_.reducer_.Release();
}
inline void RegisterJobRequest::set_allocated_reducer(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.reducer_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.reducer_.IsDefault()) {
          _impl_.reducer_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:RegisterJobRequest.reducer)
}

// -------------------------------------------------------------------

// RegisterJobReply

// bool ok = 1;
inline void RegisterJobReply::clear_ok() {
  _impl_.ok_ = false;
}
inline bool RegisterJobReply::ok() const {
  // @@protoc_insertion_point(field_get:RegisterJobReply.ok)
  return _internal_ok();
}
inline void RegisterJobReply::set_ok(bool value) {
  _internal_set_ok(value);
  // @@protoc_insertion_point(field_set:RegisterJobReply.ok)
}
inline bool RegisterJobReply::_internal_ok() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.ok_;
}
inline void RegisterJobReply::_internal_set_ok(bool value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.ok_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_master_5fservice_2eproto_2epb_2eh
