#include <rice/rice.hpp>
#include "simdjson.h"
#include "util.hpp"
#include "exception.hpp"
#include "array.hpp"
#include "hash.hpp"

using namespace Rice;

namespace LazyJSON
{
  static simdjson::dom::parser &parser()
  {
    thread_local simdjson::dom::parser parser;
    return parser;
  }

  static Object parse(String json)
  {
    auto document = std::make_shared<simdjson::dom::document>();
    auto root = parser().parse_into_document(*document, json.c_str(), json.length(), (rb_str_capacity(json) - json.length()) < simdjson::SIMDJSON_PADDING);

    simdjson::dom::element element;
    auto error = root.get(element);
    if (error)
      throw ParseError(simdjson::error_message(error));
    return LazyJSON::parse_element(std::move(document), element);
  }
}

extern "C" void Init_lazyjson() noexcept
{
#ifdef HAVE_RB_EXT_RACTOR_SAFE
  rb_ext_ractor_safe(true);
#endif

  Module rb_mLazyJSON = define_module("LazyJSON")
    .define_singleton_function("parse", &LazyJSON::parse);

  LazyJSON::ParseError::register_class(rb_mLazyJSON);
  LazyJSON::InternalError::register_class(rb_mLazyJSON);
  register_handler<simdjson::simdjson_error>([] (const auto &ex) {
    throw LazyJSON::InternalError(ex.what());
  });

  Data_Type<LazyJSON::Array> rb_cArray = define_class_under<LazyJSON::Array>(rb_mLazyJSON, "Array")
    .define_iterator(&LazyJSON::Array::begin, &LazyJSON::Array::end)
    .define_method("[]", &LazyJSON::Array::operator[]);

  Data_Type<LazyJSON::Hash> rb_cHash = define_class_under<LazyJSON::Hash>(rb_mLazyJSON, "Hash")
    .define_iterator(&LazyJSON::Hash::begin, &LazyJSON::Hash::end)
    .define_method("[]", &LazyJSON::Hash::operator[])
    .define_method("key?", &LazyJSON::Hash::has_key);
}
