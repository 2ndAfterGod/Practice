#include "Box.h"

void Box::draw(cv::Mat frame)
{
	//	coordinate lines
	cv::line(frame, cv::Point(WINDOW_WIDTH / 2, 0), cv::Point(WINDOW_WIDTH / 2, WINDOW_HEIGHT),
		cv::Scalar(255, 0, 0), thickness / 5);														//	horizontal
	cv::line(frame, cv::Point(0, WINDOW_HEIGHT / 2), cv::Point(WINDOW_WIDTH, WINDOW_HEIGHT / 2),
		cv::Scalar(255, 0, 0), thickness / 5);														//	vertical

	//	walls
	cv::line(frame, cv::Point(0, WINDOW_HEIGHT), cv::Point(WINDOW_WIDTH, WINDOW_HEIGHT),
		cv::Scalar(0, 0, 255), thickness);															//	bottom
	cv::line(frame, cv::Point(0, 0), cv::Point(0, WINDOW_HEIGHT),
		cv::Scalar(100, 100, 100), thickness);														//	left
	cv::line(frame, cv::Point(WINDOW_WIDTH, 0), cv::Point(0, 0),
		cv::Scalar(100, 100, 100), thickness);														//	right
	cv::line(frame, cv::Point(WINDOW_WIDTH, 0), cv::Point(WINDOW_WIDTH, WINDOW_HEIGHT),
		cv::Scalar(100, 100, 100), thickness);														//	top
}