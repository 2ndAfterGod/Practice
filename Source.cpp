#include <opencv2/opencv.hpp>
#include <stdio.h>
using namespace std;
using namespace cv;



struct color
{
	double blue, green, red, other;
};

class ball
{
private:

	int x = 400, y = 400, rad = 20;
	int b = 0, g = 255, r = 255;
public:

	void draw(Mat frame) 
	{
		circle(frame, Point(x, y), rad, Scalar(b,g,r), FILLED);
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
		for(x = 400; x<=700; x++)
		line(frame, Point(x-50, y), Point(x+50, y), Scalar(255, 255, 255), 30); 

	}
	
};

int main() 
{
	
	ball ball1;
	box world;
	robot robo;
	VideoCapture cap(0);
	int thickness = 2;
	Mat frame = Mat::zeros(800, 800, CV_8UC3);
	line(frame, Point(400, 0), Point(400, 800), Scalar(255, 0, 0), thickness);
	line(frame, Point(0, 400), Point(800, 400), Scalar(255, 0, 0), thickness);
	world.draw(frame);
	ball1.draw(frame);
	robo.draw(frame);
	imshow("Game world", frame);
	waitKey(0);
	return 0;
}