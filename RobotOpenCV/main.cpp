#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;
using namespace cv;

const int WIDTH = 1280, HEIGHT = 720;

const int BALL_SIZE = 10;
const float BALL_SPEED = 0.02;

const int ROBO_WIDTH = 120, ROBO_HEIGHT = 40;

const float PI = 3.14;

class Robot
{
private:
	int x = WIDTH / 2, y = HEIGHT - HEIGHT / 20;
	int width = ROBO_WIDTH, height = ROBO_HEIGHT;

public:
	void draw(Mat frame)
	{
		line(frame, Point(x - width / 2, y), Point(x + width / 2, y), Scalar(192, 15, 255), height);

	}

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}

	int getWidth() {
		return width;
	}

	int getHeight() {
		return height;
	}
};

class Ball
{
private:
	bool hit = false;
	int x = WIDTH/2, y = HEIGHT/2, rad = BALL_SIZE;
	int b, g, r;
	float speed = BALL_SPEED;
	float shift = 0, angle;

public:

	Ball() {
		b = rand() % 256;
		g = rand() % 256;
		r = rand() % 256;
		angle = (rand() % 360) * PI / 180;
	}

	void draw(Mat frame)
	{
		circle(frame, Point(x, y), rad, Scalar(b, g, r), FILLED);
	}

	void move(clock_t deltaTime, Robot bot)
	{
		int dy, dx;
		hit = false;

		shift += speed * deltaTime;
		dx = shift * cos(angle);
		dy = shift * sin(angle);

		if (x + dx >= WIDTH || x + dx <= 0) {
			angle = PI - angle;
			dx = shift * cos(angle);
			dy = shift * sin(angle);
		}

		if (y + dy <= 0) {
			angle = 2 * PI - angle;
			dx = shift * cos(angle);
			dy = shift * sin(angle);
		}

		if ((x + dx) >= (bot.getX() - bot.getWidth()) && (x + dx) <= (bot.getX() + bot.getWidth()) &&
			(y + dy) >= (bot.getY() - bot.getHeight()/2)/* && (y + dy) <= (bot.getY() + bot.getHeight()/2)*/) {
			angle = 2 * PI - angle;
			dx = shift * cos(angle);
			dy = shift * sin(angle);
			hit = true;
		}

		x += dx;
		y += dy;
	}

	bool isAlive() {
		if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT) {
			return false;
		}
		return true;
	}

	void regenerate() {
		Ball newBall;
		*this = newBall;
	}

	bool didHit() {
		return hit;
	}
};

class Box
{
private:
	int thickness = 10;

public:
	void draw(Mat frame)
	{
		//	coordinate lines
		line(frame, Point(WIDTH / 2, 0), Point(WIDTH / 2, HEIGHT), Scalar(255, 0, 0), thickness/5);
		line(frame, Point(0, HEIGHT / 2), Point(WIDTH, HEIGHT / 2), Scalar(255, 0, 0), thickness/5);

		//	walls
		line(frame, Point(0, HEIGHT), Point(WIDTH, HEIGHT), Scalar(0, 0, 255), thickness);
		line(frame, Point(0, 0), Point(0, WIDTH), Scalar(100, 100, 100), thickness);
		line(frame, Point(WIDTH, 0), Point(0, 0), Scalar(100, 100, 100), thickness);
		line(frame, Point(WIDTH, 0), Point(WIDTH, HEIGHT), Scalar(100, 100, 100), thickness);

	}
};

class Counter {
private:
	int counter = 0, font = FONT_HERSHEY_COMPLEX;
	double fontScale = 2;
	string countMes;
	string countVal;
	Point mesLoc;
	Point hitsLoc;
	Scalar textColor;
public:
	Counter(const char* name) {
		countMes = name;
		countMes += ": ";
		countVal = to_string(counter);
		mesLoc = Point(10, 50);
		hitsLoc = Point(200, 50);
		textColor = Scalar(250, 250, 250);
	}

	void draw(Mat frame) {
		putText(frame, countMes, mesLoc, font, fontScale, textColor);
		putText(frame, countVal, hitsLoc, font, fontScale, textColor);
	}

	void operator++(int) {
		counter++;
		countVal = to_string(counter);
	}
};

int main()
{
	srand(time(NULL));

	float f = 0;
	clock_t deltaTime = 0;

	Robot robot;
	Ball ball;
	Box world;
	Counter hitsCounter("HITS");

	Mat frame = Mat::zeros(HEIGHT, WIDTH, CV_8UC3);

	while (true)
	{
		frame = Mat::zeros(HEIGHT, WIDTH, CV_8UC3);

		world.draw(frame);

		ball.move(deltaTime, robot);
		if (ball.didHit()) {
			hitsCounter++;
		}
		ball.draw(frame);
		if (!ball.isAlive()) {
			ball.regenerate();
		}

		robot.draw(frame);
		hitsCounter.draw(frame);

		imshow("World model", frame);
		deltaTime = clock() - f;
		f = clock();

		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}