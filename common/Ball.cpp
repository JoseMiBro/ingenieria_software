#include "Ball.h"

Ball::Ball() 
	: pos(0.0f),
	vel(0.0f),
	gfx(0),
	radius(0.0f)
{}

Ball::Ball(float pos = 0.f, float vel = 0.f, int gfx = 0, float radius = 0.f)
	: pos(pos),
		vel(vel),
		gfx(gfx),
		radius(radius)
{}

Ball::~Ball()
{

}