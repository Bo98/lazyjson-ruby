#include <rice/rice.hpp>
#include "simdjson.h"

namespace LazyJSON
{
  class Array
  {
  public:
    class Iterator {
    public:
      using difference_type = std::ptrdiff_t;
      using value_type = Rice::Object;
      using pointer = void;
      using reference = value_type;
      using iterator_category = std::forward_iterator_tag;

      Iterator() noexcept = default;
      Iterator(const Iterator&) noexcept = default;
      Iterator& operator=(const Iterator &) noexcept = default;

      value_type operator*() const noexcept;
      Iterator& operator++() noexcept;
      Iterator operator++(int) noexcept;

      bool operator!=(const Iterator &other) const noexcept;
      inline bool operator==(const Iterator &other) const noexcept;

      bool operator<(const Iterator &other) const noexcept;
      bool operator<=(const Iterator &other) const noexcept;
      bool operator>=(const Iterator &other) const noexcept;
      bool operator>(const Iterator &other) const noexcept;

    private:
      Iterator(std::shared_ptr<simdjson::dom::document> document, simdjson::dom::array::iterator &&inner) noexcept;

      std::shared_ptr<simdjson::dom::document> m_document;
      simdjson::dom::array::iterator m_inner;

      friend class LazyJSON::Array;
    };

    Array(std::shared_ptr<simdjson::dom::document> document, simdjson::dom::array &&array);
    Rice::Object operator[](size_t idx) const;

    Iterator begin() const noexcept;
    Iterator end() const noexcept;

  private:
    std::shared_ptr<simdjson::dom::document> m_document;
    simdjson::dom::array m_array;
  };
}
