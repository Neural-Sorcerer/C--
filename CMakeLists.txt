cmake_minimum_required(VERSION 3.10)
project(C++)

# ✅ Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ✅ Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# ✅ Find ONNX Runtime
set(ONNX_RUNTIME_DIR "/usr/local/onnxruntime")
include_directories(${ONNX_RUNTIME_DIR}/include)
link_directories(${ONNX_RUNTIME_DIR}/lib)

# ✅ Add first executable script
add_executable(main src/cv_inference_pipeline.cpp)
target_link_libraries(main ${OpenCV_LIBS} onnxruntime)

# ✅ Add second executable script
add_executable(face src/cv_inference_pipeline_model_face.cpp)
target_link_libraries(face ${OpenCV_LIBS} onnxruntime)

# ✅ Add third executable script
add_executable(pose src/cv_inference_pipeline_model_pose.cpp)
target_link_libraries(pose ${OpenCV_LIBS} onnxruntime)
