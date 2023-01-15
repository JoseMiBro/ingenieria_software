#pragma once
#include "vector2d.h"
#include "stdafx.h"

////Esto otro cambio para el Commit 2

class Ball
{
	public:
		
		Ball();
		Ball(float pos, float vel, int gfx, float radius);
		~Ball();
		// Info Ball
		vec2   pos;	// Position.
		vec2   vel;	// Velocity.
		GLuint gfx;	// OpenGL for id. for visualization purposes. 
		float  radius;	// Radius.
};

