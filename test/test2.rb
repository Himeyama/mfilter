#!/usr/bin/env ruby
require "bundler/setup"
require "mfilter"

fs = 1000.0
t = Array.new(1001){|i| i / fs}
z = t.map{|e| Math::sin(e) + 0.25 * rand}
b = [0.000029146, 0.000000000, -0.000087439, 0.000000000, 0.000087439, 0.000000000, -0.000029146]
a = [1.00000, -5.86566, 14.34551, -18.72442, 13.75684, -5.39416, 0.88189]

# p fs, t



p MFilter::_filter(b, a, z, [-2.4165e-18, -2.4165e-18, 4.8331e-18, 4.8331e-18, -2.4165e-18, -2.4165e-18])