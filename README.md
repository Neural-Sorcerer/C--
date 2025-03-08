# C++

## main.cpp(code) --> main (compiled)

4. Update and upgrading the system:
$ sudo apt update -y
$ sudo apt upgrade -y

g++ --version
cmake --version

<!-- Compiler -->
sudo apt install g++

<!-- Run script -->
g++ -o main main.cpp
./main
or
g++ -o main main.cpp && ./main

<!-- CMAKE -->
sudo apt install cmake

<!-- Create a CMakeLists.txt file: -->
cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add the executable
add_executable(my_exe src/main.cpp)

<!-- Configure and build: -->
mkdir build && cd build && cmake .. && make && ./main




<!-- Read Camera -->
g++ -o src/main src/main.cpp && ./src/main

g++ -o src/video_reader src/video_reader.cpp `pkg-config --cflags --libs opencv4` && ./src/video_reader


my_project/
│── src/
│   ├── main.cpp
│── CMakeLists.txt
│── build/


sudo apt update
sudo apt install libopencv-dev
pkg-config --modversion opencv4


wget https://github.com/microsoft/onnxruntime/releases/download/v1.16.0/onnxruntime-linux-x64-1.16.0.tgz
tar -xvzf onnxruntime-linux-x64-1.16.0.tgz
sudo mv onnxruntime-linux-x64-1.16.0 /usr/local/onnxruntime

<!-- wget https://download.pytorch.org/libtorch/cpu/libtorch-shared-with-deps-2.1.0+cpu.zip -->
wget https://download.pytorch.org/libtorch/cpu/libtorch-shared-with-deps-2.6.0%2Bcpu.zip
unzip libtorch-shared-with-deps-2.6.0+cpu.zip
sudo mv libtorch /usr/local/