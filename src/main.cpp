// Script to run webcam in c++ with aiming lines
#include <iostream>
#include <opencv2/opencv.hpp>

// Default Resolutions
const cv::Size SS(640, 360);
const cv::Size SD(640, 480);
const cv::Size HD(1280, 720);
const cv::Size FHD(1920, 1080);
const cv::Size UHD(3840, 2160);

// Function to draw aiming lines
void drawAimLines(cv::Mat& frame, const cv::Size& resolution) {
    cv::Scalar color(255, 255, 0);  // Light blue

    // Draw vertical and horizontal center lines
    cv::line(frame, cv::Point(resolution.width / 2, 0), 
                    cv::Point(resolution.width / 2, resolution.height), color, 1);
    cv::line(frame, cv::Point(0, resolution.height / 2), 
                    cv::Point(resolution.width, resolution.height / 2), color, 1);

    // Draw rectangle
    cv::rectangle(frame, cv::Point(700, 510), cv::Point(1150, 720), cv::Scalar(255, 255, 255), 1);
}

// Main function to read video and apply drawing
void mainLoop(int camera = 0, int freeze = 1, const cv::Size& resolution = SD, const std::string& frameName = "Frame") {
    cv::VideoCapture cap(camera);

    // Set resolution
    cap.set(cv::CAP_PROP_FRAME_WIDTH, resolution.width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, resolution.height);

    if (!cap.isOpened()) {
        std::cerr << "Error: Cannot open camera!" << std::endl;
        return;
    }

    // Create a named window with a fixed size
    cv::namedWindow(frameName, cv::WINDOW_NORMAL);
    cv::resizeWindow(frameName, 1280, 720);

    cv::Mat frame;

    while (true) {
        cap >> frame;                       // Capture frame

        if (frame.empty()) break;           // Stop if no frame is captured

        drawAimLines(frame, resolution);    // Draw aim lines

        cv::imshow(frameName, frame);       // Display frame

        // Press 'q' or 'ESC' to quit
        char key = cv::waitKey(freeze);
        if (key == 'q' || key == 27) break;
    }

    // Release resources
    cap.release();
    cv::destroyAllWindows();
}

int main() {
    mainLoop();
    return 0;
}
