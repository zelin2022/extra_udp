# assume script is at the top level dir of the library
THIS_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
TOP_LEVEL_PATH="$(dirname "$THIS_DIR")"

if [ $# -eq 0 ]; then
    echo "No arguments provided"
    exit 1
fi

mkdir -p $TOP_LEVEL_PATH/flatbuffer_tmp
cd $TOP_LEVEL_PATH/flatbuffer_tmp

if [ ! -d "${TOP_LEVEL_PATH}/flatbuffer_tmp/flatbuffers" ]
then
  git clone git@github.com:google/flatbuffers.git
fi

FLATCPATH=$TOP_LEVEL_PATH/flatbuffer_tmp/flatbuffers/flatc

cd $TOP_LEVEL_PATH/flatbuffer_tmp/flatbuffers
if [ ! -f $FLATCPATH ]
then
  cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
  make
fi

cd $TOP_LEVEL_PATH

LIBPATH="$TOP_LEVEL_PATH/build/lib/flatbuffers"
mkdir -p $LIBPATH
rm -rf $LIBPATH/*

$FLATCPATH --cpp -o $LIBPATH $1
