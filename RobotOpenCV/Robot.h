#pragma once

#include <opencv2/opencv.hpp>
#include <ctime>
#include "windowParam.h"
#include "ViewFrame.h"
//	robot parameters
const int ROBO_WIDTH = 120, ROBO_HEIGHT = 40;
const float ROBOT_SPEED = 1.0;

class Robot
{
private:
	int x = WINDOW_WIDTH / 2, y = WINDOW_HEIGHT - WINDOW_HEIGHT / 20,
		width = ROBO_WIDTH, height = ROBO_HEIGHT;
	float speed = ROBOT_SPEED;
	ViewFrame cam; 

public:
	Robot();
	void draw(cv::Mat frame);					//	drawing rules
	void move(clock_t deltaTime, int key);		//	moving rules
	void updateCam();
	void showCam();
	cv::Mat getCamFrame();

	int getX()
	{ return x; }
	int getY()
	{ return y; }
	int getWidth() 
	{ return width; }
	int getHeight()
	{ return height; }

};