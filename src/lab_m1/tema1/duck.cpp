#include "duck.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"
#include <iostream>

using namespace duck;
/*
	NAME:	Dumitrescu Alexandra
	GROUP:	333CA
*/


Duck::Duck()
{
}
Duck::~Duck()
{
}

void Duck::Init(float speed) {
	/* Random generating position on OX starting from upper field, 0 position on OY */
	positionX = rand() % 100;
	positionY = 0;

	/* Random generating direction angle while avoiding 90 degrees aprox values */
	directionAngle = 0;
	while (!(directionAngle >= 120 && directionAngle <= 280 && !(directionAngle <= 165 && directionAngle >= 145))) {
		directionAngle = rand() % 314;
	}
	directionAngle /= 100;

	/* Re initializing starting values for time, bullets and speed */
	timeSpent = 0;
	bullets = 3;
	status = movement::MOVE;
	maximumTime = 30;
	this->speed = speed;
}

void Duck::Respawn()
{
	/* Respawning a duck if it was shot or if its time is over */
	if (status != movement::SHOT) {
		lives--;
	}
	duckIndex++;
	bullets = 3;
	if (duckIndex % 5 == 0 && duckIndex != 0) {
		speed = speed + (duckIndex / 5) * initialSpeed / 5;
	}
	Init(speed);
}


void Duck::ComputeShootingFrame()
{
	/* Based on the aprox dimensions of a duck and on its position and direction compute the shooting rectangle frame */
	frame.coordinates[0][0] = positionX;
	frame.coordinates[0][1] = positionY;

	frame.coordinates[1][0] = positionX + lenght * cos(directionAngle);
	frame.coordinates[1][1] = positionY + lenght * sin(directionAngle);

	frame.coordinates[2][0] = positionX + width * cos(1.57 + directionAngle);
	frame.coordinates[2][1] = positionY + width * sin(1.57 + directionAngle);

	frame.coordinates[3][0] = frame.coordinates[2][0] + lenght * cos(directionAngle);
	frame.coordinates[3][1] = frame.coordinates[2][1] + lenght * sin(directionAngle);

}

void Duck::Shoot(float posX, float posY)
{

	if (status != movement::SHOT)
	{
		bullets--;

		if (bullets == 0) {
			lives--;
			status = movement::ESCAPED;
		}
		/* Compute rectangle frame based on position and direction */
		ComputeShootingFrame();

		/* Based on the rectangle frame compute another frame */
		float minimumPositionX = std::min(frame.coordinates[0][0], std::min(frame.coordinates[1][0], std::min(frame.coordinates[2][0], frame.coordinates[3][0])));
		float minimumPositionY = std::min(frame.coordinates[0][1], std::min(frame.coordinates[1][1], std::min(frame.coordinates[2][1], frame.coordinates[3][1])));
		float maximumPositionX = std::max(frame.coordinates[0][0], std::max(frame.coordinates[1][0], std::max(frame.coordinates[2][0], frame.coordinates[3][0])));
		float maximumPositionY = std::max(frame.coordinates[0][1], std::max(frame.coordinates[1][1], std::max(frame.coordinates[2][1], frame.coordinates[3][1])));

		/* Decide whether the duck was shot or not */
		if (posX <= maximumPositionX && posX >= minimumPositionX && posY <= maximumPositionY && posY >= minimumPositionY) {
			status = movement::SHOT;

			/* Hit duck, treat killing Spree bonus */
			if (bullets == 2) {
				killingSpree++;
			}
			else {
				killingSpree = 0;
				killingSpreeActivated = false;
			}
			if (killingSpree % 5 == 0 && killingSpree > 0) {
				killingSpreeActivated = true;
			}
			if (killingSpreeActivated == true) {
				score = score + 2;
			}
			else {
				score++;
			}

		}
		else {
			/* Missed duck */
			killingSpree = 0;
			killingSpreeActivated = false;
		}
		if (bullets == 0) {
			status = movement::ESCAPED;
		}
	}



}