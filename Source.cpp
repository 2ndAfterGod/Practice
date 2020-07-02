#include <opencv2/opencv.hpp>
#include <stdio.h> 
#include <time.h>
#include <math.h>
using namespace std;
using namespace cv;

class ball
{
private:

	float speed = 0.1;
	int x = 400, y = 400, rad = 20;
	int b = 0, g = 255, r = 255;
public:

	void draw(Mat frame) 
	{
		circle(frame, Point(x, y), rad, Scalar(b,g,r), FILLED);
	}
	
	int move(clock_t deltaTime)
	{
		x += speed * deltaTime;
		cout << x;
		return x;
	}

};

class box 
{
public:
	void draw(Mat frame)
	{
		
		line(frame, Point(0, 800), Point(800, 800), Scalar(0, 0, 255), 10);
		line(frame, Point(0, 0), Point(0, 800), Scalar(100, 100, 100), 10);
		line(frame, Point(800, 0), Point(0, 0), Scalar(100, 100, 100), 10);
		line(frame, Point(800, 0), Point(800, 800), Scalar(100, 100, 100), 10);
		
	}
};

class robot 
{
private:
	int x=400, y=760;
public:
	void draw(Mat frame) 
	{
		line(frame, Point(x-50, y), Point(x+50, y), Scalar(192, 15, 255), 30); 

	}
	
};

int main() 
{	
	float f = 0;
	clock_t deltaTime = 0;
	ball ball1;
	box world;
	robot robo;
	int thickness = 2;
	Mat frame = Mat::zeros(800, 800, CV_8UC3);
	while (true)
	{
		frame = Mat::zeros(800, 800, CV_8UC3);
		ball1.move(deltaTime);
		line(frame, Point(400, 0), Point(400, 800), Scalar(255, 0, 0), thickness);
		line(frame, Point(0, 400), Point(800, 400), Scalar(255, 0, 0), thickness);
		world.draw(frame);
		ball1.draw(frame);
		robo.draw(frame);
		circle(frame, Point(0, 0), 100, Scalar(0, 255, 255), FILLED);
		imshow("Game world", frame);
		deltaTime = clock() - f;
		f = clock();
		printf("It took me (%f seconds).\n", ((float)deltaTime) / CLOCKS_PER_SEC);
		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}