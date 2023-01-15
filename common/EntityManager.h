#pragma once
#include "stdafx.h"
#include "sys.h"
#include "core.h"

#include "Ball.h"
#include <vector>
#include "TextureManager.h"
using namespace std;

class EntityManager
{
    public:
    
        EntityManager(unsigned int num_balls, float max_ball_spped);
        ~EntityManager();
        

        void Init(TextureManager& txtMan);
        void Terminate();

        
        void Update(float deltaTime);
    
        // Logic Info.
        const unsigned int NUM_BALLS = 10;	// Max. num balls.
        const float MAX_BALL_SPEED = 8.f;	// Max vel. of ball. (pixels/?).
        vector<Ball*> balls;	// Array of balls.

    private:
        void CreateBalls(GLuint& ballTexture);

        void Bounce(Ball& ball1, Ball& ball2);
        void CheckMargins(Ball& ball);
};

