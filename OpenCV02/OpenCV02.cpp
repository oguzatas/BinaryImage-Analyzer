// OpenCV02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct Line {
    int startX, endX, startY, endY, intensity;
};


Line findMostIntensiveHorizontalLine(Mat& image);
Line DividenConquer(Mat& image, int startY, int endY, int& mostIntenseLineStartY, int& mostIntenseLineIntensity);


int main()
{
    


    cv::Mat originalImage = cv::imread("imagetwo.jpg", cv::IMREAD_GRAYSCALE);

    if (originalImage.empty()) {
        std::cout << "Could not open or find the image." << std::endl;
        return 1;
    }
    
    // Displaying the image
    std::cout << "Original Image size: " << originalImage.size() << std::endl;
    
    cv::Mat binaryImage;
    cv::threshold(originalImage, binaryImage, 127, 255, cv::THRESH_BINARY);
    
    String windowName = "Binary Image";
    namedWindow(windowName);
    imshow(windowName, binaryImage);
    
    cout << "press any key to continue..." << endl;
    waitKey(0); 


    destroyWindow(windowName); 

    std::cout << "Binary Image size: " << binaryImage.size() << std::endl;


    Line mostIntensiveLine = findMostIntensiveHorizontalLine(binaryImage);

    std::cout << "Most Intensive Horizontal Black Line with Sequential method: "
        << "At the Line " << mostIntensiveLine.startY  << " Intensity: " << mostIntensiveLine.intensity << std::endl;

    int mostIntenseLineStartY = 0;
    int mostIntenseLineIntensity = 0;

    Line result = DividenConquer(binaryImage, 0, binaryImage.rows - 1, mostIntenseLineStartY, mostIntenseLineIntensity);

    std::cout << "Most Intensive Line in Image using Divide and Conquer Approach: "
        << "StartY: " << mostIntensiveLine.startY
        << " Intensity: " << mostIntensiveLine.intensity << std::endl;



    return 0;
}


Line findMostIntensiveHorizontalLine(Mat& image) {
    Line result = { 0, 0, 0 };

    int rows = image.rows;
    int cols = image.cols;

    
    for (int y = 0; y < rows; ++y) {
        int intensity = 0;
        for (int x = 0; x < cols; ++x) {
            if (image.at<uchar>(y, x) == 0) { 
                intensity++;
            }
        }
        if (intensity > result.intensity) {
            result.startY = result.endY = y;
            
            result.intensity = intensity;
        }
    }

    return result;
}


Line DividenConquer(Mat& image, int startY, int endY, int& mostIntenseLineStartY, int& mostIntenseLineIntensity) {


    if (startY == endY) {
        int intensity = 0;
        for (int x = 0; x < image.cols; ++x) {
            if (image.at<uchar>(startY, x) == 0) {
                intensity++;
            }
        }

        if (intensity > mostIntenseLineIntensity) {
            mostIntenseLineStartY = startY;
            mostIntenseLineIntensity = intensity;
        }

        return { startY, intensity };
    }

    int mid = (startY + endY) / 2;

    Line left = DividenConquer(image, startY, mid, mostIntenseLineStartY, mostIntenseLineIntensity);
    Line right = DividenConquer(image, mid + 1, endY, mostIntenseLineStartY, mostIntenseLineIntensity);

    if (left.intensity >= right.intensity) {

        return left;
    }
    else {
        return right;
    }
}



