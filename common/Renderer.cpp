#include "Renderer.h"
#include <iomanip>

Renderer::Renderer(TextureManager& txtMan, EntityManager& entMan):
	txtMan(txtMan),
	entMan(entMan)
{}

Renderer::~Renderer(){}

void Renderer::Init()
{
	RenderSetUp();
}

void Renderer::Terminate(){}

void Renderer::RenderSetUp()
{
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Specifies clear values for the color buffers.
	glMatrixMode(GL_PROJECTION);	// Specifies projection matrix is the current matrix.
	glLoadIdentity();	// Replaces the current matrix with the identity matrix.
	glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);	// Multiplies the current matrix by an orthographic matrix.
	glEnable(GL_TEXTURE_2D);	// Enabling two-dimensional texturing.
	// NOTA: Mirar diferencias comentando las 2 siguientes funciones.
	glEnable(GL_BLEND);	// Blend the incoming RGBA color values with the values in the color buffers.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blend func. for alpha color.
}

void Renderer::Render(double playTime, double logicTime, double fps, double tick)
{

	glClear(GL_COLOR_BUFFER_BIT);	// Clear color buffer to preset values.

	//Render background
	RenderBackground();

	//Render balls
	RenderBalls();

	//Render Text
	RenderText(playTime, logicTime, fps, tick);

	SYS_Show();
}

void Renderer::RenderTexture(vec2 pos, vec2 size, GLuint texId)
{
	CORE_RenderCenteredSprite(pos,size, texId);
}

void Renderer::RenderBackground()
{
	for (int i = 0; i <= SCR_WIDTH / 128; i++) {
		for (int j = 0; j <= SCR_HEIGHT / 128; j++) {
			RenderTexture(
				vec2(i * 128.f + 64.f, j * 128.f + 64.f),
				vec2(128.f, 128.f),
				txtMan.GetBackgroundTexture()
			);
		}
	}
}

void Renderer::RenderBalls()
{
	for (int i = 0; i < entMan.NUM_BALLS; i++) {

		Ball* auxBall = entMan.balls[i];

		RenderTexture(
			auxBall->pos,
			vec2(auxBall->radius * 2.f, auxBall->radius * 2.f),
			auxBall->gfx
		);
	}
}

void Renderer::RenderText(double playTime, double logicTime, double fps, double tick)
{
	char buffer[100];

	FONT_DrawString(vec2(SCR_WIDTH / 2 - 19 * 16, SCR_HEIGHT - 48), "FPS: ");
	sprintf(buffer, "%f", fps);
	FONT_DrawString(vec2(SCR_WIDTH / 2 - 14 * 16, SCR_HEIGHT - 48), buffer);

	// Exchanges the front and back buffers
	FONT_DrawString(vec2(SCR_WIDTH / 2 - 19 * 16, 80), "TOTAL TIME: ");
	sprintf(buffer, "%f", playTime);
	FONT_DrawString(vec2(SCR_WIDTH / 2 - 2 * 16, 80), buffer);
	FONT_DrawString(vec2(SCR_WIDTH / 2 + 9 * 16, 80), "SECONDS");

	FONT_DrawString(vec2(SCR_WIDTH / 2 - 19 * 16, 48), "TOTAL LOGIC TIME: ");
	sprintf(buffer, "%f", logicTime);
	FONT_DrawString(vec2(SCR_WIDTH / 2 - 2 * 16, 48), buffer);
	FONT_DrawString(vec2(SCR_WIDTH / 2 + 9 * 16, 48), "SECONDS");

	FONT_DrawString(vec2(SCR_WIDTH / 2 - 19 * 16, 16), "TIME TICK: ");
	sprintf(buffer, "%f", tick * 1000.f);
	FONT_DrawString(vec2(SCR_WIDTH / 2 - 9 * 16, 16), buffer);
	FONT_DrawString(vec2(SCR_WIDTH / 2 + 1 * 16, 16), "MILISECONDS");
}