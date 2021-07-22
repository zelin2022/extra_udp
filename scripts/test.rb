#! /usr/bin/env ruby
if __FILE__ == $0

  top_dir = File.dirname(__dir__)
  Dir.chdir top_dir

  system "#{top_dir}/scripts/build.rb"
  if $?.success?
    puts "build.rb (building lib) okay\n"
  else
    puts "build.rb (building lib) bad\n"
  end

  puts File.join(top_dir, 'output/cpp/')
  system "g++ -std=c++20 -g spec/test_server1.cpp -o build/test_server1 -I#{File.join(top_dir, 'output/cpp/include/')} -L#{File.join(top_dir, 'output/cpp/')} -lextra_udp"
  if $?.success?
    puts "build server1 okay\n"
  else
    puts "build server1 bad\n"
  end

  system "g++ -std=c++20 -g spec/test_server2.cpp -o build/test_server2 -I#{File.join(top_dir, 'output/cpp/include')} -L#{File.join(top_dir, 'output/cpp')} -lextra_udp"
  if $?.success?
    puts "build server2 okay\n"
  else
    puts "build server2 bad\n"
  end
  # add .so to a ld path
  system "#{top_dir}/scripts/test_servers.sh"
  if $?.success?
    puts "test test_servers okay\n"
  else
    puts "test test_servers bad with #{$?}\n"
  end
end
