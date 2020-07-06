#pragma once

#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "windowParam.h"
#include "Robot.h"

//	ball parameters
const int BALL_SIZE = 10;
const float BALL_SPEED = 1.0;
const float PI = 3.14;

class Ball
{
private:
	bool hit = false;				//	true when ball hit robot
	int x = WINDOW_WIDTH / 2, y = WINDOW_HEIGHT / 2, rad = BALL_SIZE;
	int b, g, r;					//	color
	float speed = BALL_SPEED;
	float shift = 0, angle;
	float deltaRad = 0;

public:
	Ball();
	void draw(cv::Mat frame, cv::Mat frame2);					//	drawing rules
	void move(clock_t deltaTime, Robot bot);	//	moving rules
	bool isAlive();			//	checks if ball got away
	void regenerate();		//	respawns ball

	bool didHit()
	{ return hit; }
};