# C++ Project Setup Guide

## **Compiling and Running C++ Code**

### **File Structure**
```plaintext
PROJECT/
│── src/
│   ├── main.cpp
│   ├── video_reader.cpp
│── CMakeLists.txt
│── build/
```

### Update the System
Before installing any dependencies, update your system:

```bash
sudo apt update -y
sudo apt upgrade -y
```

### Check Installed Compiler and CMake
Check if g++ and cmake are installed:

```bash
g++ --version
cmake --version
```

### Install Compiler and CMake
If missing, install them using:

```bash
sudo apt install g++ -y
sudo apt install cmake -y
```

## **Compiling and Running Scripts**

### Basic Compilation
Compile a simple C++ program:

```bash
g++ -o main main.cpp && ./main
```

### Compile and Run a Camera Reader

```bash
g++ -o src/main src/main.cpp && ./src/main
```

### Compile and Run a Video Reader (using OpenCV)

```bash
g++ -o src/main src/main.cpp `pkg-config --cflags --libs opencv4` && ./src/main
g++ -o src/video_reader src/video_reader.cpp `pkg-config --cflags --libs opencv4` && ./src/video_reader
```

## **Installing Dependencies**

### Install OpenCV

```bash
sudo apt update
sudo apt install libopencv-dev -y
pkg-config --modversion opencv4
```

### Install ONNX Runtime

```bash
wget https://github.com/microsoft/onnxruntime/releases/download/v1.16.0/onnxruntime-linux-x64-1.16.0.tgz
tar -xvzf onnxruntime-linux-x64-1.16.0.tgz
sudo mv onnxruntime-linux-x64-1.16.0 /usr/local/onnxruntime
```

### Install LibTorch

```bash
wget https://download.pytorch.org/libtorch/cpu/libtorch-shared-with-deps-2.6.0+cpu.zip
unzip libtorch-shared-with-deps-2.6.0+cpu.zip
sudo mv libtorch /usr/local/
```

## **Building the Project with CMake**

```bash
mkdir build && cd build && cmake .. && make && ./main
mkdir build && cd build && cmake .. && make && ./cv_inference_pipeline "../assets/Earth.mp4" 1 -1 -1 -1
rm -rf build/
```

## To run code: Code Runner Extension:
```bash
use shortcut Ctrl+Alt+N
```
