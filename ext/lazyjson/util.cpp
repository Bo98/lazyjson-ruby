#include "util.hpp"
#include "exception.hpp"
#include "array.hpp"
#include "hash.hpp"

using namespace Rice;

Object LazyJSON::parse_element(std::shared_ptr<simdjson::dom::document> document, const simdjson::dom::element& element)
{
  try
  {
    switch (element.type())
    {
      case simdjson::dom::element_type::ARRAY:
        return Data_Object<LazyJSON::Array>(new LazyJSON::Array(document, element.get_array().value()), true);
      case simdjson::dom::element_type::OBJECT:
        return Data_Object<LazyJSON::Hash>(new LazyJSON::Hash(document, element.get_object().value()), true);
      case simdjson::dom::element_type::INT64:
        return Object(detail::to_ruby(element.get_int64().value()));
      case simdjson::dom::element_type::UINT64:
        return Object(detail::to_ruby(element.get_uint64().value()));
      case simdjson::dom::element_type::DOUBLE:
        return Object(detail::to_ruby(element.get_double().value()));
      case simdjson::dom::element_type::STRING:
      {
        // Rice::String doesn't accept string_view currently
        const auto str = element.get_string().value();
        return Builtin_Object<T_STRING>(detail::protect(rb_str_new, str.data(), (long)str.length()));
      }
      case simdjson::dom::element_type::BOOL:
        return Object(detail::to_ruby(element.get_bool().value()));
      case simdjson::dom::element_type::NULL_VALUE:
        return Nil;
      default:
        throw LazyJSON::ParseError("Unknown type");
    }
  }
  catch (const simdjson::simdjson_error& e)
  {
    throw LazyJSON::ParseError(e.what());
  }
}
