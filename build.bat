cmake -S . -B build -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -G "MinGW Makefiles"
cd build && mingw32-make
