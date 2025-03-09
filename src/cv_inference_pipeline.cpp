#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <opencv2/opencv.hpp>

// Namespace alias
namespace fs = std::filesystem;
using namespace std::chrono;

// Default resolutions
const cv::Size SD(640, 480);
const cv::Size HD(1280, 720);
const cv::Size FHD(1920, 1080);

// Function to create a directory if it doesn't exist
void create_directory(const std::string& path) {
    if (!fs::exists(path)) {
        fs::create_directories(path);
    }
}

// Function to format current date-time as a string
std::string get_current_datetime() {
    auto now = system_clock::now();
    auto in_time_t = system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y.%m.%d.%H-%M-%S");
    return ss.str();
}

// Function to check if a string is a valid integer (camera ID)
bool isNumber(const std::string& str) {
    return !str.empty() && str.find_first_not_of("0123456789") == std::string::npos;
}

// Main Video Processing Function
void run_pipeline(const std::string& source,
                  bool save = false,
                  int save_fps = -1,
                  int fps_limit = -1, 
                  int duration = -1,
                  cv::Size resolution = HD) {

    // Initialize VideoCapture
    cv::VideoCapture cap;
    if (isNumber(source)) {
        int cameraID = std::stoi(source);
        cap.open(cameraID);
        std::cout << "✅ Using Camera ID: " << cameraID << std::endl;
    } else {
        cap.open(source);
        std::cout << "✅ Using Video File: " << source << std::endl;
    }

    if (!cap.isOpened()) {
        std::cerr << "Error: VideoCapture is not open: " << source << std::endl;
        return;
    }

    // Set camera/video properties
    cap.set(cv::CAP_PROP_FRAME_WIDTH, resolution.width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, resolution.height);
    
    // Get camera/video properties
    int cap_fps = static_cast<int>(cap.get(cv::CAP_PROP_FPS));
    int cap_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int cap_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    int cap_frames = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));

    // Apply default values if parameters were not provided
    fps_limit = (fps_limit > 0) ? fps_limit : cap_fps;
    save_fps = (save_fps > 0) ? save_fps : fps_limit;
    cv::Size cap_resolution(cap_width, cap_height);

    // Create OpenCV display window
    std::string winname = "Inference";
    cv::namedWindow(winname, cv::WINDOW_NORMAL);
    cv::resizeWindow(winname, HD.width, HD.height);
    cv::moveWindow(winname, FHD.width / 2 - HD.width / 2, FHD.height / 2 - HD.height / 2);

    // Recording Setup
    cv::VideoWriter out_org, out_mod;
    if (save) {
        std::string cur_date_time = get_current_datetime();
        std::string cur_date = cur_date_time.substr(0, 10);

        std::string output_dir = "../output";
        std::string original_path = output_dir + "/" + cur_date + "/original/" + cur_date_time + ".mp4";
        std::string modified_path = output_dir + "/" + cur_date + "/modified/" + cur_date_time + ".mp4";

        create_directory(fs::path(original_path).parent_path().string());
        create_directory(fs::path(modified_path).parent_path().string());

        int fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');  // MPEG-4
        out_org.open(original_path, fourcc, save_fps, cap_resolution, true);
        out_mod.open(modified_path, fourcc, save_fps, resolution, true);
    }

    int count = 0;
    int count_warm_up = 5;
    auto init_time = steady_clock::now();
    auto time_limit = steady_clock::now();

    while (cap.isOpened() && (duration < 0 || duration > duration_cast<seconds>(steady_clock::now() - time_limit).count())) {
        count++;
        auto start = steady_clock::now();

        cv::Mat original, frame;
        cap >> original;

        if (original.empty()) break;

        frame = original.clone();
        cv::resize(frame, frame, resolution);
        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

        // Simulate Inference Processing (Placeholder)
        auto inference_speed_start = steady_clock::now();
        // std::this_thread::sleep_for(milliseconds(10)); // Simulated delay
        auto inference_speed_end = steady_clock::now();

        cv::cvtColor(frame, frame, cv::COLOR_RGB2BGR);

        // Record video
        if (save) {
            out_org.write(original);
            out_mod.write(frame);
        }

        // Show frame
        cv::imshow(winname, original);

        // Press 'q' or 'ESC' to quit
        char key = cv::waitKey(1);
        if (key == 'q' || key == 27) break;

        // FPS Limiting
        auto elapsed = duration_cast<milliseconds>(steady_clock::now() - init_time).count();
        int sleep_time = (1000 / fps_limit) - elapsed;
        if (sleep_time > 0) std::this_thread::sleep_for(milliseconds(sleep_time));
        init_time = steady_clock::now();

        // FPS Calculation
        double fps = 1000.0 / duration_cast<milliseconds>(steady_clock::now() - start).count();
        double inference_time = duration_cast<milliseconds>(inference_speed_end - inference_speed_start).count();

        // Show the Inference Speed
        if (count > count_warm_up) {
            std::cout << std::fixed << std::setprecision(0);
            std::cout << "FPS: " << fps << ", Frame ID: " << count << std::endl;
            std::cout << "Inference Time: " << inference_time << " ms" << std::endl;
            std::cout << "===============================" << std::endl;
        }
    }

    // Release resources
    cap.release();
    if (save) {
        out_org.release();
        out_mod.release();
    }
    cv::destroyAllWindows();
}

// Main Function
int main(int argc, char* argv[]) {
    std::string video_path = "../assets/Earth.mp4";
    
    std::string source = video_path;
    bool save = false;
    int save_fps = -1;
    int fps_limit = -1;
    int duration = -1;

    if (argc > 1) source = argv[1];
    if (argc > 2) save = std::stoi(argv[2]);
    if (argc > 3) save_fps = std::stoi(argv[3]);
    if (argc > 4) fps_limit = std::stoi(argv[4]);
    if (argc > 5) duration = std::stoi(argv[5]);

    run_pipeline(source, save, save_fps, fps_limit, duration, SD);
    return 0;
}
