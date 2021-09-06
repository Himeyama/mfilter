require "mkmf"

# oc_file = "/usr/include/octave-#{`octave-config -p VERSION`.chop}"
# oc_file = "#{ENV["HOME"]}/.local/usr/include/octave-4.0.0/octave"


oct_inc_dir = Dir.glob("#{ENV["HOME"]}/.linuxbrew/include/octave-*")
oct_inc_dir = oct_inc_dir[0] unless oct_inc_dir.empty?

$LDFLAGS += " -L#{ENV["HOME"]}/.linuxbrew/lib/octave/4.0.0"

$INCFLAGS += " -I#{oct_inc_dir}" if File.exist? oct_inc_dir
have_library("octave") 
have_library("octinterp")
have_library("m")

narray_dir = Gem.find_files("numo").map{|e| e.include?("narray") ? e : false}.select{|e| e}.to_a[0]
dir_config('narray', narray_dir, narray_dir)
have_library("narray")

create_makefile "mfilter"