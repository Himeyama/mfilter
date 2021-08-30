require "mkmf"

oc_file = "/usr/include/octave-#{`octave-config -p VERSION`.chop}"
$INCFLAGS += " -I#{oc_file}" if File.exist? oc_file
have_library("octave") 
have_library("octinterp")
have_library("m")

narray_dir = Gem.find_files("numo").map{|e| e.include?("narray") ? e : false}.select{|e| e}.to_a[0]
dir_config('narray', narray_dir, narray_dir)
have_library("narray")

create_makefile "mfilter"