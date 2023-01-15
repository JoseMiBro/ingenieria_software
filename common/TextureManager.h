#pragma once
#include "stdafx.h"
#include "core.h"
#include "font.h"

class TextureManager
{
  private:
    GLuint texbkg;
    GLuint texsmallball;

    void LoadBackGround(const char* filePath);
    void LoadBall(const char* filePath);
    void LoadFont();
  
   public:
    TextureManager();
    ~TextureManager();
    
    void Init();
    void Terminate();
  
    GLuint& GetBackgroundTexture();
    GLuint& GetBallTexture();
};

