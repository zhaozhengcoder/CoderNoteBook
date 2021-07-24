rm -rf bin

mkdir build
cd build

cmake ../src/
make

cd ../
mv build/bin ./
rm -rf build/
