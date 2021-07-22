#! /usr/bin/env ruby
require 'fileutils'
require 'erb'

CONFIG_FILE = 'config/dev.cfg'


def parse_config()
  conf = {}
  content = File.read(CONFIG_FILE)
  content.split("\n").each do |line|
    line = line.split(" ")
    conf[line[0]] = line[1]
  end
  return conf
end

def create_from_erb(filename_in, filename_out)
  unless filename_in.end_with?'.erb'
    puts "ERROR this is not a erb template"
  end
  erb_template = File.read(filename_in)

  created_file = ""
  created_file += ERB.new(erb_template, nil, '>').result()

  File.write(filename_out, created_file)
end

def build_cpp()
  top_dir = File.dirname(__dir__)
  build_dir = File.join(top_dir, 'build')
  output_cpp_dir =  File.join(top_dir, 'output/cpp')
  output_cpp_include_dir =  File.join(top_dir, 'output/cpp/include')

  FileUtils.rm_rf(output_cpp_dir) if File.directory?(output_cpp_dir)
  FileUtils.rm_rf(output_cpp_include_dir) if File.directory?(output_cpp_include_dir)
  FileUtils.mkdir_p(output_cpp_dir) unless File.directory?(output_cpp_dir)
  FileUtils.mkdir_p(output_cpp_include_dir) unless File.directory?(output_cpp_include_dir)

  puts "1x"

  Find.find(build_dir).each  do |filename|
    next if File.directory? filename
    if filename.end_with? '.hpp'
      puts filename
      FileUtils.cp(filename, output_cpp_include_dir)
    end
  end

  Dir.chdir top_dir
  system "cmake ."
  if $?.success?
    puts "cmake . okay\n"
  else
    abort "cmake . bad\n"
  end
  system "make"
  if $?.success?
    puts "make okay\n"
  else
    abort "make bad\n"
  end
  system "#{File.join(top_dir, "scripts/install_cpp.rb")}"
  if $?.success?
    puts "#{File.join(top_dir, "scripts/install_cpp.rb")} okay\n"
  else
    abort "#{File.join(top_dir, "scripts/install_cpp.rb")} bad #{$?}\n"
  end
end

if __FILE__ == $0

  top_dir = File.dirname(__dir__)

  build_dir = File.join(top_dir, 'build')
  src_dir = File.join(top_dir, 'src')
  output_dir = File.join(top_dir, 'output')

  FileUtils.rm_rf(build_dir) if File.directory?(build_dir)
  FileUtils.rm_rf(output_dir) if File.directory?(output_dir)

  FileUtils.mkdir_p(build_dir) unless File.directory?(build_dir)
  FileUtils.mkdir_p(output_dir) unless File.directory?(output_dir)

  src_config = parse_config()

  require "find"

  fbs_build_file = ""

  Find.find(src_dir).each do |filename|
    next if filename == src_dir
    relative_filename = filename.sub(src_dir,"")
    target_filename = File.join(build_dir, relative_filename)
    if File.directory? filename
      FileUtils.mkdir_p(target_filename)
      next
    end
    fbs_build_file = target_filename if filename.end_with? '.fbs' or File.basename(filename, '.erb').end_with?'.fbs'
    unless filename.end_with? '.erb'
      FileUtils.cp(filename, File.dirname(target_filename))
      puts "copy #{filename} #{File.dirname(target_filename)}"
      next
    else
      dir_temp_variable = File.dirname(target_filename)
      create_from_erb(filename, File.join(dir_temp_variable, File.basename(target_filename, '.erb')))
      puts "erb #{filename} #{File.join(dir_temp_variable, File.basename(target_filename, '.erb'))}"
    end
  end

  abort "missing fbs file" if fbs_build_file == ""

  system ("#{File.join(top_dir, "script/flatbuffers_init.sh")} #{fbs_build_file}")

  build_cpp()



  exit 0

end
