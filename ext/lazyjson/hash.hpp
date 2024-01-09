#include <rice/rice.hpp>
#include "simdjson.h"

namespace LazyJSON
{
  class Hash
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
      Iterator(std::shared_ptr<simdjson::dom::document> document, simdjson::dom::object::iterator &&inner) noexcept;

      std::shared_ptr<simdjson::dom::document> m_document;
      simdjson::dom::object::iterator m_inner;

      friend class LazyJSON::Hash;
    };

    Hash(std::shared_ptr<simdjson::dom::document> document, simdjson::dom::object &&object);
    Rice::Object operator[](Rice::String key);

    Iterator begin() const noexcept;
    Iterator end() const noexcept;

  private:
    std::shared_ptr<simdjson::dom::document> m_document;
    simdjson::dom::object m_object;
  };
}
