#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;

int main(int argc, char *argv[])
{

	if( argc < 3 ) {
		printf("Usage: orb [image 1] [image 2]\n");
		return 0;
	}

	string file1(argv[1]);
	string file2(argv[2]);

	cv::Mat srcImage1, srcImage2;

	cout << "OpenCV Version : " << CV_VERSION << std::endl;
	//cv::namedWindow("EXAMPLE01", cv::WindowFlags::WINDOW_AUTOSIZE);
	cv::namedWindow("EXAMPLE01", cv::WINDOW_NORMAL);
	srcImage1 = cv::imread(file1, cv::IMREAD_UNCHANGED);
	srcImage2 = cv::imread(file2, cv::IMREAD_UNCHANGED);

	cv::resize(srcImage1, srcImage1, cv::Size(srcImage1.cols / 2, srcImage1.rows / 2));
	cv::resize(srcImage2, srcImage2, cv::Size(srcImage2.cols / 2, srcImage2.rows / 2));

	if (srcImage1.empty() || srcImage2.empty()) {
		cout << "Loading an image is failed." << endl;
		return -1;
	}
	cv::imshow("EXAMPLE01", srcImage1);
	cv::waitKey(0);
	cv::imshow("EXAMPLE01", srcImage2);
	cv::waitKey(0);

	cout << "Feature extracting..." << endl;

	vector<cv::KeyPoint> keypoint1, keypoint2;
	cv::Ptr<cv::ORB> orbF = cv::ORB::create(100);
	cv::Mat descriptor1, descriptor2;

	orbF->detectAndCompute(srcImage1, cv::noArray(), keypoint1, descriptor1);
	orbF->detectAndCompute(srcImage2, cv::noArray(), keypoint2, descriptor2);

#if 0
	// convert keypoint info 
	vector<cv::Point2f> kp1_xy, kp2_xy;
	vector<int> kp1_xy_idx, kp2_xy_idx;
	cv::KeyPoint::convert(keypoint1, kp1_xy, kp1_xy_idx);
	cv::KeyPoint::convert(keypoint2, kp2_xy, kp2_xy_idx);
#endif
#if 0
	cout << "size of keypoint = " << keypoint1.size();
	for (int i = 0; i < keypoint1.size(); i++) {
		cout << "x,y = " << kp1_xy[i].x << "," << kp1_xy[i].y << endl;
	}
#endif

	cout << "Drawing keypoints..." << endl;

	cv::Mat kpImage1, kpImage2;
	cv::drawKeypoints(srcImage1, keypoint1, kpImage1, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
	cv::drawKeypoints(srcImage2, keypoint2, kpImage2, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);

	cv::Mat kpImageCombined = (kpImage1 + kpImage2) / 2;

	cv::imshow("EXAMPLE01", kpImageCombined);
	cv::waitKey(0);

	cv::destroyWindow("EXAMPLE01");
	return 0;
}
