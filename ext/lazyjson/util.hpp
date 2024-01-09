#include <rice/rice.hpp>
#include "simdjson.h"

namespace LazyJSON
{
  Rice::Object parse_element(std::shared_ptr<simdjson::dom::document> document, const simdjson::dom::element& element);
}
