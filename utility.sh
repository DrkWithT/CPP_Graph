if [[ $# -lt 2 ]]; then
    echo "Usage: ./utility.sh [build | test]";
    exit 1
fi

option="$1"

if [[ "$option" = "build" && $# -eq 3 ]]; then
    cmake -S . -B build --preset $2 && cmake --build build;
    cp ./build/compile_commands.json .
elif [[ "$option" = "test" ]]; then
    ctest --test-dir build -V --timeout 2
else
    echo "Usage: ./utility.sh [build | test <preset>]";
    exit 1
fi
