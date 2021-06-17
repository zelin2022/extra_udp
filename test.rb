#! /usr/bin/env ruby
if __FILE__ == $0
  system "#{__dir__}/build.rb"
  if $?.success?
    puts "build.rb (building lib) okay\n"
  else
    puts "build.rb (building lib) bad\n"
  end

  system "g++ -std=c++20 -g spec/test_server1.cpp -o build/test_server1 -I#{File.join(__dir__, 'build')} -L#{File.join(__dir__, 'output')} -lextra_udp"
  if $?.success?
    puts "build server1 okay\n"
  else
    puts "build server1 bad\n"
  end

  system "g++ -std=c++20 -g spec/test_server2.cpp -o build/test_server2 -I#{File.join(__dir__, 'build')} -L#{File.join(__dir__, 'output')} -lextra_udp"
  if $?.success?
    puts "build server2 okay\n"
  else
    puts "build server2 bad\n"
  end
  # add .so to a ld path
  system "./test_servers.sh"
  if $?.success?
    puts "test test_servers okay\n"
  else
    puts "test test_servers bad\n"
  end
end
