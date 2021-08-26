# frozen_string_literal: true

require_relative "mfilter/version"

require "mfilter.so"

module MFilter
  class Error < StandardError; end
  
  def filter(b, a, x, si: nil)
    _filter(b, a, x, si)
  end

  module_function :filter
end
