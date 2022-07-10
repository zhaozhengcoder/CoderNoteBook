dependencies_include_path=/data/home/your_path
dependencies_lib_path=/data/home/your_lib

g++ -g -I${dependencies_include_path}/lua-5.1.4/src -L ${dependencies_lib_path} -llua -Wl,-rpath=${dependencies_lib_path} test.cpp -o test