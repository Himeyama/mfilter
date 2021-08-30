#!/usr/bin/env ruby
require "bundler/setup"
require "mfilter"

fs = 1000.0
t = Array.new(1001){|i| i / fs}
x = t.map{|e| Math::sin(10 * 2 * Math::PI * e) + rand}
b = [0.000029146, 0.000000000, -0.000087439, 0.000000000, 0.000087439, 0.000000000, -0.000029146]
a = [1.00000, -5.86566, 14.34551, -18.72442, 13.75684, -5.39416, 0.88189]


y = MFilter::filter(b, a, x, si: [-2.4165e-18, -2.4165e-18, 4.8331e-18, 4.8331e-18, -2.4165e-18, -2.4165e-18])

p y

open("test/data2.dat", "w") do |f|
    f.puts [t, x, y].transpose.map{|e| e.join(" ")}
end

# gnuplot -e 'plot "test/data2.dat" using 1:2 w l title "Input Data", "test/data2.dat" using 1:3 w l title "Filtered Data"; pause -1'