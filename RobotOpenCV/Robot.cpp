#include "Robot.h"
Robot::Robot() 
{
	cam = ViewFrame(CAMERA_WIDTH, CAMERA_HEIGHT, "CAMERA");
}

void Robot::draw(cv::Mat frame)
{
	//	yeah, robot is a line - MISS (Make It Simply Stuped pattern)
	cv::line(frame, cv::Point(x - width / 2, y), cv::Point(x + width / 2, y), cv::Scalar(192, 15, 255), height);
}

void Robot::move(clock_t deltaTime, int key)
{
	int dx = speed * deltaTime;				//	delta move

	if (x - dx + width <= WINDOW_WIDTH)		//	if it is possiple to move right
	{
		if (key == 'd' || key == 'D')		//	and user press 'D' key
			x += dx;						//	then move right
	}
	if (x + dx - width >= 0)				//	if it is possiple to move left
	{
		if (key == 'a' || key == 'A')		//	and user press 'A' key
			x -= dx;						//	then move left
	}
}

void Robot::updateCam() 
{
	cam.update();
}

void Robot::showCam()
{
	cam.show();
}

cv::Mat Robot::getCamFrame() 
{
	return cam.getFrame();
}