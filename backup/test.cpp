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
