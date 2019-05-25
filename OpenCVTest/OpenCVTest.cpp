#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

int main()
{
	std::cout << "OpenCV Version : " << CV_VERSION << std::endl;
	cv::Mat img;
	cv::namedWindow("EXAMPLE01", cv::WindowFlags::WINDOW_AUTOSIZE);

	img = cv::imread("Lenna.png", cv::IMREAD_UNCHANGED);// CV_LOAD_IMAGE_COLOR);
	if (img.empty())
	{
		std::cout << "[!] You can NOT see the cat!" << std::endl;
		return -1;
	}
	cv::imshow("EXAMPLE01", img);
	cv::waitKey(0);
	cv::destroyWindow("EXAMPLE01");
	return 0;
}
