#ifndef __OPENCV_TEMPLATE_H__
#define __OPENCV_TEMPLATE_H__

//include opencv headers
#include "opencv/cv.h"
#include "opencv2/opencv.hpp"


class OpenCVTemplate{
private:
	cv::VideoCapture capture;
	cv::Mat img_ori;
	void OpenAVI(const char* filepath){ capture = cv::VideoCapture(filepath); };

public:
	OpenCVTemplate(){};
	OpenCVTemplate(const char* filepath){ OpenAVI(filepath); };	
	bool isOpened() { return capture.isOpened(); };
	bool getImage();
	cv::Mat getOriginal() { return img_ori; };
	cv::Mat EdgeDetection(cv::Mat src);

};

#endif