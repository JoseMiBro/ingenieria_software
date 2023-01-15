#include "TextureManager.h"

TextureManager::TextureManager()
{}

TextureManager::~TextureManager(){}

void TextureManager::Init()
{
	LoadFont();
	LoadBackGround("data/circle-bkg-128.png");
	LoadBall("data/tyrian_ball.png");
}

void TextureManager::Terminate()
{
  CORE_UnloadPNG(texbkg);
  CORE_UnloadPNG(texsmallball);
  FONT_End();
}

void TextureManager::LoadBackGround(const char* filePath)
{
  texbkg = CORE_LoadPNG(filePath, true);
}

void TextureManager::LoadBall(const char* filePath)
{
  texsmallball = CORE_LoadPNG(filePath, false);
}

void TextureManager::LoadFont()
{
	FONT_Init();	// Characters and symbols inicialization to draw on screen.
}

GLuint& TextureManager::GetBackgroundTexture()
{
  return texbkg;
}

GLuint& TextureManager::GetBallTexture()
{
  return texsmallball;
}