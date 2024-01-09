#include "hash.hpp"
#include "util.hpp"
#include "exception.hpp"

using namespace Rice;

LazyJSON::Hash::Hash::Iterator::Iterator(std::shared_ptr<simdjson::dom::document> document, simdjson::dom::object::iterator &&inner) noexcept : m_document(std::move(document)), m_inner(std::move(inner))
{
}

LazyJSON::Hash::Hash::Iterator::value_type LazyJSON::Hash::Hash::Iterator::operator*() const noexcept
{
  auto pair = *m_inner;
  // Rice::String doesn't accept string_view currently
  auto key = Builtin_Object<T_STRING>(detail::protect(rb_str_new, pair.key.data(), (long)pair.key.length()));
  auto value = LazyJSON::parse_element(m_document, pair.value);
  return rb_assoc_new(key, value);
}

LazyJSON::Hash::Hash::Iterator& LazyJSON::Hash::Hash::Iterator::operator++() noexcept
{
  ++m_inner;
  return *this;
}

LazyJSON::Hash::Hash::Iterator LazyJSON::Hash::Hash::Iterator::operator++(int) noexcept
{
  auto copy = *this;
  ++*this;
  return copy;
}

bool LazyJSON::Hash::Hash::Iterator::operator!=(const Iterator &other) const noexcept
{
  return m_inner != other.m_inner;
}

bool LazyJSON::Hash::Hash::Iterator::operator==(const Iterator &other) const noexcept
{
  return m_inner == other.m_inner;
}

bool LazyJSON::Hash::Hash::Iterator::operator<(const Iterator &other) const noexcept
{
  return m_inner < other.m_inner;
}

bool LazyJSON::Hash::Hash::Iterator::operator<=(const Iterator &other) const noexcept
{
  return m_inner <= other.m_inner;
}

bool LazyJSON::Hash::Hash::Iterator::operator>=(const Iterator &other) const noexcept
{
  return m_inner >= other.m_inner;
}

bool LazyJSON::Hash::Hash::Iterator::operator>(const Iterator &other) const noexcept
{
  return m_inner > other.m_inner;
}


LazyJSON::Hash::Hash(std::shared_ptr<simdjson::dom::document> document, simdjson::dom::object &&object) : m_document(std::move(document)), m_object(std::move(object))
{
}

Object LazyJSON::Hash::operator[](String key)
{
  simdjson::dom::element element;
  auto error = m_object.at_key(key.c_str()).get(element);
  if (error == simdjson::error_code::NO_SUCH_FIELD)
    return Nil;
  else if (error)
    throw LazyJSON::InternalError(simdjson::error_message(error));
  return LazyJSON::parse_element(m_document, element);
}

LazyJSON::Hash::Iterator LazyJSON::Hash::begin() const noexcept
{
  return Iterator(m_document, m_object.begin());
}

LazyJSON::Hash::Iterator LazyJSON::Hash::end() const noexcept
{
  return Iterator(m_document, m_object.end());
}
