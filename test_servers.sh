trap "exit" INT TERM
trap "kill 0" EXIT
build/test_server1 &
build/test_server2 &
wait %1 %2
# wait
