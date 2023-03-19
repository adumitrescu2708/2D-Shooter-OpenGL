#include "animations.h"

#include <cstdlib>
#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"
#include "lab_m1/tema1/transform2D.h"
#include <iostream>


/*
	NAME:	Dumitrescu Alexandra
	GROUP:	333CA
*/

void animations::MoveDuck(duck::Duck *duck, float deltaTimeSeconds,
		float logicX, float logicY,
		glm::mat3* visMatrix)
{
	duck->timeSpent += deltaTimeSeconds;
	float movementUnit = duck->speed * deltaTimeSeconds;

	switch (duck->status)
	{
	case duck::movement::MOVE:
		/* Check if duck escapes, time spent is over */
		if (duck->timeSpent > duck->maximumTime
			|| duck->bullets == 0) {
			duck->status = duck::movement::ESCAPED;
		}

		/* Treat collisions and compute reflexion angles */
		if (duck->positionX > logicX - 2) {
			duck->directionAngle = 3.14 - duck->directionAngle;
			duck->positionX = logicX - 2;
		}
		else if (duck->positionY > logicY - 2) {
			duck->directionAngle = -duck->directionAngle;
			duck->positionY = logicY - 2;
		}
		else if (duck->positionX < 2) {
			duck->directionAngle = 3.14 - duck->directionAngle;
			duck->positionX = 2;
		}
		else if (duck->positionY < 2) {
			duck->directionAngle = -duck->directionAngle;
			duck->positionY = 2;
		}
		else {
			/* Normal ahead moving */
			duck->positionX += movementUnit * cos(duck->directionAngle);
			duck->positionY += movementUnit * sin(duck->directionAngle);
		}
		break;

	case duck::movement::SHOT:
		/* If duck is shot, move faster downwards and respawn it */
		movementUnit *= 2;
		duck->directionAngle = -1.57;
		duck->positionX += movementUnit * cos(duck->directionAngle);
		duck->positionY += movementUnit * sin(duck->directionAngle);
		if (duck->positionX < -10
			|| duck->positionX > logicX + 10
			|| duck->positionY < -10
			|| duck->positionY > logicY + 10)
		{
			duck->Respawn();
		}
		break;

	case duck::movement::ESCAPED:
			/* If duck escapes move faster upwards and respawn it */
			movementUnit *= 2;
			duck->directionAngle = 1.57;
			duck->positionX += movementUnit * cos(duck->directionAngle);
			duck->positionY += movementUnit * sin(duck->directionAngle);
			if (duck->positionX < -10
				|| duck->positionX > logicX + 10
				|| duck->positionY < -10
				|| duck->positionY > logicY + 10)
			{
				duck->Respawn();
			}
			break;

		default:
			break;
	}

	/*Apply corresponding transformations */
	*visMatrix *= transform2D::Translate(duck->positionX, duck->positionY);
	*visMatrix *= transform2D::Translate(0, 0);
	*visMatrix *= transform2D::Rotate(duck->directionAngle);
}




void animations::GenerateEntryDirection(float& directionAngle, float& positionX, float& positionY)
{
	directionAngle = 0;
	while (!(directionAngle >= 100 && directionAngle <= 157)) {
		directionAngle = rand() % 157;
	}
	directionAngle /= 100;

	positionX = 0;
	positionY = 0;
}