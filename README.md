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


## Console refactor
This repo includes a console refactor in `src/` so the core loan logic can be built without Qt.
Build: g++ -std=c++11 src/*.cpp -o calc
Run example: ./calc -cp -a 100000 -i 12 -n 360
Tests: g++ -std=c++11 test/test_emi.cpp src/Loan.cpp -o test_emi && ./test_emi
