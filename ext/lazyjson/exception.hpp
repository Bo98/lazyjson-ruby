#include <stdexcept>
#include <rice/rice.hpp>

namespace LazyJSON
{
  class ParseError : public std::runtime_error
  {
  public:
    ParseError(const char* message);

    static void register_class(const Rice::Module &module);
  };

  class InternalError : public std::runtime_error
  {
  public:
    InternalError(const char* message);

    static void register_class(const Rice::Module &module);
  };
}
