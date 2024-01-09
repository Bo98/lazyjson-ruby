# frozen_string_literal: true

module LazyJSON
  module DigMixin
    def dig(*args)
      raise ArgumentError, "wrong number of arguments (given 0, expected 1+)" if args.empty?

      key = args.shift
      value = self[key]
      return if value.nil?

      if args.empty?
        value
      else
        value.dig(*args)
      end
    end
  end
  private_constant :DigMixin

  class Array
    include DigMixin
  end

  class Hash
    include DigMixin
  end
end
