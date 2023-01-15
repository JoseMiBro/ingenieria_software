#include "EntityManager.h"

EntityManager::EntityManager(unsigned int num_balls, float max_ball_spped)
  : NUM_BALLS(num_balls),
    MAX_BALL_SPEED(max_ball_spped)
{
  balls = vector<Ball*>(num_balls,nullptr);
}

EntityManager::~EntityManager(){}

void EntityManager::Init(TextureManager& txtMan)
{
	CreateBalls(txtMan.GetBallTexture());
}

void EntityManager::Terminate()
{
	for (unsigned int i = NUM_BALLS - 1; i > 0; i--)
	{
		delete balls[i];
	}
}

void EntityManager::CreateBalls(GLuint& ballTexture)
{
  for (int i = 0; i < NUM_BALLS; i++) {
    balls[i] = new Ball();
    balls[i]->pos = vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT));
    balls[i]->vel = vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED));
    balls[i]->radius = 16.f;
    balls[i]->gfx = ballTexture;
  }
}

void EntityManager::Update(float deltaTime)
{
	// Run balls
	for (int i = 0; i < NUM_BALLS; i++) 
	{
		// New Pos.
		bool collision = false;
		int colliding_ball = -1;
		vec2 newpos = balls[i]->pos + balls[i]->vel * deltaTime;

		// Collision detection.
		for (int j = 0; j < NUM_BALLS; j++) 
		{
			if (i != j) 
			{
				float iBallRadius = balls[i]->radius;
				float jBallRadius = balls[j]->radius;

				float limit = iBallRadius + jBallRadius;
				float limit2 = limit * limit;

				if (vlen2(newpos - balls[j]->pos) <= limit2) 
				{
					collision = true;
					colliding_ball = j;
					break;
				}
			}
		}

		if (collision) 
		{
			// Rebound!
			Bounce(*balls[i], *balls[colliding_ball]);
		}
		else 
		{
			balls[i]->pos = newpos;
		}

		// Rebound on margins.
		CheckMargins(*balls[i]);
	}
}

void EntityManager::Bounce(Ball& ball, Ball& colliding_ball)
{
	ball.vel *= -1.f;
	colliding_ball.vel *= -1.f;
}

void EntityManager::CheckMargins(Ball& ball)
{
	if ((ball.pos.x > SCR_WIDTH) || (ball.pos.x < 0)) {
		ball.vel.x *= -1.0;
	}
	if ((ball.pos.y > SCR_HEIGHT) || (ball.pos.y < 0)) {
		ball.vel.y *= -1.0;
	}
}
