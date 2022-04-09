#/bin/bash
rootDir="$PWD"
plugPath="plugins/ModelPlugin"
cd $plugPath
cmake -B build
cd build
make
cd $rootDir
echo "now in $rootDir"
mkdir -p build/$plugPath
cp $plugPath/build/qmldir  build/$plugPath/qmldir
cp $plugPath/build/libModelPlugin.so build/$plugPath/libModelPlugin.so
cmake -B build/
cd build/
make
cd ..
./build/Task1
