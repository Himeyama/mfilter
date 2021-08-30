# frozen_string_literal: true

require_relative "mfilter/version"

require "mfilter.so"

module MFilter
    class Error < StandardError; end
    
    def filter(b, a, x, si: nil)
        raise TypeError, "b should belong to Array or Numeric class" unless b.is_a? Array or b.is_a? Numeric
        raise TypeError, "a should belong to Array or Numeric class" unless a.is_a? Array or a.is_a? Numeric
        raise TypeError, "x should belong to Array class" unless x.is_a? Array
        raise TypeError, "si should be nil or belong to Array class" unless x.is_a? Array or x.nil?
        b = [b.to_f] if b.is_a? Numeric
        a = [a.to_f] if a.is_a? Numeric
        _filter(b, a, x, si)
    end

    module_function :filter
end
