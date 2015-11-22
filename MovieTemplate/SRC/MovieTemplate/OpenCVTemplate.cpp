#include "OpenCVTemplate.h"

bool OpenCVTemplate::getImage() {
	img_ori.release();

	capture >> img_ori;;
	if (!img_ori.empty())
		return true;
	else
		return false;
};

cv::Mat OpenCVTemplate::EdgeDetection(cv::Mat src) {
	cv::Mat gray, dst(src.rows, src.cols, CV_8UC3);
	cv::cvtColor(src, gray, cv::COLOR_RGB2GRAY);

	int ch = dst.channels();
	int width = dst.cols;
	int height = dst.rows;
	//Implement your code here.
	//Pixel's color intensity data contained in data variable of image class. (ex: dst.data, gray.data)
	//The color data of pixel (x,y) in image dst =  dst.data[y*width*ch + x*ch + k] 
	//The grayscale data of pixel (x,y) in grayscale image gray = gray.data[y*width + x] 

	float mask1[3][3] = { { -1, -2, -1 },
							{ 0, 0, 0 },
							{ 1, 2, 1 } };
	float mask2[3][3] = { { -1, 0, 1 },
	{ -2, 0, 2 },
	{ -1, 0, 1 } };
	float mask3[3][3] = { { 0, 1, 2 },
	{ -1, 0, 1 },
	{ -2, -1, 0 } };
	float mask4[3][3] = { { -2, -1, 0 },
	{ -1, 0, 1 },
	{ 0, 1, 2 } };

	int sumGray = 0;

	for (int y = 0; y < dst.rows; y++) {
		for (int x = 0; x < dst.cols; x++) {
			for (int k = 0; k < ch; k++) {
				dst.data[y*width*ch + x*ch + k] = gray.data[y*width + x + k];
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int y = 0; y < dst.rows - 2; y++) {
			for (int x = 0; x < dst.cols - 2; x++) {
				sumGray = 0;
				for (int xsize = x; xsize < (x + 3); xsize++) {
					for (int ysize = y; ysize < (y + 3); ysize++) {
						if(i==0){
							sumGray += gray.data[ysize*width + xsize] * mask1[xsize - x][ysize - y];
						}
						else if(i == 1) {
							sumGray += gray.data[ysize*width + xsize] * mask2[xsize - x][ysize - y];
						}
						else if (i == 2) {
							sumGray += gray.data[ysize*width + xsize] * mask3[xsize - x][ysize - y];
						}
						else if (i == 3) {
							sumGray += gray.data[ysize*width + xsize] * mask4[xsize - x][ysize - y];
						}
						
					}
				}
				if (sumGray < 0) {
					sumGray = -sumGray;
				}
				if (sumGray > 200) {
					if (i == 0) {
						dst.data[(y + 1)*width*ch + (x + 1)*ch + 0] = 0;
						dst.data[(y + 1)*width*ch + (x + 1)*ch + 1] = 0;
						dst.data[(y + 1)*width*ch + (x + 1)*ch + 2] = 255;
					} 
					else if (i == 1) {
						dst.data[(y + 1)*width*ch + (x + 1)*ch + 0] = 0;
						dst.data[(y + 1)*width*ch + (x + 1)*ch + 1] = 255;
						dst.data[(y + 1)*width*ch + (x + 1)*ch + 2] = 0;
					}
					else if (i == 2) {
						dst.data[(y + 1)*width*ch + (x + 1)*ch + 0] = 255;
						dst.data[(y + 1)*width*ch + (x + 1)*ch + 1] = 0;
						dst.data[(y + 1)*width*ch + (x + 1)*ch + 2] = 0;
					}
					else if (i == 3) {
						dst.data[(y + 1)*width*ch + (x + 1)*ch + 0] = 255;
						dst.data[(y + 1)*width*ch + (x + 1)*ch + 1] = 255;
						dst.data[(y + 1)*width*ch + (x + 1)*ch + 2] = 0;
					}
				}
			}
		}
	}


	return dst;
}