#!/usr/bin/env ruby
require "bundler/setup"
require "mfilter"

t = Array.new(100){|i| -Math::PI + i * 2 * Math::PI / (100 - 1)}
x = t.map{|e| Math::sin(e) + 0.25 * rand}
b = [0.2] * 5
a = [1]

y = MFilter::filter(b, a, x)

open("test/data.dat", "w") do |f|
    f.puts [t, x, y].transpose.map{|e| e.join(" ")}
end

# gnuplot -e 'plot "test/data.dat" using 1:2 w l title "Input Data", "test/data.dat" using 1:3 w l title "Filtered Data"; pause -1'