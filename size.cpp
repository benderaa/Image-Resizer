#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

// Constants
const int BUFFER_SIZE = 1024;
const int MIN_SCALE_FACTOR = 1;
const int MAX_SCALE_FACTOR = 10;

// Function to display usage instructions
void displayUsage() {
    std::cout << "Usage: image_resizer <input_file> <output_file> <scale_factor>" << std::endl;
    std::cout << "       <scale_factor> should be an integer between " << MIN_SCALE_FACTOR << " and " << MAX_SCALE_FACTOR << "." << std::endl;
}

// Function to resize an image
bool resizeImage(const std::string& inputFilePath, const std::string& outputFilePath, int scaleFactor) {
    cv::Mat inputImage = cv::imread(inputFilePath);
    if (inputImage.empty()) {
        std::cerr << "Error: Failed to open input file." << std::endl;
        return false;
    }

    // Resize the image
    cv::Mat resizedImage;
    cv::resize(inputImage, resizedImage, cv::Size(), scaleFactor, scaleFactor);

    // Save the resized image
    if (!cv::imwrite(outputFilePath, resizedImage)) {
        std::cerr << "Error: Failed to save output file." << std::endl;
        return false;
    }

    std::cout << "Image successfully resized and saved to " << outputFilePath << std::endl;
    return true;
}

int main(int argc, char** argv) {
    // Check the number of command line arguments
    if (argc != 4) {
        std::cerr << "Error: Invalid number of arguments." << std::endl;
        displayUsage();
        return 1;
    }

    // Parse command line arguments
    std::string inputFilePath = argv[1];
    std::string outputFilePath = argv[2];
    int scaleFactor = std::stoi(argv[3]);

    // Validate scale factor
    if (scaleFactor < MIN_SCALE_FACTOR || scaleFactor > MAX_SCALE_FACTOR) {
        std::cerr << "Error: Invalid scale factor. Scale factor should be between " << MIN_SCALE_FACTOR << " and " << MAX_SCALE_FACTOR << "." << std::endl;
        displayUsage();
        return 1;
    }

    // Resize the image
    if (!resizeImage(inputFilePath, outputFilePath, scaleFactor)) {
        return 1;
    }

    return 0;
}
