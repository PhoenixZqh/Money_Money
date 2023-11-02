rm -rf demo
mkdir build && cd build
cmake ..
make -j
cp demo ../demo
cd ..
rm -rf build
./demo