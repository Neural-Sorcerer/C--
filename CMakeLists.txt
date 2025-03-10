cmake_minimum_required(VERSION 3.10)
project(C++)

# ✅ Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ✅ Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# ✅ Add first executable script
add_executable(main src/cv_inference_pipeline.cpp)
target_link_libraries(main ${OpenCV_LIBS})

# ✅ Add second executable script
add_executable(face src/cv_inference_pipeline_model_face.cpp)
target_link_libraries(face ${OpenCV_LIBS})

# ✅ Add third executable script
add_executable(pose src/cv_inference_pipeline_model_pose.cpp)
target_link_libraries(pose ${OpenCV_LIBS})
