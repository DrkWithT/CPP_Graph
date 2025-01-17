# utility.sh
# By: DrkWithT
# Project: CPP_Graph

if [[ $# -lt 1 ]]; then
    echo "Usage: ./utility.sh [build <preset> | test]";
    exit 1
fi

option="$1"

if [[ "$option" = "build" && $# -ne 3 ]]; then
    cmake -S . -B build --preset $2 && cmake --build build;
    cp ./build/compile_commands.json .
elif [[ "$option" = "test" ]]; then
    ctest --test-dir build -V --timeout 2
else
    echo "Usage: ./utility.sh [build <preset> | test]";
    exit 1
fi
