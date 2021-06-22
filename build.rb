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

if __FILE__ == $0
  build_dir = File.join(__dir__, 'build')
  src_dir = File.join(__dir__, 'src')
  output_dir = File.join(__dir__, 'output')
  output_include_dir = File.join(output_dir, 'include')

  FileUtils.mkdir_p(build_dir) unless File.directory?(build_dir)
  FileUtils.mkdir_p(output_dir) unless File.directory?(output_dir)
  FileUtils.mkdir_p(output_include_dir) unless File.directory?(output_include_dir)

  src_config = parse_config()

  Dir[File.join(src_dir, '*')].each do |filename|
    unless filename.end_with? '.erb'
      FileUtils.cp(filename, build_dir)
      next
    else
      create_from_erb(filename, File.join(build_dir, File.basename(filename, '.erb')))
    end
  end

  Dir[File.join(build_dir, '*')].each do |filename|
    if filename.end_with? '.hpp'
      FileUtils.cp(filename, output_include_dir)
    end
  end

  system "cmake ."
  system "make"

  exit 0

  # FileUtils.rm_rf(build_dir)
end
