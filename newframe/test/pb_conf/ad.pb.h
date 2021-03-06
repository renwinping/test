// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ad.proto

#ifndef PROTOBUF_ad_2eproto__INCLUDED
#define PROTOBUF_ad_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ad_2eproto();
void protobuf_AssignDesc_ad_2eproto();
void protobuf_ShutdownFile_ad_2eproto();

class Ad;
class BidResponse;

// ===================================================================

class Ad : public ::google::protobuf::Message {
 public:
  Ad();
  virtual ~Ad();

  Ad(const Ad& from);

  inline Ad& operator=(const Ad& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Ad& default_instance();

  void Swap(Ad* other);

  // implements Message ----------------------------------------------

  Ad* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Ad& from);
  void MergeFrom(const Ad& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string ad_id = 1;
  inline bool has_ad_id() const;
  inline void clear_ad_id();
  static const int kAdIdFieldNumber = 1;
  inline const ::std::string& ad_id() const;
  inline void set_ad_id(const ::std::string& value);
  inline void set_ad_id(const char* value);
  inline void set_ad_id(const char* value, size_t size);
  inline ::std::string* mutable_ad_id();
  inline ::std::string* release_ad_id();
  inline void set_allocated_ad_id(::std::string* ad_id);

  // required string desc = 2;
  inline bool has_desc() const;
  inline void clear_desc();
  static const int kDescFieldNumber = 2;
  inline const ::std::string& desc() const;
  inline void set_desc(const ::std::string& value);
  inline void set_desc(const char* value);
  inline void set_desc(const char* value, size_t size);
  inline ::std::string* mutable_desc();
  inline ::std::string* release_desc();
  inline void set_allocated_desc(::std::string* desc);

  // @@protoc_insertion_point(class_scope:Ad)
 private:
  inline void set_has_ad_id();
  inline void clear_has_ad_id();
  inline void set_has_desc();
  inline void clear_has_desc();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* ad_id_;
  ::std::string* desc_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_ad_2eproto();
  friend void protobuf_AssignDesc_ad_2eproto();
  friend void protobuf_ShutdownFile_ad_2eproto();

  void InitAsDefaultInstance();
  static Ad* default_instance_;
};
// -------------------------------------------------------------------

class BidResponse : public ::google::protobuf::Message {
 public:
  BidResponse();
  virtual ~BidResponse();

  BidResponse(const BidResponse& from);

