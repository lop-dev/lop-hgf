// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: result.proto

#ifndef PROTOBUF_result_2eproto__INCLUDED
#define PROTOBUF_result_2eproto__INCLUDED

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

namespace Message {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_result_2eproto();
void protobuf_AssignDesc_result_2eproto();
void protobuf_ShutdownFile_result_2eproto();

class CResult;

// ===================================================================

class CResult : public ::google::protobuf::Message {
 public:
  CResult();
  virtual ~CResult();

  CResult(const CResult& from);

  inline CResult& operator=(const CResult& from) {
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
  static const CResult& default_instance();

  void Swap(CResult* other);

  // implements Message ----------------------------------------------

  CResult* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CResult& from);
  void MergeFrom(const CResult& from);
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

  // required string Url = 1;
  inline bool has_url() const;
  inline void clear_url();
  static const int kUrlFieldNumber = 1;
  inline const ::std::string& url() const;
  inline void set_url(const ::std::string& value);
  inline void set_url(const char* value);
  inline void set_url(const char* value, size_t size);
  inline ::std::string* mutable_url();
  inline ::std::string* release_url();
  inline void set_allocated_url(::std::string* url);

  // optional string Title = 2;
  inline bool has_title() const;
  inline void clear_title();
  static const int kTitleFieldNumber = 2;
  inline const ::std::string& title() const;
  inline void set_title(const ::std::string& value);
  inline void set_title(const char* value);
  inline void set_title(const char* value, size_t size);
  inline ::std::string* mutable_title();
  inline ::std::string* release_title();
  inline void set_allocated_title(::std::string* title);

  // repeated string Snippets = 3;
  inline int snippets_size() const;
  inline void clear_snippets();
  static const int kSnippetsFieldNumber = 3;
  inline const ::std::string& snippets(int index) const;
  inline ::std::string* mutable_snippets(int index);
  inline void set_snippets(int index, const ::std::string& value);
  inline void set_snippets(int index, const char* value);
  inline void set_snippets(int index, const char* value, size_t size);
  inline ::std::string* add_snippets();
  inline void add_snippets(const ::std::string& value);
  inline void add_snippets(const char* value);
  inline void add_snippets(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& snippets() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_snippets();

  // @@protoc_insertion_point(class_scope:Message.CResult)
 private:
  inline void set_has_url();
  inline void clear_has_url();
  inline void set_has_title();
  inline void clear_has_title();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* url_;
  ::std::string* title_;
  ::google::protobuf::RepeatedPtrField< ::std::string> snippets_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_result_2eproto();
  friend void protobuf_AssignDesc_result_2eproto();
  friend void protobuf_ShutdownFile_result_2eproto();

  void InitAsDefaultInstance();
  static CResult* default_instance_;
};
// ===================================================================


// ===================================================================

// CResult

// required string Url = 1;
inline bool CResult::has_url() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CResult::set_has_url() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CResult::clear_has_url() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CResult::clear_url() {
  if (url_ != &::google::protobuf::internal::kEmptyString) {
    url_->clear();
  }
  clear_has_url();
}
inline const ::std::string& CResult::url() const {
  return *url_;
}
inline void CResult::set_url(const ::std::string& value) {
  set_has_url();
  if (url_ == &::google::protobuf::internal::kEmptyString) {
    url_ = new ::std::string;
  }
  url_->assign(value);
}
inline void CResult::set_url(const char* value) {
  set_has_url();
  if (url_ == &::google::protobuf::internal::kEmptyString) {
    url_ = new ::std::string;
  }
  url_->assign(value);
}
inline void CResult::set_url(const char* value, size_t size) {
  set_has_url();
  if (url_ == &::google::protobuf::internal::kEmptyString) {
    url_ = new ::std::string;
  }
  url_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* CResult::mutable_url() {
  set_has_url();
  if (url_ == &::google::protobuf::internal::kEmptyString) {
    url_ = new ::std::string;
  }
  return url_;
}
inline ::std::string* CResult::release_url() {
  clear_has_url();
  if (url_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = url_;
    url_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void CResult::set_allocated_url(::std::string* url) {
  if (url_ != &::google::protobuf::internal::kEmptyString) {
    delete url_;
  }
  if (url) {
    set_has_url();
    url_ = url;
  } else {
    clear_has_url();
    url_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional string Title = 2;
inline bool CResult::has_title() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CResult::set_has_title() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CResult::clear_has_title() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CResult::clear_title() {
  if (title_ != &::google::protobuf::internal::kEmptyString) {
    title_->clear();
  }
  clear_has_title();
}
inline const ::std::string& CResult::title() const {
  return *title_;
}
inline void CResult::set_title(const ::std::string& value) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(value);
}
inline void CResult::set_title(const char* value) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(value);
}
inline void CResult::set_title(const char* value, size_t size) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* CResult::mutable_title() {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  return title_;
}
inline ::std::string* CResult::release_title() {
  clear_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = title_;
    title_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void CResult::set_allocated_title(::std::string* title) {
  if (title_ != &::google::protobuf::internal::kEmptyString) {
    delete title_;
  }
  if (title) {
    set_has_title();
    title_ = title;
  } else {
    clear_has_title();
    title_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// repeated string Snippets = 3;
inline int CResult::snippets_size() const {
  return snippets_.size();
}
inline void CResult::clear_snippets() {
  snippets_.Clear();
}
inline const ::std::string& CResult::snippets(int index) const {
  return snippets_.Get(index);
}
inline ::std::string* CResult::mutable_snippets(int index) {
  return snippets_.Mutable(index);
}
inline void CResult::set_snippets(int index, const ::std::string& value) {
  snippets_.Mutable(index)->assign(value);
}
inline void CResult::set_snippets(int index, const char* value) {
  snippets_.Mutable(index)->assign(value);
}
inline void CResult::set_snippets(int index, const char* value, size_t size) {
  snippets_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* CResult::add_snippets() {
  return snippets_.Add();
}
inline void CResult::add_snippets(const ::std::string& value) {
  snippets_.Add()->assign(value);
}
inline void CResult::add_snippets(const char* value) {
  snippets_.Add()->assign(value);
}
inline void CResult::add_snippets(const char* value, size_t size) {
  snippets_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
CResult::snippets() const {
  return snippets_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
CResult::mutable_snippets() {
  return &snippets_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Message

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_result_2eproto__INCLUDED
