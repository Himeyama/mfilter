# frozen_string_literal: true

require_relative "mfilter/version"

require "numo/narray"
require "mfilter.so"

module MFilter
    class Error < StandardError; end
    
    def filter(b, a, x, si: nil)
        raise TypeError, "b should belong to Array or Numeric class" unless b.is_a? Array or b.is_a? Numeric or b.is_a? Numo::DFloat
        raise TypeError, "a should belong to Array or Numeric class" unless a.is_a? Array or a.is_a? Numeric or a.is_a? Numo::DFloat
        raise TypeError, "x should belong to Array class" unless x.is_a? Array or x.is_a? Numo::DFloat
        raise TypeError, "si should be nil or belong to Array class" unless si.is_a? Array or si.nil? or si.is_a? Numo::DFloat
        b = [b.to_f] if b.is_a? Numeric
        a = [a.to_f] if a.is_a? Numeric
        if b.is_a? Numo::DFloat
           return na_filter(b, a, x, si)
        end
        
        _filter(b, a, x, si)
    end

    module_function :filter
end
