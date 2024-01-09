#include "exception.hpp"

using namespace Rice;

LazyJSON::ParseError::ParseError(const char* message) : std::runtime_error(message)
{
}

void LazyJSON::ParseError::register_class(const Module &module)
{
  Class rb_cParseError = define_class_under(module, "ParseError", rb_eRuntimeError);
  register_handler<LazyJSON::ParseError>([rb_cParseError] (const auto& ex) {
    throw Rice::Exception(rb_cParseError, ex.what());
  });
}

LazyJSON::InternalError::InternalError(const char* message) : std::runtime_error(message)
{
}

void LazyJSON::InternalError::register_class(const Module &module)
{
  Class rb_cInternalError = define_class_under(module, "InternalError", rb_eRuntimeError);
  register_handler<LazyJSON::InternalError>([rb_cInternalError] (const auto& ex) {
    throw Rice::Exception(rb_cInternalError, ex.what());
  });
}
