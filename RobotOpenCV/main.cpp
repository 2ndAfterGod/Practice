#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "windowParam.h"
#include "Box.h"
#include "Robot.h"
#include "Ball.h"
#include "Counter.h"
#include "ViewFrame.h"
using namespace std;
using namespace cv;

//	first one if for waitkey, second one is ESC key
const int DELAY = 10, ESC_KEY = 27;

void printUsage();

int main()
{
	
	printUsage();

	srand(time(NULL));		//	for new ball trajectory

	int key;		//	keyboard key
	float timeBuffer = 0;		//	for time magic
	clock_t deltaTime = 0;		//	also for time magic

	Robot robot;
	Ball ball;
	Box world;
	Counter hitsCounter("HITS");		//	message with hits counter
	ViewFrame papaFrame(WINDOW_WIDTH, WINDOW_HEIGHT, "World model");

	//	master window matrix
	
	
	//	main cycle
	while (true)
	{
		//	check for key pressing
		key = waitKey(DELAY);
		if (key == ESC_KEY)
			break;

		//	area
		papaFrame.update();
		robot.updateCam();

		//	action
		robot.move(deltaTime, key);
		ball.move(deltaTime, robot);

		//	check for collision
		if (ball.didHit()) {
			hitsCounter++;
		}

		//	drawing current world state
		world.draw(papaFrame.getFrame());
		ball.draw(papaFrame.getFrame(), robot.getCamFrame());
		if (!ball.isAlive()) {
			ball.regenerate();
		}
		robot.draw(papaFrame.getFrame());
		hitsCounter.draw(papaFrame.getFrame());

		//	show current world state
		robot.showCam();
		papaFrame.show();

		//	time magic
		deltaTime = clock() - timeBuffer;
		timeBuffer = clock();
	}
	return 0;
}

void printUsage() {
	cout << "::WORLD::MODEL::" << endl;
	cout << endl;
	cout << "Controls:" << endl;
	cout << "[A] - move left" << endl;
	cout << "[D] - move right" << endl;
	cout << "[Esc] - exit" << endl;
}