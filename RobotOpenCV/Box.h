#pragma once

#include <opencv2/opencv.hpp>
#include "windowParam.h"

class Box
{
private:
	int thickness = 10;			//	wall width

public:
	void draw(cv::Mat frame);	//	draws walls and coordinate lines
};