# frozen_string_literal: true

module LazyJSON
  module CollectionMixin
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

    def fetch(key, default = (default_omitted = true; nil))
      if !default_omitted && block_given?
        warn "warning: block supersedes default value argument"
      end

      value = self[key]
      return value unless value.nil?

      if block_given?
        yield(key)
      elsif default_omitted
        raise KeyError, "key not found: #{key.inspect}"
      else
        default
      end
    end
  end
  private_constant :CollectionMixin

  class Array
    include CollectionMixin
  end

  class Hash
    include CollectionMixin
  end
end
