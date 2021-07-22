#! /usr/bin/env ruby
require 'fileutils'
if __FILE__ == $0
  output_dir = File.join(__dir__, 'output/cpp')
  output_include_dir = File.join(output_dir, 'include')

  include_dest_dir = "/usr/local/include/"
  lib_dest_dir = "/usr/lib/"
  #copy include to /usr/local/include
  Dir[File.join(output_include_dir, '*')].each do |filename|
    FileUtils.cp(filename, include_dest_dir)
  end

  #copy so to /usr/lib/
  Dir[File.join(output_dir, '*')].each do |filename|
    FileUtils.cp(filename, lib_dest_dir) unless File.directory? filename
  end

end
