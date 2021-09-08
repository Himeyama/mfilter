require "mkmf"

# homebrew で Octave がインストールされている場合
oct_inc_dir = Dir.glob("#{ENV["HOME"]}/.linuxbrew/include/octave-*")
unless oct_inc_dir.empty?
    oct_inc_dir = oct_inc_dir[0]
    if File.exist? oct_inc_dir
        oct_inc_dir =~ /-(.*)$/
        oct_ver = $1
    else
        raise
    end
    oct_inc_dir += "/octave"
    oct_lib_dir = "#{ENV["HOME"]}/.linuxbrew/lib/octave/#{oct_ver}"
    oct_lib_dir = File.exist?(oct_lib_dir) ? oct_lib_dir : nil
else
    oct_inc_dir = Dir.glob("/usr/include/octave-*")
    unless oct_inc_dir.empty?
        oct_inc_dir = oct_inc_dir[0]
        if File.exist? oct_inc_dir
            oct_inc_dir =~ /-(.*)$/
            oct_ver = $1
        else
            raise
        end
        oct_inc_dir += "/octave"
        oct_lib_dir = "/usr/lib/x86_64-linux-gnu/octave/#{oct_ver}"
        oct_lib_dir = File.exist?(oct_lib_dir) ? oct_lib_dir : nil
    else
        raise "Octave がインストールされていません"
    end
end
$LDFLAGS += " -L#{oct_lib_dir}"
$INCFLAGS += " -I#{oct_inc_dir}"
$libs += " -loctinterp"



narray_dir = Gem.find_files("numo").map{|e| e.include?("narray") ? e : false}.select{|e| e}.to_a[0]
$LDFLAGS += " -L#{narray_dir}"
$INCFLAGS += " -I#{narray_dir}"
$libs += " #{narray_dir}/narray.so"

create_makefile "mfilter"