#include "Counter.h"

Counter::Counter(const char* name) {
	countMes = name;
	countMes += ": ";

	countVal = std::to_string(counter);

	mesLoc = cv::Point(10, 50);
	countLoc = cv::Point(200, 50);

	textColor = cv::Scalar(250, 250, 250);
}

void Counter::draw(cv::Mat frame) {
	putText(frame, countMes, mesLoc, font, fontScale, textColor);
	putText(frame, countVal, countLoc, font, fontScale, textColor);
}

void Counter::operator++(int) {
	counter++;
	countVal = std::to_string(counter);
}