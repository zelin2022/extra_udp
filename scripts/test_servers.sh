trap "exit 0" INT TERM
trap "kill 0" EXIT

THIS_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
TOP_LEVEL_PATH="$(dirname "$THIS_DIR")"
cd $TOP_LEVEL_PATH

build/test_server1 &
build/test_server2 &
wait %1 %2
# wait
