#include <iostream>
#include <opencv2/opencv.hpp>
#include <onnxruntime/core/session/onnxruntime_cxx_api.h>
#include <torch/script.h>

int main() {
    // ✅ Test OpenCV
    cv::Mat image = cv::Mat::zeros(480, 640, CV_8UC3);
    cv::imshow("Test Image", image);
    cv::waitKey(0);

    // ✅ Test ONNX Runtime
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "ONNX_Test");
    std::cout << "ONNX Runtime initialized successfully!" << std::endl;

    // ✅ Test PyTorch
    torch::Tensor tensor = torch::rand({2, 3});
    std::cout << "Torch Tensor:\n" << tensor << std::endl;

    return 0;
}


    // std::cout << "OpenCV CUDA support: " << cv::cuda::getCudaEnabledDeviceCount() << " GPU(s) detected." << std::endl;
    // Enable GPU acceleration
    // Explicitly set CUDA backend and target
    // faceDetector.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    // faceDetector.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);

    // std::cout << cv::getBuildInformation() << std::endl;
    // std::cout << "Backend: " << faceDetector.getPreferableBackend() << std::endl;
    // std::cout << "Target: " << faceDetector.getPreferableTarget() << std::endl;

    // faceDetector.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    // faceDetector.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);
    // exit(0);
