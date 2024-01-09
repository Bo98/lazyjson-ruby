#include "array.hpp"
#include "util.hpp"
#include "exception.hpp"

using namespace Rice;

LazyJSON::Array::Array::Iterator::Iterator(std::shared_ptr<simdjson::dom::document> document, simdjson::dom::array::iterator &&inner) noexcept : m_document(std::move(document)), m_inner(std::move(inner))
{
}

LazyJSON::Array::Array::Iterator::value_type LazyJSON::Array::Array::Iterator::operator*() const noexcept
{
  return LazyJSON::parse_element(m_document, *m_inner);
}

LazyJSON::Array::Array::Iterator& LazyJSON::Array::Array::Iterator::operator++() noexcept
{
  ++m_inner;
  return *this;
}

LazyJSON::Array::Array::Iterator LazyJSON::Array::Array::Iterator::operator++(int) noexcept
{
  auto copy = *this;
  ++*this;
  return copy;
}

bool LazyJSON::Array::Array::Iterator::operator!=(const Iterator &other) const noexcept
{
  return m_inner != other.m_inner;
}

bool LazyJSON::Array::Array::Iterator::operator==(const Iterator &other) const noexcept
{
  return m_inner == other.m_inner;
}

bool LazyJSON::Array::Array::Iterator::operator<(const Iterator &other) const noexcept
{
  return m_inner < other.m_inner;
}

bool LazyJSON::Array::Array::Iterator::operator<=(const Iterator &other) const noexcept
{
  return m_inner <= other.m_inner;
}

bool LazyJSON::Array::Array::Iterator::operator>=(const Iterator &other) const noexcept
{
  return m_inner >= other.m_inner;
}

bool LazyJSON::Array::Array::Iterator::operator>(const Iterator &other) const noexcept
{
  return m_inner > other.m_inner;
}


LazyJSON::Array::Array(std::shared_ptr<simdjson::dom::document> document, simdjson::dom::array &&array) : m_document(std::move(document)), m_array(std::move(array))
{
}

Object LazyJSON::Array::operator[](size_t idx) const
{
  simdjson::dom::element element;
  auto error = m_array.at(idx).get(element);
  if (error == simdjson::error_code::INDEX_OUT_OF_BOUNDS)
    return Nil;
  else if (error)
    throw LazyJSON::InternalError(simdjson::error_message(error));
  return LazyJSON::parse_element(m_document, element);
}

LazyJSON::Array::Iterator LazyJSON::Array::begin() const noexcept
{
  return Iterator(m_document, m_array.begin());
}

LazyJSON::Array::Iterator LazyJSON::Array::end() const noexcept
{
  return Iterator(m_document, m_array.end());
}
