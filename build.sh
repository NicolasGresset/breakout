mkdir -p build
cd build

if [ $# -eq 0 ]; then
    cmake  .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
fi

if [ $# -eq 1 ]; then
    if [ "$1" = "GAME_TESTING" ]; then
        cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DGAME_TESTING=$1
    elif [ "$1" = "clean" ]; then
        rm -rf ../build
        echo "Build directory removed"
        exit 0
    else
        echo "Usage: $0 [clean]\n       $0 [GAME_TESTING]"
        exit 1
    fi
fi

make