  inline BidResponse& operator=(const BidResponse& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const BidResponse& default_instance();

  void Swap(BidResponse* other);

  // implements Message ----------------------------------------------

  BidResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BidResponse& from);
  void MergeFrom(const BidResponse& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string request_id = 1;
  inline bool has_request_id() const;
  inline void clear_request_id();
  static const int kRequestIdFieldNumber = 1;
  inline const ::std::string& request_id() const;
  inline void set_request_id(const ::std::string& value);
  inline void set_request_id(const char* value);
  inline void set_request_id(const char* value, size_t size);
  inline ::std::string* mutable_request_id();
  inline ::std::string* release_request_id();
  inline void set_allocated_request_id(::std::string* request_id);

  // repeated .Ad ads = 2;
  inline int ads_size() const;
  inline void clear_ads();
  static const int kAdsFieldNumber = 2;
  inline const ::Ad& ads(int index) const;
  inline ::Ad* mutable_ads(int index);
  inline ::Ad* add_ads();
  inline const ::google::protobuf::RepeatedPtrField< ::Ad >&
      ads() const;
  inline ::google::protobuf::RepeatedPtrField< ::Ad >*
      mutable_ads();

  // @@protoc_insertion_point(class_scope:BidResponse)
 private:
  inline void set_has_request_id();
  inline void clear_has_request_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* request_id_;
  ::google::protobuf::RepeatedPtrField< ::Ad > ads_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_ad_2eproto();
  friend void protobuf_AssignDesc_ad_2eproto();
  friend void protobuf_ShutdownFile_ad_2eproto();

  void InitAsDefaultInstance();
  static BidResponse* default_instance_;
};
// ===================================================================


// ===================================================================

// Ad

// required string ad_id = 1;
inline bool Ad::has_ad_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Ad::set_has_ad_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Ad::clear_has_ad_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Ad::clear_ad_id() {
  if (ad_id_ != &::google::protobuf::internal::kEmptyString) {
    ad_id_->clear();
  }
  clear_has_ad_id();
}
inline const ::std::string& Ad::ad_id() const {
  return *ad_id_;
}
inline void Ad::set_ad_id(const ::std::string& value) {
  set_has_ad_id();
  if (ad_id_ == &::google::protobuf::internal::kEmptyString) {
    ad_id_ = new ::std::string;
  }
  ad_id_->assign(value);
}
inline void Ad::set_ad_id(const char* value) {
  set_has_ad_id();
  if (ad_id_ == &::google::protobuf::internal::kEmptyString) {
    ad_id_ = new ::std::string;
  }
  ad_id_->assign(value);
}
inline void Ad::set_ad_id(const char* value, size_t size) {
  set_has_ad_id();
  if (ad_id_ == &::google::protobuf::internal::kEmptyString) {
    ad_id_ = new ::std::string;
  }
  ad_id_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Ad::mutable_ad_id() {
  set_has_ad_id();
  if (ad_id_ == &::google::protobuf::internal::kEmptyString) {
    ad_id_ = new ::std::string;
  }
  return ad_id_;
}
inline ::std::string* Ad::release_ad_id() {
  clear_has_ad_id();
  if (ad_id_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = ad_id_;
    ad_id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Ad::set_allocated_ad_id(::std::string* ad_id) {
  if (ad_id_ != &::google::protobuf::internal::kEmptyString) {
    delete ad_id_;
  }
  if (ad_id) {
    set_has_ad_id();
    ad_id_ = ad_id;
  } else {
    clear_has_ad_id();
    ad_id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string desc = 2;
inline bool Ad::has_desc() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Ad::set_has_desc() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Ad::clear_has_desc() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Ad::clear_desc() {
  if (desc_ != &::google::protobuf::internal::kEmptyString) {
    desc_->clear();
  }
  clear_has_desc();
}
inline const ::std::string& Ad::desc() const {
  return *desc_;
}
inline void Ad::set_desc(const ::std::string& value) {
  set_has_desc();
  if (desc_ == &::google::protobuf::internal::kEmptyString) {
    desc_ = new ::std::string;
  }
  desc_->assign(value);
}
inline void Ad::set_desc(const char* value) {
  set_has_desc();
  if (desc_ == &::google::protobuf::internal::kEmptyString) {
    desc_ = new ::std::string;
  }
  desc_->assign(value);
}
inline void Ad::set_desc(const char* value, size_t size) {
  set_has_desc();
  if (desc_ == &::google::protobuf::internal::kEmptyString) {
    desc_ = new ::std::string;
  }
  desc_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Ad::mutable_desc() {
  set_has_desc();
  if (desc_ == &::google::protobuf::internal::kEmptyString) {
    desc_ = new ::std::string;
  }
  return desc_;
}
inline ::std::string* Ad::release_desc() {
  clear_has_desc();
  if (desc_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = desc_;
    desc_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Ad::set_allocated_desc(::std::string* desc) {
  if (desc_ != &::google::protobuf::internal::kEmptyString) {
    delete desc_;
  }
  if (desc) {
    set_has_desc();
    desc_ = desc;
  } else {
    clear_has_desc();
    desc_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// BidResponse

// required string request_id = 1;
inline bool BidResponse::has_request_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BidResponse::set_has_request_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BidResponse::clear_has_request_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BidResponse::clear_request_id() {
  if (request_id_ != &::google::protobuf::internal::kEmptyString) {
    request_id_->clear();
  }
  clear_has_request_id();
}
inline const ::std::string& BidResponse::request_id() const {
  return *request_id_;
}
inline void BidResponse::set_request_id(const ::std::string& value) {
  set_has_request_id();
  if (request_id_ == &::google::protobuf::internal::kEmptyString) {
    request_id_ = new ::std::string;
  }
  request_id_->assign(value);
}
inline void BidResponse::set_request_id(const char* value) {
  set_has_request_id();
  if (request_id_ == &::google::protobuf::internal::kEmptyString) {
    request_id_ = new ::std::string;
  }
  request_id_->assign(value);
}
inline void BidResponse::set_request_id(const char* value, size_t size) {
  set_has_request_id();
  if (request_id_ == &::google::protobuf::internal::kEmptyString) {
    request_id_ = new ::std::string;
  }
  request_id_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BidResponse::mutable_request_id() {
  set_has_request_id();
  if (request_id_ == &::google::protobuf::internal::kEmptyString) {
    request_id_ = new ::std::string;
  }
  return request_id_;
}
inline ::std::string* BidResponse::release_request_id() {
  clear_has_request_id();
  if (request_id_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = request_id_;
    request_id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void BidResponse::set_allocated_request_id(::std::string* request_id) {
  if (request_id_ != &::google::protobuf::internal::kEmptyString) {
    delete request_id_;
  }
  if (request_id) {
    set_has_request_id();
    request_id_ = request_id;
  } else {
    clear_has_request_id();
    request_id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// repeated .Ad ads = 2;
inline int BidResponse::ads_size() const {
  return ads_.size();
}
inline void BidResponse::clear_ads() {
  ads_.Clear();
}
inline const ::Ad& BidResponse::ads(int index) const {
  return ads_.Get(index);
}
inline ::Ad* BidResponse::mutable_ads(int index) {
  return ads_.Mutable(index);
}
inline ::Ad* BidResponse::add_ads() {
  return ads_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Ad >&
BidResponse::ads() const {
  return ads_;
}
inline ::google::protobuf::RepeatedPtrField< ::Ad >*
BidResponse::mutable_ads() {
  return &ads_;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ad_2eproto__INCLUDED
