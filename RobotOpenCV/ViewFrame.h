#pragma once
#include <opencv2/opencv.hpp>

class ViewFrame 
{
	int width, height;
	std::string name;
	cv::Mat frame;
public:
	ViewFrame() 
	{

	}

	ViewFrame(int w, int h, const char* str): width(w),height(h)
	{
		name = str;
		frame = cv::Mat::zeros(height, width, CV_8UC3);
	}

	void update() 
	{
		frame = cv::Mat::zeros(height, width, CV_8UC3);
	}

	cv::Mat getFrame() 
	{
		return frame;
	}

	void show() 
	{
		cv::imshow(name, frame);
	}
};

