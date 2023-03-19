#pragma once
#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include <vector>

/*
	NAME:	Dumitrescu Alexandra
	GROUP:	333CA
*/
namespace duck
{
	enum class movement {
		ESCAPED,
		SHOT,
		MOVE
	};

	struct Frame {
		int coordinates[4][2];
	};

	class Duck
	{
		public:
			Duck();
			~Duck();

			void Init(float speed);
			void Respawn();
			void Shoot(float positionX, float positionY);
			void ComputeShootingFrame();
			
			int duckIndex;
			float initialSpeed;

			float positionX, positionY;
			float directionAngle;
			float speed;
			float maximumTime;
			int bullets;
			int lives;
			int score;
			float timeSpent;

			int killingSpree;
			bool killingSpreeActivated;

			float lenght, width;

			movement status;
			Frame frame;

	};
}
