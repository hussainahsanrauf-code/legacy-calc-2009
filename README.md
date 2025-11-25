## Build
g++ -std=c++11 src/*.cpp -o calc

## Run
./calc -cp -a 100000 -i 12 -n 360

## Tests (if using GoogleTest)
mkdir build && cd build
cmake ..
make
ctest

## Configuration
Place `config.txt` in the root of the repo.

