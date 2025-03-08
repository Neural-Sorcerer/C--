cmake_minimum_required(VERSION 3.10)
project(C++)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ✅ Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# ✅ Find ONNX Runtime
set(ONNX_RUNTIME_DIR "/usr/local/onnxruntime")
include_directories(${ONNX_RUNTIME_DIR}/include)
link_directories(${ONNX_RUNTIME_DIR}/lib)

# Find PyTorch
# set(Torch_DIR "/usr/local/libtorch/share/cmake/Torch")
# find_package(Torch REQUIRED)
# include_directories(${TORCH_INCLUDE_DIRS})

# ✅ Add executable
add_executable(main src/main.cpp)

# ✅ Link libraries
target_link_libraries(main 
    ${OpenCV_LIBS} 
    # ${TORCH_LIBRARIES}
    onnxruntime
)
