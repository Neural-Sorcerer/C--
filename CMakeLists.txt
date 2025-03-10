cmake_minimum_required(VERSION 3.10)
project(C++)

# ✅ Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ✅ Find OpenCV with CUDA support
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# ✅ Find CUDA
find_package(CUDA REQUIRED)

# ✅ Ensure OpenCV was built with CUDA
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
message(STATUS "CUDA found: ${CUDA_FOUND}, version: ${CUDA_VERSION}")

# ✅ Link CUDA libraries
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -std=c++17 -O3")
list(APPEND CUDA_NVCC_FLAGS "-arch=sm_86")  # Adjust for your GPU architecture

# ✅ Add first executable script
add_executable(main src/cv_inference_pipeline.cpp)
target_link_libraries(main ${OpenCV_LIBS} ${CUDA_LIBRARIES})

# ✅ Add second executable script
add_executable(face src/cv_inference_pipeline_model_face.cpp)
target_link_libraries(face ${OpenCV_LIBS} ${CUDA_LIBRARIES})

# ✅ Add third executable script
add_executable(pose src/cv_inference_pipeline_model_pose.cpp)
target_link_libraries(pose ${OpenCV_LIBS} ${CUDA_LIBRARIES})
