// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: worker_service.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_worker_5fservice_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_worker_5fservice_2eproto_2epb_2eh

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

#define PROTOBUF_INTERNAL_EXPORT_worker_5fservice_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_worker_5fservice_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_worker_5fservice_2eproto;
class AssignWorkReply;
struct AssignWorkReplyDefaultTypeInternal;
extern AssignWorkReplyDefaultTypeInternal _AssignWorkReply_default_instance_;
class AssignWorkRequest;
struct AssignWorkRequestDefaultTypeInternal;
extern AssignWorkRequestDefaultTypeInternal _AssignWorkRequest_default_instance_;
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google


// ===================================================================


// -------------------------------------------------------------------

class AssignWorkRequest final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:AssignWorkRequest) */ {
 public:
  inline AssignWorkRequest() : AssignWorkRequest(nullptr) {}
  ~AssignWorkRequest() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR AssignWorkRequest(::google::protobuf::internal::ConstantInitialized);

  AssignWorkRequest(const AssignWorkRequest& from);
  AssignWorkRequest(AssignWorkRequest&& from) noexcept
    : AssignWorkRequest() {
    *this = ::std::move(from);
  }

  inline AssignWorkRequest& operator=(const AssignWorkRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline AssignWorkRequest& operator=(AssignWorkRequest&& from) noexcept {
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
  static const AssignWorkRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const AssignWorkRequest* internal_default_instance() {
    return reinterpret_cast<const AssignWorkRequest*>(
               &_AssignWorkRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(AssignWorkRequest& a, AssignWorkRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(AssignWorkRequest* other) {
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
  void UnsafeArenaSwap(AssignWorkRequest* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  AssignWorkRequest* New(::google::protobuf::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<AssignWorkRequest>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const AssignWorkRequest& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom( const AssignWorkRequest& from) {
    AssignWorkRequest::MergeImpl(*this, from);
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
  void InternalSwap(AssignWorkRequest* other);

  private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "AssignWorkRequest";
  }
  protected:
  explicit AssignWorkRequest(::google::protobuf::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::google::protobuf::Message::ClassData*GetClassData() const final;

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kPathFieldNumber = 1,
    kModeFieldNumber = 2,
    kClassFieldNumber = 3,
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
  // string mode = 2;
  void clear_mode() ;
  const std::string& mode() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_mode(Arg_&& arg, Args_... args);
  std::string* mutable_mode();
  PROTOBUF_NODISCARD std::string* release_mode();
  void set_allocated_mode(std::string* ptr);

  private:
  const std::string& _internal_mode() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_mode(
      const std::string& value);
  std::string* _internal_mutable_mode();

  public:
  // string class = 3;
  void clear_class_() ;
  const std::string& class_() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_class_(Arg_&& arg, Args_... args);
  std::string* mutable_class_();
  PROTOBUF_NODISCARD std::string* release_class_();
  void set_allocated_class_(std::string* ptr);

  private:
  const std::string& _internal_class_() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_class_(
      const std::string& value);
  std::string* _internal_mutable_class_();

  public:
  // @@protoc_insertion_point(class_scope:AssignWorkRequest)
 private:
  class _Internal;

  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<2, 3, 0, 39, 2> _table_;
  template <typename T> friend class ::google::protobuf::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::google::protobuf::internal::ArenaStringPtr path_;
    ::google::protobuf::internal::ArenaStringPtr mode_;
    ::google::protobuf::internal::ArenaStringPtr class__;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_worker_5fservice_2eproto;
};// -------------------------------------------------------------------

class AssignWorkReply final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:AssignWorkReply) */ {
 public:
  inline AssignWorkReply() : AssignWorkReply(nullptr) {}
  ~AssignWorkReply() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR AssignWorkReply(::google::protobuf::internal::ConstantInitialized);

  AssignWorkReply(const AssignWorkReply& from);
  AssignWorkReply(AssignWorkReply&& from) noexcept
    : AssignWorkReply() {
    *this = ::std::move(from);
  }

  inline AssignWorkReply& operator=(const AssignWorkReply& from) {
    CopyFrom(from);
    return *this;
  }
  inline AssignWorkReply& operator=(AssignWorkReply&& from) noexcept {
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
  static const AssignWorkReply& default_instance() {
    return *internal_default_instance();
  }
  static inline const AssignWorkReply* internal_default_instance() {
    return reinterpret_cast<const AssignWorkReply*>(
               &_AssignWorkReply_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(AssignWorkReply& a, AssignWorkReply& b) {
    a.Swap(&b);
  }
  inline void Swap(AssignWorkReply* other) {
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
  void UnsafeArenaSwap(AssignWorkReply* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  AssignWorkReply* New(::google::protobuf::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<AssignWorkReply>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const AssignWorkReply& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom( const AssignWorkReply& from) {
    AssignWorkReply::MergeImpl(*this, from);
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
  void InternalSwap(AssignWorkReply* other);

  private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "AssignWorkReply";
  }
  protected:
  explicit AssignWorkReply(::google::protobuf::Arena* arena);
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
  // @@protoc_insertion_point(class_scope:AssignWorkReply)
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
  friend struct ::TableStruct_worker_5fservice_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// AssignWorkRequest

// string path = 1;
inline void AssignWorkRequest::clear_path() {
  _impl_.path_.ClearToEmpty();
}
inline const std::string& AssignWorkRequest::path() const {
  // @@protoc_insertion_point(field_get:AssignWorkRequest.path)
  return _internal_path();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void AssignWorkRequest::set_path(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.path_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:AssignWorkRequest.path)
}
inline std::string* AssignWorkRequest::mutable_path() {
  std::string* _s = _internal_mutable_path();
  // @@protoc_insertion_point(field_mutable:AssignWorkRequest.path)
  return _s;
}
inline const std::string& AssignWorkRequest::_internal_path() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.path_.Get();
}
inline void AssignWorkRequest::_internal_set_path(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.path_.Set(value, GetArenaForAllocation());
}
inline std::string* AssignWorkRequest::_internal_mutable_path() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  return _impl_.path_.Mutable( GetArenaForAllocation());
}
inline std::string* AssignWorkRequest::release_path() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:AssignWorkRequest.path)
  return _impl_.path_.Release();
}
inline void AssignWorkRequest::set_allocated_path(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.path_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.path_.IsDefault()) {
          _impl_.path_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:AssignWorkRequest.path)
}

// string mode = 2;
inline void AssignWorkRequest::clear_mode() {
  _impl_.mode_.ClearToEmpty();
}
inline const std::string& AssignWorkRequest::mode() const {
  // @@protoc_insertion_point(field_get:AssignWorkRequest.mode)
  return _internal_mode();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void AssignWorkRequest::set_mode(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.mode_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:AssignWorkRequest.mode)
}
inline std::string* AssignWorkRequest::mutable_mode() {
  std::string* _s = _internal_mutable_mode();
  // @@protoc_insertion_point(field_mutable:AssignWorkRequest.mode)
  return _s;
}
inline const std::string& AssignWorkRequest::_internal_mode() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.mode_.Get();
}
inline void AssignWorkRequest::_internal_set_mode(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.mode_.Set(value, GetArenaForAllocation());
}
inline std::string* AssignWorkRequest::_internal_mutable_mode() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  return _impl_.mode_.Mutable( GetArenaForAllocation());
}
inline std::string* AssignWorkRequest::release_mode() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:AssignWorkRequest.mode)
  return _impl_.mode_.Release();
}
inline void AssignWorkRequest::set_allocated_mode(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.mode_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.mode_.IsDefault()) {
          _impl_.mode_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:AssignWorkRequest.mode)
}

// string class = 3;
inline void AssignWorkRequest::clear_class_() {
  _impl_.class__.ClearToEmpty();
}
inline const std::string& AssignWorkRequest::class_() const {
  // @@protoc_insertion_point(field_get:AssignWorkRequest.class)
  return _internal_class_();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void AssignWorkRequest::set_class_(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.class__.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:AssignWorkRequest.class)
}
inline std::string* AssignWorkRequest::mutable_class_() {
  std::string* _s = _internal_mutable_class_();
  // @@protoc_insertion_point(field_mutable:AssignWorkRequest.class)
  return _s;
}
inline const std::string& AssignWorkRequest::_internal_class_() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.class__.Get();
}
inline void AssignWorkRequest::_internal_set_class_(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.class__.Set(value, GetArenaForAllocation());
}
inline std::string* AssignWorkRequest::_internal_mutable_class_() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  return _impl_.class__.Mutable( GetArenaForAllocation());
}
inline std::string* AssignWorkRequest::release_class_() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:AssignWorkRequest.class)
  return _impl_.class__.Release();
}
inline void AssignWorkRequest::set_allocated_class_(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.class__.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.class__.IsDefault()) {
          _impl_.class__.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:AssignWorkRequest.class)
}

// -------------------------------------------------------------------

// AssignWorkReply

// bool ok = 1;
inline void AssignWorkReply::clear_ok() {
  _impl_.ok_ = false;
}
inline bool AssignWorkReply::ok() const {
  // @@protoc_insertion_point(field_get:AssignWorkReply.ok)
  return _internal_ok();
}
inline void AssignWorkReply::set_ok(bool value) {
  _internal_set_ok(value);
  // @@protoc_insertion_point(field_set:AssignWorkReply.ok)
}
inline bool AssignWorkReply::_internal_ok() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.ok_;
}
inline void AssignWorkReply::_internal_set_ok(bool value) {
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

#endif  // GOOGLE_PROTOBUF_INCLUDED_worker_5fservice_2eproto_2epb_2eh