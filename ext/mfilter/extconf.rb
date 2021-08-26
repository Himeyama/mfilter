require "mkmf"

have_library("octave")
have_library("octinterp")
have_library("m")

create_makefile "mfilter"