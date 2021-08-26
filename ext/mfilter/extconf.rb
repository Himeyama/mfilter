require "mkmf"

oc_file = "/usr/include/octave-#{`octave-config -p VERSION`.chop}"
$INCFLAGS += " -I#{oc_file}" if File.exist? oc_file
have_library("octave") 
have_library("octinterp")
have_library("m")

create_makefile "mfilter"