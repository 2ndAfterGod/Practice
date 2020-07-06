#include "Ball.h"

Ball::Ball()
{
	int angleDeg = rand() % 360;		//	set angle in degrees

	//	stuped check for stuped angle
	if (angleDeg < 20 || (angleDeg > 180 && angleDeg < 200))
		angleDeg += 80;
	if (angleDeg > 340 || (angleDeg > 160 && angleDeg <= 180))
		angleDeg -= 80;

	angle = angleDeg * PI / 180;		//	transform to angle in radians

	//	set color
	b = rand() % 256;
	g = rand() % 256;
	r = rand() % 256;
}

void Ball::draw(cv::Mat frame, cv::Mat frame2)
{
	//	yeah, ball is a circle - MISS (Make It Simply Stuped pattern)
	cv::circle(frame, cv::Point(x, y), rad, cv::Scalar(b, g, r), cv::FILLED);
	cv::circle(frame2, cv::Point(x, CAMERA_HEIGHT / 2), (int)(rad + deltaRad), cv::Scalar(b, g, r), cv::FILLED);
}

void Ball::move(clock_t deltaTime, Robot bot)
{
	int dy, dx;		//	shift projections
	hit = false;	//	ball did not hit robot yet
	float koefMovementY = WINDOW_HEIGHT * 0.0002;
	//	pre-calculating ball move
	shift = speed * deltaTime;
	dx = shift * cos(angle);
	dy = shift * sin(angle);

	//	bounces from vertical walls
	if (x + dx >= WINDOW_WIDTH || x + dx <= 0) {
		angle = PI - angle;
		dx = shift * cos(angle);
		dy = shift * sin(angle);
	}

	//	bounce from top wall
	if (y + dy <= 0) {
		angle = 2 * PI - angle;
		dx = shift * cos(angle);
		dy = shift * sin(angle);
	}

	//	bounce from robot
	if ((x + dx) >= (bot.getX() - bot.getWidth()) && (x + dx) <= (bot.getX() + bot.getWidth()) &&
		(y + dy) >= (bot.getY() - bot.getHeight() / 2) && (y + dy) <= (bot.getY() + bot.getHeight() / 2)) {
		angle = 2 * PI - angle;
		dx = shift * cos(angle);
		dy = shift * sin(angle);
		hit = true;
	}

	deltaRad = y * koefMovementY;
	//	move
	x += dx;
	y += dy;
}

bool Ball::isAlive()
{
	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) {
		return false;
	}
	return true;
}

void Ball::regenerate()
{
	Ball newBall;
	*this = newBall;
}