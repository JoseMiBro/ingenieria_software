#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
#include "EntityManager.h"
#include "TextureManager.h"
#include "Renderer.h"
#include "Clock.h"
#include <time.h>

//Esto es un cambio nuevo en la copia para generar un conflicto

struct GameInfo
{
	unsigned int num_balls = 10;
	float max_ball_speed = 8.f;
	float fpsTimer = (1.f / 60.f);
};

void GeneralInit(EntityManager& entMan, TextureManager& textureMan, Renderer& renderer)
{
	// Load textures
	textureMan.Init();
	// Init game state.
	entMan.Init(textureMan);
	// Set up rendering.
	renderer.Init();
}

void GeneralTerminate(EntityManager& entMan, TextureManager& textureMan, Renderer& renderer)
{
	renderer.Terminate();
	entMan.Terminate();
	textureMan.Terminate();
}

int Main(void)
{
	GameInfo gInfo = GameInfo();
	TextureManager textureMan = TextureManager();
	EntityManager entMan = EntityManager(gInfo.num_balls, gInfo.max_ball_speed);
	Renderer renderer = Renderer(textureMan, entMan);
	GeneralInit(entMan, textureMan, renderer);
	
	Clock timer;
	timer.StartCounter();

	double currentTime = timer.GetCounter();
	double previousTime = timer.GetCounter();
	double lastFrameTime = 0.f;
	double deltaTime = 0.f;
	double playTime = 0.f;
	double logicTime = 0.f;
	double tick = 0.f;
	double fps = 0.f;
	float multiplier = 1.f;
	float clamp = (1.f / 15.f);

	while (!SYS_GottaQuit()) // Controlling a request to terminate an application.
	{	
		//Get milisegundos
		currentTime = timer.GetCounter();
		
		// Cachear la operacion
		lastFrameTime = (currentTime - previousTime); // (counter.current  - counter previous) / frequency
		//Convertir de milisegundos a segundos
		lastFrameTime /= 1000.f;
		// Aplicar multiplicador de tiempo
		deltaTime += (lastFrameTime * multiplier);

		//Anyadir play time
		playTime += lastFrameTime;
		//Solo por claridad lógica
		tick = lastFrameTime;
		//Calcular fps
		fps = 1.f / (lastFrameTime);

		// Set up para el proximo deltaTime
		previousTime = currentTime;

		// Clampear
		if (deltaTime >= clamp)
			deltaTime = clamp;

		while (deltaTime >= gInfo.fpsTimer)
		{
			// Update
			entMan.Update(gInfo.fpsTimer);
			// Anyadir tiempo de logica
			logicTime += gInfo.fpsTimer;

			deltaTime = deltaTime - gInfo.fpsTimer;
			
			//SYS_Sleep(17);	// To force 60 fps
		}

		//Render
		renderer.Render(playTime, logicTime, fps, tick);
		SYS_Pump();	// Process Windows messages.

	}

	GeneralTerminate(entMan, textureMan, renderer);

	return 0;
}
